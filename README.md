# AstroGuard ECLSS Core

**Developer:** Taissiane Thais dos Santos  
**Current development branch:** `v2.0-mission-risk-forecasting`  
**Classification:** Private / Proprietary Research & Simulation Prototype

AstroGuard is a deterministic mission-health monitoring and explainable decision-support research prototype for long-duration spaceflight simulations. It combines spacecraft environmental/ECLSS telemetry with synthetic astronaut physiological indicators so that a crew-facing interface can identify changes, expose the software rule that produced an alert, track mission-level trends, and indicate the next verification/action encoded by the prototype.

> **Scope notice:** Research/simulation prototype. Synthetic human-health telemetry and simulation thresholds. Not a medical device, not a medical diagnosis, not flight-qualified software, and not an operational NASA system.

## NASA Space Apps Challenge 2026 relevance

The project is being developed for the long-duration mission-health problem space described by the 2026 challenge: software that collects health indicators and helps astronauts assess and act on changes in their health state.

AstroGuard addresses that software problem through:

- synthetic astronaut health indicators: heart rate, SpO2, body temperature, respiratory rate, fatigue and well-being;
- environmental/ECLSS context: oxygen, pressure, cabin temperature and actuator state;
- deterministic `NORMAL`, `ATTENTION` and `CRITICAL` health-state logic;
- explainable `ReasonCode` output rather than an unexplained alert;
- `RecommendedAction` output for prototype decision support;
- persistence/trend analytics across mission telemetry;
- deterministic mission scenarios for reproducible demonstrations;
- a 3D dashboard that combines scenario, environment, human-health state and decision-support output.

## v2.0 architecture

```text
MISSION SCENARIO
      |
      v
ECLSS / ENVIRONMENTAL TELEMETRY
      +
SYNTHETIC HUMAN-HEALTH TELEMETRY
      |
      v
DETERMINISTIC HEALTH MONITOR
      |
      v
EXPLAINABLE DECISION SUPPORT
  HealthStatus
  ReasonCode
  RecommendedAction
      |
      v
MISSION HEALTH ANALYTICS
      |
      v
CSV EVIDENCE + 3D DASHBOARD
```

## What is implemented

### Core monitoring
- Environmental simulation: O2, pressure, temperature and actuator states.
- Synthetic human telemetry: heart rate, SpO2, body temperature, respiratory rate, fatigue and well-being.
- Deterministic health states: `NORMAL`, `ATTENTION`, `CRITICAL`.

### v1.9 analytics
- Mission-level aggregation.
- Persistence/run analysis.
- Mean physiological indicators.
- Mission trend classification such as `STABLE` and `DEGRADING`.

### v2.0 explainable decision support
- Explicit reason codes for encoded software rules.
- Prototype actions including measurement verification, trend review and consultation of mission procedures.
- Condition counters for attention and critical rules.
- Decision-support telemetry stored alongside the originating measurements.

### v2.0 Mission Scenario Engine
Three deterministic scenarios are available:

1. `NOMINAL` — stable reference case.
2. `CABIN_DEGRADATION` — progressive environmental degradation with synthetic human response.
3. `LONG_DURATION_STRESS` — cumulative synthetic human-health workload/stress scenario.

The same scenario and simulation step produce the same synthetic frame, supporting reproducible demonstrations and regression tests.

## Quick start

### 1. Compile v2.0

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic \
  src/health_monitor.c \
  src/decision_support.c \
  src/mission_health_analytics.c \
  src/mission_scenario_engine.c \
  src/astroguard_v2_0.c \
  -I src -lm -o astroguard_v2_0
```

### 2. Run a scenario

```bash
./astroguard_v2_0 nominal
./astroguard_v2_0 cabin
./astroguard_v2_0 long-duration
```

Each run generates:

- `telemetry_v2_0.csv`
- `mission_health_analytics_v2_0.csv`

The telemetry includes `Scenario`, `HealthStatus`, `ReasonCode`, `RecommendedAction`, `AttentionConditions` and `CriticalConditions`.

### 3. Open the explainable 3D dashboard

Install Python dependencies if needed:

```bash
python -m pip install matplotlib
```

Then run:

```bash
python src/astroguard_v2_0_dashboard.py telemetry_v2_0.csv
```

The dashboard displays the active mission scenario, environmental state, synthetic human-health telemetry, health status, reason code and recommended prototype action.

## Automated verification

GitHub Actions compiles and tests the project automatically. The current v2.0 CI covers:

- health-monitor unit tests;
- mission-health analytics tests;
- decision-support unit and boundary tests;
- Mission Scenario Engine deterministic tests;
- legacy v1.4 and v1.9 regression checks;
- compilation of the integrated v2.0 simulator;
- execution of `NOMINAL`, `CABIN_DEGRADATION` and `LONG_DURATION_STRESS`;
- validation of generated telemetry schema and scenario behavior;
- Python syntax and required dashboard decision-support fields.

The v2.0 integrated scenario pipeline has been exercised successfully by the repository CI on the development branch.

## Evaluator demonstration path

A concise evaluation can follow this sequence:

```text
1. Run NOMINAL
   -> establish stable reference behavior

2. Run CABIN_DEGRADATION
   -> show environmental deterioration and attention/trend behavior

3. Run LONG_DURATION_STRESS
   -> show cumulative synthetic human-health changes

4. Inspect telemetry_v2_0.csv
   -> verify the measurement -> state -> reason -> action chain

5. Open the 3D dashboard
   -> visualize the same explainable telemetry

6. Inspect GitHub Actions
   -> verify automated build, unit tests and scenario regression checks
```

For the complete reproducible demonstration guide, see:

`docs/SPACE_APPS_2026_DEMO.md`

## Why explainability matters in this prototype

A health-monitoring interface should not merely display `CRITICAL`. AstroGuard v2.0 preserves an inspectable chain:

```text
MEASUREMENT
   -> ENCODED RULE
   -> HEALTH STATE
   -> REASON CODE
   -> PROTOTYPE ACTION
```

This makes the software behavior easier to audit, test and explain during a mission simulation. The reason codes explain software rules; they are not diagnoses.

## Scientific and safety boundary

All physiological values, environmental transitions, scenario relationships and decision thresholds in this repository are synthetic research/demo parameters unless explicitly documented otherwise.

AstroGuard does **not** claim:

- medical or clinical validation;
- diagnosis or treatment capability;
- validated astronaut-specific physiological thresholds;
- real astronaut health telemetry;
- certified spacecraft sensor integration;
- flight qualification;
- operational NASA or Artemis approval.

The long-duration scenario is a software demonstration of cumulative synthetic changes. It does not model or diagnose a specific disease, radiation injury, bone loss, immune dysfunction, cardiovascular disease or mental-health condition.

## Space Apps 2026 implementation record

The repository preserves the project's development history. For the 2026 event, the submission can present the complete AstroGuard system while clearly identifying which features were implemented or finalized during the official hackathon window.

This distinction is intentional: prior research and architecture remain visible, while event-period implementation can be documented through dated commits, tests, demonstration evidence and the final submission materials.

A dedicated event-period section can be completed during the hackathon with:

- start commit / baseline reference;
- features implemented during the event;
- event-period commits;
- final CI run;
- final screenshots/video;
- submitted project URL and timestamp.

## Project evolution

```text
v1.2  ECLSS telemetry foundation
v1.3  Flight Physics Simulator
v1.4  Human Health Monitoring Layer
v1.5  3D mission visualization
v1.6  Web mission dashboard
v1.7  Demonstration video specification
v1.8  Technical documentation and presentation package
v1.9  Advanced Mission Health Analytics
v2.0  Mission Scenario Engine + Explainable Decision Support
```

## Access and intellectual property

**PRIVATE / PROPRIETARY PROJECT — ALL RIGHTS RESERVED**

Copyright (c) 2026 Taissiane Thais dos Santos. All rights reserved.

Access to this repository does not grant permission to use, copy, reproduce, modify, distribute, publish, sublicense, commercialize, or create derivative works from the source code, documentation, designs, data, or other project materials.

Any use, modification, redistribution, collaboration, evaluation beyond the access expressly granted, or other exploitation requires the prior express written authorization of Taissiane Thais dos Santos.

See `LICENSE` for the complete proprietary terms.
