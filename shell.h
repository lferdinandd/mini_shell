#ifndef SHELL_H
#define SHELL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <termios.h>

#define MAX_LINE 1024
#define MAX_ARGS 128
#define HISTORY_FILE ".mini_shell_history"
#define JOBS_MAX 64

typedef struct job {
    pid_t pgid;
    char *command;
    int running;
} job_t;

extern job_t jobs[JOBS_MAX];

void init_shell();
void read_command(char *line);
int parse_command(char *line, char **args, int *background);
int handle_redirection(char **args);
void execute_command(char **args, int background);
void handle_pipe(char *line, int background);
int is_builtin(char **args);
void run_builtin(char **args);
void add_history(const char *cmd);
void load_history();
void show_history();
void add_job(pid_t pgid, const char *cmd);
void remove_job(pid_t pgid);
void list_jobs();
void put_job_fg(int job_id);
void put_job_bg(int job_id);
void sigint_handler(int sig);
void sigtstp_handler(int sig);
void sigchld_handler(int sig);

#endif
