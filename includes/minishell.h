/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:20:45 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/11/16 10:45:24 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"

extern int	g_var;

typedef struct s_shell {
	char	*command;
	char	*prompt;
}	t_shell;

/* minishell.c */
void	init_shell(t_shell *shell);
void	run_shell(t_shell *shell);
void	clean_shell(t_shell *shell);
/*signal*/
void	signal_handler(int sig);

#endif
