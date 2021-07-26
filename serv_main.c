/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 16:30:07 by edal--ce          #+#    #+#             */
/*   Updated: 2021/07/26 16:48:05 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "server.h"
#include <signal.h>
int handler(int code)
{
	printf("we got code %d", code);
	return 1;
}
int main()
{
	pid_t pid = getpid();
	printf("Server pid %d\n", pid);
	signal(SIGUSR1, handler);
	while (1)
	{

	}
	return 0;
}