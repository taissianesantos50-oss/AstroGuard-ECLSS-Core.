# AstroGuard ECLSS Core v2.0 — Space Apps 2026 Demonstration

## Purpose
AstroGuard v2.0 is a research/simulation software prototype for long-duration mission health monitoring. It combines synthetic environmental and human-health telemetry with deterministic, explainable decision-support logic.

This demonstration is designed to make the prototype easy to understand and reproduce during evaluation.

> Important: synthetic telemetry and simulation thresholds are used. AstroGuard is not a medical device and does not provide a medical diagnosis.

## Demonstration pipeline

`Mission Scenario -> ECLSS / Environment -> Human Telemetry -> Health State -> Reason Code -> Recommended Action -> Mission Analytics -> 3D Dashboard`

## Build
From the repository root:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic \
  src/health_monitor.c \
  src/decision_support.c \
  src/mission_health_analytics.c \
  src/mission_scenario_engine.c \
  src/astroguard_v2_0.c \
  -I src -lm -o astroguard_v2_0
```

## Scenario 1 — Nominal reference

```bash
./astroguard_v2_0 nominal
```

Purpose: demonstrate a stable reference case. Expected behavior is predominantly NORMAL with no decision-support intervention required.

## Scenario 2 — Cabin degradation

```bash
./astroguard_v2_0 cabin
```

Purpose: demonstrate progressive environmental degradation and the transition from passive monitoring toward attention/review behavior. This scenario is intentionally not forced to become a medical emergency.

## Scenario 3 — Long-duration stress

```bash
./astroguard_v2_0 long-duration
```

Purpose: demonstrate cumulative synthetic human-health changes over mission time and how explainable decision-support rules react to those changes.

## Generated evidence
Each run produces:

- `telemetry_v2_0.csv` — frame-by-frame environmental, human-health and decision-support telemetry.
- `mission_health_analytics_v2_0.csv` — mission-level summary and trend information.

Important telemetry fields include:

- `Scenario`
- `HealthStatus`
- `ReasonCode`
- `RecommendedAction`
- `AttentionConditions`
- `CriticalConditions`

These fields make the decision process inspectable rather than presenting only an unexplained alert.

## Visual demonstration
After generating `telemetry_v2_0.csv`, run:

```bash
python src/astroguard_v2_0_dashboard.py telemetry_v2_0.csv
```

The dashboard visualizes mission time, environmental stress, synthetic human-health load, the active scenario, health status, reason code and recommended software action.

## What to show an evaluator
1. Run `nominal` and show the stable baseline.
2. Run `cabin` and show the environmental degradation plus explainable attention behavior.
3. Run `long-duration` and show cumulative synthetic health changes and decision-support responses.
4. Open the generated CSV to demonstrate that every visual state is backed by inspectable telemetry.
5. Show the GitHub Actions result to demonstrate automated build, unit testing and scenario regression checks.

## Explainability principle
AstroGuard does not output only `NORMAL`, `ATTENTION` or `CRITICAL`. The v2.0 decision-support layer also records why a rule fired and what software action is associated with that rule. Examples include measurement verification, trend review and consultation of mission procedures.

The encoded actions are demonstration/prototype logic. They do not replace medical judgment, flight rules or validated operational procedures.

## Reproducibility
The Mission Scenario Engine is deterministic: the same scenario and simulation step produce the same synthetic frame. This allows demonstrations, tests and evaluation runs to be reproduced consistently.

## Current validation boundary
The project currently demonstrates software architecture, deterministic simulation, telemetry processing, explainable rule execution, mission analytics and visualization. It does not claim clinical validation, hardware flight qualification, sensor certification or operational NASA approval.

## Space Apps implementation framing
For the 2026 event, the repository can present the implementation work completed for the challenge while preserving the project's development history. The demonstration should clearly distinguish prior architectural work from features implemented or finalized during the official hackathon window.
