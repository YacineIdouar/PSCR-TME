#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int nb_enfant =1;
	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		nb_enfant = 0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				nb_enfant = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else {
			nb_enfant++;
			std::cout << "Le pid : " << getpid() << " Le père : " << getppid() << " Nombre enfant : " << nb_enfant << std::endl;
			}
		}
		if(i <= N && j==N){nb_enfant++;}
	}
	for (int i=0; i< nb_enfant;i++){
		wait(nullptr);
	}
	std::cout << "Le processus : " << getpid() << " finit le wait" << std::endl;
	return 0;
}
