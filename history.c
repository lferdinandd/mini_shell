#include "shell.h"

void add_history(const char *cmd) {
    FILE *f = fopen(HISTORY_FILE, "a");
    if (f) {
        fputs(cmd, f);
        fclose(f);
    }
}

void load_history() {
    FILE *f = fopen(HISTORY_FILE, "r");
    if (!f) return;

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, f)) {
        // could add to memory if desired
    }
    fclose(f);
}

void show_history() {
    FILE *f = fopen(HISTORY_FILE, "r");
    if (!f) return;

    char line[MAX_LINE];
    int i = 1;
    while (fgets(line, MAX_LINE, f)) {
        printf("%d: %s", i++, line);
    }
    fclose(f);
}
