/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:58:59 by fvarrin           #+#    #+#             */
/*   Updated: 2021/12/08 10:31:06 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

t_binary_char	g_binary_char = {0, 0};

void	print_binary_char(void)
{
	ft_printf("%c", g_binary_char.c);
	g_binary_char.cursor = 0;
	g_binary_char.c = 0;
}

void	handle_sigusr1(
			int sig __attribute__((unused)),
			siginfo_t *info,
			void *context __attribute__((unused))
		)
{
	g_binary_char.c ^= 0;
	g_binary_char.cursor++;
	if (g_binary_char.cursor == 8)
		print_binary_char();
	else
		g_binary_char.c = g_binary_char.c << 1;
	kill(info->si_pid, SIGUSR1);
}

void	handle_sigusr2(
			int sig __attribute__((unused)),
			siginfo_t *info,
			void *context __attribute__((unused))
		)
{
	g_binary_char.c ^= 1;
	g_binary_char.cursor++;
	if (g_binary_char.cursor == 8)
		print_binary_char();
	else
		g_binary_char.c = g_binary_char.c << 1;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa_usr1;
	struct sigaction	sa_usr2;

	sa_usr1.sa_flags = SA_SIGINFO;
	sa_usr1.sa_sigaction = handle_sigusr1;
	sa_usr2.sa_flags = SA_SIGINFO;
	sa_usr2.sa_sigaction = handle_sigusr2;
	sigaction(SIGUSR1, &sa_usr1, NULL);
	sigaction(SIGUSR2, &sa_usr2, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}
