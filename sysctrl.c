#include<stdio.h>
#include<stdlib.h>
#include<sys/sysctl.h>

void get_max_cpu() {
	int names[] = {CTL_HW,HW_NCPU};
	int name_len = 2;
	int max_cpu;
	size_t len = sizeof(max_cpu);
	int error;
	error = sysctl(names,name_len,&max_cpu,&len,NULL,0);
	if(error){
		printf("Error in sysctl system call");
		exit(1);
	}
	printf("No if max process for this machine is %d",max_cpu);
}

void get_memory_size() {
	int names[] = {CTL_HW,HW_MEMSIZE};
	int name_len = 2;
	int max_cpu;
	size_t len = sizeof(max_cpu);
	int error;
	error = sysctl(names,name_len,&max_cpu,&len,NULL,0);
	if(error){
		printf("Error in sysctl system call");
		exit(1);
	}
	printf("Physical memory installed in machine : %d",max_cpu);
}



int main(){
	get_max_cpu();
	get_memory_size();
	return 0;
}


