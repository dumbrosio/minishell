#include "minishell.h"

int	heredoc(t_shell *shell, t_command *cmd)
{
	char *line;
	char *tmp;
	int tmp_file;

	// if (get_token(shell) != T_WORD)
	// 	return (write_error(shell));
	write(1, "heredoc\n", 14);
	if (shell->expand)
		expand(shell);
	tmp_file = open("/tmp/ms_tmp", O_CREAT | O_TRUNC | O_RDWR, 0600);
	tmp = ft_strdup(shell->buffer);
	line = readline("> ");
	while (ft_strcmp(line, tmp))
	{
		ft_putendl_fd(line, tmp_file);
		free(line);
		line = readline("> ");
	}
	close(tmp_file);
	free(line);
	free(tmp);
	cmd->srcfd = tmp_file;
	ft_strcpy(cmd->srcfile, "/tmp/ms_tmp");
	return (0);
}