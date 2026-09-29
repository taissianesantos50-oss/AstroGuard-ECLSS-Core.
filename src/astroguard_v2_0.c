#include <stdio.h>
#include <string.h>
#include "health_monitor.h"
#include "mission_health_analytics.h"
#include "decision_support.h"
#include "mission_scenario_engine.h"

#define SAMPLE_COUNT 21U

typedef struct {
    MissionScenarioType scenario;
    ScenarioFrame frame;
    DecisionSupportResult decision;
} MissionTelemetryV2;

static MissionScenarioType parse_scenario(int argc, char **argv)
{
    if (argc < 2) return SCENARIO_CABIN_DEGRADATION;
    if (strcmp(argv[1], "nominal") == 0) return SCENARIO_NOMINAL;
    if (strcmp(argv[1], "cabin") == 0) return SCENARIO_CABIN_DEGRADATION;
    if (strcmp(argv[1], "long-duration") == 0) return SCENARIO_LONG_DURATION_STRESS;
    return (MissionScenarioType)-1;
}

static void write_telemetry_row(FILE *file, const MissionTelemetryV2 *m)
{
    const ScenarioFrame *f = &m->frame;
    fprintf(file,
        "%s,%.1f,%.2f,%.2f,%.2f,%d,%d,%.1f,%.1f,%.1f,%.1f,%.2f,%.2f,%s,%s,%s,%d,%d\n",
        mission_scenario_name(m->scenario), f->time_s, f->environmental_o2_percent,
        f->pressure_psi, f->cabin_temp_c, f->oxygen_valve, f->heater,
        f->human.heart_rate_bpm, f->human.spo2_percent, f->human.body_temp_c,
        f->human.respiratory_rate_bpm, f->human.fatigue_index, f->human.wellbeing_index,
        health_status_name(m->decision.state),
        decision_reason_name(m->decision.primary_reason),
        decision_action_name(m->decision.action),
        m->decision.attention_condition_count, m->decision.critical_condition_count);
}

static int write_analytics(const MissionHealthAnalytics *a, MissionScenarioType scenario)
{
    FILE *file = fopen("mission_health_analytics_v2_0.csv", "w");
    if (!file) return -1;
    fprintf(file,
        "Scenario,SampleCount,NormalCount,AttentionCount,CriticalCount,LongestAttentionRun,"
        "LongestCriticalRun,MeanHeartRate,MeanSpO2,MeanBodyTemp,MeanRespRate,"
        "MeanFatigue,MeanWellBeing,Trend\n");
    fprintf(file,
        "%s,%zu,%zu,%zu,%zu,%zu,%zu,%.2f,%.2f,%.2f,%.2f,%.3f,%.3f,%s\n",
        mission_scenario_name(scenario), a->sample_count, a->normal_count,
        a->attention_count, a->critical_count, a->longest_attention_run,
        a->longest_critical_run, a->mean_heart_rate_bpm, a->mean_spo2_percent,
        a->mean_body_temp_c, a->mean_respiratory_rate_bpm, a->mean_fatigue_index,
        a->mean_wellbeing_index, mission_health_trend_name(a->trend));
    fclose(file);
    return 0;
}

int main(int argc, char **argv)
{
    MissionScenarioType scenario = parse_scenario(argc, argv);
    FILE *telemetry;
    HealthTelemetry health_samples[SAMPLE_COUNT];
    MissionHealthAnalytics analytics;

    if ((int)scenario < 0) {
        fprintf(stderr, "Usage: %s [nominal|cabin|long-duration]\n", argv[0]);
        return 1;
    }

    telemetry = fopen("telemetry_v2_0.csv", "w");
    if (!telemetry) return 2;

    fprintf(telemetry,
        "Scenario,Time,O2,Pressure,Temp,O2_Valve,Heater,HeartRate,SpO2,BodyTemp,RespRate,"
        "Fatigue,WellBeing,HealthStatus,ReasonCode,RecommendedAction,AttentionConditions,CriticalConditions\n");

    for (unsigned int t = 0U; t < SAMPLE_COUNT; ++t) {
        MissionTelemetryV2 m;
        m.scenario = scenario;
        if (mission_scenario_frame(scenario, t, &m.frame) != 0) {
            fclose(telemetry);
            return 3;
        }
        m.decision = evaluate_decision_support(&m.frame.human);
        m.frame.human.status = m.decision.state;
        health_samples[t] = m.frame.human;
        write_telemetry_row(telemetry, &m);
    }
    fclose(telemetry);

    if (mission_health_analyze(health_samples, SAMPLE_COUNT, &analytics) != 0) return 4;
    if (write_analytics(&analytics, scenario) != 0) return 5;

    printf("ASTROGUARD ECLSS CORE v2.0 - MISSION SCENARIO DECISION SUPPORT\n");
    printf("Scenario: %s\n", mission_scenario_name(scenario));
    printf("Samples: %zu | NORMAL: %zu | ATTENTION: %zu | CRITICAL: %zu\n",
        analytics.sample_count, analytics.normal_count, analytics.attention_count, analytics.critical_count);
    printf("Trend: %s\n", mission_health_trend_name(analytics.trend));
    printf("Research/simulation prototype; synthetic health telemetry; not a medical diagnosis.\n");
    return 0;
}
