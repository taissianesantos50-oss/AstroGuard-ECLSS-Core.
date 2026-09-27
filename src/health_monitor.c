#include "health_monitor.h"

/* AstroGuard v1.4 Human Health Monitoring Layer.
 * Thresholds are illustrative simulation parameters only.
 * They are NOT clinical limits or flight-qualified safety logic.
 */
HealthStatus evaluate_health(const HealthTelemetry *h)
{
    int attention=0, critical=0;
    if (!h) return HEALTH_CRITICAL;
    if (h->heart_rate_bpm < 50.0f || h->heart_rate_bpm > 120.0f) attention++;
    if (h->spo2_percent < 94.0f) attention++;
    if (h->body_temp_c < 35.5f || h->body_temp_c > 38.0f) attention++;
    if (h->respiratory_rate_bpm < 10.0f || h->respiratory_rate_bpm > 24.0f) attention++;
    if (h->fatigue_index >= 0.75f) attention++;
    if (h->wellbeing_index <= 0.25f) attention++;
    if (h->spo2_percent < 90.0f) critical++;
    if (h->fatigue_index >= 0.90f && h->wellbeing_index <= 0.15f) critical++;
    if (critical > 0) return HEALTH_CRITICAL;
    if (attention >= 2) return HEALTH_ATTENTION;
    return HEALTH_NORMAL;
}

const char *health_status_name(HealthStatus status)
{
    switch (status) {
        case HEALTH_NORMAL: return "NORMAL";
        case HEALTH_ATTENTION: return "ATTENTION";
        case HEALTH_CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}
