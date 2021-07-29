/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 16:30:07 by edal--ce          #+#    #+#             */
/*   Updated: 2021/07/29 17:00:49 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "server.h"
#include <stdio.h>
#include <signal.h>

#define ZERO	SIGUSR1
#define ONE		SIGUSR2

void	receivetest(int t)
{
	static unsigned int	amt = 0;
	static unsigned int	rev_c = 0;

	if (amt == 8)
	{
		write(1, &rev_c, 1);
		amt = 0;
		rev_c = 0;
	}
	if (t == 1)
		rev_c = (rev_c << 1) + 1;
	else
		rev_c = (rev_c << 1);
	++amt;
}

void	receivetest1(void)
{
	receivetest(1);
}

void	receivetest2(void)
{
	receivetest(0);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	printf("Server pid %d\n", pid);
	signal(SIGUSR1, &receivetest1);
	signal(SIGUSR2, &receivetest2);
	while (1)
		pause();
	return (0);
}
