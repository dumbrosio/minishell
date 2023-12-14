#include "minishell.h"

void	bubble_sort(char **arr, int n)
{
	int	i;
	int	j;

	i = n - 1;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				ft_swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i--;
	}
}

int	ft_envp_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
