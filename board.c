/******************************************************************************
** Student name:    Darcy Morgan
** Student number:  S3659847
** Course:          Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "board.h"

Cell BOARD_1[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

Cell BOARD_2[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

void initialiseBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int boardHt = 0;
    int boardWd = 0;

    while(boardHt<=BOARD_HEIGHT){
        while(boardWd<=BOARD_WIDTH){
            board[boardHt][boardWd]=EMPTY;
            boardWd++;
        }
        boardWd=0;
        boardHt++;
    }
}

void loadBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
 Cell boardToLoad[BOARD_HEIGHT][BOARD_WIDTH])
{
    int boardHt = 0;
    int boardWd = 0;
    while(boardHt<=BOARD_HEIGHT){
        while(boardWd<=BOARD_WIDTH){
            board[boardHt][boardWd]=boardToLoad[boardHt][boardWd];
            boardWd++;
        }
        boardWd=0;
        boardHt++;
    }
}
/*header document makes placePlayer seem superflous?*/
Boolean placePlayer(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Position position)
{
    if(board[position.y][position.x]==BLOCKED){
        return FALSE;
    }
    else if(position.x >BOARD_WIDTH || position.x < 0){
        return FALSE;
    }
    else if(position.y >BOARD_HEIGHT || position.y < 0){
        return FALSE;
    }
    else{
        board[position.y][position.x]=PLAYER;
        return TRUE;
    }
}

PlayerMove movePlayerForward(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
    Position position = getNextForwardPosition(player);
    if(board[position.y][position.x]==BLOCKED){
        return CELL_BLOCKED;
    }
    else if(position.x >BOARD_WIDTH - 1|| position.x < 0){
        return OUTSIDE_BOUNDS;
    }
    else if(position.y >BOARD_HEIGHT - 1|| position.y < 0){
        return OUTSIDE_BOUNDS;
    }
    else{
        board[player->position.y][player->position.x]=EMPTY;
        board[position.y][position.x]=PLAYER;
        updatePosition(player, position);
        return PLAYER_MOVED;
    }
}

void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
    /*
    position of the console cursor relative to the top leftmost point
    in board cell units and not character units (including measurement row and column)
    starts at 1, not 0 ;)

    why does the input for this recieve the player lol
    */
    int renderHeight = 1;
    int renderWidth = 1;
    while(renderHeight<=BOARD_HEIGHT+1){
        while(renderWidth<=BOARD_WIDTH+1){
            printf("|");
            if(renderWidth==1&&renderHeight==1){
                printf(" ");
            }
            else if(renderWidth==1){
                printf("%d",renderHeight-2);
            }
            else if(renderHeight==1){
                printf("%d",renderWidth-2);
            }
            /*
            note: important for switches to approximate most common cases and 
            write them in order from most frequent to least frequent
            to improve performance (albeit tiny improvement)
            */
            else{
                switch(board[renderHeight-2][renderWidth-2]){
                    case EMPTY:
                    printf(" ");break;
                    case BLOCKED:
                    printf("*");break;
                    case PLAYER:
                    displayDirection(player->direction);break;
                }

            }


        renderWidth++;
        }
        renderWidth=1;
        renderHeight++;
        printf("|\n");
    }
    renderHeight=1;
}
