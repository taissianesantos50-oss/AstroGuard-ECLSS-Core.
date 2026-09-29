#include <assert.h>
#include <stdio.h>
#include "mission_scenario_engine.h"

int main(void)
{
    ScenarioFrame a, b, c;

    assert(mission_scenario_frame(SCENARIO_NOMINAL, 0U, &a) == 0);
    assert(mission_scenario_frame(SCENARIO_NOMINAL, 20U, &b) == 0);
    assert(a.environmental_o2_percent == b.environmental_o2_percent);
    assert(a.human.heart_rate_bpm == b.human.heart_rate_bpm);
    assert(b.human.status == HEALTH_NORMAL);

    assert(mission_scenario_frame(SCENARIO_CABIN_DEGRADATION, 6U, &a) == 0);
    assert(mission_scenario_frame(SCENARIO_CABIN_DEGRADATION, 20U, &b) == 0);
    assert(b.environmental_o2_percent < a.environmental_o2_percent);
    assert(b.pressure_psi < a.pressure_psi);
    assert(b.human.spo2_percent < a.human.spo2_percent);
    assert(b.human.fatigue_index > a.human.fatigue_index);

    assert(mission_scenario_frame(SCENARIO_LONG_DURATION_STRESS, 0U, &a) == 0);
    assert(mission_scenario_frame(SCENARIO_LONG_DURATION_STRESS, 20U, &b) == 0);
    assert(b.human.fatigue_index > a.human.fatigue_index);
    assert(b.human.wellbeing_index < a.human.wellbeing_index);
    assert(b.human.heart_rate_bpm > a.human.heart_rate_bpm);

    assert(mission_scenario_frame(SCENARIO_LONG_DURATION_STRESS, 10U, &a) == 0);
    assert(mission_scenario_frame(SCENARIO_LONG_DURATION_STRESS, 10U, &c) == 0);
    assert(a.human.heart_rate_bpm == c.human.heart_rate_bpm);
    assert(a.human.fatigue_index == c.human.fatigue_index);

    assert(mission_scenario_frame(SCENARIO_NOMINAL, 21U, &a) != 0);
    assert(mission_scenario_frame(SCENARIO_NOMINAL, 0U, NULL) != 0);
    assert(mission_scenario_frame((MissionScenarioType)99, 0U, &a) != 0);

    puts("AstroGuard v2.0 mission scenario engine tests: PASS");
    return 0;
}
