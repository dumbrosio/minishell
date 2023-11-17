#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_var;

typedef struct s_shell
{
	char	*command;
	char	*prompt;
}			t_shell;

typedef enum e_token
{
	T_WORD,
	T_PIPE,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_NL,
	T_EOF,
	T_ERROR,
	T_NOTOKEN
}			t_token;

/* minishell.c */
void		init_shell(t_shell *shell);
void		run_shell(t_shell *shell);
void		clean_shell(t_shell *shell);
/*signal*/
void		signal_handler(int sig);

#endif
