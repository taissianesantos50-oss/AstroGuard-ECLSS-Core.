#!/usr/bin/env python3
"""Offline structural smoke check for the research dashboard (not a browser test)."""
from html.parser import HTMLParser
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
HTML = ROOT / "dashboard" / "index.html"
JS = ROOT / "dashboard" / "app.js"
CSS = ROOT / "dashboard" / "styles.css"

class Elements(HTMLParser):
    def __init__(self):
        super().__init__()
        self.ids = set()
        self.scripts = []
        self.stylesheets = []

    def handle_starttag(self, tag, attrs):
        a = dict(attrs)
        if "id" in a:
            if a["id"] in self.ids:
                raise ValueError("duplicate DOM id: " + a["id"])
            self.ids.add(a["id"])
        if tag == "script" and "src" in a:
            self.scripts.append(a["src"])
        if tag == "link" and a.get("rel") == "stylesheet":
            self.stylesheets.append(a.get("href"))

def main():
    for file in (HTML, JS, CSS):
        if not file.is_file() or not file.read_text(encoding="utf-8").strip():
            raise RuntimeError("missing or empty dashboard asset: " + file.name)
    p = Elements()
    p.feed(HTML.read_text(encoding="utf-8"))
    if "app.js" not in p.scripts or "styles.css" not in p.stylesheets:
        raise RuntimeError("dashboard asset references are incomplete")
    script = JS.read_text(encoding="utf-8")
    referenced = set(re.findall(r'getElementById\s*\(\s*["\']([^"\']+)["\']\s*\)', script))
    missing = referenced - p.ids
    if missing:
        raise RuntimeError("missing dashboard DOM targets: " + ", ".join(sorted(missing)))
    print("Dashboard structural smoke check passed; browser rendering remains unverified.")

if __name__ == "__main__":
    main()
