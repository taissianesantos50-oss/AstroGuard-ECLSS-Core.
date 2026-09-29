#ifndef ASTROGUARD_MISSION_SCENARIO_ENGINE_H
#define ASTROGUARD_MISSION_SCENARIO_ENGINE_H

#include "health_monitor.h"

typedef enum {
    SCENARIO_NOMINAL = 0,
    SCENARIO_CABIN_DEGRADATION,
    SCENARIO_LONG_DURATION_STRESS
} MissionScenarioType;

typedef struct {
    float time_s;
    float environmental_o2_percent;
    float pressure_psi;
    float cabin_temp_c;
    int oxygen_valve;
    int heater;
    HealthTelemetry human;
} ScenarioFrame;

const char *mission_scenario_name(MissionScenarioType scenario);
int mission_scenario_frame(MissionScenarioType scenario, unsigned int step, ScenarioFrame *out);

#endif
