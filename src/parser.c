#include "minishell.h"

void	parse_append(t_shell *shell, t_token *token, int c)
{
	if (c == '>' && shell->command[shell->command_pos - 2] == '>')
		*token = T_APPEND;
	else if (shell->command[shell->command_pos - 2] == '>')
	{
		*token = T_GREAT;
		shell->command_pos--;
	}
}

void	parse_heredoc(t_shell *shell, t_token *token, int c)
{
	if (c == '<' && shell->command[shell->command_pos - 2] == '<')
		*token = T_HEREDOC;
	else if (shell->command[shell->command_pos - 2] == '<')
	{
		*token = T_LESS;
		shell->command_pos--;
	}
}

void	parse_quote(t_shell *shell, t_token *token, int c)
{
	char	quote;

	quote = shell->command[shell->command_pos - 2];
	while (c != quote && c != 0)
	{
			store_char(shell, c);
			c = shell->command[shell->command_pos++];
	}
	if (c == quote)
	{
		store_char(shell, '\0');
		if (ft_strchr(" |><", shell->command[shell->command_pos]))
			shell->token_error = 0;
		else
			shell->token_error = 1;
		*token = T_WORD;
	}
	else if (*token == T_NOTOKEN)
		*token = T_ERROR;
}

void	parse_inword(t_shell *shell, t_token *token, int c)
{
	if (c == '|' || c == '<' || c == 0 || c == '"'
		|| c == '>' || c == '\n' || c == ' ' || c == '\t' || c == '\'')
	{
		if (c != ' ' && c != '\t')
			shell->command_pos--;
		store_char(shell, '\0');
		*token = T_WORD;
	}
	else
		store_char(shell, c);
}

t_token	get_token(t_shell *shell)
{
	t_pstatus	state;
	t_token		token;
	int			c;

	state = P_NEUTRAL;
	token = T_NOTOKEN;
	shell->buffer_pos = 0;
	c = shell->command[shell->command_pos++];
	shell->token_error = 1;
	while (token == T_NOTOKEN || c != 0)
	{
		choose_state(shell, &state, &token, c);
		if (c == 0)
			break ;
		if ((state == P_INWORD && token == T_WORD && c == ' '))
			shell->token_error = 0;
		if (token == T_NOTOKEN)
			c = shell->command[shell->command_pos++];
		else
			return (token);
	}
	if (token != T_NOTOKEN)
		return (token);

	if (c == 0)
		return (T_NL);
	return (T_ERROR);
}
