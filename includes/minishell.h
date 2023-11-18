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
	char	**args;
	char	**envp;
	char	*cmd;
	char	*path_cmd;
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
void		clean_shell(t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
void		run_shell(t_shell *shell);

/*path*/
char		*get_abs_path(char *cmd);

/*signals*/
void		signal_handler(int sig);

#endif
