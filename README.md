# AstroGuard-ECLSS-Core

**Developer:** Taissiane Thais dos Santos  
**Classification:** Private / Proprietary Research & Simulation Prototype

## Access and intellectual property

**PRIVATE / PROPRIETARY PROJECT — ALL RIGHTS RESERVED**

Copyright (c) 2026 Taissiane Thais dos Santos. All rights reserved.

Access to this repository does **not** grant permission to use, copy, reproduce, modify, distribute, publish, sublicense, commercialize, or create derivative works from the source code, documentation, designs, data, or other project materials.

Any use, modification, redistribution, collaboration, evaluation beyond the access expressly granted, or other exploitation requires the **prior express written authorization of Taissiane Thais dos Santos**.

See the `LICENSE` file for the complete proprietary terms.

> Research / simulation prototype. Synthetic telemetry. Not a medical device and not flight-qualified software.

## v1.8 — Final Technical Package

AstroGuard is a research and simulation prototype for long-duration space missions. The project combines environmental ECLSS simulation with deterministic human-health monitoring, telemetry storage, 3D mission visualization and a browser-based mission dashboard.

### Architecture

Environment telemetry  
→ Human physiological telemetry  
→ Health Monitoring  
→ Decision Engine  
→ NORMAL / ATTENTION / CRITICAL  
→ Telemetry & Storage  
→ 3D mission visualization / Web dashboard

### Implemented

- Environmental simulation: O2, pressure, temperature and actuator states.
- Human telemetry simulation: heart rate, SpO2, body temperature, respiratory rate, fatigue and well-being.
- Deterministic health states: NORMAL, ATTENTION and CRITICAL.
- Integrated verification scenario that exercises all three states.
- Combined mission telemetry CSV.
- Unit and robustness tests.
- Automated GitHub Actions CI.
- 3D mission visualization.
- Web mission dashboard.
- v1.8 architecture, technical documentation, audit, presentation and submission checklist.

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

All physiological values, scenario transitions and decision thresholds are synthetic demonstration parameters. They are not medical measurements, clinical thresholds, Artemis mission measurements, or flight-qualified safety logic.

This repository does not claim medical diagnosis, clinical validation, medical-device status, operational spacecraft certification, real astronaut telemetry, or NASA/Artemis validation.

### v1.5 — 3D mission visualization

Install and run:

    python -m pip install -r requirements-v1.5.txt
    python src/astroguard_v1_5.py

The visualization is research/demo software. Derived stress indices are not medical scores and are not flight-qualified decision logic.

See:

- `docs/v1.5_3d_mission_visualization.md`
- `docs/v1.5_architecture.md`
- `src/astroguard_v1_5.py`

### v1.6 — Web mission dashboard

Open locally:

    dashboard/index.html

The demonstration telemetry is embedded in `dashboard/app.js`, so the interface can be opened directly in a modern browser.

See:

- `dashboard/index.html`
- `dashboard/styles.css`
- `dashboard/app.js`
- `docs/v1.6_web_dashboard.md`

### v1.7 — Demonstration video package

The repository contains the storyboard, capture checklist and final production script for the demonstration video.

See:

- `docs/v1.7_demonstration_video.md`
- `docs/v1.7_video_storyboard.md`
- `docs/v1.7_video_capture_checklist.md`
- `docs/v1.7_final_video_production_script.md`

### v1.8 — Documentation, architecture and presentation

See:

- `docs/v1.8_final_technical_documentation.md`
- `docs/v1.8_architecture_diagram.md`
- `docs/v1.8_architecture_diagram.svg`
- `docs/v1.8_presentation_outline.md`
- `docs/v1.8_presentation.md`
- `docs/v1.8_final_audit_report.md`
- `docs/v1.8_submission_checklist.md`
- `docs/v1.8_final_submission_manifest.md`
- `.github/workflows/astroguard-ci.yml`

### Roadmap

- v1.4 — Human Health Monitoring Layer
- v1.5 — 3D mission visualization
- v1.6 — Web dashboard
- v1.7 — Demonstration video specification
- v1.8 — Final technical documentation, architecture and presentation
- Next — Actual demonstration video and final submission evidence package
- Future — v1.9 Advanced Mission Health Analytics
