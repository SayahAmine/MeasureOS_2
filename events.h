#ifndef EVENTS_H
#define EVENTS_H

typedef enum {
    EVENT_NONE = 0,
    EVENT_S1_THRESHOLD,
    EVENT_S2_THRESHOLD
} EventType;

typedef struct {
    EventType type;
    float temp;
} Event;

#endif
