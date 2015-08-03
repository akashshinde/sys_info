#include<stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include<stdlib.h>
#include<sys/sysctl.h>
#include <unistd.h>

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
	printf("No if max process for this machine is %d \n",max_cpu);
}

void get_no_of_processors(){
	long cpu_cores;
	cpu_cores = sysconf(_SC_NPROCESSORS_ONLN);
	printf("\n No of cpu cores present in this machine : %ld ",cpu_cores);
}

void list_kernel_process(){
	/*int mib[2];
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	size_t bufSize = 0;
	//mib[2] = what;
	//mib[3] = flag;
	if (sysctl(mib, 2, &kProcList, &bufSize, NULL, 0) < 0) {
		perror("Failure calling sysctl");
	}*/
	struct kinfo_proc *kProcList = NULL;
	int err = 0;
	size_t length = 0;
	static const int name[] = { CTL_KERN, KERN_PROC,KERN_PROC_ALL, 0 };
	err = sysctl((int *)name, (sizeof(name) / sizeof(*name)) - 1, NULL, &length, NULL, 0);
	if (err) goto ERROR;
	system("COLOR 6C");
	printf("list of running processes are : %zd",length);
	kProcList = malloc(length);
	err = sysctl((int *)name, (sizeof(name) / sizeof(*name)) - 1, kProcList, &length, NULL, 0);
	int proc_count = length / sizeof(struct kinfo_proc);
	printf("processes are : %d",proc_count);
	
	for(int i=0;i< proc_count;i++){
		uid_t uid = kProcList[i].kp_eproc.e_ucred.cr_uid;
		struct passwd *user = getpwuid(uid);
		char *username = user ? user->pw_name : "user name not found";
	//	printf("\nProcess nice values is : %s",kProcList[i].kp_proc.p_nice);
		printf("\nParent process for below process is : %d",kProcList[i].kp_eproc.e_ppid);
		printf("\n cpu tick time is : %d ",kProcList[i].kp_proc.p_estcpu);
		printf("pid=%d, uid=%d, username=%s\n",kProcList[i].kp_proc.p_pid,uid,username);
		}

ERROR:
	perror(NULL);
}

void get_memory_size() {
//	int names[] = {CTL_HW,HW_PHYSEM};
	int name_len = 2;
	int max_cpu;
	size_t len = sizeof(max_cpu);
	int error;
	error = sysctlbyname("hw.physmem",&max_cpu,&len,NULL,0);
	if(error){
		printf("Error in sysctl system call");
		exit(1);
	}
	printf("Physical memory installed in machine : %d \n",max_cpu);
}

int main(){
//	get_max_cpu();
//	get_memory_size();
	list_kernel_process();
	get_no_of_processors();
	return 0;
}


