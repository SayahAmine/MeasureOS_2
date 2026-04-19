#ifndef SENSORS_H
#define SENSORS_H

#include "events.h"

void sensors_init(float initial_temp);
Event parse_temperature(const char *message);

#endif
