#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Ask and get user's name
void getName(char *getname);
// Get gematrial value of given name
int getGematria(const char *gemName);

int getGematria(const char *gemName){
    // Were going to need a dictionary of each letter in the English alphabet

    // Run while loop for each character of the name, and add the value to the gematria integer (but exclude non letters)
    int gematria = 0;
    while (*gemName){
        // Get character at the specific pointer and make it uppercase
        char letter = toupper(*gemName);
        // If it is a letter, add the value of the letter to gematria
        if (letter >= 'A' && letter <= 'Z'){
            gematria += letter - 'A' + 1;
        }
        *gemName++;
    }
    return gematria;
}

void getName(char *getname){
    // Ask for user's name
    printf("\nEnter your name: ");
    fgets(getname, 256, stdin);
    size_t nameLen = strlen(getname);
    // Remove newline
    if (nameLen > 0 && getname[nameLen - 1] =='\n') {
        getname[nameLen - 1] = '\0';
    }
}

