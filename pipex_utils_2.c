/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:15:56 by loigonza          #+#    #+#             */
/*   Updated: 2024/07/01 19:35:38 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

char	**ft_getenv(char *env_path)
{
	char	**split_res;
	int		i;
	char	*tmp;

	split_res = ft_split(&env_path[5], ':');
	i = 0;
	while (split_res[i])
	{
		tmp = split_res[i];
		split_res[i] = ft_strjoin(split_res[i], "/");
		free(tmp);
		i++;
	}
	return (split_res);
}

int	ft_fork(char *env[], char *argv[], int i, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_fail("fork", 1, 2, NULL);
	if (pid == 0)
	{
		close(fd[0]);
		if (i == 0)
		{
			open_file(argv[0]);
			i++;
		}
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			print_fail("failed to redirect stdout", 1, 2, NULL);
		ft_continuar(env, &argv[i], i);
	}
	if (pid > 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			print_fail("failed redirecting stdin", 1, 2, NULL);
		return (pid);
	}
	return (pid);
}

char	*ft_slash(char *argv, char *split_res[])
{
	int		j;
	char	*joined_path;

	j = 0;
	if (!argv)
		return (argv);
	if (argv[j] == '/')
		return (argv);
	else
	{
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
	}
	return (NULL);
}

void	open_file(char *infile)
{
	int	fd_i;

	fd_i = open(infile, O_RDONLY);
	if (fd_i < 0)
		print_fail("bash: infile: Permission denied", 0, 1, NULL);
	if (dup2(fd_i, STDIN_FILENO) == -1)
		print_fail("failed redirecting stdin", 1, 2, NULL);
	close(fd_i);
}

void	ft_continuar(char*env[], char *argv[], int i)
{
	char	**cmd;
	char	**split_res;
	char	*path;
	char	*tmp;
	char	*env_path;

	i = 0;
	cmd = NULL;
	split_res = NULL;
	path = NULL;
	if (argv[i + 1])
	{
		tmp = argv[i];
		cmd = create_command(tmp);
		env_path = path_exist(env);
		if (env_path)
			split_res = ft_getenv(/*env, */env_path);
		if (split_res)
			path = ft_slash(tmp, split_res);
	}
	if (argv[i + 2] == NULL)
		ft_output(argv, cmd, split_res, path);
	if (split_res)
	{
		free_paths(split_res);
		split_res = NULL;
	}
	ft_execute(env, argv, cmd, path/*, split_res*/);
/*	if (split_res)
	{
		free_paths(split_res);
		split_res = NULL;
	}*/
	free_paths(cmd);
}
