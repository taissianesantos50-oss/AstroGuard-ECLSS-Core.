#ifndef ASTROGUARD_HEALTH_MONITOR_H
#define ASTROGUARD_HEALTH_MONITOR_H

typedef enum { HEALTH_NORMAL=0, HEALTH_ATTENTION=1, HEALTH_CRITICAL=2 } HealthStatus;

typedef struct {
    float heart_rate_bpm;
    float spo2_percent;
    float body_temp_c;
    float respiratory_rate_bpm;
    float fatigue_index;
    float wellbeing_index;
    HealthStatus status;
} HealthTelemetry;

HealthStatus evaluate_health(const HealthTelemetry *health);
const char *health_status_name(HealthStatus status);

#endif
