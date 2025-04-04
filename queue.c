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
    while(temp != NULL)
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

    return true;

}

//check whether the tiles of two game states are the same
static bool same_tiles(struct game_state currentState, struct game_state toCompare)
{
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 4; c++)
        {
            if(currentState.tiles[r][c] != toCompare.tiles[r][c])
            {
                return false;
            }
        }
    }
    
    return true;

}


void enqueue(struct queue *q, struct game_state state) {
    size_t toAdd = serialize(state);
    insert_at_head(&(q -> data), toAdd);

    return;
    
}

struct game_state dequeue(struct queue *q) { 
    size_t toCompare = remove_from_tail(&(q -> data));

    return deserialize(toCompare); 
}

int number_of_moves(struct game_state start) {
    struct queue q;
    q.data.head = NULL;

    struct game_state complete;

    //initialize here
    complete.empty_row = 3;
    complete.empty_col = 3;
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
    complete.tiles[3][3] = 0;

    enqueue(&q, start);

    
    while(q.data.head != NULL)
    {
        struct game_state temp = dequeue(&q);
        if(same_tiles(temp, complete))
        {
            free_list(q.data);
            return temp.num_steps;
        }
        else
        {
            if(temp.empty_col != 3)
            {
                struct game_state left = temp; 
                move_left(&left);

                if(checker(&q, left))
                {
                    enqueue(&q, left);
                }
            }
            
            if(temp.empty_col != 0)
            {
                struct game_state right = temp; 
                move_right(&right);

                if(checker(&q, right))
                {
                    enqueue(&q, right);
                }
            }
            
            if(temp.empty_row != 3)
            {
                struct game_state up = temp; 
                move_up(&up);

                if(checker(&q, up))
                {
                    enqueue(&q, up);
                }
            }

            if(temp.empty_row != 0)
            {
                struct game_state down = temp; 
                move_down(&down);

                if(checker(&q, down))
                {
                    enqueue(&q, down);
                }
            }
        }
    }
    
    return -1; 
}
