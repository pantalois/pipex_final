/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:08:58 by loigonza          #+#    #+#             */
/*   Updated: 2024/07/01 20:56:42 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

char	*ft_join_path(char *argv, char	*split_res[])
{
	int		j;
	char	*joined_path;

	j = 0;
	while (split_res[j])
	{
		argv = check_space(argv);
		joined_path = ft_strjoin(split_res[j], argv);
		if (access(joined_path, X_OK) == 0)
			return (joined_path);
		else
		{
			if (joined_path)
			{
				free(joined_path);
				joined_path = NULL;
			}
			j++;
		}
	}
	return (NULL);
}

void	ft_continue2(char *argv[], char *cmd[], char *split_res[], char *path)
{
	int	i;

	i = 0;
	if (argv[i + 2] == NULL)
		ft_output(argv, cmd, split_res, path);
	if (split_res)
	{
		free_paths(split_res);
		split_res = NULL;
	}
}

void	ft_unset(char *path, char *argv[], char **cmd, char *env[])
{
	int	i;

	i = 0;
	path = "no existo";
	if (execve(argv[i], cmd, env) == -1)
	{
		free_paths(cmd);
		write(2, "bash: ", 6);
		write(2, argv[i], ft_strlen(argv[i]));
		write(2, ": No such file or directory\n", 28);
		exit (127);
	}
}


