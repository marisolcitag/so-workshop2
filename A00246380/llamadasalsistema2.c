/*Este archivo es la llamada al sistema:
fork():Cuando utilizamos la llamada al sistema fork, el proceso hijo creado es una copia exacta del padre (salvo por el PID y la memoria que ocupa). Al proceso hijo se le facilita una copia de las variables del proceso padre y de
los descriptores de fichero. Es importante destacar que las variables del
proceso hijo son una copia de las del padre (no se refieren físicamente a la
misma variable), por lo que modificar una variable en uno de los procesos
no se refleja en el otro.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>	/* para tener pid_t */

static const unsigned int ITERS = 8;

int main(int argc, char **argv)
{
	unsigned int i = 0, j = 0, h = 0;
	pid_t s = 0;
	int status = 0;

	if (argc != 2) {
		fprintf(stderr, "Uso: %s cantidad_de_hijos\n", argv[0]);
		exit(1);
	}
	h = atoi(argv[1]);

	for (i = 0; i < h; i++) {
		s = fork();
		if (s < 0) {
			perror("Creando el hijo");
			exit(1);
		} else if (s == 0) {
			for (j = 0; j < ITERS; j++) {
				printf("Hijo pid=%5d: iteracion %3d\n", getpid(), j);
			}
			return 0;  /* no quiero nietos! */
		} else {
			printf("PADRE: hijo pid=%5d, creado\n", s);
		}
	}

	for (i = 0; i < h; i++) {
		s = wait(&status);
		if (s < 0) {
			perror("Esperando el hijo");
			exit(1);
		}
		printf("PADRE: hijo pid=%5d, terminado\n", s);
	}
	return 0;
}
