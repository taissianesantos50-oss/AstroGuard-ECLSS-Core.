#include <math.h>
#include "mission_health_analytics.h"

static int severity(HealthStatus status) {
    switch (status) {
        case HEALTH_NORMAL: return 0;
        case HEALTH_ATTENTION: return 1;
        case HEALTH_CRITICAL: return 2;
        default: return -1;
    }
}

const char *mission_health_trend_name(MissionHealthTrend trend) {
    switch (trend) {
        case TREND_STABLE: return "STABLE";
        case TREND_IMPROVING: return "IMPROVING";
        case TREND_DEGRADING: return "DEGRADING";
        default: return "UNKNOWN";
    }
}

int mission_health_analyze(const HealthTelemetry *samples,
                           size_t sample_count,
                           MissionHealthAnalytics *out) {
    size_t i;
    size_t attention_run = 0;
    size_t critical_run = 0;
    double hr_sum = 0.0;
    double spo2_sum = 0.0;
    double temp_sum = 0.0;
    double resp_sum = 0.0;
    double fatigue_sum = 0.0;
    double wellbeing_sum = 0.0;
    int first_severity;
    int last_severity;

    if (samples == NULL || out == NULL || sample_count == 0U) {
        return -1;
    }

    *out = (MissionHealthAnalytics){0};
    out->sample_count = sample_count;

    first_severity = severity(samples[0].status);
    last_severity = severity(samples[sample_count - 1U].status);
    if (first_severity < 0 || last_severity < 0) {
        return -2;
    }

    for (i = 0U; i < sample_count; ++i) {
        if (severity(samples[i].status) < 0) {
            return -2;
        }
        if (!isfinite(samples[i].heart_rate_bpm) || !isfinite(samples[i].spo2_percent) || !isfinite(samples[i].body_temp_c) || !isfinite(samples[i].respiratory_rate_bpm) || !isfinite(samples[i].fatigue_index) || !isfinite(samples[i].wellbeing_index) || samples[i].heart_rate_bpm < 0.0f || samples[i].respiratory_rate_bpm < 0.0f || samples[i].spo2_percent < 0.0f || samples[i].spo2_percent > 100.0f || samples[i].fatigue_index < 0.0f || samples[i].fatigue_index > 1.0f || samples[i].wellbeing_index < 0.0f || samples[i].wellbeing_index > 1.0f) return -3;

        hr_sum += samples[i].heart_rate_bpm;
        spo2_sum += samples[i].spo2_percent;
        temp_sum += samples[i].body_temp_c;
        resp_sum += samples[i].respiratory_rate_bpm;
        fatigue_sum += samples[i].fatigue_index;
        wellbeing_sum += samples[i].wellbeing_index;

        switch (samples[i].status) {
            case HEALTH_NORMAL:
                ++out->normal_count;
                attention_run = 0U;
                critical_run = 0U;
                break;
            case HEALTH_ATTENTION:
                ++out->attention_count;
                ++attention_run;
                critical_run = 0U;
                if (attention_run > out->longest_attention_run) {
                    out->longest_attention_run = attention_run;
                }
                break;
            case HEALTH_CRITICAL:
                ++out->critical_count;
                ++critical_run;
                attention_run = 0U;
                if (critical_run > out->longest_critical_run) {
                    out->longest_critical_run = critical_run;
                }
                break;
            default:
                return -2;
        }
    }

    out->mean_heart_rate_bpm = (float)(hr_sum / (double)sample_count);
    out->mean_spo2_percent = (float)(spo2_sum / (double)sample_count);
    out->mean_body_temp_c = (float)(temp_sum / (double)sample_count);
    out->mean_respiratory_rate_bpm = (float)(resp_sum / (double)sample_count);
    out->mean_fatigue_index = (float)(fatigue_sum / (double)sample_count);
    out->mean_wellbeing_index = (float)(wellbeing_sum / (double)sample_count);

    if (last_severity > first_severity || (last_severity == first_severity && out->critical_count > 0U && first_severity < 2)) {
        out->trend = TREND_DEGRADING;
    } else if (last_severity < first_severity) {
        out->trend = TREND_IMPROVING;
    } else {
        out->trend = TREND_STABLE;
    }

    return 0;
}
