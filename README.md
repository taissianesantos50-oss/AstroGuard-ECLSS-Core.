# AstroGuard-ECLSS-Core

## v1.4 — Human Health Monitoring Layer

**Developer:** Taissiane Thais dos Santos  
**Repository:** AstroGuard-ECLSS-Core.  
**Version:** 1.4.0  
**Branch:** v1.4-human-health-monitoring

AstroGuard is a research and simulation prototype for long-duration space missions. Version 1.4 extends the environmental ECLSS layer with a deterministic human-health monitoring layer.

### Architecture

Environment telemetry
→ Human physiological telemetry
→ Decision engine
→ Health state
→ CSV telemetry
→ 3D mission visualization

### Implemented in v1.4

- Environmental simulation: O2, pressure, temperature and actuator states.
- Human telemetry simulation: heart rate, SpO2, body temperature, respiratory rate, fatigue and well-being.
- Deterministic health states: NORMAL, ATTENTION and CRITICAL.
- Integrated verification scenario that exercises all three states.
- Combined mission telemetry CSV.
- Unit and robustness tests.
- Technical evaluation report and telemetry protocol documentation.

### Build and run

Compile with strict warnings enabled:

    gcc -std=c11 -Wall -Wextra -Wpedantic src/health_monitor.c src/astroguard_v1_4.c -I src -o astroguard_v1_4

Run:

    ./astroguard_v1_4

The program generates `telemetry_v1_4.csv`.

### Test

    gcc -std=c11 -Wall -Wextra -Wpedantic src/health_monitor.c tests/test_health_monitor.c -I src -o test_health_monitor
    ./test_health_monitor

Expected result: exit code 0.

### Integrated verification scenario

The demonstration intentionally produces:

    NORMAL → ATTENTION → CRITICAL

This is a synthetic software-verification scenario designed to exercise the decision engine. It is not a clinical or operational mission scenario.

### Scientific and safety scope

All physiological values, scenario transitions and decision thresholds in this version are synthetic demonstration parameters. They are not medical measurements, clinical thresholds, Artemis mission measurements, or flight-qualified safety logic.

This repository does not claim medical diagnosis, clinical validation, or operational spacecraft certification.

### Authorship

**Taissiane Thais dos Santos** is the identified developer of this project.

### v1.5 — 3D mission visualization

The v1.5 visualization reads the v1.4 telemetry contract and renders an animated 3D mission telemetry trajectory. The visualization separates environmental stress from a human-stress representation and displays the current health state without changing the v1.4 decision engine.

Install and run:

    python -m pip install -r requirements-v1.5.txt
    python src/astroguard_v1_5.py

The visualization is research/demo software. Derived stress indices are not medical scores and are not flight-qualified decision logic.

See:

- `docs/v1.5_3d_mission_visualization.md`
- `docs/v1.5_architecture.md`
- `src/astroguard_v1_5.py`

### v1.6 — Web mission dashboard

v1.6 adds a browser-based mission interface built on the verified v1.4 telemetry scenario and v1.5 visualization concepts. It provides a live-style dashboard with health state, environmental telemetry, human telemetry, visualization-only stress indices, a time-series chart, actuator-state display and the current telemetry packet.

Open locally:

    dashboard/index.html

No build step is required. The demonstration telemetry is embedded in dashboard/app.js, so the interface can be opened directly in a modern browser.

See:

- dashboard/index.html
- dashboard/styles.css
- dashboard/app.js
- docs/v1.6_web_dashboard.md

The dashboard is explicitly a simulation/research prototype. It does not diagnose astronauts, replace clinical systems, or issue flight commands.

### Evaluation

See:

- `docs/v1.4_evaluation_report.md`
- `docs/telemetry_protocol_v1_4.md`
- `telemetry/sample_health_telemetry.csv`

### Roadmap

- v1.4 — Human Health Monitoring Layer
- v1.5 — 3D mission visualization
- v1.6 — Web dashboard
- v1.7 — Demonstration video
- v1.8 — Final documentation and presentation
