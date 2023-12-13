#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT && errno != 2)
	{
		g_var = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT && errno == 2)
		g_var = 131;
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= old_size)
		return (ptr);
	else
	{
		new_ptr = malloc(new_size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, old_size);
			free(ptr);
		}
		return (new_ptr);
	}
}

int	add_to_rl(char *cmd)
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
