"""End-to-end CLI tests using only synthetic telemetry and the Python standard library."""
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

SCRIPT = Path(__file__).with_name("telemetry_quality_gate.py")


class TelemetryCLIIntegrationTests(unittest.TestCase):
    def invoke(self, text):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "synthetic.csv"
            report = root / "report.json"
            source.write_text(text, encoding="utf-8")
            completed = subprocess.run(
                [sys.executable, str(SCRIPT), str(source), "--output", str(report)],
                capture_output=True, text=True, timeout=10, check=False,
            )
            self.assertTrue(report.is_file(), completed.stderr)
            return completed, json.loads(report.read_text(encoding="utf-8"))

    def test_valid_csv_exits_success_and_writes_report(self):
        completed, report = self.invoke("time,oxygen\n0,20.9\n1,20.8\n")
        self.assertEqual(completed.returncode, 0, completed.stderr)
        self.assertTrue(report["passed"])
        self.assertEqual(report["row_count"], 2)

    def test_invalid_csv_exits_failure_and_writes_report(self):
        completed, report = self.invoke("time,oxygen\n0,NaN\n")
        self.assertEqual(completed.returncode, 1)
        self.assertFalse(report["passed"])
        self.assertTrue(report["issues"])

    def test_malformed_quoted_csv_fails_with_report(self):
        completed, report = self.invoke('time,oxygen\n0,"20.9\n')
        self.assertEqual(completed.returncode, 1)
        self.assertFalse(report["passed"])
        self.assertTrue(any("read_error" in issue for issue in report["issues"]))

    def test_same_input_produces_same_hash(self):
        _, first = self.invoke("time,oxygen\n0,20.9\n")
        _, second = self.invoke("time,oxygen\n0,20.9\n")
        self.assertEqual(first["sha256"], second["sha256"])


if __name__ == "__main__":
    unittest.main()
