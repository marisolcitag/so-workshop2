/* Este archivo contiene una llamada al sistema:
creat(): Crea el archivo o lo sobrescribe en caso de existir.*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
int i,fd;
fd=creat("create",0600);
	for(i=0;i<20;i++)
	write(fd,&i,sizeof(i));
        printf("Hola, soy una llamada al sistema y cree un fichero y escribi del 0 al 20");
}

