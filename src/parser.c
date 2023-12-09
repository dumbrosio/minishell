#include "minishell.h"

void	parse_append(t_shell *shell, t_token *token, int c)
{
	if (c == '>' && shell->command[shell->command_pos - 2] == '>')
		*token = T_APPEND;
	else if (shell->command[shell->command_pos - 2] == '>')
	{
		*token = T_GREAT;
		//ungetc(c, stdin);
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
		//ungetc(c, stdin);
		shell->command_pos--;
	}
}

void	parse_quote(t_shell *shell, t_token *token, int c)
{
	char	quote;

	quote = shell->command[shell->command_pos - 2];
	while (c != quote && c != 0)
	{
		if (c == '\\')
		{
			c = ft_getchar(shell);
			if (c == EOF)
				c = '\\';
			store_char(shell, c);
		}
		store_char(shell, c);
		c = shell->command[shell->command_pos++];
	}
	if (c == quote)
	{
		store_char(shell, '\0');
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
	while (token == T_NOTOKEN || c != 0)
	{
		choose_state(shell, &state, &token, c);
		if (c == 0)
			break ;
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
