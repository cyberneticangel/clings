// project_events.c - solution

#include <stdbool.h>
#include <stddef.h>

#include "clings.h"

#define MAX_HANDLERS 8

typedef enum { EV_CLICK, EV_KEY } EventType;

typedef void (*Handler)(void *ctx, int payload);

typedef struct {
    EventType type;
    Handler fn;
    void *ctx;
} Subscription;

typedef struct {
    Subscription subs[MAX_HANDLERS];
    size_t count;
} EventBus;

typedef struct {
    char text[32];
    size_t len;
} KeyLog;

bool bus_subscribe(EventBus *bus, EventType type, Handler fn, void *ctx) {
    if (bus->count >= MAX_HANDLERS) {
        return false;
    }
    bus->subs[bus->count++] = (Subscription){.type = type, .fn = fn, .ctx = ctx};
    return true;
}

int bus_emit(EventBus *bus, EventType type, int payload) {
    int ran = 0;
    for (size_t i = 0; i < bus->count; i++) {
        if (bus->subs[i].type == type) {
            bus->subs[i].fn(bus->subs[i].ctx, payload);
            ran++;
        }
    }
    return ran;
}

void on_click_count(void *ctx, int payload) {
    (void)payload; // unused
    int *count = ctx;
    (*count)++;
}

void on_key_log(void *ctx, int payload) {
    KeyLog *log = ctx;
    if (log->len + 1 < sizeof(log->text)) {
        log->text[log->len++] = (char)payload;
        log->text[log->len] = '\0';
    }
}

void on_any_sum(void *ctx, int payload) {
    long *sum = ctx;
    *sum += payload;
}

int main(void) {
    EventBus bus = {.count = 0};
    int clicks = 0;
    KeyLog log = {.text = "", .len = 0};
    long sum = 0;

    CHECK(bus_subscribe(&bus, EV_CLICK, on_click_count, &clicks));
    CHECK(bus_subscribe(&bus, EV_KEY, on_key_log, &log));
    CHECK(bus_subscribe(&bus, EV_CLICK, on_any_sum, &sum));
    CHECK(bus_subscribe(&bus, EV_KEY, on_any_sum, &sum));

    CHECK_INT(bus_emit(&bus, EV_CLICK, 10), 2);
    CHECK_INT(bus_emit(&bus, EV_CLICK, 20), 2);
    CHECK_INT(bus_emit(&bus, EV_KEY, 'h'), 2);
    CHECK_INT(bus_emit(&bus, EV_KEY, 'i'), 2);

    CHECK_INT(clicks, 2);
    CHECK_STR(log.text, "hi");
    CHECK_INT(sum, 10 + 20 + 'h' + 'i');

    for (int i = 0; i < 4; i++) {
        CHECK(bus_subscribe(&bus, EV_CLICK, on_click_count, &clicks));
    }
    CHECK(!bus_subscribe(&bus, EV_CLICK, on_click_count, &clicks));

    clicks = 0;
    CHECK_INT(bus_emit(&bus, EV_CLICK, 0), 6);
    CHECK_INT(clicks, 5);

    return clings_report();
}
