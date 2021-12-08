/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:57:59 by fvarrin           #+#    #+#             */
/*   Updated: 2021/12/08 13:56:42 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_binary_message	g_binary_message = {0, NULL, 0, 0, 0};

void	print_usage(void)
{
	ft_printf("usage: ./client [server-pid] [message]\n");
	exit(-1);
}

void	send_next_bit(
			int sig __attribute__((unused)),
			siginfo_t *info __attribute__((unused)),
			void *context __attribute__((unused))
		)
{
	char	c;

	if (g_binary_message.bit_cursor == 0)
	{
		c = g_binary_message.message[g_binary_message.char_cursor++];
		if (!c)
			exit(0);
		g_binary_message.c = c;
	}
	if (g_binary_message.c & 0b10000000)
		kill(g_binary_message.pid, SIGUSR2);
	else
		kill(g_binary_message.pid, SIGUSR1);
	g_binary_message.c = g_binary_message.c << 0b1;
	g_binary_message.bit_cursor++;
	if (g_binary_message.bit_cursor == 8)
		g_binary_message.bit_cursor = 0;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
		print_usage();
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		print_usage();
	g_binary_message.pid = pid;
	g_binary_message.message = argv[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = send_next_bit;
	sigaction(SIGUSR1, &sa, NULL);
	send_next_bit(0, NULL, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
