#include "shell.h"

job_t jobs[JOBS_MAX] = {0};

int main() {
    char line[MAX_LINE];

    init_shell();
    load_history();

    while (1) {
        printf("mini-shell$ ");
        fflush(stdout);

        if (!fgets(line, MAX_LINE, stdin)) break;

        if (strlen(line) > 1) {
            add_history(line);
            read_command(line);
        }
    }

    return 0;
}
