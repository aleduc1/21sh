/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othertools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/12 18:41:37 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void welcome(void)
{
    ft_putstr("\033[1;32m\n");                                                                   
    ft_putstr("██████╗  ██╗███████╗██╗  ██╗\n");
    usleep(150000);
    ft_putstr("╚════██╗███║██╔════╝██║  ██║\n");
    usleep(150000);
    ft_putstr(" █████╔╝╚██║███████╗███████║\n");
    usleep(150000);
    ft_putstr("██╔═══╝  ██║╚════██║██╔══██║\n");
    usleep(150000);
    ft_putstr("███████╗ ██║███████║██║  ██║\n");
    usleep(150000);
    ft_putstr("╚══════╝ ╚═╝╚══════╝╚═╝  ╚═╝\n\n");
    ft_putstr("\033[0m");
}

char *reverse_str(char *inputstr)
{
    char *start = inputstr;
    int len = ft_strlen(inputstr);
    char *end = (inputstr + len - 1);

    while(start < end )
    {
        *start = *start ^ *end;
        *end = *end ^ *start;
        *start = *end ^ *start;
        start++;
        end--;
    }
    return (inputstr);
}

char *lst_to_str(t_node **input, char *inputstr)
{
    t_node *cpycursor;
    int i;

    i = 0;
    cpycursor = (*input)->next;
    inputstr = NULL;
    inputstr = malloc(sizeof(char) * 4096);
    while(cpycursor != NULL)
    {
        inputstr[i] = cpycursor->key;
        cpycursor = cpycursor->next;
        i++;
    }
    inputstr[i] = '\0';
    inputstr = reverse_str(inputstr);
    ft_putstr(inputstr);
    ft_putstr("\n");
    return(inputstr);
}
