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
# include <limits.h>

# define PATH_MAX 4096
# define BUFFERSIZE 4096
# define MAXARG 50    /* max args in cmd */
# define MAXFNAME 500 /* max chars in file name */
# define MAXWORD 500  /* max chars in arg */

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
	int		expand;
	int		stderr_fd;
	int		stdin_fd;
	int		stdout_fd;
	pid_t	main_pid;
	size_t	buffer_pos;
	size_t	command_pos;
	int		token_error;
	int		unset_path;
}			t_shell;

typedef enum e_token
{
	T_APPEND,
	T_HEREDOC,
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
	P_APPEND,
	P_HEREDOC,
	P_INWORD,
	P_NEUTRAL,
	P_QUOTE,
}			t_pstatus;

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
	char	tmp_arg[MAXWORD];
}			t_command;

typedef struct s_entry
{
	char	*entry;
	char	*key;
	char	*value;
}			t_entry;

/* minishell */
void		init_shell(t_shell *shell, char **envp);
void		run_shell(t_shell *shell);
void		exec_command(t_shell *shell);
void		clean_shell(t_shell *shell);

/*path1*/
void		get_envp_path(t_shell *shell, char ***path);
int			check_file(char *absolute, char ***path, char **copy);
char**		handle_null_path(char **path, char *copy);
char		*get_abs_path(t_shell *shell, char *command);
void		clean_abs_path(char **absolute, char ***path, char **copy);

/*path2*/
char		*build_abs_path(char *path, char *command);
void		expand_cmd_cycle(char **copy, char *curpath, int *i, int *j);
void		expand_command(t_shell *shell, char *command, char **copy);
void		free_path(char **path);

/*parser*/
void		init_token(t_shell *shell, t_pstatus *state, t_token *token, int *c);
void		parse_append(t_shell *shell, t_token *token, int c);
void		parse_heredoc(t_shell *shell, t_token *token, int c);
void		parse_quote(t_shell *shell, t_token *token, int c);
void		parse_inword(t_shell *shell, t_token *token, int c);
t_token		get_token(t_shell *shell,t_command *cmd);

/*parser_utils*/
int			ft_getchar(t_shell *shell);
void		choose_state(t_shell *shell, t_pstatus *state, t_token *token, int c);
void		parse_neutral(t_shell *shell, t_pstatus *state, t_token *token, int c);
void		store_char(t_shell *shell, int c);

/* executor */
int			cmd_special(t_shell *shell, t_command *cmd);
t_token		command(t_shell *shell, pid_t *wpid, int makepipe, int *pipefdp);
pid_t		invoke(t_shell *shell, t_command *cmd);
void		invoke_child(t_shell *shell, t_command *cmd, char *abs_path);

/* builtins1 */
int			ft_echo(t_command *cmd);
int			ft_env(t_shell *shell);
int			ft_pwd(t_shell *shell);
int			is_builtin(t_command *cmd);
int			exec_builtin(t_shell *shell, t_command *cmd);

/* builtins2 */
int			other_builtins(t_shell *shell, t_command *cmd);
void		export_error(t_shell *shell, char *key, int *i);
int			export_checker(t_command *cmd, int i);
void		cd_write_error(t_shell *shell, char *arg);

/* builtins5 */
int			ft_export(t_shell *shell, t_command *cmd);
int			print_export_entry(t_shell *shell);
int			export_core(t_shell *shell, t_command *cmd);
void		print_export_var(char *env_var);
void 		handle_export_arg(t_shell *shell, char *arg);

/* builtins3 */
int			ft_unset(t_shell *shell, t_command *cmd);
int			find_var_index(t_shell *shell, char *key);
char		**create_new_envp(t_shell *shell, int var_index);
int			ft_exit(t_shell *shell, t_command *cmd);
int			check_exit_arg(int *arg, t_shell *shell, t_command *cmd, int *i);

/* builtins4 */
int			ft_cd(t_shell *shell, t_command *cmd);
char		*set_new_path_cd(t_shell *shell, char *str);
char		*build_new_path_cd(char *curpath, char *str);
void		build_path_cd(char **splitted, int i, char *path);
void		update_pwd_cd(t_shell *shell, char *path);

/* executor_utils1*/
int			set_red_in(t_shell *shell, t_command *cmd);
int			set_red_out(t_shell *shell, t_command *cmd);
int			switch_tokens(t_shell *shell, t_command *cmd);
void		add_word_token(t_shell *shell, t_command *cmd);
void		init_command(t_command *cmd, pid_t *wpid, int makepipe, int *pipefdp);

/* executor_utils2*/
int			is_terminal_tk(t_token token);
int			wait_command(t_shell *shell, pid_t pid);
void		free_command_args(t_command *cmd);
void		redirect(t_command *cmd);
void		set_pipe(t_command *cmd);

/* executor_utils3*/
void		reset_filename(char *filename);
void		set_exit_status(t_shell *shell, int status);
void		set_file(t_command *cmd);

/* env1*/
char		**ft_getenv_entry(char **env, char *key);
char		*ft_getenv(t_shell *shell, char *key);
char		*create_env_entry(char *key, char *value);
void		ft_setenv(t_shell *shell, char *key, char *value);

/*utils1*/
char		**copy_environment(char **env);
void		clean_split(char **split);
void		print_error(char *str);
int			write_error(t_shell *shell, char *token);
void		print_error_2(t_shell *shell, char *str);

/*expander*/
void		expand(t_shell *shell);
void		add_exit(t_shell *shell, int *i, int *j);
void		add_expanded_value(t_shell *shell, char *buffer_copy, int *i, int *j);


/*heredoc*/
int			set_heredoc(t_shell *shell, t_command *cmd);
void		copy_tmp_arg(t_command *cmd);

/*utils2*/
void		signal_handler(int sig);
char		*ft_strndup(const char *s, size_t n);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int			add_to_rl(char *cmd);

#endif
