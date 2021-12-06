/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:59:15 by fvarrin           #+#    #+#             */
/*   Updated: 2021/12/06 11:23:46 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

typedef struct s_binary_char {
	char	c;
	int		cursor;
}	t_binary_char;

typedef struct s_binary_message {
	int		pid;
	char	*message;
	char	c;
	int		bit_cursor;
	int		char_cursor;
}	t_binary_message;
#endif
