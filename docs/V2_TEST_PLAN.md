# AstroGuard ECLSS Core v2.0 — Decision-Support Verification Test Plan

Developer: **Taissiane Thais dos Santos**

Status: **research and technical preparation**

This document defines verification cases for the planned deterministic mission-health decision-support layer. It is a test specification, not a clinical protocol and not flight-qualification evidence.

## 1. Purpose

The v2.0 verification plan ensures that every decision-support output is deterministic, explainable and traceable to the synthetic telemetry and rule that produced it.

Each test must answer:

1. What telemetry entered the system?
2. Which explicit rule was evaluated?
3. Which reason code was produced?
4. Which software state was produced?
5. What non-diagnostic verification/action message was displayed?
6. Was the result reproducible?

## 2. Verification principles

- Identical inputs must produce identical outputs.
- No reason code may appear without its documented triggering condition.
- No action message may diagnose a medical condition.
- Synthetic thresholds must remain labelled as simulation parameters unless separately sourced and validated.
- Missing/invalid telemetry must not silently become NORMAL.
- Aggregate analytics must be reproducible from the underlying samples.
- Dashboard output must agree with the machine-readable output.

## 3. Core reason-code tests

| Test ID | Synthetic input/condition | Expected reason code | Expected state | Expected software response |
|---|---|---|---|---|
| DS-001 | all parameters inside simulation ranges | `NONE` | NORMAL | continue monitoring; no active alert |
| DS-002 | HR < 50 bpm | `HR_OUTSIDE_SIM_RANGE` | depends on aggregate attention rule | identify HR rule; request measurement/sensor verification |
| DS-003 | HR > 120 bpm | `HR_OUTSIDE_SIM_RANGE` | depends on aggregate attention rule | identify HR rule; request measurement/sensor verification |
| DS-004 | SpO2 < 94% and >= 90% | `SPO2_BELOW_SIM_ATTENTION` | depends on aggregate attention rule | identify SpO2 rule; request re-check and trend review |
| DS-005 | SpO2 < 90% | `SPO2_BELOW_SIM_CRITICAL` | CRITICAL | identify critical SpO2 simulation rule; request immediate verification and applicable mission procedure |
| DS-006 | body temp < 35.5 C | `BODY_TEMP_OUTSIDE_SIM_RANGE` | depends on aggregate attention rule | identify temperature rule; request verification |
| DS-007 | body temp > 38.0 C | `BODY_TEMP_OUTSIDE_SIM_RANGE` | depends on aggregate attention rule | identify temperature rule; request verification |
| DS-008 | respiratory rate < 10 bpm | `RESP_RATE_OUTSIDE_SIM_RANGE` | depends on aggregate attention rule | identify respiratory rule; request verification |
| DS-009 | respiratory rate > 24 bpm | `RESP_RATE_OUTSIDE_SIM_RANGE` | depends on aggregate attention rule | identify respiratory rule; request verification |
| DS-010 | fatigue >= 0.75 | `FATIGUE_HIGH_SIM` | depends on aggregate attention rule | identify synthetic fatigue rule; review trend/context |
| DS-011 | wellbeing <= 0.25 | `WELLBEING_LOW_SIM` | depends on aggregate attention rule | identify synthetic wellbeing rule; review trend/context |
| DS-012 | fatigue >= 0.90 AND wellbeing <= 0.15 | `FATIGUE_WELLBEING_SIM_CRITICAL` | CRITICAL | identify compound rule; verify inputs and follow applicable mission procedure |

## 4. Aggregation/state tests

The existing v1.4 classifier uses a CRITICAL-first rule and returns ATTENTION when two or more attention conditions are present. v2.0 must preserve or explicitly version any change to that behavior.

| Test ID | Conditions | Expected result |
|---|---|---|
| ST-001 | zero attention, zero critical | NORMAL |
| ST-002 | one attention condition | NORMAL under current v1.4 aggregation rule; reason code may still be logged |
| ST-003 | two attention conditions | ATTENTION |
| ST-004 | three or more attention conditions | ATTENTION |
| ST-005 | any critical condition | CRITICAL |
| ST-006 | critical + multiple attention conditions | CRITICAL |
| ST-007 | null/invalid health object | fail-safe non-NORMAL behavior; explicitly logged |

## 5. Persistence tests

| Test ID | Sequence | Expected persistence behavior |
|---|---|---|
| PS-001 | NORMAL x5 | longest attention = 0; longest critical = 0 |
| PS-002 | ATTENTION x3 | longest attention = 3 |
| PS-003 | ATTENTION x2, NORMAL, ATTENTION x4 | longest attention = 4 |
| PS-004 | CRITICAL x3 | longest critical = 3 |
| PS-005 | CRITICAL x2, NORMAL, CRITICAL | longest critical = 2 |
| PS-006 | NORMAL -> ATTENTION -> CRITICAL | state chronology preserved exactly |

## 6. Trend tests

The current v1.9 trend is intentionally simple: compare final severity with initial severity.

| Test ID | Initial -> final | Expected trend |
|---|---|---|
| TR-001 | NORMAL -> NORMAL | STABLE |
| TR-002 | NORMAL -> ATTENTION | DEGRADING |
| TR-003 | NORMAL -> CRITICAL | DEGRADING |
| TR-004 | CRITICAL -> ATTENTION | IMPROVING |
| TR-005 | ATTENTION -> NORMAL | IMPROVING |
| TR-006 | CRITICAL -> CRITICAL | STABLE |

Any future forecasting algorithm must receive a new version identifier and separate tests; it must not silently replace this definition.

## 7. Boundary-value tests

Every numeric comparison must be tested immediately below, exactly at and immediately above the encoded boundary.

Required boundaries:

- HR: 50 and 120 bpm;
- SpO2: 94% and 90%;
- body temperature: 35.5 and 38.0 C;
- respiratory rate: 10 and 24 bpm;
- fatigue: 0.75 and 0.90;
- wellbeing: 0.25 and 0.15.

Example: because the current SpO2 attention rule is `< 94.0`, a value of exactly `94.0` must not trigger that rule, while `93.99` must trigger it.

## 8. Invalid-data tests

Planned decision-support validation must include:

- NaN/non-finite values where applicable;
- impossible negative physiological values;
- missing telemetry fields;
- malformed CSV rows;
- unexpected state/reason-code values;
- empty sample sets;
- output-file creation failure.

The system must report invalid input explicitly rather than presenting it as healthy/normal telemetry.

## 9. CSV verification

### Raw telemetry output

Verify:

- header/schema is exact and versioned;
- sample count matches simulation count;
- timestamps remain ordered;
- numeric fields are parseable;
- state values belong to the documented enum;
- reason-code fields, when implemented, correspond to evaluated rules.

### Aggregate analytics output

Verify:

- counts sum to total samples;
- persistence values can be independently recomputed;
- means match raw samples within defined floating-point tolerance;
- trend matches the documented deterministic rule;
- version metadata identifies the analytics definition.

## 10. Dashboard consistency tests

For selected packets, verify that dashboard values match machine-readable telemetry for:

- mission time;
- HR;
- SpO2;
- respiratory rate;
- temperature;
- fatigue/wellbeing;
- health state;
- reason code;
- trend;
- persistence metrics.

The dashboard must display a research/simulation notice and must not transform a reason code into a medical diagnosis.

## 11. Explainability acceptance test

For every ATTENTION or CRITICAL display, a reviewer must be able to trace:

`displayed state -> reason code -> rule -> input value -> telemetry packet -> documented threshold provenance`

Failure of any link fails the explainability test.

## 12. CI acceptance criteria

A future v2.0 implementation is ready for integration only when:

- C compilation succeeds with warnings treated according to repository policy;
- existing v1.4/v1.9 regression tests still pass;
- all implemented v2.0 unit tests pass;
- boundary tests pass;
- persistence/trend tests pass;
- generated CSV validation passes;
- dashboard/static syntax checks pass;
- no undocumented threshold or reason code is introduced.

## 13. Space Apps preparation boundary

This file defines verification requirements during the **RESEARCH & TECHNICAL PREPARATION** phase. It does not claim that the challenge-specific implementation has already been produced during the NASA Space Apps 2026 hackathon.

The challenge implementation and the work actually performed during the event should remain separately identifiable in version history.

## 14. Safety statement

AstroGuard is currently a research/simulation software prototype using synthetic physiological telemetry. This test plan verifies software behavior against encoded requirements. It does not establish medical validity, clinical safety, astronaut-health certification, spacecraft flight qualification, or NASA endorsement.
