#include "shell.h"

void add_job(pid_t pgid, const char *cmd) {
    for (int i = 0; i < JOBS_MAX; ++i) {
        if (jobs[i].pgid == 0) {
            jobs[i].pgid = pgid;
            jobs[i].command = strdup(cmd);
            jobs[i].running = 1;
            break;
        }
    }
}

void remove_job(pid_t pgid) {
    for (int i = 0; i < JOBS_MAX; ++i) {
        if (jobs[i].pgid == pgid) {
            free(jobs[i].command);
            jobs[i].pgid = 0;
            jobs[i].running = 0;
        }
    }
}

void list_jobs() {
    for (int i = 0; i < JOBS_MAX; ++i) {
        if (jobs[i].pgid) {
            printf("[%d] %s (%s)\n", i, jobs[i].command,
                   jobs[i].running ? "Running" : "Stopped");
        }
    }
}

void put_job_fg(int job_id) {
    if (jobs[job_id].pgid) {
        tcsetpgrp(STDIN_FILENO, jobs[job_id].pgid);
        kill(-jobs[job_id].pgid, SIGCONT);
        waitpid(-jobs[job_id].pgid, NULL, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, getpid());
    }
}

void put_job_bg(int job_id) {
    if (jobs[job_id].pgid) {
        kill(-jobs[job_id].pgid, SIGCONT);
        jobs[job_id].running = 1;
    }
}
