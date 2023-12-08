#include "minishell.h"

int	add_to_rlh(char *cmd)
{
	int	i;

	if (ft_strlen(cmd) == 0)
		return (0);
	i = 0;
	while (cmd[i])
		if (!ft_strchr(" \t\n", cmd[i++]))
			return (1);
	return (0);
}
int handle_input(t_shell *shell, t_token term)
{
	if (term == T_NL)
	{
		shell->command_pos = 0;
		if (add_to_rlh(shell->command))
			add_history(shell->command);
		else
		{
			free(shell->command);
			shell->command = readline(shell->prompt);
			return 0;
		}
	}
	return 1;
}

void handle_command(t_shell *shell, t_token *term, pid_t *pid)
{
	*term = command(shell, pid, 0, NULL);
	if (*term == T_ERROR)
	{
		print_error("Bad command");
		*term = T_NL;
	}
	else if (*pid > 0)
		wait_command(shell, *pid);
}
