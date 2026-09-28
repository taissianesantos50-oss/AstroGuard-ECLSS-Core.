# AstroGuard ECLSS Core v2.0 — Decision Support Action Matrix

Developer: **Taissiane Thais dos Santos**

Status: **Research & Technical Preparation**

> Research/simulation prototype. Synthetic physiological telemetry. Decision-support demonstration only. Not a medical device, clinical diagnostic system, treatment protocol, or flight-qualified spacecraft software.

## 1. Purpose

This document defines the explainable decision-support behavior proposed for AstroGuard. The software should not merely display a state; it should show **what changed, which monitored variables contributed, why the software raised the state, and what non-diagnostic verification step is suggested**.

The matrix deliberately avoids prescribing medication, treatment, diagnosis, or autonomous clinical intervention. Any future operational medical recommendation would require an approved mission medical concept, validated clinical guidance, mission-specific constraints, qualified personnel, and appropriate certification.

## 2. Decision-support principles

1. **Explainability:** every ATTENTION or CRITICAL state must expose its contributing rule(s).
2. **Traceability:** each contributing rule must map to the threshold provenance documentation.
3. **Persistence:** repeated abnormal classifications should be distinguished from a single sample.
4. **Cross-domain context:** environmental and synthetic human telemetry may be displayed together without claiming causation.
5. **Human authority:** the prototype suggests verification/escalation steps; it does not diagnose or make clinical decisions.
6. **Conservative wording:** actions use terms such as re-check, verify sensor, review trend, and escalate according to an approved mission procedure.

## 3. State-to-action matrix

| Software state | What the astronaut sees | Why the state appears | Contributing information shown | Prototype suggested action | Escalation logic | Evidence/status |
|---|---|---|---|---|---|---|
| `NORMAL` | Green/nominal mission-health state and current telemetry | Current sample does not satisfy the encoded ATTENTION/CRITICAL aggregation rules | HR, SpO2, body temperature, respiratory rate, fatigue index, wellbeing index; environmental context displayed separately | Continue monitoring; no medical conclusion is generated | Re-evaluate on the next sample and preserve trend history | Engineering behavior; synthetic verification |
| `ATTENTION` | Attention-required state plus highlighted contributing variables | At least two encoded attention conditions are present in the current v1.4 health-monitor rule | Exact triggered rules and current values; persistence counter; mission trend | Re-check the affected measurements; verify sensor/data validity; review recent trend and environmental telemetry; follow the applicable approved mission procedure if the condition persists | Persistence and worsening trend should increase visibility/priority, but do not autonomously create a diagnosis | Engineering decision-support concept; thresholds remain illustrative unless separately sourced/validated |
| `CRITICAL` | Critical software alert with prominent contributing variables | At least one encoded critical condition is present | Exact critical rule(s), current values, persistence, environmental context and actuator telemetry | Prompt immediate measurement/sensor verification and escalation according to the applicable approved mission medical/operations procedure; preserve the event in telemetry | Critical persistence remains visible until subsequent samples/rules change state; no autonomous treatment is initiated | Engineering decision-support concept; not clinical or flight-qualified logic |

## 4. Trigger explanation model

The dashboard should eventually expose machine-readable reason codes rather than only the aggregate state. Proposed reason identifiers:

| Reason code | Existing rule represented | Display explanation | Classification |
|---|---|---|---|
| `HR_OUTSIDE_SIM_RANGE` | HR < 50 or HR > 120 bpm | Heart-rate value crossed the prototype simulation boundary | Illustrative simulation parameter |
| `SPO2_BELOW_SIM_ATTENTION` | SpO2 < 94% | SpO2 crossed the prototype attention boundary | Illustrative simulation parameter |
| `TEMP_OUTSIDE_SIM_RANGE` | body temperature < 35.5 or > 38.0 C | Body-temperature value crossed the prototype simulation boundary | Illustrative simulation parameter |
| `RESP_OUTSIDE_SIM_RANGE` | respiratory rate < 10 or > 24 bpm | Respiratory-rate value crossed the prototype simulation boundary | Illustrative simulation parameter |
| `FATIGUE_HIGH_SIM` | fatigue index >= 0.75 | Synthetic fatigue index crossed its prototype attention boundary | Synthetic/engineering index |
| `WELLBEING_LOW_SIM` | wellbeing index <= 0.25 | Synthetic wellbeing index crossed its prototype attention boundary | Synthetic/engineering index |
| `SPO2_BELOW_SIM_CRITICAL` | SpO2 < 90% | SpO2 crossed the prototype critical boundary | Illustrative simulation parameter |
| `FATIGUE_WELLBEING_SIM_CRITICAL` | fatigue >= 0.90 AND wellbeing <= 0.15 | Synthetic fatigue/wellbeing combination crossed the prototype critical rule | Synthetic/engineering index |

These reason codes explain **software rule activation**, not a medical diagnosis.

## 5. Proposed user-facing decision-support sequence

```text
TELEMETRY SAMPLE
      |
      v
RULE EVALUATION
      |
      v
NORMAL / ATTENTION / CRITICAL
      |
      +--> REASON CODES
      |        |
      |        v
      |   CONTRIBUTING VARIABLES
      |        |
      v        v
PERSISTENCE + TREND + ENVIRONMENTAL CONTEXT
      |
      v
EXPLAINABLE PROMPT
      |
      +--> RE-CHECK MEASUREMENT
      +--> VERIFY SENSOR / DATA QUALITY
      +--> REVIEW RECENT TREND & ENVIRONMENT
      +--> FOLLOW APPROVED MISSION PROCEDURE / ESCALATION PATH
```

## 6. Scientific and operational basis

NASA-STD-3001 Volume 1 establishes technical requirements directed at crew health, medical care, human performance and medical operations. NASA describes in-mission preventive health care as including capabilities and resources to monitor physiological and psychosocial well-being, with mission-specific analysis and medical/operational context.

NASA also describes decision-support approaches in space medicine. Appendix E of NASA-STD-3001 discusses evidence-based probabilistic risk assessment as a decision-support tool for clinical stakeholders, engineering teams and medical mission planners. NASA medical-operations material also describes research into medical decision-support capabilities for crews operating away from immediate terrestrial support.

These references support the **general design rationale for monitoring, explainability, risk assessment and escalation capability**. They do **not** validate AstroGuard's current numerical thresholds, synthetic indices, reason codes, or proposed user-interface prompts.

Primary public references:

- NASA Human Spaceflight Standards — https://www.nasa.gov/ochmo/human-spaceflight-and-aviation-standards/
- NASA-STD-3001 Volume 1: Crew Health — https://www.nasa.gov/reference/nasa-std-3001v1/
- NASA-STD-3001, Section 3: Health and Medical Care — https://www.nasa.gov/reference/3-0-health-and-medical-care/
- NASA-STD-3001, Section 6: Medical Operations — https://www.nasa.gov/reference/6-0-medical-operations/
- NASA-STD-3001 Appendix E: Health and Medical Care Technical Requirements — https://www.nasa.gov/reference/appendix-e-health-and-medical-care-technical-requirements/
- NASA In-Flight Medical Care — https://www.nasa.gov/ochmo/health-and-medical-systems/in-flight-medical-care/

## 7. Traceability to current implementation

Current implementation reference: `src/health_monitor.c`.

The current classifier uses explicit deterministic rules and returns `HEALTH_NORMAL`, `HEALTH_ATTENTION`, or `HEALTH_CRITICAL`. The source already states that the thresholds are illustrative simulation parameters and are not clinical limits or flight-qualified safety logic.

Threshold-level provenance is maintained separately in:

- `docs/THRESHOLD_PROVENANCE_TABLE.md`
- `docs/SCIENTIFIC_EVIDENCE_MATRIX.md`

## 8. Implementation boundary for v2.0 preparation

During research and technical preparation, it is appropriate to define this architecture, reason-code vocabulary, traceability requirements, test strategy and scientific boundaries.

A challenge-specific implementation can later decide which of these concepts to implement and demonstrate, while keeping a transparent distinction between prior research/preparation and work performed for the NASA Space Apps 2026 challenge implementation.

## 9. Acceptance criteria for a future implementation

A future code implementation should not be considered complete until automated tests demonstrate that:

- every encoded health rule can emit a deterministic reason code;
- NORMAL emits no abnormal reason code;
- ATTENTION exposes all contributing attention rules;
- CRITICAL exposes the critical rule(s) that caused the state;
- persistence counts are deterministic;
- reason codes survive CSV/telemetry serialization;
- the dashboard displays reasons without converting them into diagnoses;
- synthetic verification scenarios are explicitly identified as synthetic;
- no suggested action is represented as NASA-approved clinical guidance unless a future source and validation process explicitly establishes that fact.
