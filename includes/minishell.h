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
void		clean_shell(t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
void		run_shell(t_shell *shell);
void		signal_handler(int sig);

/*path1*/
void	get_envp_path(t_shell *shell, char ***path);
int		check_file(char *absolute, char ***path, char **copy);
char	*get_abs_path(t_shell *shell, char *command);
void	clean_abs_path(char **absolute, char ***path, char **copy);
char	*set_new_path(t_shell *shell, char *str);

/*path2*/
char	*build_abs_path(char *path, char *command);
void	expand_cmd_cycle(char **copy, char *curpath, int *i, int *j);
void	expand_command(t_shell *shell, char *command, char **copy);
void	free_path(char **path);
void	build_path(char **splitted, int i, char *path);
char	*build_new_path(char *curpath, char *str);

/*debug*/
void		test_parser(t_shell *shell);

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
int			ft_export(t_shell *shell, t_command *cmd);
int			export_core(t_shell *shell, t_command *cmd);
int			ft_unset(t_shell *shell, t_command *cmd);
int			ft_cd(t_shell *shell, t_command *cmd);

/* builtins3 */
int			print_export_entry(t_shell *shell);
int			ft_exit(t_shell *shell);
void		update_pwd(t_shell *shell, char *path);

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
int			pop_env_entry(char ***env, char *key);

/* env2*/
void		ft_add_entry(char ***env, char *entry);
int			ft_setenv(t_shell *shell, char *key, char *value);
int			ft_setenv_entry(char *token, t_entry *entry);
void		clean_entry(t_entry *entry);
void		strcat_union(char *str, char *key, char *value);

/*utils1*/
char		**copy_environment(char **env);
void		clean_split(char **split);
void		print_error(char *str);
int			write_error(t_shell *shell);

/*expander*/
void		expand(t_shell *shell);
void		add_exit(t_shell *shell, int *i, int *j);
void		add_expanded_value(t_shell *shell, char *buffer_copy, int *i, int *j);


/*heredoc*/
int			set_heredoc(t_shell *shell, t_command *cmd);
void		copy_tmp_arg(t_command *cmd);

/*utils2*/
void		exec_command(t_shell *shell);


#endif
