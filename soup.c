/*Library*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 100
int is_valid_option(int result){
    char inBuf[SIZE];
    /*Check for valid input between 1 and 4*/
    while(!(result >=1 && result <= 4)){
            printf("Option %d is not valid!\n\n",result);
            fgets(inBuf, SIZE, stdin);
            sscanf(inBuf, "%d", &result);
    }
    /*Return the input*/
    return result;
}
int menu(){
    /*Print out the menu to prompt user: */
    char inBuf[SIZE];
    int result;
    printf("1. Mixed Soup\n2. Alphabet soup\n3. Number soup\n4. Quit\n\nSelect an option: ");
    fgets(inBuf, SIZE, stdin);
    sscanf(inBuf, "%d", &result);
    /*Return the input put my the user*/
    return is_valid_option(result);
}

void printCharToAsciiNum(char* soup){
    int i;
    char change = '\0';
    /*Make soup into soup code for number*/
    printf("Soup Code: ");
    for(i = 0; i < 10; i++){
        change = (int)soup[i];
        printf("%d",change);
    }
    printf("\n");
}

void printCharToAsciiMix(char* soup){
    int i;
    char change = '\0';
    /*Make soup into soup code for mixed and alphabet*/
    printf("Soup Code: ");
    for(i = 0; i < 10; i++){
        change = (int)soup[i];
        if(change < 100){
            printf("0%d",change);
        }
        else{
           printf("%d",change);
        }
    }
    printf("\n");
}

void score_status(char* gameSoup, char* playerSoup, char* botSoup, int*playerMatchPoint, int*botMatchPoint, int* playerRoundPoint, int* botRoundPoint, int* whichCase, char name[]){
    int j;
    int pCount=0, bCount=0;
    /*Get the number of match player have by looping through the array*/
    printf("%s's soup: ",name);
    printf("\"%s\"\n", playerSoup);
    if((*whichCase) == 1 || (*whichCase) ==2){
    printCharToAsciiMix(playerSoup);
    }
    else{
        printCharToAsciiNum(playerSoup);
    }
    for(j = 0;j < 10; j++){
        if(gameSoup[j] == playerSoup[j]){
            (*playerMatchPoint)+=1;
            pCount+= 1;
        }
    }
    /*Correctly printing the match by looping through it again*/
    printf("Match: %d [", pCount);
    pCount = 0;
    for(j = 0;j < 10; j++){
        if(gameSoup[j] == playerSoup[j]){
            pCount+= 1;
            printf("X");
        }
        else{
            printf("-");
        }
    }
    printf("]\n");

    //Bot
    printf("\n");
    /*Get the number of match bot have*/
    printf("Bot soup: ");
    printf("\"%s\"\n", botSoup);
    if((*whichCase) == 1 || (*whichCase) ==2){
    printCharToAsciiMix(botSoup);
    }
    else{
        printCharToAsciiNum(botSoup);
    }
    for(j = 0;j < 10; j++){
        if(gameSoup[j] == botSoup[j]){
            (*botMatchPoint) += 1;
            bCount+=1;
        }
    }
    /*Correctly printing the match*/
    printf("Match: %d [", bCount);
    bCount = 0;
    for(j = 0;j < 10; j++){
        if(gameSoup[j] == botSoup[j]){
            bCount+=1;
            printf("X");
        }
        else{
            printf("-");
        }
    }
    printf("]\n");

    /*Calculating the point at the end of a round*/
    if(pCount > bCount){
        (*playerRoundPoint) += 5;
    }
    else if(pCount < bCount){
        (*botRoundPoint) += 5;
    }
    else{
        (*playerRoundPoint) +=2;
        (*botRoundPoint) += 2;
    }
    printf("\n%s; Matchpoint: %d; Roundpoint: %d\n",name , *playerMatchPoint, *playerRoundPoint);
    printf("Bot; Matchpoint: %d; Roundpoint: %d\n", *botMatchPoint, *botRoundPoint);

}

void mixed_soup(char* inputSoup){
    int j;
    char var;
    /*Make the array passed in into a mixed soup*/
    for(j = 0; j < 10; j++){
        var = rand() % 94 + 33;

    if(strchr(inputSoup, var) == NULL){
        inputSoup[j] = var;
        inputSoup[j+1] = '\0';
    }
    else{
        j -= 1;
        continue;
    }
    }
}


void alphabet_soup(char* inputSoup){
    int j;
    char var;
    /*Make the array passed in into a alphabet soup*/
    for(j = 0; j < 10; j++){
        char bigOrSmall = rand() % 2;
        if(bigOrSmall == 0){
            var = rand() % 26 + 97;
        }
        else{
            var = rand() % 26 + 65;
        }
        if(strchr(inputSoup, var) == NULL){
            inputSoup[j] = var;
            inputSoup[j+1] = '\0';
        }
        else{
            j -= 1;
            continue;
        }
    }
}

void number_soup(char* inputSoup) {
    int usedDigits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int j;
    char var;
    /*Make the array passed in into a number soup by storing the already used as 1 and the blank as 0 in another array*/
    for (j = 0; j < 10; j++) {
        do {
            var = rand() % 10 + 48;
        } while (usedDigits[var - '0'] != 0);

        inputSoup[j] = var;
        usedDigits[var - '0'] = 1;
    }

    inputSoup[10] = '\0';
}



void reset_soup(char* inputSoup){
    int i;
    //Reset the soup
    for(i = 0; i < 10; i++){
        inputSoup[i] = rand();
    }
    inputSoup[10] = '\0';
}

int ifContainOnlyLetter(char name[]){
    int i;
    for(i = 0; i< strlen(name); i++){
        if(!(((int)name[i] >= 65 && (int)name[i] <= 122)||(int)name[i] == 32)){
            return 0;
        }
    }
    return 1;
}


int main(){
    char inBuf[SIZE];
    char name[SIZE];
    int selectedOpt;
    int end = 0;
    char enter;
    /*Seed*/
    srand(time(NULL));
    /*Loop so that can replay*/
    do{
    int n =0;
    int playerMatchPoint=0, botMatchPoint=0, playerRoundPoint=0, botRoundPoint=0;
    /*Print out the welcome message*/
    printf("**********************************\n*   Welcome to Character Soup   *\n**********************************\n");
    printf("Player's name: ");
    fgets(inBuf, SIZE, stdin);
    sscanf(inBuf, "%[^\n]", name);
    /*Ensure that the length of the name is only 25 char or less*/
    while(strlen(name) ==0 ||strlen(name) > 25 || ifContainOnlyLetter(name)==0){
        printf("Please re-enter your name \n");
        fgets(inBuf, SIZE, stdin);
        sscanf(inBuf, "%[^\n]", name);
    }
    printf("\n");
    selectedOpt = menu();
    // int i,j;
    char gameSoup[SIZE];
    char playerSoup[SIZE];
    char botSoup[SIZE];
    int whichCase = 0;
    /*Switch statement for which type of soup the user enter*/
    switch (selectedOpt)
    {
    case 1:
    /*This variable is for score point to know which Soup code generator to use as number only need 2 ASCII while other need 3*/
    whichCase =1;
    printf("**********************************\n*   Mixed Soup   *\n**********************************\n");
    printf("%s,             match points: 0  round points: 0\n", name);
    printf("Computer,       match points: 0  round points: 0\n");
    printf("\n[Play]\n\n");
    fgets(inBuf, SIZE, stdin);
    sscanf(inBuf, "%c", &enter);
    /*While loop for 10 round (Could have do for loop)*/
    while(n < 10){
        n += 1;
        printf("Round helo: %d/10\n",n );
        /*Change the array into mixed soup*/
        mixed_soup(gameSoup);
        mixed_soup(playerSoup);
        mixed_soup(botSoup);


        printf("Soup: \"%s\"\n", gameSoup);
        printCharToAsciiMix(gameSoup);
        printf("************************************\n");

        /*Call score status at the end of each round*/
        score_status(gameSoup, playerSoup, botSoup, &playerMatchPoint, &botMatchPoint, &playerRoundPoint, &botRoundPoint, &whichCase, name);
        printf("\n");
        printf("[Continue]\n\n");
        /*Click anything to move on*/
        fgets(inBuf, SIZE, stdin);
        sscanf(inBuf, "%c", &enter);
    }

    /*Score evaluation */
    printf("%s, score: %d\n\t ", name, playerMatchPoint + playerRoundPoint);
    printf("match points: %d round points: %d\n",playerMatchPoint, playerRoundPoint);
    printf("Computer, score: %d\n\t ", botMatchPoint + botRoundPoint);
    printf("match points: %d round points: %d\n\n",botMatchPoint, botRoundPoint);

    /*Check the winner by comparing the sum of round and match point*/
    if(playerMatchPoint + playerRoundPoint > botMatchPoint + botRoundPoint){
        printf("%s won this game.\n\n", name);
    }
    else if (playerMatchPoint + playerRoundPoint < botMatchPoint + botRoundPoint){
        printf("Computer won this game.\n\n");
    }
    else{
        printf("The game ended in a tie.\n\n");
    }
    break;
    case 2:
    whichCase =2;
    printf("**********************************\n*   Alphabet Soup   *\n**********************************\n");
    printf("%s,             match points: 0  round points: 0\n", name);
    printf("Computer,       match points: 0  round points: 0\n");
    printf("\n[Play]\n\n");
    fgets(inBuf, SIZE, stdin);
    sscanf(inBuf, "%c", &enter);
    while(n < 10){
        n+= 1;
        printf("Round: %d/10\n",n );

        /*Make all the soup into alphabet soup*/
        alphabet_soup(gameSoup);
        alphabet_soup(playerSoup);
        alphabet_soup(botSoup);

        printf("Soup: \"%s\"\n", gameSoup);
        printCharToAsciiMix(gameSoup);
        printf("************************************\n");

        /*Called score status at the end of each round*/
        score_status(gameSoup, playerSoup, botSoup, &playerMatchPoint, &botMatchPoint, &playerRoundPoint, &botRoundPoint, &whichCase, name);
        printf("\n");
        
        printf("[Continue]\n\n");
        /*Click anything to move on*/
        fgets(inBuf, SIZE, stdin);
        sscanf(inBuf, "%c", &enter);

    }
    /*Score evluation and winner of the match*/
    printf("%s, score: %d\n\t ", name, playerMatchPoint + playerRoundPoint);
    printf("match points: %d round points: %d\n",playerMatchPoint, playerRoundPoint);
    printf("Computer, score: %d\n\t ", botMatchPoint + botRoundPoint);
    printf("match points: %d round points: %d\n\n",botMatchPoint, botRoundPoint);
    if(playerMatchPoint + playerRoundPoint > botMatchPoint + botRoundPoint){
        printf("%s won this game.\n\n", name);
    }
    else if (playerMatchPoint + playerRoundPoint < botMatchPoint + botRoundPoint){
        printf("Computer won this game.\n\n");
    }
    else{
        printf("The game ended in a tie.\n\n");
    }
        break;

    case 3:
    whichCase =3;
    printf("**********************************\n*   Number soup   *\n**********************************\n");
    printf("%s,             match points: 0  round points: 0\n", name);
    printf("Computer,       match points: 0  round points: 0\n");
    printf("\n[Play]\n\n");
    fgets(inBuf, SIZE, stdin);
    sscanf(inBuf, "%c", &enter);
    /*Loop*/
    while(n < 10){
        n+=1;
        printf("Round: %d/10\n",n );

        /*Change the array into number soup*/
        number_soup(gameSoup);
        number_soup(playerSoup);
        number_soup(botSoup);

        printf("Soup: \"%s\"\n", gameSoup);
        printCharToAsciiNum(gameSoup);
        printf("************************************\n");

        /*Score at the end of each round*/
        score_status(gameSoup, playerSoup, botSoup, &playerMatchPoint, &botMatchPoint, &playerRoundPoint, &botRoundPoint, &whichCase, name);
        printf("\n");            printf("[Continue]\n\n");
        fgets(inBuf, SIZE, stdin);
        sscanf(inBuf, "%c", &enter);
        
    }
    /*Score announcement and Winner*/
    printf("%s, score: %d\n\t ", name, playerMatchPoint + playerRoundPoint);
    printf("match points: %d round points: %d\n",playerMatchPoint, playerRoundPoint);
    printf("Computer, score: %d\n\t ", botMatchPoint + botRoundPoint);
    printf("match points: %d round points: %d\n\n",botMatchPoint, botRoundPoint);
    if(playerMatchPoint + playerRoundPoint > botMatchPoint + botRoundPoint){
        printf("\n%s won this game.\n\n", name);
    }
    else if (playerMatchPoint + playerRoundPoint < botMatchPoint + botRoundPoint){
        printf("\nComputer won this game.\n\n");
    }
    else{
        printf("\nThe game ended in a tie.\n\n");
    }
    break;
    case 4:
    /*End the program by existing the loop*/
        end = 1;
        printf("Good bye\n");
        break;
    }
    /*If the end is 1 then exist (only when chose option 4)*/
    if(end != 1){
        printf("\n[Return to menu]\n\n");
        fgets(inBuf, SIZE, stdin);
        sscanf(inBuf, "%c", &enter);
    }
    }while(end != 1);
    return 0;
}
