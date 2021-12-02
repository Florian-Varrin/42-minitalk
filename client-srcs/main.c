/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:57:59 by fvarrin           #+#    #+#             */
/*   Updated: 2021/12/02 17:08:08 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_convert_binary(char *nbr, char *base_from, char *base_to)
{
	char	*dest;
	char	*additional_zeros;
	char	*sized_dest;
	int		dest_len;
	int		i;

	dest = ft_convert_base(nbr, base_from, base_to);
	dest_len = ft_strlen(dest);
	if (dest_len == 7)
		return (dest);
	else
	{
		additional_zeros = ft_calloc(7 - dest_len + 1, sizeof(char));
		i = 0;
		while (i < (7 - dest_len))
			additional_zeros[i++] = '0';
		sized_dest = ft_strjoin(additional_zeros, dest);
		free(dest);
		free(additional_zeros);
		return (sized_dest);
	}
}

char	*char_to_binary(char c)
{
	char	*ascii_value;
	char	decimal_base[11];
	char	binary_base[11];
	char	*binary_value;

	ft_build_decimalbase(decimal_base);
	ft_build_binary_base(binary_base);
	ascii_value = ft_itoa((int)c);
	binary_value = ft_convert_binary(ascii_value, decimal_base, binary_base);
	free(ascii_value);
	return (binary_value);
}

void	send_char(char *binary_value, int pid)
{
	int		i;

	i = 0;
	while (binary_value[i])
	{
		if (binary_value[i++] == '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		pid;
	int		strlen;
	char	*binary;

	if (argc != 3)
		return (-1);
	i = 0;
	strlen = ft_strlen(argv[2]);
	pid = ft_atoi(argv[1]);
	while (i < strlen)
	{
		binary = char_to_binary(argv[2][i++]);
		send_char(binary, pid);
		free(binary);
	}
	return (0);
}
