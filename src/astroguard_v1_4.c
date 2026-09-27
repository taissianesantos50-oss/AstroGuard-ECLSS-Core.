#include <stdio.h>
#include "health_monitor.h"

/* ASTROGUARD-ECLSS-CORE v1.4
 * Human Health Monitoring Layer
 * Developer: Taissiane Thais dos Santos
 * Research/simulation prototype. Human values and thresholds are synthetic.
 *
 * Demonstration scenario:
 * 0-7   NORMAL baseline
 * 8-13  ATTENTION conditions
 * 14-20 CRITICAL conditions
 *
 * These transitions are intentionally synthetic so the integrated simulation
 * exercises every decision state for software verification/demonstration.
 */
typedef struct {
    float time, o2, pressure, temp;
    int o2_valve, heater;
    HealthTelemetry human;
} MissionTelemetry;

static void print_row(FILE *file, const MissionTelemetry *m)
{
    const char *s = health_status_name(m->human.status);

    printf("%.1f,%.2f,%.2f,%.2f,%d,%d,%.1f,%.1f,%.1f,%.1f,%.2f,%.2f,%s\n",
        m->time, m->o2, m->pressure, m->temp, m->o2_valve, m->heater,
        m->human.heart_rate_bpm, m->human.spo2_percent,
        m->human.body_temp_c, m->human.respiratory_rate_bpm,
        m->human.fatigue_index, m->human.wellbeing_index, s);

    if (file) {
        fprintf(file, "%.1f,%.2f,%.2f,%.2f,%d,%d,%.1f,%.1f,%.1f,%.1f,%.2f,%.2f,%s\n",
            m->time, m->o2, m->pressure, m->temp, m->o2_valve, m->heater,
            m->human.heart_rate_bpm, m->human.spo2_percent,
            m->human.body_temp_c, m->human.respiratory_rate_bpm,
            m->human.fatigue_index, m->human.wellbeing_index, s);
    }
}

int main(void)
{
    FILE *file = fopen("telemetry_v1_4.csv", "w");

    MissionTelemetry m = {
        0.0f, 21.5f, 4.30f, 21.0f, 0, 0,
        {72.0f, 98.0f, 36.7f, 16.0f, 0.10f, 0.90f, HEALTH_NORMAL}
    };

    if (!file) {
        printf("ERROR: could not create telemetry_v1_4.csv\n");
        return 1;
    }

    fprintf(file,
        "Time,O2,Pressure,Temp,O2_Valve,Heater,HeartRate,SpO2,"
        "BodyTemp,RespRate,Fatigue,WellBeing,HealthStatus\n");

    printf("ASTROGUARD ECLSS CORE v1.4\n");
    printf("Human Health Monitoring Layer\n");
    printf("Developer: Taissiane Thais dos Santos\n");
    printf("Integrated verification scenario: NORMAL -> ATTENTION -> CRITICAL\n\n");
    printf("Time,O2,Pressure,Temp,O2_Valve,Heater,HeartRate,SpO2,"
           "BodyTemp,RespRate,Fatigue,WellBeing,HealthStatus\n");

    for (int t = 0; t <= 20; t++) {
        m.time = (float)t;

        if (t > 5) {
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

        /*
         * Synthetic demonstration phases. These values are not clinical
         * thresholds and must not be interpreted as medical guidance.
         */
        if (t >= 8 && t < 14) {
            m.human.heart_rate_bpm = 130.0f;
            m.human.fatigue_index = 0.80f;
        }

        if (t >= 14) {
            m.human.heart_rate_bpm = 135.0f;
            m.human.spo2_percent = 88.0f;
            m.human.respiratory_rate_bpm = 25.0f;
            m.human.fatigue_index = 0.92f;
            m.human.wellbeing_index = 0.12f;
        }

        if (m.pressure < 0.0f) {
            m.pressure = 0.0f;
        }

        m.o2_valve = (m.o2 < 20.0f) ? 1 : 0;
        m.heater = (m.temp < 15.0f) ? 1 : 0;

        m.human.status = evaluate_health(&m.human);
        print_row(file, &m);
    }

    fclose(file);

    printf("\nSIMULATION COMPLETE.\n");
    printf("Telemetry: telemetry_v1_4.csv\n");
    printf("All human-health values are synthetic.\n");

    return 0;
}
