# AstroGuard ECLSS Core — Scientific Evidence & Traceability Matrix

Developer: **Taissiane Thais dos Santos**

Track: **RESEARCH & TECHNICAL PREPARATION → NASA SPACE APPS 2026 CHALLENGE IMPLEMENTATION**

Status: research/simulation documentation. This matrix does not establish clinical validation, medical-device status, flight qualification, or NASA endorsement.

## Evidence classification

- **SCIENTIFIC CONTEXT** — supported as a relevant human-spaceflight or environmental-health topic by authoritative literature/standards, but not necessarily a validated threshold for AstroGuard.
- **ENGINEERING ASSUMPTION** — value, rule, weighting, or relationship selected for software architecture/prototyping and requiring separate validation before operational use.
- **SYNTHETIC VERIFICATION** — artificial value/scenario used to exercise deterministic software behavior and tests.
- **FUTURE RESEARCH** — proposed capability requiring additional evidence, data, validation, or challenge-specific implementation.

## Traceability matrix

| AstroGuard variable / concept | Current role | Evidence classification | Scientific / engineering basis | Current limitation | Required next evidence step |
|---|---|---|---|---|---|
| Heart rate (HR) | Synthetic physiological telemetry and health-state input | SCIENTIFIC CONTEXT + SYNTHETIC VERIFICATION | Cardiovascular adaptation is an identified NASA human-spaceflight risk; NASA-STD-3001 provides crew-health requirements and evidence-based human-performance context. | Current AstroGuard values/thresholds are not asserted as astronaut clinical limits. | Identify an authoritative source appropriate to the exact use case before assigning any operational threshold. |
| SpO2 | Synthetic physiological telemetry and health-state input | SCIENTIFIC CONTEXT + SYNTHETIC VERIFICATION | Oxygen availability and crew health are relevant to human spaceflight; NASA human-system standards cover crew health and environmental/habitability requirements. | Current SpO2 scenario values are synthetic; no claim that AstroGuard thresholds are NASA medical limits. | Separate sensor measurement assumptions, clinical interpretation, and spacecraft environmental oxygen requirements. |
| Body temperature | Synthetic physiological telemetry and health-state input | SCIENTIFIC CONTEXT + SYNTHETIC VERIFICATION | Crew health monitoring and hostile/closed-environment conditions are recognized human-spaceflight concerns. | Synthetic body-temperature values do not constitute diagnostic criteria. | Add source-specific measurement context and validated interpretation only if required by the challenge implementation. |
| Respiratory rate | Synthetic physiological telemetry and health-state input | SCIENTIFIC CONTEXT + SYNTHETIC VERIFICATION | Physiological monitoring is relevant to crew health; NASA standards establish a broader evidence-based crew-health framework. | Current thresholds/scenarios are demonstration logic, not clinical decision rules. | Document measurement assumptions and authoritative threshold evidence before operational interpretation. |
| Fatigue index | Synthetic derived indicator | ENGINEERING ASSUMPTION + SYNTHETIC VERIFICATION | NASA identifies sleep loss, circadian desynchronization, workload, isolation and confinement as factors affecting health/performance. | AstroGuard's scalar fatigue index is not a NASA-defined clinical metric. | Define an explicit derivation method or retain it clearly as a synthetic demonstration variable. |
| Wellbeing index | Synthetic derived indicator | ENGINEERING ASSUMPTION + SYNTHETIC VERIFICATION | NASA Human Factors and Behavioral Performance research addresses behavioral health, sleep, cognition, team performance, isolation and confinement. | The current scalar wellbeing index is not a validated behavioral-health instrument. | Replace or map it to an evidence-backed construct only if scientifically justified and appropriate. |
| NORMAL / ATTENTION / CRITICAL | Deterministic software classification | ENGINEERING ASSUMPTION | Explicit, inspectable state logic supports reproducible software verification. | State names must not be interpreted as medical diagnoses. | Maintain traceability from every state transition to documented software rules and evidence category. |
| STABLE / IMPROVING / DEGRADING | Mission-health temporal summary | ENGINEERING ASSUMPTION | Deterministic trend classification provides auditable temporal summarization. | Current v1.9 rule compares severity at the final sample with the first sample; it is not predictive medicine. | Test alternative deterministic trend definitions and document rationale before changing the reference algorithm. |
| O2 / environmental oxygen | ECLSS/environmental synthetic telemetry | SCIENTIFIC CONTEXT + SYNTHETIC VERIFICATION | NASA identifies hostile/closed environments as a major human-spaceflight hazard; environmental conditions and vehicle habitability are covered by NASA-STD-3001 Vol. 2. | Existing simulation values are not claimed as certified spacecraft operating limits. | Trace any future operational range to the exact NASA standard/revision and mission context. |
| Cabin/suit pressure | ECLSS/environmental synthetic telemetry | SCIENTIFIC CONTEXT + SYNTHETIC VERIFICATION | Pressure is explicitly part of the spacecraft closed-environment/habitability context identified by NASA. | Current pressure scenario is a software stress case, not a certified pressure schedule. | Distinguish cabin vs suit architecture and source exact requirements before operational use. |
| Environmental temperature | ECLSS/environmental synthetic telemetry | SCIENTIFIC CONTEXT + SYNTHETIC VERIFICATION | NASA identifies temperature as an important habitability factor in hostile/closed spacecraft environments. | Existing simulated temperatures are verification inputs rather than certified limits. | Map future ranges to NASA-STD-3001 Vol. 2 requirements relevant to the selected habitat/suit context. |
| Environmental + human telemetry correlation | Mission-health analytics concept | FUTURE RESEARCH | NASA notes that human-spaceflight hazards can interact and that combined effects are an active research concern. | AstroGuard does not currently demonstrate causal physiological relationships. | Treat correlation as exploratory unless supported by appropriate datasets and study design; do not infer causation. |
| Mission risk forecasting | v2.0 research direction | FUTURE RESEARCH | NASA risk work considers interacting human and mission-system hazards and the need for crew support during deep-space missions. | No validated predictive risk model currently exists in AstroGuard. | Keep v2.0 deterministic/explainable; define risk inputs, evidence provenance, uncertainty, verification scenarios and non-clinical boundaries before implementation. |
| Astronaut action / decision support | Challenge-aligned future interface | FUTURE RESEARCH | Greater distance from Earth increases the importance of crew self-sufficiency; NASA studies systems-operations support and human performance. | Recommendations must not be represented as medical treatment instructions without appropriate authority/validation. | Implement explainable software actions such as re-check, inspect telemetry, confirm sensor integrity, or escalate according to a documented protocol. |

## Primary authoritative sources for this research track

1. NASA Human Research Program — Risks of Human Spaceflight: https://www.nasa.gov/hrp/risks/
2. NASA Human Research Program — Five Hazards of Human Spaceflight: https://www.nasa.gov/hrp/hazards/
3. NASA-STD-3001 Volume 1 — Crew Health: https://www.nasa.gov/reference/nasa-std-3001v1/
4. NASA-STD-3001 Volume 2 — Human Factors, Habitability, and Environmental Health: https://www.nasa.gov/reference/nasa-std-3001v2/
5. NASA Human Spaceflight Standards overview: https://www.nasa.gov/ochmo/human-spaceflight-and-aviation-standards/
6. NASA Human Factors and Behavioral Performance: https://www.nasa.gov/reference/about-human-factors-and-behavioral-performance/
7. NASA Human System Risk Board: https://www.nasa.gov/directorates/esdmd/hhp/human-system-risk-board/
8. NASA NTRS — Integrated Research Plan on combined spaceflight hazards: https://ntrs.nasa.gov/citations/20205003665

## Scientific interpretation rule

A source demonstrating that a variable or hazard is scientifically relevant does **not** automatically validate AstroGuard's numerical threshold, weighting, classification, or recommended action. Each operational numerical rule requires its own traceable evidence and context.

## Current scientific boundary

AstroGuard currently uses synthetic physiological and environmental telemetry for deterministic software verification. The project demonstrates architecture, state classification, temporal analytics, telemetry, visualization and automated testing. It does not diagnose disease, prescribe treatment, replace crew medical systems, claim use of real astronaut health data, or claim NASA certification/endorsement.

## Next evidence tasks

- Extract only context-appropriate requirements from the current NASA-STD-3001 revisions.
- Build a threshold provenance table: variable → code location → current value → classification → source → rationale → validation status.
- Separate environmental spacecraft limits from human physiological interpretation.
- Define sensor assumptions and uncertainty fields.
- Define explainable, non-clinical decision-support actions.
- Preserve synthetic test scenarios separately from scientifically sourced reference values.
- Record the exact version/date of every standard used so later revisions can be audited.
