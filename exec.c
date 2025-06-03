#include "shell.h"

void execute_command(char **args, int background) {
    pid_t pid = fork();

    if (pid == 0) {
        setpgid(0, 0);
        handle_redirection(args);
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        setpgid(pid, pid);
        if (background) {
            add_job(pid, args[0]);
        } else {
            tcsetpgrp(STDIN_FILENO, pid);
            waitpid(pid, NULL, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpid());
        }
    }
}

int handle_redirection(char **args) {
    for (int i = 0; args[i]; ++i) {
        if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        } else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i+1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        } else if (strcmp(args[i], "2>") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDERR_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
    return 0;
}

void handle_pipe(char *line, int background) {
    char *cmd1 = strtok(line, "|");
    char *cmd2 = strtok(NULL, "|");

    char *args1[MAX_ARGS], *args2[MAX_ARGS];
    parse_command(cmd1, args1, &background);
    parse_command(cmd2, args2, &background);

    int pipefd[2];
    pipe(pipefd);

    pid_t p1 = fork();
    if (p1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        execvp(args1[0], args1);
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    pid_t p2 = fork();
    if (p2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        execvp(args2[0], args2);
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
}
