# AstroGuard ECLSS Core — NASA Space Apps 2026 Submission Evidence Map

Developer: **Taissiane Thais dos Santos**

Status: **RESEARCH & TECHNICAL PREPARATION**

Purpose: create a traceable map between the 2026 challenge, AstroGuard capabilities, implementation evidence, verification evidence, scientific/source evidence, and the material that must be demonstrated in a future challenge-specific submission.

> This document is preparation evidence. It does not claim that the challenge-specific implementation has already been produced during the hackathon.

## 1. Official challenge target

Selected 2026 challenge: **Create Health Monitoring Software for Astronauts on Space Missions**.

Official challenge intent: build health-monitoring software that gathers health indicators and enables astronauts to evaluate and act on the status of their health during space missions.

Official challenge page:
https://www.spaceappschallenge.org/2026/challenges/create-health-monitoring-software-for-astronauts-on-space-missions/

## 2. Evidence classes

Each future submission claim should be supported by one or more of these evidence classes:

- **REQ** — official challenge requirement/context;
- **CODE** — implementation source code;
- **TEST** — deterministic test or verification specification;
- **CI** — automated build/test result;
- **DATA** — generated telemetry/analytics output;
- **UI** — dashboard or visualization evidence;
- **SCI** — scientific/technical source;
- **DOC** — architecture, provenance or scope documentation;
- **DEMO** — reproducible demonstration/video evidence;
- **EVENT** — work specifically produced during the official hackathon window.

## 3. Capability-to-evidence matrix

| Capability / claim | Challenge relationship | Code evidence | Test / CI evidence | Data / UI evidence | Scientific / documentation evidence | Current readiness |
|---|---|---|---|---|---|---|
| Gather physiological indicators | Direct: gathers health indicators | `src/health_monitor.c`, `include/health_monitor.h`, v1.9 integration | existing health-monitor tests + `docs/V2_TEST_PLAN.md` | physiological fields in v1.9 telemetry/dashboard | `docs/SCIENTIFIC_EVIDENCE_MATRIX.md`, `docs/NASA_SCIENTIFIC_SOURCE_AUDIT.md` | Strong prototype evidence |
| Heart-rate monitoring | Health indicator | HealthTelemetry + evaluator | HR boundary/reason-code cases defined in V2 test plan | HR telemetry/dashboard | scientific evidence matrix + threshold provenance | Variable justified; numeric simulation thresholds not NASA-validated |
| SpO2 monitoring | Health indicator | HealthTelemetry + evaluator | SpO2 attention/critical and boundary cases | SpO2 telemetry/dashboard | evidence matrix + provenance table | Variable justified; encoded thresholds remain simulation parameters |
| Body-temperature monitoring | Health indicator | HealthTelemetry + evaluator | low/high temperature boundary cases | temperature telemetry/dashboard | evidence matrix + provenance table | Variable justified; threshold validation pending |
| Respiratory-rate monitoring | Health indicator | HealthTelemetry + evaluator | respiratory boundary cases | respiratory telemetry/dashboard | evidence matrix + provenance table | Variable justified; threshold validation pending |
| Fatigue/wellbeing representation | Behavioral/human-state context | HealthTelemetry + evaluator | synthetic fatigue/wellbeing cases | telemetry/dashboard indices | evidence matrix explicitly labels synthetic indices | Synthetic research variables only |
| Deterministic health-state classification | Helps astronaut evaluate status | `evaluate_health()` -> NORMAL / ATTENTION / CRITICAL | classifier and boundary cases | status field in telemetry/dashboard | threshold provenance + decision-support matrix | Implemented prototype |
| Explain why an alert occurred | Supports evaluation and transparency | reason-code layer is specified, implementation reserved/planned | reason-code cases in V2 test plan | future dashboard reason display | `docs/DECISION_SUPPORT_ACTION_MATRIX.md` | Specification ready; implementation evidence still required |
| Enable an astronaut to act on status | Direct challenge relationship | challenge-specific decision-support implementation still required | action/reason acceptance tests specified | future UI must expose non-diagnostic verification/action guidance | Decision Support Action Matrix | Important implementation gap |
| Persistence of abnormal states | Supports evaluation over time | v1.9 mission-health analytics | persistence tests specified | aggregate analytics CSV/dashboard | v1.9 architecture + V2 test plan | Implemented analytics concept |
| Health trend over mission | Supports longitudinal evaluation | v1.9 STABLE / IMPROVING / DEGRADING analytics | trend tests specified | analytics CSV/dashboard | v1.9 architecture + V2 test plan | Implemented simple deterministic trend |
| Environmental + human telemetry context | Mission-context integration | ECLSS telemetry + human telemetry integration | integrated simulation tests | combined telemetry/dashboard | architecture documentation | Prototype evidence exists |
| Reproducibility | Supports validity | deterministic C pipeline | CI/build/tests | reproducible CSV outputs | architecture/test plan | Strong software-engineering target |
| Scientific traceability | Supports validity | no scientific claim should exist only in code | provenance checks planned | N/A | Scientific Evidence Matrix + NASA Source Audit + Threshold Provenance | Strong documentation; exact threshold sourcing remains open |
| Research/simulation safety boundary | Prevents overclaiming | source comments/output notices | tests should preserve notice | dashboard should display notice | all v2 preparation docs | Explicit |

## 4. Current evidence chain

The intended traceability chain for every important submission statement is:

`Challenge requirement -> AstroGuard capability -> source file/function -> test -> CI result -> generated output -> dashboard/demo -> scientific/source citation`

A claim is considered **submission-ready** only when the relevant links in that chain exist and can be shown to a reviewer.

## 5. Existing repository evidence

### CODE

Key existing technical areas include:

- deterministic ECLSS simulation/control logic;
- `src/health_monitor.c` human-health classification;
- v1.9 mission-health analytics;
- integrated synthetic mission telemetry;
- dashboard/visualization assets.

### TEST

Existing and planned evidence includes:

- health-monitor unit/regression testing;
- mission-health analytics testing;
- integrated v1.9 simulation verification;
- `docs/V2_TEST_PLAN.md` for reason codes, boundaries, persistence, trend, CSV and dashboard consistency.

### DOC

Preparation documentation:

- `SPACE_APPS_2026_READINESS.md`
- `docs/SCIENTIFIC_EVIDENCE_MATRIX.md`
- `docs/THRESHOLD_PROVENANCE_TABLE.md`
- `docs/DECISION_SUPPORT_ACTION_MATRIX.md`
- `docs/V2_TEST_PLAN.md`
- `docs/NASA_SCIENTIFIC_SOURCE_AUDIT.md`
- this evidence map.

## 6. Evidence still required before a final Space Apps submission

### Challenge-specific implementation evidence

The future implementation should provide visible evidence that the astronaut can do more than observe a status. The interface should expose, at minimum:

1. current state;
2. contributing indicator(s);
3. deterministic reason code;
4. trend/persistence context;
5. a non-diagnostic verification/action prompt;
6. clear synthetic/research status of the prototype.

### CI evidence

For the challenge-specific commit/branch, preserve:

- commit SHA;
- workflow/run identifier;
- successful C build;
- unit-test result;
- integration-test result;
- CSV/schema validation result;
- dashboard/static validation result.

### DATA evidence

Preserve a small reproducible demonstration dataset showing at least:

- normal scenario;
- attention scenario;
- critical synthetic scenario;
- recovery/improving scenario where supported;
- reason codes and state transitions.

### DEMO evidence

The final demonstration should visibly connect:

`telemetry -> state -> reason -> trend/persistence -> astronaut-facing action/verification guidance`

The demo must not imply clinical diagnosis or flight qualification.

### SCI evidence

Before changing a synthetic threshold into a scientifically sourced threshold, require:

`exact source -> population -> measurement context -> numeric value -> interpretation -> code location -> test`

If this chain is incomplete, retain the **simulation parameter** label.

## 7. Official submission compliance checklist

Before submission, verify:

- the solution directly addresses the selected Space Apps challenge;
- every external source/resource used is cited;
- license documentation required by the Space Apps participant terms is present and compatible with the materials being submitted;
- third-party assets/code/data have appropriate permissions/licenses;
- project description distinguishes original AstroGuard work, external resources and event-specific work;
- the project page links only to materials intended to be shared as part of the submission;
- no statement implies NASA endorsement, medical validation or spacecraft flight qualification.

## 8. Judging-oriented evidence organization

Where the applicable event uses the standard Space Apps judging dimensions, organize evidence so reviewers can quickly inspect:

- **Impact:** why autonomous health-status awareness matters in long-duration missions;
- **Creativity:** what is distinctive about combining deterministic human telemetry, ECLSS context, explainable reason codes and mission-health analytics;
- **Validity:** tests, CI, reproducibility, scientific traceability and explicit limitations;
- **Relevance:** direct mapping to gathering health indicators and enabling evaluation/action;
- **Presentation:** concise dashboard, reproducible demo, architecture diagram and clear narrative.

This section organizes evidence; it does not predict judging outcomes or awards.

## 9. Event-work evidence boundary

NASA Space Apps 2026 is scheduled for November 14-15, 2026. The official site states that project submission opens November 14 and closes November 15 local time, and encourages participants to submit what they accomplish over the course of the hackathon.

For transparency, preserve an identifiable event-work trail, for example:

- event-specific branch created at the appropriate time;
- first event commit SHA/time;
- event implementation commits;
- event test/CI runs;
- final event commit SHA;
- demo generated from that final event state.

The existing AstroGuard repository history remains evidence of **RESEARCH & TECHNICAL PREPARATION**.

## 10. Intellectual-property and publication note

The 2026 Participant Terms state that submitted solutions must include appropriate license documentation and that sources/resources used in the project must be cited. Submission also grants NASA permissions described in those terms to display and disseminate the submitted solution in support of the Challenge.

Therefore, before submission, the repository/license/publication strategy must be reviewed deliberately. Do not assume that keeping a repository private by itself satisfies submission requirements.

Official Participant Terms:
https://www.spaceappschallenge.org/legal/

## 11. Current status

**Preparation status:** evidence architecture established.

**Major remaining gap:** challenge-specific astronaut-facing decision-support implementation and its event-specific CODE/TEST/CI/DATA/UI/DEMO evidence.

**Scientific status:** physiological variables have contextual support, while current encoded numeric health thresholds remain explicitly illustrative/synthetic unless individually sourced and validated.

**Product status:** research/simulation prototype; not a medical device, clinical diagnostic system, operational spacecraft controller, flight-qualified system, or NASA-endorsed product.
