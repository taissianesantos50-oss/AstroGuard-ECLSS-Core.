#include <stdio.h>
#include "health_monitor.h"
#include "mission_health_analytics.h"
#include "decision_support.h"

#define SAMPLE_COUNT 21U

typedef struct {
    float time, o2, pressure, temp;
    int o2_valve, heater;
    HealthTelemetry human;
    DecisionSupportResult decision;
} MissionTelemetryV2;

static void write_telemetry_row(FILE *file, const MissionTelemetryV2 *m)
{
    fprintf(file,
        "%.1f,%.2f,%.2f,%.2f,%d,%d,%.1f,%.1f,%.1f,%.1f,%.2f,%.2f,%s,%s,%s,%d,%d\n",
        m->time, m->o2, m->pressure, m->temp, m->o2_valve, m->heater,
        m->human.heart_rate_bpm, m->human.spo2_percent,
        m->human.body_temp_c, m->human.respiratory_rate_bpm,
        m->human.fatigue_index, m->human.wellbeing_index,
        health_status_name(m->decision.state),
        decision_reason_name(m->decision.primary_reason),
        decision_action_name(m->decision.action),
        m->decision.attention_condition_count,
        m->decision.critical_condition_count);
}

static int write_analytics(const MissionHealthAnalytics *a)
{
    FILE *file = fopen("mission_health_analytics_v2_0.csv", "w");
    if (!file) return -1;
    fprintf(file,
        "SampleCount,NormalCount,AttentionCount,CriticalCount,LongestAttentionRun,"
        "LongestCriticalRun,MeanHeartRate,MeanSpO2,MeanBodyTemp,MeanRespRate,"
        "MeanFatigue,MeanWellBeing,Trend\n");
    fprintf(file,
        "%zu,%zu,%zu,%zu,%zu,%zu,%.2f,%.2f,%.2f,%.2f,%.3f,%.3f,%s\n",
        a->sample_count, a->normal_count, a->attention_count, a->critical_count,
        a->longest_attention_run, a->longest_critical_run,
        a->mean_heart_rate_bpm, a->mean_spo2_percent, a->mean_body_temp_c,
        a->mean_respiratory_rate_bpm, a->mean_fatigue_index,
        a->mean_wellbeing_index, mission_health_trend_name(a->trend));
    fclose(file);
    return 0;
}

int main(void)
{
    FILE *telemetry = fopen("telemetry_v2_0.csv", "w");
    HealthTelemetry health_samples[SAMPLE_COUNT];
    MissionHealthAnalytics analytics;
    MissionTelemetryV2 m = {
        0.0f, 21.5f, 4.30f, 21.0f, 0, 0,
        {72.0f, 98.0f, 36.7f, 16.0f, 0.10f, 0.90f, HEALTH_NORMAL},
        {HEALTH_NORMAL, DS_REASON_NONE, DS_ACTION_CONTINUE_MONITORING, 0, 0}
    };

    if (!telemetry) {
        fprintf(stderr, "ERROR: could not create telemetry_v2_0.csv\n");
        return 1;
    }

    fprintf(telemetry,
        "Time,O2,Pressure,Temp,O2_Valve,Heater,HeartRate,SpO2,BodyTemp,RespRate,"
        "Fatigue,WellBeing,HealthStatus,ReasonCode,RecommendedAction,"
        "AttentionConditions,CriticalConditions\n");

    for (unsigned int t = 0U; t < SAMPLE_COUNT; ++t) {
        m.time = (float)t;

        if (t > 5U) {
            m.temp -= 0.65f;
            m.pressure -= 0.04f * (float)t;
            m.o2 -= 0.15f;
            m.human.heart_rate_bpm += 1.8f;
            m.human.spo2_percent -= 0.28f;
            m.human.body_temp_c -= 0.015f;
            m.human.respiratory_rate_bpm += 0.45f;
            m.human.fatigue_index += 0.035f;
            m.human.wellbeing_index -= 0.030f;
        }

        if (t >= 8U && t < 14U) {
            m.human.heart_rate_bpm = 130.0f;
            m.human.fatigue_index = 0.80f;
        }
        if (t >= 14U) {
            m.human.heart_rate_bpm = 135.0f;
            m.human.spo2_percent = 88.0f;
            m.human.respiratory_rate_bpm = 25.0f;
            m.human.fatigue_index = 0.92f;
            m.human.wellbeing_index = 0.12f;
        }

        if (m.pressure < 0.0f) m.pressure = 0.0f;
        m.o2_valve = (m.o2 < 20.0f) ? 1 : 0;
        m.heater = (m.temp < 15.0f) ? 1 : 0;

        m.decision = evaluate_decision_support(&m.human);
        m.human.status = m.decision.state;
        health_samples[t] = m.human;
        write_telemetry_row(telemetry, &m);
    }

    fclose(telemetry);

    if (mission_health_analyze(health_samples, SAMPLE_COUNT, &analytics) != 0) {
        fprintf(stderr, "ERROR: mission health analytics failed\n");
        return 2;
    }
    if (write_analytics(&analytics) != 0) {
        fprintf(stderr, "ERROR: could not create analytics output\n");
        return 3;
    }

    printf("ASTROGUARD ECLSS CORE v2.0 - EXPLAINABLE DECISION SUPPORT\n");
    printf("Samples: %zu | NORMAL: %zu | ATTENTION: %zu | CRITICAL: %zu\n",
        analytics.sample_count, analytics.normal_count,
        analytics.attention_count, analytics.critical_count);
    printf("Trend: %s\n", mission_health_trend_name(analytics.trend));
    printf("Telemetry: telemetry_v2_0.csv\n");
    printf("Analytics: mission_health_analytics_v2_0.csv\n");
    printf("Research/simulation prototype. Synthetic human-health telemetry.\n");
    printf("Reason codes explain software rules and are not medical diagnoses.\n");
    return 0;
}
