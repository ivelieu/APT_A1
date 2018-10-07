/******************************************************************************
** Student name:    Darcy Morgan
** Student number:  S3659847
** Course:          Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "game.h"

CommandStage activeStage;
Cell board[BOARD_HEIGHT][BOARD_WIDTH];
Player* mainPlayer;
void playGame(){
    printf("You can use the following commands to play the game:\n");
    printf("%s <g>\n", COMMAND_LOAD);
    printf("\tg: number of the game board to load\n");
    printf("%s <x>,<y>,<direction>\n", COMMAND_INIT);
    printf("\tx: horizontal position of the car on the board (between 0 and %d)\n"\
        ,BOARD_WIDTH);
    printf("\ty: vertical position of the car on the board (between 0 and %d)\n"\
        ,BOARD_HEIGHT);
    printf("direction: direction of the car\'s movement (%s, %s, %s, %s)\n", \
        DIRECTION_NORTH, DIRECTION_SOUTH, DIRECTION_EAST, DIRECTION_WEST);
    printf("%s (or %s)", COMMAND_FORWARD, COMMAND_FORWARD_SHORTCUT);
    printf("%s (or %sl)\n", COMMAND_TURN_LEFT, COMMAND_TURN_LEFT_SHORTCUT);
    printf("%s (or %s)\n", COMMAND_TURN_RIGHT, COMMAND_TURN_RIGHT_SHORTCUT);
    printf("%s\n", COMMAND_QUIT);
    activeStage = LOAD;

    initialiseBoard(board);
    displayBoard(board, NULL);
    while(1){
        if(activeStage == RETURN){
            break;
        }
        chooseGameMenu();
    }
}

void chooseGameMenu(){
    char* choice = "";
    int tokensUsed;
    /*
    c string arrays are confusing
    this is to read each argument as a seperate component
    */
    char** tokenSet = malloc(MAX_TOKENS * sizeof(char));
    int i;/*iterator for multiple loops in this function*/
    for(i=0;i<MAX_TOKENS;i++){
        tokenSet[i] = malloc(MAX_INPUT + NULL_SPACE);
    } 


    choice = malloc(MAX_INPUT * sizeof(char));
    showGameMenu();
    choice = getStringSafe(MAX_INPUT);
    if(strcmp(choice, "4")==0 || strcmp(choice, "")==0){
        printf("Invalid input.\n");
        return;
    }

    i=0;
    tokenSet[i] = strtok(choice, " ");
    i++;

    while(i<MAX_TOKENS*sizeof(char)){
        tokenSet[i]=strtok(NULL, ",");
        if(tokenSet[i]==NULL)break;
        i++;
    }
    tokensUsed = i;

    /*
    each active stage has its own function for checking
    valid commands and executing them. while this does repeat a few lines of
    code for similar commands across stages, i believed this to be the
    most effective solution for splitting functions (to
    maintain readibility of code)

    note: board initilization is handled before activeStage.LOAD
    activeStage.INIT refers to player initilization
    */
    if (activeStage==LOAD)
    {
        loadCommandSet(tokenSet, tokensUsed);
    }
    else if (activeStage==INIT)
    {
        initCommandSet(tokenSet, tokensUsed);
    }
    else if (activeStage==PLAY)
    {
        playCommandSet(tokenSet, tokensUsed);
    }   
}
void loadCommandSet(char** tokenSet, int tokensUsed){
    /*load command*/
    if(strcmp(COMMAND_LOAD, tokenSet[0])==0){
        if(tokensUsed == 2 && strcmp(tokenSet[1], "1") == 0){
            loadBoard(board, BOARD_1);
            activeStage = INIT;
        }
        else if(tokensUsed == 2 && strcmp(tokenSet[1], "2") == 0){
            loadBoard(board, BOARD_2);
            activeStage = INIT;
        }
        else{
            printf("invalid input.\n");
        }
        displayBoard(board, NULL);
    }
    /*quit command*/
    else if(strcmp(COMMAND_QUIT, tokenSet[0])==0){
        activeStage = RETURN;
    }
    else{
        printf("Invalid input.\n");
        displayBoard(board, NULL);
    }
}
void initCommandSet(char** tokenSet, int tokensUsed){    
/*load command*/
    if(strcmp(COMMAND_LOAD, tokenSet[0])==0){
        if(tokensUsed == 2 && strcmp(tokenSet[1], "1") == 0){
            loadBoard(board, BOARD_1);
        }
        else if(tokensUsed == 2 && strcmp(tokenSet[1], "2") == 0){
            loadBoard(board, BOARD_2);
        }
        else{
            goto invalid;
        }
    }
    /*quit command*/
    else if(tokensUsed == 1 && strcmp(COMMAND_QUIT, tokenSet[0])==0){
        activeStage = RETURN;
    }

    /*init command*/
    else if(tokensUsed == 4 && strcmp(COMMAND_INIT, tokenSet[0])==0){

        Direction direction;
        Position* position;

        int x = atoi(tokenSet[1]);
        int y = atoi(tokenSet[2]);
        if(x==0 && strcmp(tokenSet[1], "0")!=0){
            goto invalid;
        }
        else if(y==0 && strcmp(tokenSet[2], "0")!=0){
            goto invalid;
        }
        /*validating input as integers
        then setting direction and the location
        to the global Player struct called player*/

        if(strcmp(tokenSet[3], DIRECTION_NORTH)==0){
            direction = NORTH;
        }
        else if(strcmp(tokenSet[3], DIRECTION_SOUTH)==0){
            direction = SOUTH;
        }
        else if(strcmp(tokenSet[3], DIRECTION_WEST)==0){
            direction = WEST;
        }
        else if(strcmp(tokenSet[3], DIRECTION_EAST)==0){
            direction = EAST;
        }
        else{
            goto invalid;
        }

        mainPlayer=malloc(64);
        position = malloc(2*sizeof(int));
        position->x = x; 
        position->y = y;
        initialisePlayer(mainPlayer, position, direction);
        if(placePlayer(board, mainPlayer->position)==FALSE){
            printf("Invalid input: The player cannot initialise there!\n");

            displayBoard(board, mainPlayer);
            return;
        }
        activeStage = PLAY;

    }
    else{
        /*this is one of the more powerful uses of goto*/
        /*shame i didn't use more, right?*/
        invalid:
        printf("Invalid input.\n");
        displayBoard(board, NULL);
        return;
    }
    displayBoard(board, mainPlayer);
}
void playCommandSet(char** tokenSet, int tokensUsed){
    if(tokensUsed != 1){
        /*this means I don't need to evaluate tokensUsed below*/
        printf("Invalid input.\n");
        displayBoard(board, mainPlayer);
        return;
    }
    /*forward command*/
    if((strcmp(COMMAND_FORWARD, tokenSet[0])==0 \
        || strcmp(COMMAND_FORWARD_SHORTCUT, tokenSet[0])==0)){
        PlayerMove pm = movePlayerForward(board, mainPlayer);
        if(pm == CELL_BLOCKED){
            printf("Error: cannot move forward because the road is blocked. \n");
        }
        else if(pm == OUTSIDE_BOUNDS){
            printf("Error: The car is at the edge of the board"
                " and cannot move further in that direction\n");
        }
        else{
        mainPlayer->moves++;
        }
    }
    /*turn commands*/
    else if((strcmp(COMMAND_TURN_LEFT, tokenSet[0])==0) \
        || strcmp(COMMAND_TURN_LEFT_SHORTCUT, tokenSet[0])==0){
        turnDirection(mainPlayer,TURN_LEFT);
    }
    else if((strcmp(COMMAND_TURN_RIGHT, tokenSet[0])==0) \
        || strcmp(COMMAND_TURN_RIGHT_SHORTCUT, tokenSet[0])==0){
        turnDirection(mainPlayer,TURN_RIGHT);
    }

    /*quit command*/
    else if(strcmp(COMMAND_QUIT, tokenSet[0])==0){
        printf("Total player moves: %d\n", mainPlayer->moves/2);
        activeStage = RETURN;
        return;
    }
    else{
        printf("Invalid input.\n");
    }
    displayBoard(board, mainPlayer);

}






void showGameMenu(){
    printf("Currently acceptable commands:\n");
    if (activeStage==LOAD)
    {
        printf("%s <g>\n", COMMAND_LOAD);
        printf("%s\n\n", COMMAND_QUIT);
    }
    else if (activeStage==INIT)
    {
        printf("%s <g>\n", COMMAND_LOAD);
        printf("%s <x>,<y>,<direction>\n", COMMAND_INIT);
        printf("%s\n\n", COMMAND_QUIT);
    }
    else if (activeStage==PLAY)
    {
        printf("%s (or %s)", COMMAND_FORWARD, COMMAND_FORWARD_SHORTCUT);
        printf("%s (or %sl)\n", COMMAND_TURN_LEFT, COMMAND_TURN_LEFT_SHORTCUT);
        printf("%s (or %s)\n", COMMAND_TURN_RIGHT, COMMAND_TURN_RIGHT_SHORTCUT);
        printf("%s\n\n", COMMAND_QUIT);
    }
}