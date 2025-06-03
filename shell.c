#include "shell.h"

void init_shell() {
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGCHLD, sigchld_handler);
}

void read_command(char *line) {
    int background = 0;

    if (strchr(line, '|')) {
        handle_pipe(line, background);
        return;
    }

    char *args[MAX_ARGS];
    if (parse_command(line, args, &background) == 0) return;

    if (is_builtin(args)) {
        run_builtin(args);
    } else {
        execute_command(args, background);
    }
}

int parse_command(char *line, char **args, int *background) {
    int i = 0;
    char *token = strtok(line, " \t\n");

    while (token && i < MAX_ARGS - 1) {
        if (strcmp(token, "&") == 0)
            *background = 1;
        else
            args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return i;
}
