    /******************************************************************************
** Student name:    Darcy Morgan
** Student number:  S3659847
** Course:          Advanced Programming Techniques - S1 2018
******************************************************************************/
#include "player.h"

void initialisePlayer(Player * player, Position * position, Direction direction)
{
    player->position.x = position->x;
    player->position.y = position->y;
    player->direction = direction;
    player->moves = 0;
}

void turnDirection(Player * player, TurnDirection turnDirection)
{
    /* maybe there is a way to only have one player->direction switch + turnDirection switch? 
    i think this is the more efficient method */
    switch(turnDirection){
    	case TURN_RIGHT:
    	switch(player->direction){
    		case NORTH:
    		player->direction=EAST;return;
    		case EAST:
    		player->direction=SOUTH;return;
    		case SOUTH:
    		player->direction=WEST;return;
    		case WEST:
    		player->direction=NORTH;return;
    	}
    	case TURN_LEFT:
    	switch(player->direction){
    		case NORTH:
    		player->direction=WEST;return;
    		case EAST:
    		player->direction=NORTH;return;
    		case SOUTH:
    		player->direction=EAST;return;
    		case WEST:
    		player->direction=SOUTH;return;
    	}

    }

}

Position getNextForwardPosition(const Player * player)
{
    Position position = player->position;
    switch(player->direction){
    	case NORTH:
    	position.y--;break;
    	case EAST:
    	position.x++;break;
    	case SOUTH:
    	position.y++;break;
    	case WEST:
    	position.x--;break;
    }

    return position;
}

void updatePosition(Player * player, Position position)
{
	player->position = position;
    player->moves++;
}

void displayDirection(Direction direction)
{
	switch(direction){
		case NORTH:
		printf(DIRECTION_ARROW_OUTPUT_NORTH);break;
		case EAST:
		printf(DIRECTION_ARROW_OUTPUT_EAST);break;
		case SOUTH:
		printf(DIRECTION_ARROW_OUTPUT_SOUTH);break;
		case WEST:
		printf(DIRECTION_ARROW_OUTPUT_WEST);break;
	}
}
