/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:58:59 by fvarrin           #+#    #+#             */
/*   Updated: 2021/12/02 17:12:37 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

t_binary_char	g_binary_char = {{0}, 0};

void	print_binary_char(void)
{
	char	decimal_base[11];
	char	binary_base[11];
	char	*decimal_value;
	char	*binary_value;
	int		ascii_value;

	ft_build_decimalbase(decimal_base);
	ft_build_binary_base(binary_base);
	binary_value = g_binary_char.binary_value;
	decimal_value = ft_convert_base(binary_value, binary_base, decimal_base);
	ascii_value = ft_atoi(decimal_value);
	free(decimal_value);
	ft_printf("%c", ascii_value);
	g_binary_char.cursor = 0;
}

void	handle_sigusr1(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	(void) info;
	g_binary_char.binary_value[g_binary_char.cursor] = '0';
	g_binary_char.cursor++;
	if (g_binary_char.cursor == 7)
		print_binary_char();
}

void	handle_sigusr2(int sig, siginfo_t *info, void *context)
{
	(void) sig;
	(void) context;
	(void) info;
	g_binary_char.binary_value[g_binary_char.cursor] = '1';
	g_binary_char.cursor++;
	if (g_binary_char.cursor == 7)
		print_binary_char();
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
