#include <assert.h>
#include <stdio.h>
#include "decision_support.h"

static HealthTelemetry nominal(void)
{
    HealthTelemetry h = {75.0f, 98.0f, 36.7f, 16.0f, 0.20f, 0.80f, HEALTH_NORMAL};
    return h;
}

int main(void)
{
    DecisionSupportResult r;
    HealthTelemetry h;

    h = nominal();
    r = evaluate_decision_support(&h);
    assert(r.state == HEALTH_NORMAL);
    assert(r.primary_reason == DS_REASON_NONE);
    assert(r.action == DS_ACTION_CONTINUE_MONITORING);

    h = nominal(); h.heart_rate_bpm = 49.99f;
    r = evaluate_decision_support(&h);
    assert(r.state == HEALTH_NORMAL);
    assert(r.primary_reason == DS_REASON_HR_OUTSIDE_SIM_RANGE);
    assert(r.action == DS_ACTION_REVIEW_TREND);

    h = nominal(); h.heart_rate_bpm = 50.0f;
    r = evaluate_decision_support(&h);
    assert(r.primary_reason == DS_REASON_NONE);

    h = nominal(); h.spo2_percent = 93.99f;
    r = evaluate_decision_support(&h);
    assert(r.primary_reason == DS_REASON_SPO2_BELOW_SIM_ATTENTION);
    assert(r.state == HEALTH_NORMAL);

    h = nominal(); h.spo2_percent = 94.0f;
    r = evaluate_decision_support(&h);
    assert(r.primary_reason == DS_REASON_NONE);

    h = nominal(); h.spo2_percent = 89.99f;
    r = evaluate_decision_support(&h);
    assert(r.state == HEALTH_CRITICAL);
    assert(r.primary_reason == DS_REASON_SPO2_BELOW_SIM_CRITICAL);
    assert(r.action == DS_ACTION_CONSULT_MISSION_PROCEDURE);

    h = nominal(); h.spo2_percent = 90.0f;
    r = evaluate_decision_support(&h);
    assert(r.state == HEALTH_NORMAL);
    assert(r.primary_reason == DS_REASON_SPO2_BELOW_SIM_ATTENTION);

    h = nominal(); h.heart_rate_bpm = 130.0f; h.respiratory_rate_bpm = 25.0f;
    r = evaluate_decision_support(&h);
    assert(r.state == HEALTH_ATTENTION);
    assert(r.attention_condition_count == 2);
    assert(r.primary_reason == DS_REASON_HR_OUTSIDE_SIM_RANGE);
    assert(r.action == DS_ACTION_VERIFY_MEASUREMENT);

    h = nominal(); h.fatigue_index = 0.90f; h.wellbeing_index = 0.15f;
    r = evaluate_decision_support(&h);
    assert(r.state == HEALTH_CRITICAL);
    assert(r.primary_reason == DS_REASON_FATIGUE_WELLBEING_SIM_CRITICAL);

    r = evaluate_decision_support(NULL);
    assert(r.state == HEALTH_CRITICAL);
    assert(r.primary_reason == DS_REASON_INVALID_TELEMETRY);
    assert(r.action == DS_ACTION_VERIFY_SENSOR_OR_DATA);

    assert(decision_reason_name(DS_REASON_SPO2_BELOW_SIM_CRITICAL) != NULL);
    assert(decision_action_name(DS_ACTION_REVIEW_TREND) != NULL);

    puts("AstroGuard v2.0 decision-support tests: PASS");
    return 0;
}
