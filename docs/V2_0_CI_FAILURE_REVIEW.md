# AstroGuard v2.0 — CI failure review (historical)

Date reviewed: 2026-10-13. Scope: GitHub Actions runs #36–#41, as evidenced by user-provided screenshots and repository workflow/commit inspection. This is a research/simulation prototype; CI success is not flight or medical certification.

## Run #36 — link failure (confirmed)
- Failed job: `c-build-and-test`, step compiling the integrated v2.0 decision-support simulation.
- Screenshot log shows linker `undefined reference` errors for `mission_scenario_name` and `mission_scenario_frame`.
- Root cause: build command omitted the implementation module `src/mission_scenario_engine.c` while the simulator referenced its functions.
- Subsequent v2.0 workflow includes the module in the integrated compilation command. Later successful runs support that the build configuration was repaired.

## Run #37 — failure not yet diagnosed
- GitHub Actions history shows failure following a dashboard change to display the active scenario.
- The failing job/step logs were not supplied. Do not assert a root cause without those logs.
- Subsequent green runs indicate later CI success, but do not independently establish the precise fix for #37.

## Run #38 — cabin-degradation assertion mismatch (strongly supported)
- Failed job: `c-build-and-test`, step `Run and verify v2.0 cabin degradation scenario`.
- Screenshot log shows simulator completed 21 synthetic samples (20 NORMAL, 1 ATTENTION, 0 CRITICAL), trend DEGRADING, then exited the shell step with status 1.
- The historical workflow required `CONSULT_MISSION_PROCEDURE` in the cabin telemetry; the later workflow accepts `REVIEW_TREND` or `VERIFY_MEASUREMENT` and asserts ATTENTION and DEGRADING.
- The next run (#39) was green with commit title `ci(v2.0): align cabin scenario assertions with progressive degradation`. This supports an over-strict expected action in the old test. The screenshot alone does not expose which individual shell command returned 1.

## Validation evidence and limitations
- Screenshots show v2.0 runs #39, #40, and #41 succeeded on the v2.0 development branch.
- Screenshots show run #46 succeeded on `main` following the v1.9 PR #3 merge; this **does not** imply v2.0 was merged to `main`.
- No new v2.0 CI run or independent end-to-end validation was performed as part of this review.
- Do not merge v2.0, publish a release, or claim flight readiness solely on this evidence.

## Before a v2.0 release
1. Inspect historical #37 failed step/log to close the remaining diagnosis.
2. Confirm a fresh green CI run on the exact v2.0 release candidate, including all three scenarios and dashboard checks.
3. Review diffs and release notes, verify private-repository permissions, and explicitly approve any merge or tag.
