#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../src/mission_health_analytics.h"

static int nearf(float a, float b) {
    return fabsf(a - b) < 0.001f;
}

int main(void) {
    const HealthTelemetry degrading[] = {
        {72.0f, 98.0f, 36.7f, 14.0f, 0.10f, 0.90f, HEALTH_NORMAL},
        {80.0f, 96.0f, 36.9f, 16.0f, 0.30f, 0.70f, HEALTH_ATTENTION},
        {88.0f, 94.0f, 37.1f, 18.0f, 0.50f, 0.50f, HEALTH_ATTENTION},
        {102.0f, 90.0f, 37.8f, 22.0f, 0.80f, 0.20f, HEALTH_CRITICAL},
        {108.0f, 88.0f, 38.0f, 24.0f, 0.90f, 0.10f, HEALTH_CRITICAL}
    };
    const HealthTelemetry improving[] = {
        {105.0f, 89.0f, 37.9f, 23.0f, 0.90f, 0.10f, HEALTH_CRITICAL},
        {86.0f, 95.0f, 37.0f, 17.0f, 0.40f, 0.60f, HEALTH_ATTENTION},
        {74.0f, 98.0f, 36.7f, 14.0f, 0.10f, 0.90f, HEALTH_NORMAL}
    };
    MissionHealthAnalytics result;

    assert(mission_health_analyze(NULL, 0U, &result) == -1);
    assert(mission_health_analyze(degrading, 5U, NULL) == -1);

    assert(mission_health_analyze(degrading, 5U, &result) == 0);
    assert(result.sample_count == 5U);
    assert(result.normal_count == 1U);
    assert(result.attention_count == 2U);
    assert(result.critical_count == 2U);
    assert(result.longest_attention_run == 2U);
    assert(result.longest_critical_run == 2U);
    assert(result.trend == TREND_DEGRADING);
    assert(nearf(result.mean_heart_rate_bpm, 90.0f));
    assert(nearf(result.mean_spo2_percent, 93.2f));

    assert(mission_health_analyze(improving, 3U, &result) == 0);
    assert(result.trend == TREND_IMPROVING);
    assert(result.normal_count == 1U);
    assert(result.attention_count == 1U);
    assert(result.critical_count == 1U);

    assert(mission_health_trend_name(TREND_STABLE)[0] == 'S');
    assert(mission_health_trend_name(TREND_IMPROVING)[0] == 'I');
    assert(mission_health_trend_name(TREND_DEGRADING)[0] == 'D');

    const HealthTelemetry spike[] = {
        {72,98,36.7f,16,0.1f,0.9f,HEALTH_NORMAL},
        {72,88,36.7f,16,0.1f,0.9f,HEALTH_CRITICAL},
        {72,98,36.7f,16,0.1f,0.9f,HEALTH_NORMAL}
    };
    assert(mission_health_analyze(spike, 3U, &result) == 0);
    assert(result.trend == TREND_DEGRADING);
    HealthTelemetry invalid = spike[0];
    invalid.spo2_percent = NAN;
    assert(mission_health_analyze(&invalid, 1U, &result) == -3);
    puts("mission_health_analytics: PASS");
    return 0;
}
