/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:49:26 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/30 17:29:06 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

int	main(int argc, char *argv[], char *env[])
{
	int	j;
	int	i;
	int	status;
	int	fd[2];
	/*pid_t pids[argc - 3]*/

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
		/*pids = */ft_fork(env, &argv[j], i, fd);
		j++;
		i++;
	}
	if (check_status(argv, argc, status) == 127)
		return (127);
	return (0);
}

char	**create_command(char *argv)
{
	char	**cmd;

	cmd = NULL;
	if (argv == NULL)
	{
		write(2, "chao\n", 5);
		return (cmd);
	}
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		//write(2, "o\n", 2);
		print_fail("command not found:", 0, 127, argv); //split didnt work error msg
	}
	return (cmd);
}

void	print_fail(char *str, int i, int ex, char *cmd)
{
	if (i)
	{
		perror(str);
		write(2, "nojodas", 7);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (ex == 127)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\n", 2);
		//	write(2, "asd\n", 4);
		//	fprintf(stderr, "%d \n", ex);
			exit(ex);
		}
		ft_putstr_fd(str, 2);
		ft_putstr_fd(cmd, 2);
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
