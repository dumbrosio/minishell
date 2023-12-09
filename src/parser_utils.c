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
	else if (*state == P_APPEND)
		parse_append(shell, token, c);
	else if (*state == P_HEREDOC)
		parse_heredoc(shell, token, c);
	else if (*state == P_QUOTE)
		parse_quote(shell, token, c);
	else if (*state == P_INWORD)
		parse_inword(shell, token, c);
}

void	parse_neutral(t_shell *shell, t_pstatus *state, t_token *token, int c)
{
	shell->expand = 1;
	if (c == '|')
		*token = T_PIPE;
	else if (c == '\n')
		*token = T_NL;
	else if (c == ' ' || c == '\t')
		return ;
	else if (c == '>')
		*state = P_APPEND;
	else if (c == '<')
		*state = P_HEREDOC;
	else if (c == '"' || c == '\'')
	{
		*state = P_QUOTE;
		if (c == '\'')
			shell->expand = 0;
	}
	else
	{
		*state = P_INWORD;
		store_char(shell, c);
	}
}
