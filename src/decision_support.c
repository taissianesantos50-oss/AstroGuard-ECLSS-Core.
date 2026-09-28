#include "decision_support.h"

static DecisionSupportResult invalid_result(void)
{
    DecisionSupportResult r;
    r.state = HEALTH_CRITICAL;
    r.primary_reason = DS_REASON_INVALID_TELEMETRY;
    r.action = DS_ACTION_VERIFY_SENSOR_OR_DATA;
    r.attention_condition_count = 0;
    r.critical_condition_count = 1;
    return r;
}

DecisionSupportResult evaluate_decision_support(const HealthTelemetry *h)
{
    DecisionSupportResult r;
    int attention = 0;
    int critical = 0;
    DecisionReasonCode first_attention = DS_REASON_NONE;
    DecisionReasonCode first_critical = DS_REASON_NONE;

    if (!h) return invalid_result();

#define ADD_ATTENTION(condition, code) do { \
    if (condition) { \
        attention++; \
        if (first_attention == DS_REASON_NONE) first_attention = (code); \
    } \
} while (0)

#define ADD_CRITICAL(condition, code) do { \
    if (condition) { \
        critical++; \
        if (first_critical == DS_REASON_NONE) first_critical = (code); \
    } \
} while (0)

    ADD_ATTENTION(h->heart_rate_bpm < 50.0f || h->heart_rate_bpm > 120.0f,
                  DS_REASON_HR_OUTSIDE_SIM_RANGE);
    ADD_ATTENTION(h->spo2_percent < 94.0f,
                  DS_REASON_SPO2_BELOW_SIM_ATTENTION);
    ADD_ATTENTION(h->body_temp_c < 35.5f || h->body_temp_c > 38.0f,
                  DS_REASON_BODY_TEMP_OUTSIDE_SIM_RANGE);
    ADD_ATTENTION(h->respiratory_rate_bpm < 10.0f || h->respiratory_rate_bpm > 24.0f,
                  DS_REASON_RESP_RATE_OUTSIDE_SIM_RANGE);
    ADD_ATTENTION(h->fatigue_index >= 0.75f,
                  DS_REASON_FATIGUE_HIGH_SIM);
    ADD_ATTENTION(h->wellbeing_index <= 0.25f,
                  DS_REASON_WELLBEING_LOW_SIM);

    ADD_CRITICAL(h->spo2_percent < 90.0f,
                 DS_REASON_SPO2_BELOW_SIM_CRITICAL);
    ADD_CRITICAL(h->fatigue_index >= 0.90f && h->wellbeing_index <= 0.15f,
                 DS_REASON_FATIGUE_WELLBEING_SIM_CRITICAL);

#undef ADD_ATTENTION
#undef ADD_CRITICAL

    r.attention_condition_count = attention;
    r.critical_condition_count = critical;

    /* Preserve v1.4 state aggregation exactly. */
    r.state = evaluate_health(h);

    if (critical > 0) {
        r.primary_reason = first_critical;
        r.action = DS_ACTION_CONSULT_MISSION_PROCEDURE;
    } else if (attention >= 2) {
        r.primary_reason = first_attention;
        r.action = DS_ACTION_VERIFY_MEASUREMENT;
    } else if (attention == 1) {
        /* Current v1.4 aggregate state remains NORMAL with one attention rule,
         * but v2.0 preserves the reason for explainability and trend review.
         */
        r.primary_reason = first_attention;
        r.action = DS_ACTION_REVIEW_TREND;
    } else {
        r.primary_reason = DS_REASON_NONE;
        r.action = DS_ACTION_CONTINUE_MONITORING;
    }

    return r;
}

const char *decision_reason_name(DecisionReasonCode reason)
{
    switch (reason) {
        case DS_REASON_NONE: return "NONE";
        case DS_REASON_INVALID_TELEMETRY: return "INVALID_TELEMETRY";
        case DS_REASON_HR_OUTSIDE_SIM_RANGE: return "HR_OUTSIDE_SIM_RANGE";
        case DS_REASON_SPO2_BELOW_SIM_ATTENTION: return "SPO2_BELOW_SIM_ATTENTION";
        case DS_REASON_SPO2_BELOW_SIM_CRITICAL: return "SPO2_BELOW_SIM_CRITICAL";
        case DS_REASON_BODY_TEMP_OUTSIDE_SIM_RANGE: return "BODY_TEMP_OUTSIDE_SIM_RANGE";
        case DS_REASON_RESP_RATE_OUTSIDE_SIM_RANGE: return "RESP_RATE_OUTSIDE_SIM_RANGE";
        case DS_REASON_FATIGUE_HIGH_SIM: return "FATIGUE_HIGH_SIM";
        case DS_REASON_WELLBEING_LOW_SIM: return "WELLBEING_LOW_SIM";
        case DS_REASON_FATIGUE_WELLBEING_SIM_CRITICAL: return "FATIGUE_WELLBEING_SIM_CRITICAL";
        default: return "UNKNOWN_REASON";
    }
}

const char *decision_action_name(DecisionAction action)
{
    switch (action) {
        case DS_ACTION_CONTINUE_MONITORING: return "CONTINUE_MONITORING";
        case DS_ACTION_VERIFY_MEASUREMENT: return "VERIFY_MEASUREMENT";
        case DS_ACTION_VERIFY_SENSOR_OR_DATA: return "VERIFY_SENSOR_OR_DATA";
        case DS_ACTION_REVIEW_TREND: return "REVIEW_TREND";
        case DS_ACTION_CONSULT_MISSION_PROCEDURE: return "CONSULT_MISSION_PROCEDURE";
        default: return "UNKNOWN_ACTION";
    }
}
