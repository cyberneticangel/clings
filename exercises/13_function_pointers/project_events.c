// project_events.c - PROJECT: Event bus
//
// Many C libraries (GUI toolkits, networking libraries, ...) let you register
// *callbacks*: functions they call later when something happens. Since C has
// no closures, a callback usually comes with a `void *context` pointer that
// gets passed back to it, so it can reach whatever data it needs.
//
// Build a small event bus:
//
//   bool bus_subscribe(EventBus *bus, EventType type, Handler fn, void *ctx)
//       Registers fn to be called for events of `type`. Returns false when
//       MAX_HANDLERS is reached.
//
//   int bus_emit(EventBus *bus, EventType type, int payload)
//       Calls every handler subscribed to `type`, in subscription order,
//       as fn(ctx, payload). Returns how many handlers ran.
//
// Then write the three handlers used in main (their signatures must match
// the Handler typedef):
//
//   on_click_count  - ctx points to an int; increment it
//   on_key_log      - ctx points to a KeyLog; append the key (payload, a
//                     char) to its text, keeping it '\0'-terminated
//   on_any_sum      - ctx points to a long; add payload to it

// I AM NOT DONE

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

// Write your functions here.

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
    CHECK(!bus_subscribe(&bus, EV_CLICK, on_click_count, &clicks)); // full

    clicks = 0;
    CHECK_INT(bus_emit(&bus, EV_CLICK, 0), 6);
    CHECK_INT(clicks, 5);

    return clings_report();
}
