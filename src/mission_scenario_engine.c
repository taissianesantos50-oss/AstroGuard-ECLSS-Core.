#include <stddef.h>
#include "mission_scenario_engine.h"

static ScenarioFrame baseline(unsigned int step)
{
    ScenarioFrame f;
    f.time_s = (float)step;
    f.environmental_o2_percent = 21.5f;
    f.pressure_psi = 4.30f;
    f.cabin_temp_c = 21.0f;
    f.oxygen_valve = 0;
    f.heater = 0;
    f.human.heart_rate_bpm = 72.0f;
    f.human.spo2_percent = 98.0f;
    f.human.body_temp_c = 36.7f;
    f.human.respiratory_rate_bpm = 16.0f;
    f.human.fatigue_index = 0.10f;
    f.human.wellbeing_index = 0.90f;
    f.human.status = HEALTH_NORMAL;
    return f;
}

const char *mission_scenario_name(MissionScenarioType scenario)
{
    switch (scenario) {
        case SCENARIO_NOMINAL: return "NOMINAL";
        case SCENARIO_CABIN_DEGRADATION: return "CABIN_DEGRADATION";
        case SCENARIO_LONG_DURATION_STRESS: return "LONG_DURATION_STRESS";
        default: return "UNKNOWN_SCENARIO";
    }
}

int mission_scenario_frame(MissionScenarioType scenario, unsigned int step, ScenarioFrame *out)
{
    ScenarioFrame f;
    float active;

    if (out == NULL || step > 20U) return -1;
    f = baseline(step);

    switch (scenario) {
        case SCENARIO_NOMINAL:
            /* Stable synthetic baseline for regression/reference runs. */
            break;

        case SCENARIO_CABIN_DEGRADATION:
            if (step > 5U) {
                active = (float)(step - 5U);
                f.environmental_o2_percent -= 0.15f * active;
                f.pressure_psi -= 0.06f * active;
                f.cabin_temp_c -= 0.45f * active;
                f.human.heart_rate_bpm += 2.2f * active;
                f.human.spo2_percent -= 0.45f * active;
                f.human.respiratory_rate_bpm += 0.55f * active;
                f.human.fatigue_index += 0.04f * active;
                f.human.wellbeing_index -= 0.035f * active;
            }
            break;

        case SCENARIO_LONG_DURATION_STRESS:
            /* Synthetic cumulative workload/isolation-style scenario.
             * This does not model or diagnose a specific medical condition.
             */
            active = (float)step;
            f.human.heart_rate_bpm += 1.7f * active;
            f.human.respiratory_rate_bpm += 0.38f * active;
            f.human.fatigue_index += 0.043f * active;
            f.human.wellbeing_index -= 0.039f * active;
            f.human.spo2_percent -= 0.12f * active;
            f.cabin_temp_c -= 0.08f * active;
            break;

        default:
            return -2;
    }

    if (f.environmental_o2_percent < 0.0f) f.environmental_o2_percent = 0.0f;
    if (f.pressure_psi < 0.0f) f.pressure_psi = 0.0f;
    if (f.human.fatigue_index > 1.0f) f.human.fatigue_index = 1.0f;
    if (f.human.wellbeing_index < 0.0f) f.human.wellbeing_index = 0.0f;

    f.oxygen_valve = (f.environmental_o2_percent < 20.0f) ? 1 : 0;
    f.heater = (f.cabin_temp_c < 15.0f) ? 1 : 0;
    f.human.status = evaluate_health(&f.human);
    *out = f;
    return 0;
}
