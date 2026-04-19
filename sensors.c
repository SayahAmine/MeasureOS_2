#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sensors.h"

static float last_temperature = 0.0f;
static int sensors_initialized = 0;

void sensors_init(float initial_temp) {
    last_temperature = initial_temp;
    sensors_initialized = 1;
}

Event parse_temperature(const char *message) {
    Event event = {EVENT_NONE, 0.0f};

    if (strncmp(message, "TEMP:", 5) != 0) {
        return event;
    }

    event.temp = (float) atof(message + 5);
    printf("[SENSOR] Temp = %.2f C\n", event.temp);

    if (!sensors_initialized) {
        sensors_init(event.temp);
        return event;
    }

    if (last_temperature <= 39.0f && event.temp > 39.0f) {
        event.type = EVENT_S2_THRESHOLD;
    } else if (last_temperature <= 37.0f && event.temp > 37.0f) {
        event.type = EVENT_S1_THRESHOLD;
    }

    last_temperature = event.temp;
    return event;
}
