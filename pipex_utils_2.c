/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:15:56 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/29 18:09:03 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

char	**ft_getenv(char *env[])
{
	int		j;
	char	*env_path;
	char	**split_res;
	int		i;
	char	*tmp;

	j = 0;
	while (env[j] != NULL)
	{
		if ((ft_strncmp(env[j], "PATH=", 5)) == 0)
			env_path = env[j];
		j++;
	}
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
	}
	return (0);
}

char	*ft_slash(char *argv, char *split_res[])
{
	int		j;

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
			split_res[j] = ft_free_strjoin(split_res[j], argv);
			if (access(split_res[j], X_OK) == 0)
				return (split_res[j]);
			else
			{
				free(split_res[j]);
				j++;
			}
		}
	}
	return (argv);
}

void	open_file(char *infile)
{
	int	fd_i;

	fd_i = open(infile, O_RDONLY);
	if (fd_i < 0)
		print_fail("Error opening input file", 0, 1, NULL);
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

	i = 0;
	cmd = NULL;
	split_res = NULL;
	path = NULL;
	if (argv[i + 1])
	{
		tmp = argv[i];
		cmd = create_command(tmp);
		split_res = ft_getenv(env);
		path = ft_slash(tmp, split_res);
	}
	if (argv[i + 2] == NULL)
		ft_output(argv);
	ft_execute(env, argv, cmd, path);
	free_paths(split_res);
	free_paths(cmd);
}
