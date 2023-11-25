#include "minishell.h"

void	init_command(t_command *cmd, pid_t *wpid, int makepipe, int *pipefdp)
{
	cmd->argc = 0;
	cmd->pfd[0] = -1;
	cmd->pfd[1] = -1;
	cmd->srcfd = STDIN_FILENO;
	cmd->dstfd = STDOUT_FILENO;
	reset_filename(cmd->srcfile);
	reset_filename(cmd->dstfile);
	cmd->makepipe = makepipe;
	cmd->wpid = wpid;
	cmd->pipefdp = pipefdp;
}

int	switch_simple_tokens(t_shell *shell, t_command *cmd)
{
	if (cmd->tk == T_WORD)
	{
		add_word(shell, cmd);
		return (1);
	}
	else if (cmd->tk == T_LESS)
	{
		if (set_redirect_in(shell, cmd))
			return (2);
		return (1);
	}
	else if (cmd->tk == T_GREAT || cmd->tk == T_DGREAT)
	{
		if (set_redirect_out(shell, cmd))
			return (2);
		return (1);
	}
	return (0);
}

void	add_word(t_shell *shell, t_command *cmd)
{
	if (cmd->argc >= MAXARG - 1)
	{
		print_error("Too many args");
		return ;
	}
	cmd->argv[cmd->argc] = malloc(strlen(shell->buffer) + 1);
	if (cmd->argv[cmd->argc] == NULL)
	{
		print_error("Out of arg memory");
		return ;
	}
	ft_strcpy(cmd->argv[cmd->argc], shell->buffer);
	cmd->argc++;
}

int	set_redirect_in(t_shell *shell, t_command *cmd)
{
	if (cmd->makepipe)
	{
		print_error("Extra <");
		return (1);
	}
	if (gettoken(shell) != T_WORD)
	{
		print_error("Illegal <");
		return (1);
	}
	cmd->srcfd = -1;
	ft_strcpy(cmd->srcfile, shell->buffer);
	return (0);
}

int	set_redirect_out(t_shell *shell, t_command *cmd)
{
	if (cmd->dstfd != STDOUT_FILENO)
	{
		print_error("Extra > or >>");
		return (1);
	}
	if (gettoken(shell) != T_WORD)
	{
		print_error("Illegal > or >>");
		return (1);
	}
	cmd->dstfd = -1;
	ft_strcpy(cmd->dstfile, shell->buffer);
	cmd->append = (cmd->tk == T_DGREAT);
	return (0);
}
