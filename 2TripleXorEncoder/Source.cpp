#include <stdio.h>

void TripleXor(unsigned char* buf, int size) {
const char encoderChar = '\x42';
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 3; j++) {
			buf[i] = buf[i] ^ (encoderChar + j);
		}

	}
}

void PrintHex(unsigned char* buf, int size) {
	printf("Buffer size: %d\n", size);
	printf("\"");
	for (int i = 0; i < size; i++) {
		if ((i % 16 == 15) && (i != size - 1)) {
			printf("\"\n\"");
		}
		printf("\\x");
		if (buf[i] < (unsigned char)'\x10') {
			printf("0");
		}
		printf("%x", buf[i]);
	}
	printf("\"\n");
}

int main() {
	// Change me! msfvenom output here
	unsigned char buf[] = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";

	printf("Buffer before encoding:\n");
	PrintHex(buf, sizeof(buf)-1);

	TripleXor(buf, sizeof(buf)-1);
	printf("Buffer after encoding:\n");
	PrintHex(buf, sizeof(buf)-1);

	return 0;
}
