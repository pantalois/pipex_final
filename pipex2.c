/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:49:26 by loigonza          #+#    #+#             */
/*   Updated: 2024/07/01 20:04:22 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

int	main(int argc, char *argv[], char *env[])
{
	int	j;
	int	i;
	int	status;
	int	fd[2];
	int	pids[2];

	j = 1;
	i = 0;
	status = 0;
	if (argc != 5)
	{
		write(2, "Error: not enough arguments\n", 28);
		return (0);
	}
	while (argv[j + 1])
	{
		if (pipe(fd) == -1)
			print_fail("pipe", 1, 2, NULL);
		pids[i] = ft_fork(env, &argv[j], i, fd);
		j++;
		i++;
	}
	return (check_status(argv, argc, status, pids));
}

char	**create_command(char *argv)
{
	char	**cmd;

	cmd = NULL;
	if (argv == NULL)
	{
		return (cmd);
	}
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		print_fail(": command not found", 0, 127, argv);
	}
	return (cmd);
}

void	print_fail(char *str, int i, int ex, char *cmd)
{
	if (i)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (ex == 127)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\n", 2);
			exit(ex);
		}
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
		exit(ex);
	}
}

void	free_paths(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
	free(path);
	path = NULL;
}

char	*check_space(char *tmp)
{
	int	i;

	i = 0;
	if (ft_strchr(tmp, ' '))
	{
		while (tmp[i] != ' ')
			i++;
		tmp[i] = '\0';
		return (tmp);
	}
	else
		return (tmp);
}
