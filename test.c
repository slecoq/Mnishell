#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
# include <pthread.h>


int main(int argc, char **argv, char **env) {
	char *path = "/usr/bin/ls";
	char *args[] = {"/usr/bin/ls", "-al", "-h", NULL} ;

	execve(path, args, env);
	perror("execve");
}
