#include "shell.h"

int is_builtin(char **args) {
    return (strcmp(args[0], "cd") == 0 ||
            strcmp(args[0], "exit") == 0 ||
            strcmp(args[0], "history") == 0 ||
            strcmp(args[0], "jobs") == 0 ||
            strcmp(args[0], "fg") == 0 ||
            strcmp(args[0], "bg") == 0);
}

void run_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        chdir(args[1] ? args[1] : getenv("HOME"));
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "history") == 0) {
        show_history();
    } else if (strcmp(args[0], "jobs") == 0) {
        list_jobs();
    } else if (strcmp(args[0], "fg") == 0) {
        put_job_fg(atoi(args[1]));
    } else if (strcmp(args[0], "bg") == 0) {
        put_job_bg(atoi(args[1]));
    }
}
