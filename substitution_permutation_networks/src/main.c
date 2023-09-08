#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "aes.h"

int main(int argc, char* argv[]) {

    unsigned char key[16], block[16], direction;
    int c;

    while ((c = getopt(argc, argv, "edk:")) != -1) {
        if (c == 'e' || c == 'd') {
            direction = c;
        }
        else if (c == 'k') {
            for (int i = 0; i < 16; i++) {
                key[i] = *optarg;
                optarg++;
            }
        }
    }

    // Encipher and place result into enciphered.txt
    if (direction == 'e') {
        FILE* f = fopen("enciphered.txt", "w");
        printf("Input(ascii):        ");
        for (int i = 0; i < 16; i++) {
            block[i] = *argv[optind];
            argv[optind]++;
            printf("%c", block[i]);
        }
        printf("\nInput(hexadecimal):  ");
        for (int i = 0; i < 16; i++) {
            printf("%02x", block[i]);
        }
        encipher_block(block, key);
        printf("\nOutput(hexadecimal): ");
        for (int i = 0; i < 16; i++) {
            fprintf(f, "%c", block[i]);
            printf("%02x", block[i]);
        }
        printf("\n");
    }
    // Decipher contents of enciphered.txt and display
    else if (direction == 'd') {
        FILE* f = fopen("enciphered.txt", "r");
        printf("Input(hexadecimal):  ");
        for (int i = 0; i < 16; i++) {
            block[i] = fgetc(f);
            printf("%02x", block[i]);
        }
        decipher_block(block, key);
        printf("\nOutput(hexadecimal): ");
        for (int i = 0; i < 16; i++) {
            printf("%02x", block[i]);
        }
        printf("\nOutput(ascii):       ");
        for (int i = 0; i < 16; i++) {
            printf("%c", block[i]);
        }
        printf("\n");
    }

    return 0;
}
