#include "parser.h"

t_cmd *cmd_parser(t_lex *cmd)
{
    printf("\nCMD = [");
    while (cmd)
    {
        printf("\"%s\", ", cmd->token->data);
        cmd = cmd->next;
    }
    printf("]\n");
}