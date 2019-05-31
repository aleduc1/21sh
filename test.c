/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 14:46:52 by sbelondr          #+#    #+#             */
/*   Updated: 2019/05/19 15:27:03 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

static int	g_cmd_num;

static void	handler(int sig)
{
	if (getpid() == getpgrp())
		printf("fg process group: %ld\n", (long)tcgetpgrp(STDERR_FILENO));
	printf("Process %ld (%d) receive signal %d (%s)\n", (long)getpid(),
			g_cmd_num, sig, strsignal(sig));
	if (sig == SIGTSTP)
		raise(SIGSTOP);
}

int main(int ac, char **av)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		printf("sigaction\n");
		exit(0);
	}
	if (sigaction(SIGTSTP, &sa, NULL) == -1)
	{
		printf("sigaction\n");
		exit(0);
	}
	if (sigaction(SIGCONT, &sa, NULL) == -1)
	{
		printf("sigaction\n");
		exit(0);
	}

	g_cmd_num++;
	printf("%4d\t %5ld %5ld %5ld %5ld\n", g_cmd_num, (long)getpid(), (long)getppid(),
			(long)getpgrp(), (long)getsid(0));
	for(;;)
		pause();
	return (0);
}
