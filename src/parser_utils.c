#include "minishell.h"

int	ft_getchar(t_shell *shell)
{
	int		c;
	ssize_t	r;

	r = read(shell->stdin_fd, &c, 1);
	if (r == 0)
		c = EOF;
	return (c);
}

void	store_char(t_shell *shell, int c)
{
	if (shell->buffer_pos >= BUFFERSIZE)
	{
		printf("Error\n");
		exit(1);
	}
	shell->buffer[(shell->buffer_pos)++] = c;
}

void	choose_method(t_shell *shell, t_pstatus *state, t_token *token, int c)
{
	if (*state == P_NEUTRAL)
		parse_neutral(shell, state, token, c);
	else if (*state == P_DGREAT)
		parse_dgreat(shell, token, c);
	else if (*state == P_QUOTE)
		parse_quote(shell, token, c);
	else if (*state == P_INWORD)
		parse_inword(shell, token, c);
}
