/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:28 by aleduc            #+#    #+#             */
/*   Updated: 2019/03/12 17:19:32 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	default_term_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
}

void	raw_term_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tgetent(NULL, getenv("TERM"));
}
