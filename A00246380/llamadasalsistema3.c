#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

static const unsigned int READ_END = 0;
static const unsigned int WRITE_END = 1;
static const unsigned int ITERS = 32;

int main(void)
{
	pid_t fork_id = -1;
	int pipe_fd[2] = {0,0};

	if (pipe(pipe_fd) < 0) {
		perror("pipe()");
		exit(1);
	}
	if ((fork_id = fork()) < 0) {
		perror("fork()");
		exit(1);
	};

	if (fork_id != 0) {  /* soy el padre */
		int status = 0;
		pid_t fork_id = 0;
		if ((fork_id = fork()) < 0) {
			perror("fork()");
			exit(1);
		};
		if (fork_id != 0) {  /* sigo siendo el padre */
			close(pipe_fd[READ_END]);
			close(pipe_fd[WRITE_END]); /* cierro entrada y salida, el padre no se comunica */
			wait(&status);
			wait(&status); /* espero que ambos hijos terminen */
		} else /* soy el segundo hijo, leo del pipe */ {
			int in = 0;
			close(pipe_fd[WRITE_END]); /* cierro la entrada, no la usamos */
			while (0<read(pipe_fd[READ_END], &in, sizeof(int))) {
				printf("Hijo2: recibe %d\n", in);
			}
			close(pipe_fd[READ_END]);
		}
	} else {  /* soy el primogénito, escribo en el pipe */
		unsigned int i = 0;
		close(pipe_fd[READ_END]); /* cierro la salida, no la usamos*/
		for (i=0; i<ITERS; i++) {
			printf("Hijo1: envía %d\n", i);
			write(pipe_fd[WRITE_END], &i, sizeof(int));
		}
		close(pipe_fd[WRITE_END]);
	}

	return 0;
}
