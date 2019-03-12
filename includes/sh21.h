#ifndef SH21_H
# define SH21_H

#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <term.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/ioctl.h>
#include "libft.h"
#include "get_next_line.h"

# define PRINTABLE (buffer[0] >= 32 && buffer[0] < 127)
# define CTRL_D (buffer[0] == 4 && buffer[1] == 0)
# define CTRL_C (buffer[0] == 3 && buffer[1] == 0)

# define DELETE (buffer[0] == 27 && buffer[2] == '3')
# define BACKSPACE (buffer[0] == 127 && buffer[1] == 0)

# define HOME (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72)
# define END (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70)
# define PG_UP (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 53)
# define PG_DOWN (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 54)

# define NL (buffer[0] == 10 && buffer[1] == 0)

# define ARROW_UP   (buffer[0] == 27 && buffer[2] == 'A')
# define ARROW_DOWN   (buffer[0] == 27 && buffer[2] == 'B')
# define ARROW_RIGHT (buffer[0] == 27 && buffer[2] == 'C')
# define ARROW_LEFT (buffer[0] == 27 && buffer[2] == 'D')


# define SHIFT_UP (buffer[0] == 27 && buffer[1] == 91 && buffer[2] ==  '1' && buffer[5] == 'A')
# define SHIFT_DOWN (buffer[0] == 27 && buffer[1] == 91 && buffer[2] ==  '1' && buffer[5] == 'B')
# define SHIFT_RIGHT (buffer[0] == 27 && buffer[1] == 91 && buffer[2] ==  '1' && buffer[5] == 'C')
# define SHIFT_LEFT (buffer[0] == 27 && buffer[1] == 91 && buffer[2] ==  '1' && buffer[5] == 'D')

//# define TAB (buffer[0] == 9 && buffer[1] == 0)


char **g_env;

typedef struct      s_node
{
    char            key;
    char            *line;
    struct s_node   *prev;
    struct s_node   *next;  
}                   t_node;

typedef struct      s_pos
{
    size_t          inputlen;

    size_t          nblines;
    size_t          currentline;

    struct winsize  termsize;

    size_t          row;
    size_t          column;
    size_t          startrow;
    size_t          startcolumn;
    size_t          tailrow;
    int             tailcolumn;
    size_t          saverow;
    size_t          savecolumn;

    t_node          *history;
    char            *hisbackup;
    int             historycount;
    int             historysum;

    t_node          *clipboard;
    int             selection;
    int             selectcount;
}                   t_pos;

void                welcome(void);
void	            default_term_mode(void);
void	            raw_term_mode(void);

t_node              *check_input(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos);
void                wrapping(t_pos *pos);
void                redraw(t_pos *pos, t_node *lstcursor);
void                actualize(t_pos *pos, t_node *lstcursor, t_node **input, char buffer[]);
t_node              *editline(t_pos *pos, t_node *lstcursor, t_node **input, char buffer[]);
t_node              *read_input(t_node **input, t_pos *pos);

void                savecursor(t_pos *pos);
void                cursorback(t_pos *pos);
void                get_cursor(int i, int j, char answer[], t_pos *pos);
void                stalk_cursor(t_pos *pos);
void                go_upright(t_pos *pos);
void                go_downleft(t_pos *pos);

t_node              *left(t_node *lstcursor, char buffer[], t_pos *pos);
t_node              *right(t_node *lstcursor, char buffer[], t_pos *pos);
t_node              *up(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos);
t_node              *down(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos);
t_node              *backspace(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos);
t_node              *del_key(t_node *lstcursor, t_node **input, char buffer[], t_pos *pos);
t_node              *home_end(t_node *lstcursor, char buffer[], t_pos * pos);
t_node              *backwardjump(t_node *lstcursor, char buffer[], t_pos *pos);
t_node              *forwardjump(t_node *lstcursor, char buffer[], t_pos *pos);
t_node              *ctrl_n_friends(t_node *lstcursor, char buffer[]);

void                dpush(t_node **head, char key);
void                dprintlist(t_node *node, int direction);
void                insert(t_node *prev_node, char key);
void                ddel(t_node **head, t_node *del);
void                ddellist(t_node *head);

void                print_prompt(void);
char                *reverse_str(char *inputstr);
char                *lst_to_str(t_node **input, char *inputstr);
int                 ft_outc(int c);
void                get_inputlen(t_pos *pos, t_node *input);
void                get_startingpos(t_pos *pos);
void                get_tail(t_pos *pos);
t_node              *travel_to_last(t_node *lstcursor, t_pos *pos);
char                *lst_to_str(t_node **input, char *inputstr);

void                inserthistory(t_node *prev_node, char *line, t_pos *pos);
t_node              *clean_for_history(t_node *lstcursor, t_node **input, t_pos *pos);
t_node              *history_to_lst(t_node *lstcursor, char *historyline, t_node **input, t_pos *pos);
t_node              *history_downcase(t_node *lstcursor, t_node **input, t_pos *pos);

t_node              *selectmode( char buffer[], t_pos *pos);
t_node              *shift_left(t_node *lstcursor, char buffer[], t_pos *pos);
t_node              *shift_right(t_node *lstcursor, char buffer[], t_pos *pos);

void	            init_prompt(t_pos *pos);
t_node	            *read_input(t_node **input, t_pos *pos);
char	            *prompt(t_node *input, t_pos *pos);

#endif
