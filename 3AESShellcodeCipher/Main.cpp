#include <stdio.h>
#include "AES.h" //https://github.com/SergeyBel/AES 

int main() {
	// Change me! Shellcode from msfvenom here. Must be padded to be 16-byte aligned.
	unsigned char shellcode[] = 
	  { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	unsigned char key[] = { 0x43, 0x5e, 0x3b, 0xde, 0x6a, 0x10, 0x07, 0x3f, 0x3a, 0xf9, 0xa1, 0x5a, 0xd3, 0x11, 0x03, 0xd0 };
	unsigned int outLen = 0;
	unsigned int size = sizeof(shellcode);

	AES aes(128);

	printf("Before encryption:\n");
	aes.printHexArray(shellcode, size);
	printf("\n\n");

	unsigned char* cipheredBuffer = aes.EncryptECB(shellcode, size, key, outLen);

	printf("After encryption:\n");
	aes.printHexArray(cipheredBuffer, size);
	printf("\n\n");

	unsigned char* decipheredBuffer = aes.DecryptECB(cipheredBuffer, size, key);

	printf("After decryption:\n");
	aes.printHexArray(decipheredBuffer, size);
	printf("\n\n");

	printf("Size of buffer: %d\n", size);

	return 0;
}
