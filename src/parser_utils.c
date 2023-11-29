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
		print_error("Error\n");
		exit(1);
	}
	shell->buffer[(shell->buffer_pos)++] = c;
}

void	choose_state(t_shell *shell, t_pstatus *state, t_token *token, int c)
{
	if (*state == P_NEUTRAL)
		parse_neutral(shell, state, token, c);
	else if (*state == P_DGREAT)
		parse_dgreat(shell, token, c);
	else if (*state == P_DLESS)
		parse_dless(shell, token, c);
	else if (*state == P_QUOTE)
		parse_quote(shell, token, c);
	else if (*state == P_INWORD)
		parse_inword(shell, token, c);
}

void	parse_neutral(t_shell *shell, t_pstatus *state, t_token *token, int c)
{
	if (c == '|')
		*token = T_PIPE;
	else if (c == '\n')
		*token = T_NL;
	else if (c == ' ' || c == '\t')
		return ;
	else if (c == '>')
		*state = P_DGREAT;
	else if (c == '<')
		*state = P_DLESS;
	else if (c == '"' || c == '\'')
		*state = P_QUOTE;
	else
	{
		*state = P_INWORD;
		store_char(shell, c);
	}
}
