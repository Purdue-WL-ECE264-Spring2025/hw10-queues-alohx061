#include "queue.h"
#include "tile_game.h"

static bool checker(struct queue *q, struct game_state state);
static bool same_tiles(struct game_state current, struct game_state toAdd);

//check whether you can enqueue
static bool checker(struct queue *q, struct game_state state)
{
    size_t toAdd = serialize(state);
    
    //check if the state has not been entered
    struct list_node* temp = (q -> data).head;
    while(temp -> next != NULL)
    {
        if(temp -> value == toAdd)
        {
            return false;
        }
        if(same_tiles(deserialize(temp -> value), state))
        {
            return false;
        }
        temp = temp -> next;
    }

    if(temp -> value != toAdd && same_tiles(deserialize(temp -> value), state))
    {
        return false;
    }
    return true;

}

//check whether the tiles of two game states are the same
static bool same_tiles(struct game_state currentState, struct game_state toCompare)
{
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            if(currentState.tiles[r][c] == toCompare.tiles[r][c])
            {
                return true;
            }
        }
    }
    
    return false;

}


void enqueue(struct queue *q, struct game_state state) {
    size_t toAdd = serialize(state);
    insert_at_tail(&(q -> data), toAdd);

    return;
    
}

struct game_state dequeue(struct queue *q) { 
    size_t toCompare = remove_from_head(&(q -> data));

    return deserialize(toCompare); 
}

int number_of_moves(struct game_state start) {
    struct queue q;

    struct game_state complete;

    //initialize here
    complete.empty_row = 0;
    complete.empty_col = 0;
    complete.num_steps = 0;
    int counter = 1;
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            complete.tiles[r][c] = counter;
            counter++;
        }
    }
    complete.tiles[4][4] = 0;

    if(checker(&q, start))
    {
        enqueue(&q, start);
    }
    
    while(q.data.head -> next != NULL)
    {
        struct game_state temp = dequeue(&q);
        if(same_tiles(temp, complete))
        {
            return temp.num_steps;
        }
        else
        {
            struct game_state left = temp; 
            move_left(&temp);
            left.num_steps++;

            struct game_state right = temp; 
            move_right(&temp);
            right.num_steps++;

            struct game_state up = temp; 
            move_up(&temp);
            up.num_steps++;

            struct game_state down = temp; 
            move_down(&temp);
            down.num_steps++;

            enqueue(&q, left);
            enqueue(&q, right);
            enqueue(&q, up);
            enqueue(&q, down);
        }

    }
    
    return -1; 
}
