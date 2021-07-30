/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 16:30:07 by edal--ce          #+#    #+#             */
/*   Updated: 2021/07/30 17:21:54 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define ZERO	SIGUSR1
#define ONE		SIGUSR2

void	receive(int sig, siginfo_t *info, void *context)
{
	static unsigned int	amt = 0;
	static char			rev_c = 0;

	(void)context;
	if (sig == SIGUSR1)
		rev_c = (rev_c << 1) + 1;
	else
		rev_c = (rev_c << 1);
	if (++amt == 8)
	{
		if (rev_c == 0)
			kill(info->si_pid, SIGUSR1);
		else
			write(1, &rev_c, 1);
		amt = 0;
		rev_c = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = receive;
	sig.sa_flags = SA_SIGINFO;
	printf("Server pid : %d\n", getpid());
	if (sigaction(SIGUSR1, &sig, NULL) != 0)
		return (write (1, "signal error\n", 13));
	if (sigaction(SIGUSR2, &sig, NULL) != 0)
		return (write (1, "signal error\n", 13));
	while (1)
		pause();
	return (0);
}
