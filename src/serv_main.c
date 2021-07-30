/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 16:30:07 by edal--ce          #+#    #+#             */
/*   Updated: 2021/07/30 15:26:54 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define ZERO	SIGUSR1
#define ONE		SIGUSR2

int	receivetest(int t)
{
	static unsigned int	amt = 0;
	static char rev_c = 0;

	
	if (t == 1)
		rev_c = (rev_c << 1) + 1;
	else
		rev_c = (rev_c << 1);
	++amt;
	if (amt == 8)
	{
		write(1, &rev_c, 1);
		amt = 0;
		rev_c = 0;
	}
	return (0);
}

void	receivetest1(int i)
{
	i = 1;
	receivetest(i);
}

void	receivetest2(int i)
{
	i = 0;
	receivetest(i);
}

int	main(void)
{
	printf("Server pid : %d\n", getpid());
	signal(SIGUSR1, &receivetest1);
	signal(SIGUSR2, &receivetest2);
	while (1)
		pause();
	return (0);
}
