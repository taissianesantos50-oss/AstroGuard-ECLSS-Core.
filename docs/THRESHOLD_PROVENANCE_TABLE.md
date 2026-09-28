# AstroGuard ECLSS Core — Threshold Provenance Table

Developer: **Taissiane Thais dos Santos**

Branch: `v2.0-mission-risk-forecasting`

Status: **Research / technical preparation**

## Purpose

This document traces numerical thresholds and scenario values currently used by AstroGuard to their software location, intended role and evidence status.

A physiological variable being scientifically relevant does **not** mean that every numerical threshold currently encoded by AstroGuard has been validated by NASA or validated for astronaut clinical use. Unless a threshold has a specific, applicable source and validation context, it remains an engineering/synthetic simulation parameter.

## Evidence-status vocabulary

- **SCIENTIFIC CONTEXT** — the variable/measurement is supported as relevant by an authoritative scientific or spaceflight-health source.
- **ENGINEERING ASSUMPTION** — a project-defined deterministic rule used for software behavior; not claimed as a clinical or flight limit.
- **SYNTHETIC VERIFICATION** — a deliberately generated value used to exercise software states and tests.
- **SOURCE REQUIRED** — a numerical threshold must not be presented as scientifically validated until an applicable source and context are documented.
- **FUTURE RESEARCH** — candidate for later calibration/validation.

## A. Human-health classification thresholds

| Variable / rule | Current software threshold | Location | Software purpose | Provenance status |
|---|---:|---|---|---|
| Heart rate | `< 50 bpm` or `> 120 bpm` | `src/health_monitor.c` / `evaluate_health()` | Adds one ATTENTION condition | ENGINEERING ASSUMPTION / SOURCE REQUIRED |
| SpO2 | `< 94%` | `src/health_monitor.c` / `evaluate_health()` | Adds one ATTENTION condition | ENGINEERING ASSUMPTION / SOURCE REQUIRED |
| Body temperature | `< 35.5 °C` or `> 38.0 °C` | `src/health_monitor.c` / `evaluate_health()` | Adds one ATTENTION condition | ENGINEERING ASSUMPTION / SOURCE REQUIRED |
| Respiratory rate | `< 10` or `> 24 breaths/min` | `src/health_monitor.c` / `evaluate_health()` | Adds one ATTENTION condition | ENGINEERING ASSUMPTION / SOURCE REQUIRED |
| Fatigue index | `>= 0.75` | `src/health_monitor.c` / `evaluate_health()` | Adds one ATTENTION condition | PROJECT-DEFINED SYNTHETIC INDEX |
| Wellbeing index | `<= 0.25` | `src/health_monitor.c` / `evaluate_health()` | Adds one ATTENTION condition | PROJECT-DEFINED SYNTHETIC INDEX |
| SpO2 critical condition | `< 90%` | `src/health_monitor.c` / `evaluate_health()` | Produces a CRITICAL condition | ENGINEERING ASSUMPTION / SOURCE REQUIRED |
| Combined fatigue/wellbeing | fatigue `>= 0.90` AND wellbeing `<= 0.15` | `src/health_monitor.c` / `evaluate_health()` | Produces a CRITICAL condition | PROJECT-DEFINED SYNTHETIC RULE |
| ATTENTION aggregation | at least `2` attention conditions | `src/health_monitor.c` / `evaluate_health()` | Returns `HEALTH_ATTENTION` | ENGINEERING ASSUMPTION |
| CRITICAL aggregation | at least `1` critical condition | `src/health_monitor.c` / `evaluate_health()` | Returns `HEALTH_CRITICAL` | ENGINEERING ASSUMPTION |

### Scientific context for monitored vital signs

NASA material supports the relevance of monitoring vital signs such as heart rate, oxygen saturation and respiratory rate in spaceflight medical capability. Historical NASA Human Research Program work also described physiological monitoring requirements including heart rate, body temperature, respiratory rate and blood oxygen saturation. These references support the **choice of variables**, not automatic adoption of AstroGuard's current numerical cutoffs.

## B. Synthetic v1.9 verification scenario

The integrated scenario in `src/astroguard_v1_9.c` intentionally drives the software through nominal, attention and critical states. These values are test stimuli, not astronaut medical records.

| Scenario parameter | Current value/rule | Purpose | Status |
|---|---:|---|---|
| Initial O2 | `21.5` | Initial synthetic environmental state | SYNTHETIC VERIFICATION |
| Initial pressure | `4.30 psi` | Initial synthetic environmental state | SYNTHETIC VERIFICATION / mission-context review required |
| Initial temperature | `21.0 °C` | Initial synthetic environmental state | SYNTHETIC VERIFICATION |
| Initial heart rate | `72 bpm` | Nominal test sample | SYNTHETIC VERIFICATION |
| Initial SpO2 | `98%` | Nominal test sample | SYNTHETIC VERIFICATION |
| Initial body temperature | `36.7 °C` | Nominal test sample | SYNTHETIC VERIFICATION |
| Initial respiratory rate | `16/min` | Nominal test sample | SYNTHETIC VERIFICATION |
| Initial fatigue index | `0.10` | Nominal synthetic index | SYNTHETIC VERIFICATION |
| Initial wellbeing index | `0.90` | Nominal synthetic index | SYNTHETIC VERIFICATION |
| HR during attention phase | `130 bpm` | Forces attention-path verification | SYNTHETIC VERIFICATION |
| Fatigue during attention phase | `0.80` | Forces attention-path verification | SYNTHETIC VERIFICATION |
| HR during critical phase | `135 bpm` | Critical-scenario stimulus | SYNTHETIC VERIFICATION |
| SpO2 during critical phase | `88%` | Forces critical-path verification | SYNTHETIC VERIFICATION |
| Respiratory rate during critical phase | `25/min` | Critical-scenario stimulus | SYNTHETIC VERIFICATION |
| Fatigue during critical phase | `0.92` | Combined critical-rule stimulus | SYNTHETIC VERIFICATION |
| Wellbeing during critical phase | `0.12` | Combined critical-rule stimulus | SYNTHETIC VERIFICATION |
| O2 valve activation | O2 `< 20.0` | Demonstrates deterministic actuator state | ENGINEERING ASSUMPTION / SOURCE REQUIRED |
| Heater activation | temperature `< 15.0 °C` | Demonstrates deterministic actuator state | ENGINEERING ASSUMPTION / SOURCE REQUIRED |

## C. What NASA evidence currently establishes

### NASA-STD-3001

NASA-STD-3001 is the Agency-level human-spaceflight standard family for minimizing crew health and performance risks. Volume 1 addresses crew health and medical care; Volume 2 addresses human factors, habitability and environmental health.

This establishes an appropriate standards framework for AstroGuard research traceability, but AstroGuard must not describe itself as compliant, certified, flight-qualified or NASA-validated without a formal requirements-level compliance assessment and applicable verification evidence.

### Human Research Program (HRP)

NASA's Human Research Program studies and develops methods to protect astronaut health and performance. HRP provides the scientific context for treating human physiological and behavioral performance as mission-relevant research domains.

### Vital-sign monitoring relevance

NASA technical material identifies capabilities to assess/store vital signs including oxygen saturation, heart rate and respiratory rate. NASA HRP historical physiological-monitoring work also included heart rate, body temperature, respiratory rate and blood oxygen saturation.

Therefore AstroGuard can accurately state that these **types of measurements are relevant to spaceflight health monitoring research**. It should not state that NASA endorses AstroGuard's current thresholds.

## D. Threshold acceptance rule for future development

Before changing a threshold status from `ENGINEERING ASSUMPTION / SOURCE REQUIRED` to a scientifically sourced status, record:

1. exact source and revision/date;
2. source section/page/table;
3. population represented;
4. measurement conditions and sensor assumptions;
5. mission/environment context;
6. exact numerical value/range supported;
7. whether the source is descriptive, operational, clinical or a formal requirement;
8. applicability limitations;
9. code file/function using the threshold;
10. test case demonstrating the rule.

No threshold should be labeled a "NASA limit" merely because it resembles a familiar terrestrial clinical value.

## E. v2.0 design rule

The planned v2.0 mission-risk/decision-support layer should consume **explicitly classified inputs** and preserve provenance metadata. It should not silently convert project-defined synthetic thresholds into medical predictions.

Recommended output terminology:

- `NOMINAL SOFTWARE STATE`
- `ATTENTION-REQUIRED SOFTWARE STATE`
- `CRITICAL SOFTWARE STATE`
- `TREND: STABLE / IMPROVING / DEGRADING`
- `RECOMMENDED CHECK` or `DECISION-SUPPORT ACTION`

Avoid claims such as:

- "astronaut diagnosis";
- "medical emergency confirmed";
- "NASA-approved threshold";
- "flight-certified decision";
- "clinical prediction".

## F. Primary reference framework

- NASA-STD-3001 Volume 1 — Crew Health, Rev C (2023).
- NASA-STD-3001 Volume 2 — Human Factors, Habitability, and Environmental Health, current 2026 revision.
- NASA Human Research Program (HRP).
- NASA OCHMO technical material on spaceflight experience and medical care.
- NASA HRP physiological-monitoring research/history.

## Scientific boundary

AstroGuard is a research/simulation software prototype. Current physiological telemetry is synthetic. This provenance table is a traceability mechanism and does not constitute medical validation, NASA certification, flight qualification or clinical approval.
