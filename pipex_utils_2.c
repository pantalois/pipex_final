/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:15:56 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/27 17:22:12 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"
#include <string.h>

char	**ft_getenv(char *env[])
{
	int		j;
	char	*env_path;
	char	**split_res;
	int		i;

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
		split_res[i] = ft_strjoin(split_res[i], "/");
		i++;
	}
	return (split_res);
}

int	ft_fork(char *env[], char *argv[]/*, int argc*/, int i)
{
	pid_t	pid;
	int		fd[2];
	//int		status = 0;

	if (pipe(fd) == -1)
		print_fail("pipe", 1, 2, NULL);
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
		ft_continuar(env, &argv[i],/* argc, */i);
	}
	if (pid > 0)
	{
		//wait(NULL);//wait(&status) == pid || if pid = 127 saldra con exit 127, entonces esto ya me saldra del programa con 127
		//wait(&status);
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			print_fail("failed redirecting stdin", 1, 2, NULL);
		/*if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			return (127);*/
		//indicar de alguna marena
/*		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			print_fail("failed redirecting stdin", 1, 2, NULL);*/
	}
	return (0);
}

char	*ft_slash(char *argv, char *split_res[])
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = argv;
	if (tmp[j] == '/')
		return (tmp);
	else
	{
		while (split_res[j])
		{
			tmp = check_space(tmp);
			split_res[j] = ft_strjoin(split_res[j], tmp);
			if (access(split_res[j], X_OK) == 0)
				return (split_res[j]);
			else
			{
				free(split_res[j]);
				j++;
			}
		}
	}
	return (tmp);
}

void	open_file(char *infile)
{
	int	fd_i;
	
	fd_i = open(infile, O_RDONLY);
	if (fd_i < 0)
		print_fail("Error opening input file\n", 0, 1, NULL);
	if (dup2(fd_i, STDIN_FILENO) == -1)
		print_fail("failed redirecting stdin\n", 1, 2, NULL);
	close(fd_i);
}

void	ft_continuar(char*env[], char *argv[],/* int argc, */int i)
{
	char	**cmd = NULL;
	char	**split_res;
	char	*path;
	char	*tmp;
	int		fd_o;

	i = 0;
	if (argv[i + 1])
	{
	tmp = argv[i];
	cmd = create_command(tmp);
	split_res = ft_getenv(env);
	path = ft_slash(tmp, split_res); //pasar argc para indicarle cuando sea el ultimo comando que haga el outfile
	}
	if (argv[i + 2] == NULL)
	{
	fd_o = open("outfile", O_WRONLY | O_CREAT |  O_TRUNC, 0644);
	if (fd_o < 0)
		print_fail("Error opening output file\n", 0, 1, NULL);
	if (dup2(fd_o, STDOUT_FILENO) == -1)
		perror("failed redirecting strdout");
	}
	//write_execve_args(path, cmd/*, env*/);
	if (argv[i + 2] == NULL)
	{
		if (execve(path, cmd, env) == -1)
		{
			free_paths(cmd);
			print_fail("command not found: ", 0, 127, argv[i]);
		//	exit(127);
		}
	}
	else
	{
		if (execve(path, cmd, env) == -1)
		{
		free_paths(cmd);
		print_fail("command not found: ", 0, 0, argv[i]);
		//exit(127);
		}
	}
	free_paths(cmd);//cuidado leaks
}
