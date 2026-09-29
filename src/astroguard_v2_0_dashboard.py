import csv
import sys
from pathlib import Path
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


def load(path):
    with path.open(newline="", encoding="utf-8") as f:
        rows = list(csv.DictReader(f))
    if not rows:
        raise ValueError("Telemetry file is empty")
    required = {
        "Scenario", "Time", "O2", "Pressure", "Temp", "HeartRate", "SpO2", "BodyTemp",
        "RespRate", "Fatigue", "WellBeing", "HealthStatus", "ReasonCode",
        "RecommendedAction", "AttentionConditions", "CriticalConditions"
    }
    missing = required.difference(rows[0])
    if missing:
        raise ValueError("Missing v2.0 telemetry fields: " + ", ".join(sorted(missing)))
    return rows


def norm(v, lo, hi):
    return 0.5 if hi == lo else max(0.0, min(1.0, (v - lo) / (hi - lo)))


def draw_spacecraft(ax):
    ax.plot([-0.35, 0.35], [0, 0], [0, 0], linewidth=8)
    ax.plot([-0.35, -0.35], [-0.7, 0.7], [0, 0], linewidth=5)
    ax.plot([0.35, 0.35], [-0.7, 0.7], [0, 0], linewidth=5)
    ax.plot([0.35, 0.65], [0, 0], [0, 0], linewidth=3)
    ax.scatter([0], [0], [0], s=120, marker="s")


def main():
    path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("telemetry_v2_0.csv")
    if not path.exists():
        raise FileNotFoundError(f"{path} not found. Run the AstroGuard v2.0 C simulator first.")

    rows = load(path)
    scenario = rows[0]["Scenario"]
    times = [float(r["Time"]) for r in rows]
    env = [1 - (0.4 * norm(float(r["O2"]), 18, 22) + 0.3 * norm(float(r["Pressure"]), 0, 4.5) + 0.3 * norm(float(r["Temp"]), 10, 22)) for r in rows]
    human = [0.30 * (1 - norm(float(r["SpO2"]), 85, 100)) + 0.25 * norm(float(r["HeartRate"]), 50, 140) + 0.20 * norm(float(r["RespRate"]), 10, 30) + 0.15 * float(r["Fatigue"]) + 0.10 * (1 - float(r["WellBeing"])) for r in rows]

    fig = plt.figure(figsize=(15, 9))
    ax = fig.add_subplot(111, projection="3d")
    ax.set_title(f"ASTROGUARD v2.0 | {scenario} | EXPLAINABLE MISSION HEALTH DECISION SUPPORT")
    ax.set_xlabel("Mission Time")
    ax.set_ylabel("Environmental Stress")
    ax.set_zlabel("Human Stress")
    ax.set_xlim(min(times), max(times) if max(times) > min(times) else min(times) + 1)
    ax.set_ylim(0, 1)
    ax.set_zlim(0, 1)
    ax.view_init(elev=24, azim=-58)

    line, = ax.plot([], [], [], linewidth=2)
    point, = ax.plot([], [], [], marker="o", markersize=9)
    draw_spacecraft(ax)
    telemetry_panel = ax.text2D(0.01, 0.97, "", transform=ax.transAxes, va="top", family="monospace")
    decision_panel = ax.text2D(0.64, 0.97, "", transform=ax.transAxes, va="top", family="monospace")
    notice = ax.text2D(0.01, 0.02, "RESEARCH / SIMULATION PROTOTYPE | Synthetic human-health telemetry | Not a medical diagnosis", transform=ax.transAxes, family="monospace", fontsize=8)

    def update(i):
        line.set_data(times[: i + 1], env[: i + 1])
        line.set_3d_properties(human[: i + 1])
        point.set_data([times[i]], [env[i]])
        point.set_3d_properties([human[i]])
        r = rows[i]
        status = r["HealthStatus"]
        mission_status = {"NORMAL": "NOMINAL", "ATTENTION": "ATTENTION REQUIRED", "CRITICAL": "CRITICAL ALERT"}.get(status, "UNKNOWN")
        env_status = "STABLE" if env[i] < 0.35 else "DEGRADED"
        human_status = "LOW" if human[i] < 0.35 else "ELEVATED"

        telemetry_panel.set_text(
            "ASTROGUARD CORE v2.0\n"
            f"SCENARIO   {r['Scenario']}\nTIME       {r['Time']} s\nHEALTH     {status}\n"
            f"HR         {r['HeartRate']} bpm\nSpO2       {r['SpO2']} %\nBODY TEMP  {r['BodyTemp']} C\n"
            f"RESP       {r['RespRate']} bpm\nFATIGUE    {r['Fatigue']}\nWELLBEING  {r['WellBeing']}\n"
            f"O2 ENV     {r['O2']} %\nPRESSURE   {r['Pressure']} psi\nCABIN TEMP {r['Temp']} C"
        )
        decision_panel.set_text(
            "MISSION DECISION SUPPORT\n"
            f"STATUS   {mission_status}\nREASON   {r['ReasonCode']}\nACTION   {r['RecommendedAction']}\n"
            f"ATTN #   {r['AttentionConditions']}\nCRIT #   {r['CriticalConditions']}\n\n"
            f"ENVIRONMENT  {env_status}\nHUMAN LOAD   {human_status}\n\n"
            "WHY?  Encoded deterministic rule\nNEXT? Follow the displayed verification/action"
        )
        return line, point, telemetry_panel, decision_panel, notice

    animation = FuncAnimation(fig, update, frames=len(rows), interval=500, blit=False, repeat=True)
    _ = animation
    print(f"Loaded {len(rows)} v2.0 frames | scenario={scenario} | source={path}")
    plt.show()


if __name__ == "__main__":
    main()
