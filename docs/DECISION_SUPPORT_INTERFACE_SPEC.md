# AstroGuard ECLSS Core v2.0 — Decision Support Interface Specification

Developer: **Taissiane Thais dos Santos**

Status: **Research & Technical Preparation**

## 1. Objective

Define the interface contract for an explainable mission-health decision-support layer. The interface is intended to convert deterministic monitoring outputs into information an astronaut can inspect and use to decide what verification step or applicable mission procedure to consult.

This specification does not implement the challenge-specific hackathon solution. It defines requirements and acceptance criteria for later implementation.

## 2. Core interaction model

The interface shall preserve the following traceability chain:

`TELEMETRY -> STATE -> REASON CODE -> TRIGGERING VALUE/RULE -> TREND/PERSISTENCE -> SUGGESTED VERIFICATION -> APPLICABLE PROCEDURE`

The user must never have to infer why an ATTENTION or CRITICAL state appeared.

## 3. Primary status panel

The primary panel shall display:

- Mission time / sample timestamp
- Overall health-monitor state: `NORMAL`, `ATTENTION`, or `CRITICAL`
- Trend: `STABLE`, `IMPROVING`, or `DEGRADING`
- Current persistence duration/count for non-normal state
- Number of active reason codes
- Research/simulation status indicator

The state label must not be converted into a disease or diagnosis label.

## 4. Health indicator cards

Each monitored indicator should have an individual card containing:

- indicator name;
- current synthetic value;
- unit;
- local status;
- reason code when applicable;
- encoded simulation boundary relevant to the current event;
- trend/context where available;
- data-quality/sensor-validity indicator.

Initial indicators:

- Heart Rate (HR)
- SpO2
- Body Temperature
- Respiratory Rate
- Fatigue Index
- Wellbeing Index

Environmental/ECLSS context may be shown separately to avoid confusing environmental telemetry with physiological telemetry.

## 5. Explainability drawer

Selecting an active alert shall expose an explanation containing:

1. **What changed?** — indicator and observed value.
2. **Which rule fired?** — exact deterministic comparison.
3. **Why is it visible?** — reason code and aggregation contribution.
4. **How long has it persisted?** — persistence metric.
5. **What is the trajectory?** — deterministic trend classification.
6. **What should be verified?** — non-diagnostic verification step.
7. **What is the evidence status?** — scientific context / engineering assumption / synthetic verification.

Example representation:

```text
STATE: CRITICAL
REASON: SPO2_BELOW_SIM_CRITICAL
VALUE: 88.0 %
SIMULATION RULE: SpO2 < 90.0 %
PERSISTENCE: 3 samples
TREND: DEGRADING
VERIFY: Re-check telemetry and sensor/data validity; consult the applicable mission procedure.
EVIDENCE STATUS: Synthetic simulation threshold — not a NASA-validated clinical threshold.
```

## 6. Suggested-action contract

Suggested actions must be conservative and procedural. Permitted action classes include:

- `VERIFY_MEASUREMENT`
- `VERIFY_SENSOR_OR_DATA`
- `REVIEW_TREND`
- `REVIEW_ENVIRONMENT_CONTEXT`
- `CONSULT_MISSION_PROCEDURE`
- `CONTINUE_MONITORING`

The interface must not produce autonomous treatment instructions, medication recommendations, clinical diagnoses, or claims that a crew member has a disease.

## 7. State behavior

### NORMAL

Display nominal monitoring state and continue monitoring. A single attention-level reason that does not meet the aggregate ATTENTION rule may still be logged/exposed for traceability without changing the overall state.

### ATTENTION

Display all contributing reason codes, triggering values, persistence and trend. Prompt the user to verify measurements/data and review context.

### CRITICAL

Display the critical reason code prominently, preserve all contributing reasons, show persistence/trend, and direct the user to verify the data and consult the applicable mission procedure. The software itself does not prescribe treatment.

## 8. Data-quality state

Invalid, missing, malformed or non-finite telemetry must not silently map to `NORMAL`.

A dedicated data-quality state/message shall distinguish:

- unavailable measurement;
- invalid measurement;
- stale measurement;
- malformed packet;
- sensor/data verification required.

This is separate from physiological classification.

## 9. Machine-readable event contract

A future implementation should emit an event structure with at least:

```text
timestamp
mission_time
indicator
value
unit
reason_code
overall_state
persistence
trend
action_code
evidence_status
rule_version
```

This allows the dashboard, CSV/log output and automated tests to use the same deterministic event definition.

## 10. Dashboard acceptance criteria

The interface passes acceptance only if:

- displayed telemetry equals the machine-readable source;
- every ATTENTION/CRITICAL display exposes at least one valid reason code;
- every reason code maps to a documented rule;
- every action maps to a documented action class;
- trend and persistence match analytics output;
- invalid telemetry cannot appear as nominal without an explicit policy;
- simulation/scientific provenance is visible;
- no medical diagnosis is generated;
- a reviewer can reproduce the displayed state from the input packet.

## 11. Demonstration scenario specification

A future demo should include a deterministic sequence showing:

1. nominal baseline;
2. first attention-level indicator;
3. aggregate ATTENTION condition;
4. persistence increase;
5. transition to CRITICAL through a documented synthetic rule;
6. explainability drawer showing the cause;
7. suggested verification/procedure action;
8. recovery sequence demonstrating `IMPROVING`;
9. return to `NORMAL` where the synthetic scenario permits it.

The same sequence must be reproducible from saved telemetry.

## 12. Evidence linkage

Implementation evidence shall link this specification to:

- `docs/DECISION_SUPPORT_ACTION_MATRIX.md`
- `docs/THRESHOLD_PROVENANCE_TABLE.md`
- `docs/SCIENTIFIC_EVIDENCE_MATRIX.md`
- `docs/NASA_SCIENTIFIC_SOURCE_AUDIT.md`
- `docs/V2_TEST_PLAN.md`
- `docs/SPACE_APPS_SUBMISSION_EVIDENCE_MAP.md`

## 13. NASA Space Apps alignment

The 2026 challenge asks participants to build health-monitoring software that gathers health indicators and enables astronauts to evaluate and act on their health status. This specification addresses the evaluation/action side through deterministic explanations, verification actions, trend/persistence context and traceable reason codes.

Challenge reference:
https://www.spaceappschallenge.org/2026/challenges/create-health-monitoring-software-for-astronauts-on-space-missions/

## 14. Development boundary

This document is a preparation/specification artifact. It does not claim that the Space Apps challenge implementation has already been built during the hackathon window. Challenge-specific implementation work should remain separately identifiable in version history.

## 15. Safety and scope statement

AstroGuard is a research/simulation software prototype using synthetic physiological telemetry. The interface specification describes explainable software behavior. It is not a medical device specification, clinical decision-support validation, operational astronaut-care protocol, flight qualification, or NASA endorsement.
