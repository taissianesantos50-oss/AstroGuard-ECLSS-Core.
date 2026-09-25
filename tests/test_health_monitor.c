#include <assert.h>
#include <string.h>
#include "../src/health_monitor.h"

int main(void)
{
    HealthTelemetry normal={72.0f,98.0f,36.7f,16.0f,0.10f,0.90f,HEALTH_NORMAL};
    HealthTelemetry attention={130.0f,92.0f,36.7f,16.0f,0.80f,0.60f,HEALTH_NORMAL};
    HealthTelemetry critical={72.0f,88.0f,36.7f,16.0f,0.10f,0.90f,HEALTH_NORMAL};

    assert(evaluate_health(&normal)==HEALTH_NORMAL);
    assert(evaluate_health(&attention)==HEALTH_ATTENTION);
    assert(evaluate_health(&critical)==HEALTH_CRITICAL);
    assert(strcmp(health_status_name(HEALTH_NORMAL),"NORMAL")==0);
    assert(strcmp(health_status_name(HEALTH_ATTENTION),"ATTENTION")==0);
    assert(strcmp(health_status_name(HEALTH_CRITICAL),"CRITICAL")==0);
    return 0;
}
