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
→ Future visualization

### Implemented in v1.4

- Environmental simulation: O2, pressure, temperature and actuator states.
- Human telemetry simulation: heart rate, SpO2, body temperature, respiratory rate, fatigue and well-being.
- Transparent health states: NORMAL, ATTENTION and CRITICAL.
- Combined mission telemetry CSV.
- Deterministic unit tests.
- Documentation of protocol and limitations.

### Run

Compile the v1.4 simulation:

    gcc src/health_monitor.c src/astroguard_v1_4.c -I src -o astroguard_v1_4

Run:

    ./astroguard_v1_4

The program generates telemetry_v1_4.csv.

### Test

    gcc src/health_monitor.c tests/test_health_monitor.c -I src -o test_health_monitor
    ./test_health_monitor

### Scientific and safety scope

All physiological values and decision thresholds in this version are synthetic demonstration parameters. They are not medical measurements, clinical thresholds, Artemis mission measurements, or flight-qualified safety logic.

This repository does not claim medical diagnosis, clinical validation, or operational spacecraft certification.

### Authorship

**Taissiane Thais dos Santos** is the identified developer of this project.

### Roadmap

- v1.4 — Human Health Monitoring Layer
- v1.5 — 3D mission visualization
- v1.6 — Web dashboard
- v1.7 — Demonstration video
- v1.8 — Final documentation and presentation
