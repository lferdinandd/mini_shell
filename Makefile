CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = main.o shell.o builtins.o exec.o jobs.o signals.o history.o

mini_shell: $(OBJS)
	$(CC) $(CFLAGS) -o mini_shell $(OBJS)

clean:
	rm -f *.o mini_shell
