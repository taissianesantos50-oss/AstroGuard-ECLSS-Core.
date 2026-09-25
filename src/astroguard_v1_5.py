import csv, sys
from pathlib import Path
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def load_telemetry(path):
    with path.open(newline='', encoding='utf-8') as handle:
        rows=list(csv.DictReader(handle))
    required={'Time','O2','Pressure','Temp','HeartRate','SpO2','RespRate','Fatigue','WellBeing','HealthStatus'}
    missing=required.difference(rows[0]) if rows else required
    if missing: raise ValueError(f'Missing telemetry columns: {sorted(missing)}')
    return rows

def norm(v,lo,hi):
    return 0.5 if hi==lo else max(0.0,min(1.0,(v-lo)/(hi-lo)))

def main():
    default=Path('telemetry_v1_4.csv')
    sample=Path('telemetry/sample_health_telemetry.csv')
    path=Path(sys.argv[1]) if len(sys.argv)>1 else (default if default.exists() else sample)
    rows=load_telemetry(path)
    times=[float(r['Time']) for r in rows]
    env=[1-(0.4*norm(float(r['O2']),18,22)+0.3*norm(float(r['Pressure']),0,4.5)+0.3*norm(float(r['Temp']),10,22)) for r in rows]
    human=[0.30*(1-norm(float(r['SpO2']),85,100))+0.25*norm(float(r['HeartRate']),50,140)+0.20*norm(float(r['RespRate']),10,30)+0.15*float(r['Fatigue'])+0.10*(1-float(r['WellBeing'])) for r in rows]
    fig=plt.figure(figsize=(12,7)); ax=fig.add_subplot(111,projection='3d')
    line,=ax.plot([],[],[],linewidth=2); point,=ax.plot([],[],[],marker='o',markersize=8)
    info=ax.text2D(0.02,0.95,'',transform=ax.transAxes,va='top')
    ax.set_title('ASTROGUARD v1.5 - 3D Mission Telemetry Visualization')
    ax.set_xlabel('Mission Time'); ax.set_ylabel('Environmental Stress'); ax.set_zlabel('Human Stress')
    ax.set_xlim(min(times),max(times) if max(times)>min(times) else min(times)+1); ax.set_ylim(0,1); ax.set_zlim(0,1)
    ax.view_init(elev=25,azim=-60)
    def update(i):
        line.set_data(times[:i+1],env[:i+1]); line.set_3d_properties(human[:i+1])
        point.set_data([times[i]],[env[i]]); point.set_3d_properties([human[i]])
        r=rows[i]
        info.set_text(f't={r["Time"]} s | Health={r["HealthStatus"]} | HR={r["HeartRate"]} bpm | SpO2={r["SpO2"]}% | O2={r["O2"]}% | P={r["Pressure"]} psi')
        return line,point,info
    animation=FuncAnimation(fig,update,frames=len(rows),interval=350,blit=False)
    print(f'Loaded {len(rows)} telemetry frames from {path}')
    plt.show()

if __name__=='__main__': main()