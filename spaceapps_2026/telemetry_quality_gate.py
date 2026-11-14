#!/usr/bin/env python3
"""Offline, dependency-free CSV telemetry quality gate for synthetic ECLSS research.

This tool checks structural integrity and reproducibility, not medical or flight safety.
It does not upload data or require network access.
"""
import argparse
import csv
import hashlib
import json
import math
from pathlib import Path


def validate(path):
    source = Path(path)
    raw = source.read_bytes()
    issues = []
    rows = 0
    fields = []
    with source.open("r", encoding="utf-8-sig", newline="") as stream:
        reader = csv.DictReader(stream, restval=None, restkey=None, dialect="excel", strict=True)
        fields = reader.fieldnames or []
        if not fields:
            issues.append("missing_header")
        if len(fields) != len(set(fields)):
            issues.append("duplicate_columns")
        if any(not name or not name.strip() for name in fields):
            issues.append("blank_column_name")
        for line, record in enumerate(reader, start=2):
            rows += 1
            if None in record or any(value is None for value in record.values()):
                issues.append(f"line_{line}:column_count_mismatch")
            for key, value in record.items():
                if key is None or value is None:
                    continue
                stripped = value.strip()
                if stripped.lower() in {"nan", "+nan", "-nan", "inf", "+inf", "-inf", "infinity", "+infinity", "-infinity"}:
                    issues.append(f"line_{line}:{key}:nonfinite_literal")
                elif stripped and _looks_numeric(stripped):
                    try:
                        if not math.isfinite(float(stripped)):
                            issues.append(f"line_{line}:{key}:nonfinite_number")
                    except (ValueError, OverflowError):
                        pass
    if rows == 0:
        issues.append("no_data_rows")
    return {
        "schema_version": "1.0",
        "purpose": "synthetic_telemetry_quality_only",
        "input_file": source.name,
        "sha256": hashlib.sha256(raw).hexdigest(),
        "row_count": rows,
        "columns": fields,
        "passed": not issues,
        "issues": issues,
        "disclaimer": "Not a flight, clinical, or human-safety validation."
    }


def _looks_numeric(value):
    return value[0] in "+-.0123456789"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("csv_file", type=Path)
    parser.add_argument("--output", type=Path, help="Optional local JSON report path")
    args = parser.parse_args()
    try:
        result = validate(args.csv_file)
    except (OSError, UnicodeError, csv.Error) as exc:
        result = {"schema_version": "1.0", "passed": False, "issues": [f"read_error:{type(exc).__name__}"]}
    report = json.dumps(result, ensure_ascii=False, indent=2, sort_keys=True)
    if args.output:
        args.output.write_text(report + "\n", encoding="utf-8")
    else:
        print(report)
    return 0 if result["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
