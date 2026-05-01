//Author: Elijah Riggs
//Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>
#define WORD_LENGTH 5
#define MAX_GUESSES 6

bool getWord(char word[]);
void getGuess(char guess[]);
bool validGuess(char guess[]);
int length(char word[]);
void toLowerStr(char word[]);
char toLower(char letter);
char toUpper(char letter);
bool isLetter(char letter);
bool sameWord(char guess[], char word[]);
void printBoard(char guesses[][WORD_LENGTH + 1], int count, char word[]);
void printGuess(char guess[], char word[]);
bool inWrongSpot(char guess[], char word[], int letterPosition);

int main(){
    char word[WORD_LENGTH + 1];
    char guesses[MAX_GUESSES][WORD_LENGTH + 1];
    int count = 0;
    bool won = false;
    if (getWord(word) == false){
        return 0;
    }
    toLowerStr(word);
    while (count < MAX_GUESSES && won == false){
        if (count == MAX_GUESSES - 1){
            printf("FINAL GUESS! Enter your guess: ");
        }
        else{
            printf("GUESS %d! Enter your guess: ", count + 1);
        }
        getGuess(guesses[count]);
        printf("==============================\n");
        count++;
        printBoard(guesses, count, word);
        if (sameWord(guesses[count - 1], word)){
            won = true;
        }
    }
    if (won == true){
        printf("\n     ");
        for (int i = 0; i < WORD_LENGTH; i++){
            printf("%c", toUpper(word[i]));
        }
        printf("\nYou won in %d guesses!\n", count);
        printf("Amazing!\n");
    }
    else{
        printf("\nYou lost, better luck next time!\n");
        printf("The word was ");
        for (int i = 0; i < WORD_LENGTH; i++){
            printf("%c", toUpper(word[i]));
        }
        printf(".\n");
    }
    return 0;
}

bool getWord(char word[]){
    FILE *fpointer = fopen("word.txt", "r");
    if (fpointer == NULL){
        printf("Could not open word.txt\n");
        return false;
    }
    fscanf(fpointer, "%5s", word);
    word[WORD_LENGTH] = '\0';
    fclose(fpointer);
    return true;
}

void getGuess(char guess[]){
    scanf("%s", guess);
    toLowerStr(guess);
    while (validGuess(guess) == false){
        if (length(guess) != WORD_LENGTH){
            printf("Your guess must be 5 letters long.\n");
        }
        else{
            printf("Your guess must only contain letters.\n");
        }
        printf("Please try again: ");
        scanf("%s", guess);
        toLowerStr(guess);
    }
}

bool validGuess(char guess[]){
    if (length(guess) != WORD_LENGTH){
        return false;
    }
    for (int i = 0; i < WORD_LENGTH; i++){
        if (isLetter(guess[i]) == false){
            return false;
        }
    }
    return true;
}

int length(char word[]){
    int lengthCount = 0;
    while (word[lengthCount] != '\0'){
        lengthCount++;
    }
    return lengthCount;
}

void toLowerStr(char word[]){
    int index = 0;
    while (word[index] != '\0'){
        word[index] = toLower(word[index]);
        index++;
    }
}

char toLower(char letter){
    if (letter >= 'A' && letter <= 'Z'){
        return letter + 32;
    }
    return letter;
}

char toUpper(char letter){
    if (letter >= 'a' && letter <= 'z'){
        return letter - 32;
    }
    return letter;
}

bool isLetter(char letter){
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')){
        return true;
    }
    return false;
}

bool sameWord(char guess[], char word[]){
    for (int i = 0; i < WORD_LENGTH; i++){
        if (guess[i] != word[i]){
            return false;
        }
    }
    return true;
}

void printBoard(char guesses[][WORD_LENGTH + 1], int count, char word[]){
    for (int i = 0; i < count; i++){
        printGuess(guesses[i], word);
    }
}

void printGuess(char guess[], char word[]){
    for (int i = 0; i < WORD_LENGTH; i++){
        if (guess[i] == word[i]){
            printf("%c", toUpper(guess[i]));
        }
        else{
            printf("%c", guess[i]);
        }
    }
    printf("\n");
    for (int i = 0; i < WORD_LENGTH; i++){
        if (inWrongSpot(guess, word, i) == true){
            printf("^");
        }
        else{
            printf(" ");
        }
    }
    printf("\n");
}

bool inWrongSpot(char guess[], char word[], int letterPosition){
    if (guess[letterPosition] == word[letterPosition]){
        return false;
    }
    for (int j = 0; j < WORD_LENGTH; j++){
        if (guess[letterPosition] == word[j] && guess[j] != word[j]){
            return true;
        }
    }
    return false;
}
