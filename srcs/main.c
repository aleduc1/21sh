#include "21s.h"

void    init_prompt(t_pos *pos)
{
    raw_term_mode();
    pos->history = NULL;
    dpush(&pos->history, 'X');
    pos->historycount = 0;
    pos->historysum = 0;
    pos->nblines = 0;
    pos->currentline = 0;
    pos->selection = 0;
    pos->whichside = 0;
}

t_node      *read_input(t_node **input, t_pos *pos)
{
    char buffer[6];
    t_node *lstcursor;
    
    lstcursor = *input;
    ft_bzero(buffer, 6);
    ft_putstr(tgetstr("im", NULL));
    while(read(STDIN_FILENO, &buffer, 6) > 0 && !NEWLINE)
    {
        lstcursor = editline(pos, lstcursor, input, buffer);
        stalk_cursor(pos);
        ft_bzero(buffer,5);
    }
    travel_to_last(lstcursor, pos);
    ft_putstr("\n");
    return (*input);
}

char  *prompt(t_node *input, t_pos *pos)
{
    char *inputstr;

    print_prompt();
    get_startingpos(pos);
    inputstr = NULL;
    input = NULL;
    dpush(&input, ' ');
    input = read_input(&input, pos);
    if (input)
    {
        inputstr = lst_to_str(&input, inputstr);
        inserthistory(pos->history, inputstr, pos);
    }
    ddellist(input);
    pos->historycount = 0;
    return (inputstr);
}

int main()
{
    t_node *input;
    t_pos pos;
    char *inputstr;

    input = NULL;
    init_prompt(&pos);
    welcome();
    while (21)
    {
        input = prompt(input, &pos);
    }
}