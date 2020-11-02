#include <windows.h>
#include <cstdio>

//standard libs

int get_dll_size(const char *dll_name){

	FILE *fp = fopen(dll_name,"r");
	fseek(fp,0L,SEEK_END);
	int sz = ftell(fp);
	fclose(fp);
	//function to get the size of a dll file
	return sz+1000;

}

int main(int argc,char *argv[]){

	if(argc != 3){

		fprintf(stderr,"Usage:%s pid dll",argv[0]);
		return 1;
	//checking if arguments were provided
	}


	DWORD pid;
	sscanf(argv[1],"%u",&pid);
	HANDLE op = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
	//opening the process
	if(op == NULL){
	
		fprintf(stderr,"Unable to open process");
		CloseHandle(op);
		return 2;
		//error handling

	}
	LPVOID vae = VirtualAllocEx(op,NULL,get_dll_size(argv[2]),MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	//allocating memmory 
	if(vae == NULL){

		fprintf(stderr,"Unable to allocate memmory");
		CloseHandle(op);
		return 3;

	}
	BOOL wpm = WriteProcessMemory(op,vae,argv[2],strlen(argv[2])+1,NULL);
	//writing to the process
	if(wpm == 0){

		fprintf(stderr,"Unable to write to process");
		CloseHandle(op);
		return 4;

	}
	HANDLE crt = CreateRemoteThread(op,NULL,0,(LPTHREAD_START_ROUTINE)LoadLibraryA,vae,0,NULL);
	//creating new thread
	if(crt == NULL){

		fprintf(stderr,"Unable to create remote thread");
		CloseHandle(op);
		CloseHandle(crt);
		return 5;

	}

	CloseHandle(op);
	CloseHandle(crt);
	//closing handles
	return 0;

}
