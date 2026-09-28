#ifndef ASTROGUARD_DECISION_SUPPORT_H
#define ASTROGUARD_DECISION_SUPPORT_H

#include "health_monitor.h"

/* AstroGuard v2.0 Decision Support Layer
 * Research/simulation prototype only.
 * Reason codes explain encoded software rules; they are not diagnoses.
 */
typedef enum {
    DS_REASON_NONE = 0,
    DS_REASON_INVALID_TELEMETRY,
    DS_REASON_HR_OUTSIDE_SIM_RANGE,
    DS_REASON_SPO2_BELOW_SIM_ATTENTION,
    DS_REASON_SPO2_BELOW_SIM_CRITICAL,
    DS_REASON_BODY_TEMP_OUTSIDE_SIM_RANGE,
    DS_REASON_RESP_RATE_OUTSIDE_SIM_RANGE,
    DS_REASON_FATIGUE_HIGH_SIM,
    DS_REASON_WELLBEING_LOW_SIM,
    DS_REASON_FATIGUE_WELLBEING_SIM_CRITICAL
} DecisionReasonCode;

typedef enum {
    DS_ACTION_CONTINUE_MONITORING = 0,
    DS_ACTION_VERIFY_MEASUREMENT,
    DS_ACTION_VERIFY_SENSOR_OR_DATA,
    DS_ACTION_REVIEW_TREND,
    DS_ACTION_CONSULT_MISSION_PROCEDURE
} DecisionAction;

typedef struct {
    HealthStatus state;
    DecisionReasonCode primary_reason;
    DecisionAction action;
    int attention_condition_count;
    int critical_condition_count;
} DecisionSupportResult;

DecisionSupportResult evaluate_decision_support(const HealthTelemetry *health);
const char *decision_reason_name(DecisionReasonCode reason);
const char *decision_action_name(DecisionAction action);

#endif
