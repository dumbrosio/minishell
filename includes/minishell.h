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
# define MAXARG 50 /* max args in cmd */
# define MAXFNAME 500 /* max chars in file name */
# define MAXWORD 500 /* max chars in arg */

extern int	g_var;

typedef struct s_shell
{
	char	**envp;
	char	**localenvp;
	char	*buffer;
	char	*command;
	char	*path_cmd;
	char	*prompt;
	int		exit_code;
	int		stderr_fd;
	int		stdin_fd;
	int		stdout_fd;
	pid_t	main_pid;
	size_t	buffer_pos;
	size_t	command_pos;
}			t_shell;

typedef enum e_token
{
	T_DGREAT,
	T_DLESS,
	T_EOF,
	T_ERROR,
	T_GREAT,
	T_LESS,
	T_NL,
	T_NOTOKEN,
	T_PIPE,
	T_WORD,
}			t_token;

typedef enum e_pstatus
{
	P_DGREAT,
	P_DLESS,
	P_INWORD,
	P_NEUTRAL,
	P_QUOTE,
}	t_pstatus;

typedef struct s_command
{
	char	*argv[MAXARG];
	char	dstfile[MAXFNAME];
	char	srcfile[MAXFNAME];
	int		*pipefdp;
	int		append;
	int		argc;
	int		dstfd;
	int		makepipe;
	int		pfd[2];
	int		pid;
	int		srcfd;
	pid_t	*wpid;
	t_token	term;
	t_token	tk;
}	t_command;

typedef struct s_entry
{
	char	*entry;
	char	*key;
	char	*value;
}	t_entry;

/* minishell */
void	clean_shell(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
void	run_shell(t_shell *shell);
void	signal_handler(int sig);

/*path*/
char	*create_abs_path(char *path, char *cmd);
char	*get_abs_path(t_shell *shell, char *cmd);
void	free_path(char **path);
char	*set_new_path(t_shell *shell, char *str);
char	*build_new_path(char *curpath, char *str);

/*debug*/
void	test_parser(t_shell *shell);

/*parser*/
int		ft_getchar(t_shell *shell);
t_token	get_token(t_shell *shell);
void	choose_state(t_shell *shell, t_pstatus *state, t_token *token, int c);
void	parse_dgreat(t_shell *shell, t_token *token, int c);
void	parse_dless(t_shell *shell, t_token *token, int c);
void	parse_inword(t_shell *shell, t_token *token, int c);
void	parse_neutral(t_shell *shell, t_pstatus *state, t_token *token, int c);
void	parse_quote(t_shell *shell, t_token *token, int c);
void	store_char(t_shell *shell, int c);

/* executor */
int		cmd_special(t_shell *shell, t_command *cmd);
t_token	command(t_shell *shell, pid_t *wpid, int makepipe, int *pipefdp);

/* builtins1 */
int		ft_echo(t_command *cmd);
int		ft_env(t_shell *shell);
int		ft_pwd(t_shell *shell);
int		is_builtin(t_command *cmd);
int 	exec_builtin(t_shell *shell, t_command *cmd);

/* builtins2 */
int		ft_cd(t_shell *shell,t_command *cmd);
int		ft_exit(t_shell *shell);
int		ft_export(t_shell *shell,t_command *cmd);
int		ft_unset(t_shell *shell,t_command *cmd);
int		other_builtins(t_shell *shell, t_command *cmd);

/* executor_utils1*/
int		set_redirect_in(t_shell *shell, t_command *cmd);
int		set_redirect_out(t_shell *shell, t_command *cmd);
int		switch_simple_tokens(t_shell *shell, t_command *cmd);
void	add_word(t_shell *shell, t_command *cmd);
void	init_command(t_command *cmd, pid_t *wpid, int makepipe, int *pipefdp);

/* executor_utils2*/
int		is_terminal_token(t_token token);
int		wait_command(t_shell *shell, pid_t pid);
void	free_command_args(t_command *cmd);
void	redirect(t_command *cmd);
void	setpipe(t_command *cmd);

/* executor_utils3*/
pid_t	invoke(t_shell *shell, t_command *cmd);
void	invoke_child(t_shell *shell, t_command *cmd);
void	reset_filename(char *filename);
void	set_exit_status(t_shell *shell, int status);
void	set_file(t_command *cmd);

/* env1*/
char	**ft_getenv_entry(char **env, char *key);
char	*ft_getenv(t_shell *shell, char *key);
int		pop_env_entry(char ***env, char *key);

/* env2*/
void	ft_add_entry(char ***env, char *entry);
int		ft_setenv(t_shell *shell, char *key, char *value);
void	update_pwd(t_shell *shell, char *path);

/*utils*/
char	**copy_environment(char **env);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
void	clean_split(char **split);
void	print_error(char *str);

#endif
