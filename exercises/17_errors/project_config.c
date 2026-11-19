// project_config.c - PROJECT: Config file parser with error reporting
//
// Programs commonly read settings from a simple text format:
//
//     # comments start with '#'
//     name = clings
//     port = 8080
//
//     verbose = true
//
// Write a parser that reports *useful* errors, with line numbers.
//
//   ConfigError config_parse(Config *cfg, FILE *f, int *error_line)
//       Reads every line. Blank lines and lines starting with '#' (after
//       optional leading whitespace) are ignored. Other lines must be
//       `key = value` (whitespace around key and value is trimmed).
//       Known keys:
//           name     a string, at most NAME_MAX - 1 chars    -> cfg->name
//           port     an integer 1..65535                       -> cfg->port
//           verbose  "true" or "false"                         -> cfg->verbose
//       On the FIRST problem, store its 1-based line number in *error_line
//       and return the matching error:
//           CFG_ERR_SYNTAX       no '=' on the line, or empty key
//           CFG_ERR_UNKNOWN_KEY  key isn't one of the above
//           CFG_ERR_BAD_VALUE    value is invalid for that key
//       Otherwise return CFG_OK. Keys that don't appear keep their defaults.
//
//   const char *config_error_str(ConfigError e)
//       A human-readable message for each error (any text you like, but
//       not NULL or empty).
//
// Reuse ideas from earlier: trim() from project_tokenizer and parse_int()
// from errors1. Write them again here (it's good practice!).

// I AM NOT DONE

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clings.h"

#define NAME_MAX 16

typedef struct {
    char name[NAME_MAX];
    int port;
    bool verbose;
} Config;

typedef enum {
    CFG_OK,
    CFG_ERR_SYNTAX,
    CFG_ERR_UNKNOWN_KEY,
    CFG_ERR_BAD_VALUE,
} ConfigError;

// Write your functions here.

// Test helper: parse a string as if it were a file.
static ConfigError parse_text(Config *cfg, const char *text, int *line) {
    FILE *f = tmpfile();
    if (f == NULL) {
        return CFG_ERR_SYNTAX;
    }
    fputs(text, f);
    rewind(f);
    ConfigError e = config_parse(cfg, f, line);
    fclose(f);
    return e;
}

static Config defaults(void) {
    Config c = {.name = "default", .port = 80, .verbose = false};
    return c;
}

int main(void) {
    Config cfg = defaults();
    int line = 0;

    ConfigError e = parse_text(&cfg,
                               "# my app\n"
                               "name = clings\n"
                               "\n"
                               "   # indented comment\n"
                               "  port=8080  \n"
                               "verbose =   true\n",
                               &line);
    CHECK_INT(e, CFG_OK);
    CHECK_STR(cfg.name, "clings");
    CHECK_INT(cfg.port, 8080);
    CHECK(cfg.verbose);

    cfg = defaults();
    CHECK_INT(parse_text(&cfg, "port = 22\n", &line), CFG_OK);
    CHECK_STR(cfg.name, "default");
    CHECK_INT(cfg.port, 22);

    cfg = defaults();
    CHECK_INT(parse_text(&cfg, "name = a\nthis has no equals\n", &line),
              CFG_ERR_SYNTAX);
    CHECK_INT(line, 2);

    CHECK_INT(parse_text(&cfg, "\n\n = value\n", &line), CFG_ERR_SYNTAX);
    CHECK_INT(line, 3);

    CHECK_INT(parse_text(&cfg, "# ok\ncolour = blue\n", &line),
              CFG_ERR_UNKNOWN_KEY);
    CHECK_INT(line, 2);

    CHECK_INT(parse_text(&cfg, "port = 99999\n", &line), CFG_ERR_BAD_VALUE);
    CHECK_INT(line, 1);
    CHECK_INT(parse_text(&cfg, "port = 80x\n", &line), CFG_ERR_BAD_VALUE);
    CHECK_INT(parse_text(&cfg, "verbose = maybe\n", &line), CFG_ERR_BAD_VALUE);
    CHECK_INT(parse_text(&cfg, "name = this name is way too long\n", &line),
              CFG_ERR_BAD_VALUE);

    for (int i = CFG_OK; i <= CFG_ERR_BAD_VALUE; i++) {
        const char *msg = config_error_str((ConfigError)i);
        CHECK(msg != NULL && msg[0] != '\0');
    }

    return clings_report();
}
