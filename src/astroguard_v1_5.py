import csv, sys
from pathlib import Path
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def load(path):
    with path.open(newline="", encoding="utf-8") as f:
        rows = list(csv.DictReader(f))
    if not rows:
        raise ValueError("Telemetry file is empty")
    return rows

def norm(v, lo, hi):
    return 0.5 if hi == lo else max(0.0, min(1.0, (v-lo)/(hi-lo)))

def draw_spacecraft(ax):
    # Simplified conceptual spacecraft geometry for visual orientation.
    ax.plot([-0.35,0.35],[0,0],[0,0],linewidth=8)
    ax.plot([-0.35,-0.35],[-0.7,0.7],[0,0],linewidth=5)
    ax.plot([0.35,0.35],[-0.7,0.7],[0,0],linewidth=5)
    ax.plot([0.35,0.65],[0,0],[0,0],linewidth=3)
    ax.scatter([0],[0],[0],s=120,marker="s")

def main():
    default=Path("telemetry_v1_4.csv")
    sample=Path("telemetry/sample_health_telemetry.csv")
    path=Path(sys.argv[1]) if len(sys.argv)>1 else (default if default.exists() else sample)
    rows=load(path)
    times=[float(r["Time"]) for r in rows]
    env=[1-(0.4*norm(float(r["O2"]),18,22)+0.3*norm(float(r["Pressure"]),0,4.5)+0.3*norm(float(r["Temp"]),10,22)) for r in rows]
    human=[0.30*(1-norm(float(r["SpO2"]),85,100))+0.25*norm(float(r["HeartRate"]),50,140)+0.20*norm(float(r["RespRate"]),10,30)+0.15*float(r["Fatigue"])+0.10*(1-float(r["WellBeing"])) for r in rows]

    fig=plt.figure(figsize=(14,8))
    ax=fig.add_subplot(111,projection="3d")
    ax.set_title("ASTROGUARD v1.5 | 3D MISSION TELEMETRY")
    ax.set_xlabel("Mission Time")
    ax.set_ylabel("Environmental Stress")
    ax.set_zlabel("Human Stress")
    ax.set_xlim(min(times),max(times) if max(times)>min(times) else min(times)+1)
    ax.set_ylim(0,1)
    ax.set_zlim(0,1)
    ax.view_init(elev=24,azim=-58)

    line,=ax.plot([],[],[],linewidth=2)
    point,=ax.plot([],[],[],marker="o",markersize=9)
    draw_spacecraft(ax)
    panel=ax.text2D(0.02,0.96,"",transform=ax.transAxes,va="top",family="monospace")
    alert=ax.text2D(0.70,0.96,"",transform=ax.transAxes,va="top",family="monospace")

    def update(i):
        line.set_data(times[:i+1],env[:i+1])
        line.set_3d_properties(human[:i+1])
        point.set_data([times[i]],[env[i]])
        point.set_3d_properties([human[i]])
        r=rows[i]
        status=r["HealthStatus"]
        mission_status={"NORMAL":"NOMINAL","ATTENTION":"ATTENTION REQUIRED","CRITICAL":"CRITICAL ALERT"}.get(status,"UNKNOWN")
        env_status="STABLE" if env[i]<0.35 else "DEGRADED"
        human_status="LOW" if human[i]<0.35 else "ELEVATED"
        panel.set_text(
            "ASTROGUARD CORE\n"
            f"TIME      {r['Time']} s\n"
            f"HEALTH    {status}\n"
            f"HR        {r['HeartRate']} bpm\n"
            f"SpO2      {r['SpO2']} %\n"
            f"RESP      {r['RespRate']} bpm\n"
            f"O2        {r['O2']} %\n"
            f"PRESSURE  {r['Pressure']} psi\n"
            f"TEMP      {r['Temp']} C"
        )
        alert.set_text(
            "MISSION STATUS\n"
            f"{mission_status}\n\n"
            f"ENVIRONMENT  {env_status}\n"
            f"HUMAN LOAD   {human_status}"
        )
        return line,point,panel,alert

    animation=FuncAnimation(fig,update,frames=len(rows),interval=400,blit=False,repeat=True)
    print(f"Loaded {len(rows)} frames from {path}")
    plt.show()

if __name__=="__main__":
    main()
