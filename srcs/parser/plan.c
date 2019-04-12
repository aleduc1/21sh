/*
** Goal :
** Regroup tokens into simple commands
** Create a token command for simple commands
** In it we will put every token between operator, so a LL
** 
** Coding :
** From the last cut point to the new one, we need to split this part of the LL
** And put it into a simple command token
** Once part of the LL is detached , connect it to a simple command token's node
** 
** Steps :
** 1- Identifying start and end of the part of the LL to detach
** 		Can be broken down into 2 step
** 2- Detach it
** 3- Create a command token with the LL in it
** 4- Attach it to the LL
** 5- Move pointer for whats after the cmd token's node and repeat if its not finished
**
** Breakdown :
** 1:
** - Set start at first node after delim or operators if node exist
** - Set end the node before an operator or delim (iterate from start)
** 2:
** - Save pointer of node before start
** - Save pointer of node after end
** - Set first_ptr->next to NULL
** - Set second_ptr->previous to NULL
** - Set start->previous to NULL
** - Set end->next to NULL
** 3:
** - Create a token command
** - Put &start in token->data (maybe make data in token type void* to be able to cast it t_type or LL) (Or create a token type LL, create another token struct to add a LL, and do with that)
** 4:
** - Create a node of a LL with the token in it
** - Link next and prev the the two ptr saved at step 2
** 5:
** - Start step 1 again with the second_ptr as param
*/
