#include<stdio.h>
#include<unistd.h>
#include<signal.h>

#define display_kill() fprintf(stdout,"hey is it working : %d",getpid())

int process_id;
void signal_hook(int sign){
	if(sign == SIGINT){
		printf("ctrl+c will also not ");
		printf("\n to kill this program please open new session in terminal and enter following command \n");
		printf("\t kill -9 %d \n",process_id);
	}
	if(sign == SIGTSTP){
		printf("ctrl+z will also not work here \n");
		printf("\n to kill this program please open new session in terminal and enter following command \n");
		printf("\t kill -9 %d \n",process_id);
	}
}

int main(){
	process_id = getpid();
	// Hooking ctrl+c signal
	if(signal(SIGINT,signal_hook) == SIG_ERR){
		printf("Signal hooking failed \n");
	}

	// Hooking ctrl+z signal
	if(signal(SIGTSTP,signal_hook) == SIG_ERR){
		printf("Signal hooking failed \n");
	}

	// let the program continue running 
	for( ; ; ){
	   pause();	
	}
	return 0;
}
