/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 16:30:40 by edal--ce          #+#    #+#             */
/*   Updated: 2021/07/30 17:22:52 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	ft_atoi(const char *in)
{
	int	pos;
	int	nb;

	nb = 0;
	pos = 1;
	while (*in == ' ' || *in == '	' || *in == '\n'
		|| *in == '\t' || *in == '\v' || *in == '\f' || *in == '\r')
		in++;
	if (*in == '-' && ++in)
		pos = -1;
	else if (*in == '+')
		in++;
	while (*in && *in < 58 && *in > 47)
		nb = nb * 10 + (*(in++) - '0');
	return (nb * pos);
}

unsigned int	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	send_char(int pid, char c)
{
	unsigned char	mask;
	int				i;

	i = -1;
	mask = 0b10000000;
	while (++i < 8)
	{
		if (c & mask)
		{
			if (kill(pid, SIGUSR1) == -1)
				return (write(1, "Bad PID !\n", 10));
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (write(1, "Bad PID !\n", 10));
		}
		usleep(100);
		c = c << 1;
	}
	return (0);
}

void	done(int i)
{
	(void)i;
	write(1, "Message received\n", 17);
}

int	main(int argc, char const *argv[])
{
	int				pid;
	unsigned int	len;
	unsigned int	i;

	if (argc != 3)
		return (write(1, "usage : ./client [PID] [MESSAGE]\n", 33));
	i = 0;
	signal(SIGUSR1, &done);
	if ((pid = ft_atoi(argv[1])) == 0)
		write(1, "Bad PID !\n", 10);
	len = ft_strlen(argv[2]);
	while (pid && i <= len)
		if (send_char(pid, argv[2][i++]))
			return (1);
	return (0);
}
