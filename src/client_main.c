/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 16:30:40 by edal--ce          #+#    #+#             */
/*   Updated: 2021/07/29 17:25:20 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
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
	if (*in == '-')
	{
		pos = -1;
		in++;
	}
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

int	usage(void)
{
	write(1, "usage : ./client [PID] [MESSAGE]\n", 33);
	return (1);
}

void	send_char(int pid, char c)
{
	unsigned char	mask;
	unsigned int	i;

	i = 0;
	mask = 0b10000000;
	while (i < 8)
	{
		if (c & mask)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		c = c << 1;
		++i;
	}
}

int	main(int argc, char const *argv[])
{
	int				pid;
	unsigned int	len;
	unsigned int	i;

	if (argc != 3)
		return (usage());
	i = 0;
	pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	while (i < len)
		send_char(pid, argv[2][i++]);
	return (0);
}
