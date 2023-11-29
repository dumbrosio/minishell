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
# define MAXARG 50 /* max args in cmd */
# define MAXFNAME 500 /* max chars in file name */
# define MAXWORD 500 /* max chars in arg */

# define BUFFERSIZE 4096

extern int	g_var;

typedef struct s_shell
{
	char	*prompt;
	char	*buffer;
	size_t	buffer_pos;
	char	*command;
	size_t	command_pos;
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
	pid_t	main_pid;
	int		exit_code;
	char	*path_cmd;
	char	**envp;
	char	**localenvp;
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

typedef struct s_command
{
	int		argc;
	int		srcfd;
	int		dstfd;
	int		pid;
	int		pfd[2];
	char	*argv[MAXARG];
	char	srcfile[MAXFNAME];
	char	dstfile[MAXFNAME];
	int		append;
	t_token	tk;
	t_token	term;
	int		makepipe;
	int		*pipefdp;
	pid_t	*wpid;
}	t_command;

/* minishell.c */
void	clean_shell(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
void	run_shell(t_shell *shell);

/*path*/
char	*create_abs_path(char *path, char *cmd);
void	free_path(char **path);
char	*get_abs_path(t_shell *shell, char *cmd);

/*signals*/
void	signal_handler(int sig);

/*debug*/
void	test_parser(t_shell *shell);

/*parser*/
int		ft_getchar(t_shell *shell);
void	store_char(t_shell *shell, int c);
void	choose_state(t_shell *shell, t_pstatus *state, t_token *token, int c);
void	parse_dgreat(t_shell *shell, t_token *token, int c);
void	parse_dless(t_shell *shell, t_token *token, int c);
void	parse_neutral(t_shell *shell, t_pstatus *state, t_token *token, int c);
void	parse_quote(t_shell *shell, t_token *token, int c);
void	parse_inword(t_shell *shell, t_token *token, int c);
t_token	get_token(t_shell *shell);

/* executor */
t_token	command(t_shell *shell, pid_t *wpid, int makepipe, int *pipefdp);
int		cmd_special(t_shell *shell, t_command *cmd);

/* executor utils 1*/
void	init_command(t_command *cmd, pid_t *wpid, int makepipe, int *pipefdp);
void	add_word(t_shell *shell, t_command *cmd);
int		switch_simple_tokens(t_shell *shell, t_command *cmd);
int		set_redirect_in(t_shell *shell, t_command *cmd);
int		set_redirect_out(t_shell *shell, t_command *cmd);

/* executor utils 2*/
int		is_terminal_token(t_token token);
void	redirect(t_command *cmd);
void	free_command_args(t_command *cmd);
int		wait_command(t_shell *shell, pid_t pid);
void	setpipe(t_command *cmd);

/* executor utils 3*/
void	reset_filename(char *filename);
void	set_file(t_command *cmd);
void	set_exit_status(t_shell *shell, int status);
pid_t	invoke(t_shell *shell, t_command *cmd);
void	invoke_child(t_shell *shell, t_command *cmd);

/* env */
char	*ft_getenv(t_shell *shell, char *key);
char	**get_env_entry(char **env, char *key);

/*utils*/
void	print_error(char *str);
char	**copy_environment(char **env);
void	ft_split_clean(char **split);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);

#endif
