// project_config.c - solution

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

static char *trim(char *s) {
    while (isspace((unsigned char)*s)) {
        s++;
    }
    char *end = s + strlen(s);
    while (end > s && isspace((unsigned char)end[-1])) {
        end--;
    }
    *end = '\0';
    return s;
}

static bool parse_int(const char *str, int *out) {
    char *end;
    errno = 0;
    long v = strtol(str, &end, 10);
    if (end == str || *end != '\0' || errno == ERANGE || v < INT_MIN ||
        v > INT_MAX) {
        return false;
    }
    *out = (int)v;
    return true;
}

static ConfigError apply_setting(Config *cfg, const char *key,
                                 const char *value) {
    if (strcmp(key, "name") == 0) {
        if (strlen(value) >= NAME_MAX) {
            return CFG_ERR_BAD_VALUE;
        }
        strcpy(cfg->name, value);
    } else if (strcmp(key, "port") == 0) {
        int port;
        if (!parse_int(value, &port) || port < 1 || port > 65535) {
            return CFG_ERR_BAD_VALUE;
        }
        cfg->port = port;
    } else if (strcmp(key, "verbose") == 0) {
        if (strcmp(value, "true") == 0) {
            cfg->verbose = true;
        } else if (strcmp(value, "false") == 0) {
            cfg->verbose = false;
        } else {
            return CFG_ERR_BAD_VALUE;
        }
    } else {
        return CFG_ERR_UNKNOWN_KEY;
    }
    return CFG_OK;
}

ConfigError config_parse(Config *cfg, FILE *f, int *error_line) {
    char buf[256];
    int line_no = 0;
    while (fgets(buf, sizeof(buf), f) != NULL) {
        line_no++;
        char *line = trim(buf);
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }
        char *eq = strchr(line, '=');
        if (eq == NULL) {
            *error_line = line_no;
            return CFG_ERR_SYNTAX;
        }
        *eq = '\0';
        char *key = trim(line);
        char *value = trim(eq + 1);
        if (key[0] == '\0') {
            *error_line = line_no;
            return CFG_ERR_SYNTAX;
        }
        ConfigError e = apply_setting(cfg, key, value);
        if (e != CFG_OK) {
            *error_line = line_no;
            return e;
        }
    }
    return CFG_OK;
}

const char *config_error_str(ConfigError e) {
    switch (e) {
    case CFG_OK:
        return "no error";
    case CFG_ERR_SYNTAX:
        return "syntax error: expected 'key = value'";
    case CFG_ERR_UNKNOWN_KEY:
        return "unknown key";
    case CFG_ERR_BAD_VALUE:
        return "invalid value";
    }
    return "unknown error";
}

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
