# Telemetry Protocol v1.4

| Field | Unit | Description |
|---|---|---|
| Time | simulation step | Mission simulation time |
| O2 | % | Simulated oxygen concentration |
| Pressure | psi | Simulated internal pressure |
| Temp | C | Simulated environmental temperature |
| O2_Valve | 0/1 | Simulated oxygen actuator |
| Heater | 0/1 | Simulated heater |
| HeartRate | bpm | Simulated heart rate |
| SpO2 | % | Simulated blood oxygen saturation |
| BodyTemp | C | Simulated body temperature |
| RespRate | breaths/min | Simulated respiratory rate |
| Fatigue | 0–1 | Simulated fatigue index |
| WellBeing | 0–1 | Simulated self-reported well-being |
| HealthStatus | enum | NORMAL, ATTENTION, or CRITICAL |

All records are generated from deterministic simulation logic. All human-health values are synthetic.
