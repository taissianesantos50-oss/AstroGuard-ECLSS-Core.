#ifndef ASTROGUARD_MISSION_HEALTH_ANALYTICS_H
#define ASTROGUARD_MISSION_HEALTH_ANALYTICS_H

#include <stddef.h>
#include "health_monitor.h"

typedef enum {
    TREND_STABLE = 0,
    TREND_IMPROVING = 1,
    TREND_DEGRADING = 2
} MissionHealthTrend;

typedef struct {
    size_t sample_count;
    size_t normal_count;
    size_t attention_count;
    size_t critical_count;
    size_t longest_attention_run;
    size_t longest_critical_run;
    float mean_heart_rate_bpm;
    float mean_spo2_percent;
    float mean_body_temp_c;
    float mean_respiratory_rate_bpm;
    float mean_fatigue_index;
    float mean_wellbeing_index;
    MissionHealthTrend trend;
} MissionHealthAnalytics;

int mission_health_analyze(const HealthTelemetry *samples,
                           size_t sample_count,
                           MissionHealthAnalytics *out);

const char *mission_health_trend_name(MissionHealthTrend trend);

#endif
