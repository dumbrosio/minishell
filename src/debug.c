#include "minishell.h"

void	test_parser(t_shell *shell)
{
	int			next_command;
	t_command	cmd;
	while((shell->command = readline(shell->prompt)))
	{
		shell->command_pos = 0;
		next_command = 0;
		while (next_command == 0)
		{
			switch (get_token(shell,&cmd))
			{
				case T_WORD:
					printf("T_WORD (%s)\n", shell->buffer);
					break;
				case T_PIPE:
					printf("T_PIPE\n");
					break;
				case T_GREAT:
					printf("T_GREAT\n");
					break;
				case T_APPEND:
					printf("T_APPEND\n");
					break;
				case T_LESS:
					printf("T_LESS\n");
					break;
				case T_HEREDOC:
					printf("T_HEREDOC\n");
					break;
				case T_NL:
					printf("T_NL\n");
					next_command =1;
					break;
				case T_EOF:
					printf("T_EOF\n");
					next_command =1;
					break;
				case T_ERROR:
					printf("T_ERROR\n");
					next_command =1;
					break;
				default:
					printf("DEFAULT\n");
					break;
			}
		}
	}
}
