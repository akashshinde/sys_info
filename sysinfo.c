#include<stdio.h>
#include<sys/utsname.h>

int main(void){
	int result;
	struct utsname sys_info;	
	result = uname(&sys_info);
	printf("\nSystem Name is : %s",sys_info.sysname);
	printf("\nSystem node name is : %s",sys_info.nodename);
	printf("\nRelease level of operating system is : %s",sys_info.release);
	printf("\nOperating system version is : %s",sys_info.version);
	printf("\nMachine hardware platform is : %s",sys_info.machine);
	return 0;
}
