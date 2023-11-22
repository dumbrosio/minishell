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

# define BUFFERSIZE 4096

extern int	g_var;

typedef struct s_shell
{
	char	**args;
	char	**envp;
	char	*cmd;
	char	*path_cmd;
	char	*prompt;
	char	*buffer;
	size_t	buffer_pos;
	char	*command;
	size_t	command_pos;
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
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

typedef enum e_pstatus
{
	P_NEUTRAL,
	P_DGREAT,
	P_DLESS,
	P_QUOTE,
	P_INWORD
}	t_pstatus;

/* minishell.c */
void	clean_shell(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
void	run_shell(t_shell *shell);

/*path*/
char	*create_abs_path(char *path, char *cmd);
void	free_path(char **path);
char	*get_abs_path(char *cmd);

/*signals*/
void	signal_handler(int sig);

/*parser*/
void	test_parser(t_shell *shell);
int		ft_getchar(t_shell *shell);
void	store_char(t_shell *shell, int c);
void	choose_method(t_shell *shell, t_pstatus *state, t_token *token, int c);
void	parse_dgreat(t_shell *shell, t_token *token, int c);
void	parse_dless(t_shell *shell, t_token *token, int c);
void	parse_neutral(t_shell *shell, t_pstatus *state, t_token *token, int c);
void	parse_quote(t_shell *shell, t_token *token, int c);
void	parse_inword(t_shell *shell, t_token *token, int c);
t_token	gettoken(t_shell *shell);

/*utils*/
void	print_error(t_shell *shell, char **str);
char	**copy_environment(char **env);

#endif
