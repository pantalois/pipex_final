/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:50:34 by loigonza          #+#    #+#             */
/*   Updated: 2024/07/01 19:34:06 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

void	ft_execute(char *env[], char *argv[], char **cmd, char *path)
{
	int	i;

	i = 0;
	if (!path && argv[i])
	{
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
	(void)path;
	fd_o = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_o < 0)
	{
		if (cmd)
		{
			free_paths(cmd);
			cmd = NULL;
		}
		if (path)
		{
			free(path);
			path = NULL;
		}
		if (split_res)
		{
			free_paths(split_res);
			split_res = NULL;
		}
		print_fail("bash: out: Permission denied", 0, 1, NULL);
	}
	/*if (path)
	{
		free(path);
		path = NULL;
	}*/
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
		//write (2, "hola\n", 5);
	//	wait(&status);
		waitpid(pids[i], &status, 0);
		//fprintf(stderr, "%d \n", status);
	//	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
	//	{
		//	write(2, "uno\n", 4);
			if (/*argv[argc - 2]*/ k == 1)
			{
		//		write(2, "dos\n", 4);
				k++;
				i++;
			}
	//	}
			else
				return (WEXITSTATUS(status));
	}
	return (0);
}

//Error opening output file cambiar mensaje de error
//
char	*path_exist(char *env[])
{
	char *env_path;
	int	j;

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
