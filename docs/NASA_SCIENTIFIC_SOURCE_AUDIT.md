# AstroGuard ECLSS Core — NASA Scientific Source Traceability Audit

Developer: **Taissiane Thais dos Santos**

Status: **Research & Technical Preparation — NASA Space Apps 2026**

## 1. Purpose

This audit records which NASA/Space Apps sources support the scientific and engineering context of AstroGuard, what each source can legitimately support, and—equally important—what it does **not** establish.

A source supporting the relevance of a physiological or environmental variable does not automatically validate a numeric threshold, algorithm, clinical interpretation, or flight-safety decision.

## 2. Source-to-claim matrix

| ID | Source | AstroGuard area supported | What the source supports | Claim boundary |
|---|---|---|---|---|
| NASA-S01 | NASA Space Apps 2026 — Create Health Monitoring Software for Astronauts on Space Missions | Project/challenge alignment | Long-duration missions expose astronauts to multiple health hazards; the challenge asks for software that gathers health indicators and enables astronauts to evaluate and act on health status. | Does not validate AstroGuard implementation, thresholds, clinical accuracy, or award eligibility/result. |
| NASA-S02 | NASA Human Research Program — Risks of Human Spaceflight | Mission-health context | NASA identifies health/performance risks associated with spaceflight, including cardiovascular adaptation, hypoxia and behavioral risks. | Does not prescribe AstroGuard's alert thresholds or classifier. |
| NASA-S03 | NASA Human Research Program — Five Hazards of Human Spaceflight | Mission context/risk model | Identifies space radiation, isolation/confinement, distance from Earth, gravity fields and hostile/closed environments as major hazards. | Hazard identification is not a patient-specific diagnosis or quantitative risk forecast. |
| NASA-S04 | NASA-STD-3001 Volume 1 — Crew Health | Crew-health requirements context | Establishes NASA-level crew-health technical requirements across pre-, in- and post-mission phases. | Referencing the standard does not make AstroGuard compliant, certified, flight-qualified or medically validated. |
| NASA-S05 | NASA-STD-3001 Volume 2 — Human Factors, Habitability, and Environmental Health | Human-system/environment context | Establishes technical requirements for human-rated systems involving human factors, habitability, environmental health, crew interfaces and related systems. | Does not validate the project's synthetic environmental thresholds or dashboard design by itself. |
| NASA-S06 | NASA Human Spaceflight Standards overview | Standards architecture | NASA describes Vol. 1 as crew-health focused and Vol. 2 as human factors/habitability/environmental-health focused. | Useful for document classification, not proof of implementation compliance. |
| NASA-S07 | NASA Human Research Program overview | Research-method context | HRP develops methods to protect astronaut health/performance and conducts research using ground facilities, ISS and analog environments. | Does not establish that AstroGuard participated in or was validated by HRP research. |
| NASA-S08 | NASA Human Factors and Behavioral Performance — Spaceflight Risks | Fatigue/wellbeing and autonomy context | Documents behavioral/performance risks, sleep/workload concerns and the need for systems-operations support for future crews. | Does not validate AstroGuard's synthetic fatigue/wellbeing indices or their numerical cutoffs. |
| NASA-S09 | NASA Human System Risks | Broader mission-risk taxonomy | NASA tracks multiple human-system risks including inflight medical conditions, cardiovascular adaptations, CO2 exposure, hypoxia, sleep/circadian/workload and Earth-independent operations. | A NASA risk category must not be presented as an AstroGuard diagnosis or as evidence that its forecasting model predicts that condition. |

## 3. Traceability by AstroGuard variable

### Heart rate

Scientific context: cardiovascular adaptation is a recognized human-spaceflight health/performance research area (NASA-S02/NASA-S09).

AstroGuard status: heart rate is a relevant synthetic monitoring variable. Current numerical rules remain **engineering/simulation assumptions** unless a threshold-specific source and mission context are documented.

### SpO2

Scientific context: NASA recognizes hypoxia as a human-spaceflight risk (NASA-S02/NASA-S09).

AstroGuard status: SpO2 is used as a synthetic indicator related to oxygenation. This contextual relationship does **not** establish that the current `<94%` and `<90%` software thresholds are NASA limits.

### Body temperature

Scientific context: crew health monitoring and environmental health are within the NASA-STD-3001/HRP framework (NASA-S04/NASA-S05/NASA-S07).

AstroGuard status: body temperature is retained as a synthetic physiological telemetry variable. Current numerical limits require independent threshold provenance before any stronger claim.

### Respiratory rate

Scientific context: respiratory/oxygenation concerns fall within broader crew-health and hypoxia risk contexts (NASA-S02/NASA-S04/NASA-S09).

AstroGuard status: respiratory rate is a synthetic health-monitoring variable. Current numerical cutoffs remain simulation parameters.

### Fatigue and wellbeing indices

Scientific context: NASA identifies behavioral health, inadequate sleep, irregular schedules, workload and human-performance concerns during spaceflight (NASA-S08/NASA-S09).

AstroGuard status: `fatigue_index` and `wellbeing_index` are **project-defined synthetic normalized indices**. NASA sources support the relevance of monitoring human performance/behavioral context but do not validate these indices or their current cutoffs.

### Environmental O2 / pressure / temperature

Scientific context: hostile/closed environments are among NASA's five hazards and NASA-STD-3001 Volume 2 covers environmental health/human-system design (NASA-S03/NASA-S05).

AstroGuard status: environmental telemetry supports the ECLSS simulation context. Individual actuator thresholds in the prototype must remain identified as engineering/synthetic assumptions unless traced to an applicable requirement.

## 4. Decision-support traceability

The Space Apps challenge specifically frames the goal as gathering health indicators and enabling astronauts to evaluate and act on their health status (NASA-S01).

AstroGuard's planned decision-support layer therefore focuses on software explainability:

`telemetry -> encoded rule -> reason code -> software state -> verification/action prompt`

The action prompt must remain non-diagnostic and must not claim to replace medical procedures, flight rules, ground medical support or certified autonomous medical systems.

## 5. Mission autonomy context

Distance from Earth is one of NASA's major human-spaceflight hazards (NASA-S03). NASA's human-factors research also identifies inadequate systems-operations support as a concern for future deep-space crews (NASA-S08).

This supports research into transparent onboard decision-support concepts. It does not demonstrate that AstroGuard is operationally suitable for autonomous medical decision-making.

## 6. Evidence classification policy

Every scientific/technical statement in future AstroGuard documentation should be tagged mentally or explicitly as one of:

1. **NASA/Scientific Context** — directly supported by an identified source.
2. **Engineering Assumption** — project design choice requiring no claim of medical validity.
3. **Synthetic Verification Parameter** — value selected to exercise deterministic software behavior.
4. **Implemented Software Evidence** — demonstrated by source code/test/CI artifacts.
5. **Future Research** — hypothesis or capability not yet implemented/validated.

No item may be promoted from one class to another solely because it appears near a NASA citation.

## 7. Statements currently safe for project documentation

- AstroGuard is a research/simulation prototype for deterministic mission-health telemetry and decision-support experimentation.
- NASA identifies multiple human health and performance risks associated with long-duration human spaceflight.
- NASA-STD-3001 provides NASA technical requirements relevant to crew health, human factors, habitability and environmental health.
- The 2026 Space Apps astronaut-health challenge asks teams to build software that gathers health indicators and enables astronauts to evaluate and act on health status.
- AstroGuard uses synthetic physiological telemetry for software verification.

## 8. Statements that require additional evidence or must not be claimed

Do not claim, without separate evidence:

- NASA validated or approved AstroGuard;
- AstroGuard is NASA-STD-3001 compliant;
- current thresholds are NASA clinical/flight limits;
- the system diagnoses astronaut medical conditions;
- synthetic fatigue/wellbeing scores are validated medical scales;
- the current trend classifier predicts future medical outcomes;
- the prototype is flight-qualified or safe for operational spacecraft control.

## 9. Primary references

- NASA Space Apps Challenge 2026 — Create Health Monitoring Software for Astronauts on Space Missions: https://www.spaceappschallenge.org/2026/challenges/create-health-monitoring-software-for-astronauts-on-space-missions/
- NASA Human Research Program — Risks of Human Spaceflight: https://www.nasa.gov/hrp/risks/
- NASA Human Research Program — Five Hazards of Human Spaceflight: https://www.nasa.gov/hrp/hazards/
- NASA-STD-3001 Volume 1 — Crew Health: https://www.nasa.gov/reference/nasa-std-3001v1/
- NASA-STD-3001 Volume 2 — Human Factors, Habitability, and Environmental Health: https://www.nasa.gov/reference/nasa-std-3001v2/
- NASA Human Spaceflight Standards: https://www.nasa.gov/ochmo/human-spaceflight-and-aviation-standards/
- NASA Human Research Program: https://www.nasa.gov/hrp/
- NASA Human Factors and Behavioral Performance Risks: https://www.nasa.gov/hrp/human-factors-and-behavioral-performance/hfbp-risks/
- NASA Human System Risks: https://www.nasa.gov/hhp/human-system-risks/

## 10. Maintenance rule

Before a future commit changes a synthetic threshold into a claimed science-based threshold, the project must record:

`parameter -> exact source -> applicable population -> mission context -> source value/range -> interpretation -> code location -> verification test`

If that chain is incomplete, the value remains explicitly classified as a simulation/engineering parameter.

---

**Safety boundary:** This source audit improves scientific traceability. It is not evidence of clinical validation, medical-device approval, NASA certification, NASA endorsement, or spacecraft flight qualification.
