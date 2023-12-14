#include "minishell.h"

int	set_heredoc(t_shell *shell, t_command *cmd)
{
	char	*line;
	char	*tmp;
	int		tmp_file;

	if (get_token(shell, cmd) != T_WORD)
		return (write_error(shell, "<<"));
	if (shell->expand)
		expand(shell);
	tmp_file = open("/tmp/ms_tmp", O_CREAT | O_TRUNC | O_RDWR, 0600);
	tmp = ft_strdup(shell->buffer);
	line = readline("heredoc> ");
	while (ft_strcmp(line, tmp))
	{
		ft_putendl_fd(line, tmp_file);
		free(line);
		line = readline("heredoc> ");
	}
	cmd->srcfd = tmp_file;
	close(tmp_file);
	free(line);
	free(tmp);
	ft_strcpy(cmd->srcfile, "/tmp/ms_tmp");
	return (0);
}

void	copy_tmp_arg(t_command *cmd)
{
	if (cmd->tmp_arg[0])
	{
		cmd->argv[cmd->argc] = malloc(ft_strlen(cmd->tmp_arg) + 1);
		if (cmd->argv[cmd->argc] == NULL)
		{
			print_error("Out of memory");
			return ;
		}
		ft_strcpy(cmd->argv[cmd->argc], cmd->tmp_arg);
		cmd->argc++;
		cmd->tmp_arg[0] = 0;
	}
}
