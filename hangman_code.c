/*
Welcome to the game of hangman!

    ________
    |      |
    |      O
    |     /|\
    |     / \
    |__________

The rules are:
    * The user can guess one letter at a time.
    * The user has 6 wrong tries before the man is hanged.
    * The user should not get penalized if they guessed a correct letter multiple times.
    * The user should get penalized if they guessed a wrong letter multiple times.
    * Allow user to play again.

The program keeps check of the following:
    * The secret word.
    * The letters that have been guessed.
    * The number of wrong guesses.
    * The number of games played.
    * The number of wins.
    * The number of losses.

Practice using the following:
    * Functions
    * Pointers
    * Structs
    * File I/O

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORD_LENGTH 30
#define MAX_HINT_LENGTH 70
#define NUM_WORDS 20

struct hangman {
    char letter     ;
    char guess [10] ;
    int incorrect   ;
    int correct     ;
    int win         ;
};

struct session {
    int wins   ;
    int losses ;
    int total  ;
};

typedef struct {
    char word [MAX_WORD_LENGTH];
    char hint [MAX_HINT_LENGTH];
} wordlist;

int string_length (char *s){

    char *p = s;
    while (*p != '\0')
        p++;
    
    return p-s;

}

void printresults(int incorrect){
     if (incorrect == 0) {
        printf ("________   \n"
                "|      |   \n"
                "|          \n"
                "|          \n"
                "|          \n"
                "|_________ \n");
    } else if (incorrect == 1) {
        printf ("________   \n"
                "|      |   \n"
                "|      O   \n"
                "|          \n"
                "|          \n"
                "|_________ \n");
    } else if (incorrect == 2) {
        printf ("________   \n"
                "|      |   \n"
                "|      O   \n"
                "|     /    \n"
                "|          \n"
                "|_________ \n");
    } else if (incorrect == 3) {
        printf ("________   \n"
                "|      |   \n"
                "|      O   \n"
                "|     /|   \n"
                "|          \n"
                "|_________ \n");
    } else if (incorrect == 4) {
        printf ("________   \n"
                "|      |   \n"
                "|      O   \n"
                "|     /|\\ \n"
                "|          \n"
                "|_________ \n");
    } else if (incorrect == 5) {
        printf ("________   \n"
                "|      |   \n"
                "|      O   \n"
                "|     /|\\ \n"
                "|     /    \n"
                "|_________ \n");
    } else if (incorrect == 6) {
        printf ("________   \n"
                "|      |   \n"
                "|      O   \n"
                "|     /|\\ \n"
                "|     / \\ \n"
                "|_________ \n");
    }

}

int play_game (struct hangman *game, char *word, char *hint){
    int play = 0;
    int length = string_length(word);

    printf("There are %d letters in this word:\n\t", length);

    //Initialize guessed word array
    for(int i =0; i < length; i++){
        game->guess[i] = '_';
        printf("_");
    }

    do{
        char *p = word;
        int count = 0;

        // flag to know if the guess in incorrect
        int hang = 1; 
        
        printf("\nHint: %s", hint);
        printf("\nPlease enter your guess letter\n");
        scanf(" %c", &game->letter);

        while (*p != '\0'){
            if (game->guess[count] == game->letter){
                printf("You have guessed this letter already! Try again\n");
                hang = 0; // no penalties for guessing an existing letter correctly.
            }
            else if (game->letter == *p && game->guess[count] != *p ){
                game->guess[count] = game->letter;
                game->correct += 1;
                hang = 0; // guessed correctly so no need to hang the man.
            }
            p++;
            count++;
        }
        
        if (hang){
            printf("you have guessed incorrectly!\n"); 
            //penalties apply if they guess the same wrong letter multiple times.
            game->incorrect +=1;
        } else 
            printf("you have guessed correctly!\n"); 

        printresults(game->incorrect);

        printf("\nCurrent Guess: \n\t");

        for(int i =0; i < length; i++)
            printf("%c",game->guess[i]);

        printf("\n");
            
        if ((game->correct) == length) return 1;

    } while (game->incorrect < 6);
    return 0;
}

int readfromfile (wordlist *newlist){
    
    
    FILE *fp;
    char line [100];
    int count = 0;

    fp = fopen("game_words.txt", "r");
    if (fp == NULL){
        printf("Error opening file.\n");
        return 1;
    } 

    while (count < NUM_WORDS && fscanf(fp, " %19[^,], %69[^\n]", newlist[count].word, newlist[count].hint) == 2) {
        count++;
    }

    fclose(fp);
    return 1;
}

int main (){

    char words [][10] = {"cow", "dog", "monkey", "donkey", "deer", "snake"};
    int *playagain = 0;
    int results;
    int random_number;

    wordlist newlist[NUM_WORDS] = {0};
    readfromfile(newlist);
    

    struct session newsession = {.wins=0, .losses=0, .total=0};

    do{ 
        
        printf("Welcome to Hangman game! \n");
        printresults(0);  
        
        struct hangman newgame = {0,0,0};
        srand(time(NULL));
        random_number = rand() % 6; 

        results = play_game(&newgame, newlist[random_number].word, newlist[random_number].hint);

        if (results){
            newsession.wins += 1;
            printf("\nCongratulations! you saved the man :D\n");

        }
        else {
            newsession.losses += 1;
            printf("\nSorry! your man got hanged :( \n");
        }

        newsession.total += 1;

        printf("\n\tTotal Games: %d\n\tWins: %d\tLosses: %d\n", newsession.total, newsession.wins, newsession.losses);
        printf("\nDo you wish to play again? Yes (1) or No (0).\n");
        scanf(" %d", &playagain);


    }while(playagain > 0);

    return 0;
}