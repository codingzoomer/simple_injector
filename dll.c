#include <windows.h>

//compile with -shared flag and dll extension with -o flag

BOOL APIENTRY DllMain(HANDLE hModule,DWORD reason,LPVOID lpReserved){
	//main function for dll	
	if(reason == DLL_PROCESS_ATTACH)
		MessageBox(NULL,"i am a dll!","dll injected",0);
		//if dll was attached,we are spawning messagebox

}
