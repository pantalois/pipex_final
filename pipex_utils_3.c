/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:50:34 by loigonza          #+#    #+#             */
/*   Updated: 2024/07/01 20:56:26 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

void	ft_execute(char *env[], char *argv[], char **cmd, char *path)
{
	int	i;

	i = 0;
	if (!path && argv[i])
	{
		ft_unset(path, argv, cmd, env);
	}
	if (argv[i + 2] == NULL && cmd != NULL)
	{
		if (execve(path, cmd, env) == -1)
		{
			free_paths(cmd);
			print_fail(": command not found", 0, 127, argv[i]);
		}
	}
	else if (cmd != NULL)
	{
		if (execve(path, cmd, env) == -1)
		{
			free_paths(cmd);
			print_fail(": command not found", 0, 0, argv[i]);
		}
	}
}

void	ft_output(char *argv[], char *cmd[], char **split_res, char *path)
{
	int	fd_o;
	int	i;

	i = 0;
	fd_o = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_o < 0)
	{
		if (cmd)
			free_paths(cmd);
		if (path)
		{
			free(path);
			path = NULL;
		}
		if (split_res)
			free_paths(split_res);
		print_fail("bash: out: Permission denied", 0, 1, NULL);
	}
	if (dup2(fd_o, STDOUT_FILENO) == -1)
		perror("failed redirecting strdout");
}

int	check_status(char *argv[], int argc, int status, int *pids)
{
	int	k;
	int	i;

	(void)argc;
	(void)argv;
	k = 1;
	i = 0;
	while (k <= 2)
	{
		waitpid(pids[i], &status, 0);
		if (k == 1)
		{
			k++;
			i++;
		}
		else
			return (WEXITSTATUS(status));
	}
	return (0);
}

char	*path_exist(char *env[])
{
	char	*env_path;
	int		j;

	j = 0;
	env_path = NULL;
	while (env[j] != NULL)
	{
		if ((ft_strncmp(env[j], "PATH=", 5)) == 0)
			env_path = env[j];
		j++;
	}
	return (env_path);
}
