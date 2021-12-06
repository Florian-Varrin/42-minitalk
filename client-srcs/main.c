/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:57:59 by fvarrin           #+#    #+#             */
/*   Updated: 2021/12/06 10:29:36 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_usage(void)
{
	ft_printf("usage: ./client [server-pid] [message]\n");
	exit(-1);
}

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		pid;
	int		strlen;
	char	c;

	if (argc != 3)
		print_usage();
	i = 0;
	j = 0;
	strlen = ft_strlen(argv[2]);
	pid = ft_atoi(argv[1]);
	while (i < strlen)
	{
		c = argv[2][i++];
		j = 0;
		while (j < 8) {
			if (c & 0b10000000)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			c = c << 0b1;
			j++;
			usleep(100);
		}
		usleep(1000);
	}
	return (0);
}
