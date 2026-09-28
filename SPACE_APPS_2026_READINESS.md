# AstroGuard ECLSS Core — NASA Space Apps Challenge 2026 Readiness

Developer: **Taissiane Thais dos Santos**

Development framing:

**RESEARCH & TECHNICAL PREPARATION → NASA SPACE APPS 2026 CHALLENGE IMPLEMENTATION**

Target challenge: **Create Health Monitoring Software for Astronauts on Space Missions**

Event dates: **November 14–15, 2026**

## 1. Purpose of this document

This document records the technical preparation of AstroGuard ECLSS Core before the 2026 hackathon implementation window and separates existing research/prototype capabilities from challenge-specific work to be implemented and demonstrated during the event.

The objective is transparent version history, reproducibility, and clear attribution of what existed during research/preparation versus what is accomplished during the hackathon.

## 2. Challenge alignment

The official challenge asks participants to build health-monitoring software that gathers health indicators and enables astronauts to evaluate and act on the status of their health during space missions.

### Existing AstroGuard research/prototype baseline

| Challenge area | Existing technical baseline | Evidence / component | Readiness |
|---|---|---|---|
| Health-monitoring software | Deterministic health-monitoring layer | `src/health_monitor.c`, `src/health_monitor.h` | Available |
| Physiological indicators | Synthetic HR, SpO2, body temperature, respiration, fatigue and wellbeing | v1.4/v1.9 telemetry | Available as synthetic simulation |
| Health-state evaluation | NORMAL / ATTENTION / CRITICAL | Health Monitor | Available |
| Temporal mission-health analysis | State counts, persistence and deterministic trend | `mission_health_analytics.c/.h` | Available |
| Mission/environment context | ECLSS/environmental + synthetic human telemetry | AstroGuard simulation | Available |
| Data persistence | CSV telemetry and analytics outputs | v1.9 pipeline | Available |
| User visualization | Mission dashboard and visualization layer | `dashboard/`, Python visualization | Available |
| Automated verification | Unit/integration tests and GitHub Actions | `.github/workflows/astroguard-ci.yml`, `tests/` | Available |
| Astronaut action support | Explicit, justified action/check workflow | Challenge-specific implementation | Gap / reserved for challenge work |
| Scientific traceability | Source-to-variable/rule rationale | Scientific evidence matrix | Needs strengthening |
| NASA/partner challenge resources | Traceable use of challenge-provided resources/open data | Challenge implementation | To be selected/documented |
| Final demonstration | Challenge-specific demo/video/project submission | Hackathon deliverable | Reserved for event |

## 3. Scientific preparation track

Before the event, research may document relevant evidence and assumptions for:

- heart rate;
- oxygen saturation (SpO2);
- respiratory rate;
- body temperature;
- fatigue and wellbeing constructs;
- environmental/ECLSS context;
- long-duration mission stressors described by the challenge;
- deterministic state-transition and persistence logic.

Every rule should be classified as one of:

1. **scientifically sourced parameter**;
2. **engineering assumption**;
3. **synthetic verification parameter**;
4. **future research item**.

This prevents synthetic demonstration thresholds from being presented as clinically validated limits.

## 4. Challenge implementation boundary

The official Space Apps site states that project submission opens November 14 and closes November 15, 2026, and encourages participants to submit what they accomplish over the course of the hackathon.

Accordingly, AstroGuard will preserve a visible distinction between technical preparation and challenge implementation.

A challenge-specific development branch should be created at the start of the hackathon. Challenge-specific implementation commits, integration work, final demo assets, and submission documentation should be traceable to that event branch/history.

## 5. Candidate challenge implementation goals

The following are candidates, not claims of completed challenge work:

- astronaut-facing decision-support workflow;
- explainable reason for each alert;
- recommended verification/action associated with a software state;
- integration of selected NASA/partner resources relevant to the challenge;
- challenge-specific mission scenario;
- challenge-specific dashboard interaction;
- final demonstration and evidence package;
- concise scientific-method explanation;
- project story and submission materials.

The exact implementation should be determined from the challenge resources, team decisions, and work performed during the event.

## 6. Verification evidence to preserve

For challenge work, preserve:

- commit timestamps and branch history;
- source references and data provenance;
- test results;
- CI runs;
- generated telemetry artifacts;
- screenshots/video of the working prototype;
- architecture diagram;
- documented limitations and assumptions;
- clear record of challenge-period additions.

## 7. Safety and representation boundary

AstroGuard is currently a **research/simulation software prototype**. Current physiological telemetry is synthetic unless explicitly documented otherwise.

Do not represent the project as:

- a medical device;
- a clinical diagnostic system;
- validated astronaut health software;
- flight-qualified spacecraft software;
- operational NASA software;
- endorsed, certified, sponsored, or validated by NASA merely because it participates in NASA Space Apps.

Participation in the NASA Space Apps Challenge and use of public/challenge resources must be described accurately and separately from NASA endorsement.

## 8. Repository policy before the hackathon

- `main`: consolidated stable technical history.
- `v2.0-mission-risk-forecasting`: research and technical preparation only.
- future event branch: challenge-specific implementation created at the appropriate event stage.

Do not rewrite historical commits to make earlier development appear to have occurred during the hackathon.

## 9. Readiness priorities

1. Build a scientific evidence/source matrix for each health and environmental variable.
2. Inventory the official challenge resources and identify which can be meaningfully used.
3. Define what is preparation versus what will be challenge-period implementation.
4. Prepare reproducible test scenarios without claiming clinical validation.
5. Preserve a clean Git history and evidence trail.

## 10. Current positioning

AstroGuard's existing codebase is treated as a research and technical preparation foundation. The 2026 astronaut-health challenge provides a target context for a distinct challenge implementation and demonstration.
