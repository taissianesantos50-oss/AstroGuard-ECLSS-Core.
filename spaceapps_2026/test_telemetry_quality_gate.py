"""Standard-library tests for the offline synthetic telemetry gate."""
import tempfile
import unittest
from pathlib import Path
from telemetry_quality_gate import validate


class TelemetryGateTests(unittest.TestCase):
    def check(self, csv_text):
        with tempfile.TemporaryDirectory() as folder:
            file = Path(folder) / "synthetic.csv"
            file.write_text(csv_text, encoding="utf-8")
            return validate(file)

    def test_valid_synthetic_rows(self):
        result = self.check("time,oxygen\n0,20.9\n1,20.8\n")
        self.assertTrue(result["passed"])
        self.assertEqual(result["row_count"], 2)
        self.assertEqual(len(result["sha256"]), 64)

    def test_nonfinite(self):
        result = self.check("time,oxygen\n0,NaN\n")
        self.assertFalse(result["passed"])
        self.assertTrue(any("nonfinite" in issue for issue in result["issues"]))

    def test_infinite_numeric_value(self):
        self.assertFalse(self.check("time,oxygen\n0,1e999\n")["passed"])

    def test_extra_column(self):
        self.assertFalse(self.check("a,b\n1,2,3\n")["passed"])

    def test_blank_header(self):
        self.assertFalse(self.check("a,\n1,2\n")["passed"])

    def test_ragged_row(self):
        self.assertFalse(self.check("a,b\n1\n")["passed"])

    def test_empty_data(self):
        self.assertFalse(self.check("a,b\n")["passed"])

    def test_duplicate_header(self):
        self.assertFalse(self.check("a,a\n1,2\n")["passed"])


if __name__ == "__main__":
    unittest.main()
