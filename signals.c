#include "shell.h"

void sigint_handler(int sig) {
    (void)sig;
    // ignore in shell
}

void sigtstp_handler(int sig) {
    (void)sig;
    // ignore in shell
}

void sigchld_handler(int sig) {
    (void)sig;
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        remove_job(pid);
    }
}
