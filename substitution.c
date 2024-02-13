#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define   MAXBUFFERSIZE     2000000
char buffer[MAXBUFFERSIZE];

void getAnInput();
int checkFrequency(char c[]);
int checkAlpha(char c[]);
void encrypt(char c[], char key[]);

void getAnInput() {
    buffer[0] = '\0';
    char c;
    int valid_choice = 0;
    int char_count ;
    do  {
       c = getchar();
       char_count = 0;
       while (c != '\n')  {
        buffer[char_count++] = c;
        c = getchar();
       }
       buffer[char_count] = 0x00;
       valid_choice = 1;
    } while (valid_choice == 0);
}
int checkFrequency(char c[]) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz" ;
    int frequency[26];
    frequency[0] = 0x00;
    for (size_t i = 0; i < 26; i++)  {     
        for (size_t j = 0; j < 26; j++)  {
            if (c[i] == alphabet[j] || c[i] == toupper(alphabet[j]))  {
                frequency[i]++;
            }
        } 
    }
    for (size_t i = 0; i < 26; i++) {
        if (frequency[i] != 1)  {
            return 1;
        } 
    }
    return 0;
}

int checkAlpha(char c[]) {
    for (size_t i = 0; i < 26; i++)  {
        if (!isalpha(c[i])) {
           return 1;
        }   
    }
    return 0;
}

void encrypt(char c[], char key[]) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char ciphertext[strlen(c)];
    for (size_t i = 0; i < strlen(c); i++)  {
        for (size_t j = 0; j < 26; j++)  {
            if (c[i] == alphabet[j] )  {
                ciphertext[i] = tolower(key[j]) ;
                break;
            } else if(c[i] == toupper(alphabet[j])) {
                ciphertext[i] = toupper(key[j]); 
                break;        
            } else if(!isalpha(c[i])) {
                ciphertext[i] = c[i];
            }
                
            
        }
    }
    ciphertext[strlen(c)] = '\0';
    printf("ciphertext : %s\n", ciphertext);
}


int main(int argc, char *argv[]) {
    //checking the key (command line argument)
    if (argc != 2)  {
        printf("key");
        return 1;
    } else if (strlen(argv[1]) != 26 )  {
        printf("key must contain 26 characters %lu\n", strlen(argv[1]));
        return 1;
    } else if(checkAlpha(argv[1])) {
        printf("Non alpha characters .\n");
        return 1;
    } else if(!checkFrequency(argv[1])) {
        printf("not containing each letter exactly once !");
        return 1;
    }
    // if we're here means the key is ok
    printf("plaintext : ");
    getAnInput();
    encrypt(buffer, argv[1]);
    return 0; 
}