/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/27 13:37:30 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Define POSIX feature macros before system headers that need them. */
# define _POSIX_C_SOURCE 200809L

# include <stddef.h>
# include <signal.h>

/* Global flag set by the signal handler. */
extern volatile sig_atomic_t	g_last_signal;

/* Signal handler prototypes. */
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

typedef struct linkedlist
{
    char    **token;
    int     *next;
}   t_list;

int     minishell_loop(void);

#endif
