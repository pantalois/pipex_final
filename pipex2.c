/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:49:26 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/25 10:15:07 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int	fd_o;

	i = 2;
	if (argc != 5)
	{
		perror("no good arguments especified");
		exit(1);
	}
	fd_o = open_file(argv[argc - 1], argv[1]);
	while (argv[i + 1])
	{
		ft_fork(env, argv[i]);
		i++;	
		if (dup2(fd_o, STDOUT_FILENO) == -1)
			perror("failed redirecting strdout");
		ft_continuar(env, argv[argc - 2]);
	}
	return (0);
}

char	**create_command(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		print_fail("command not found:", 0, 127, argv);
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
			ft_putstr_fd(str, 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\n", 2);
			exit(ex);
		}
		ft_putstr_fd(str, 2);
		exit(ex);
	}
}

void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
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
/*
void write_execve_args(const char *path, char *const argv[],  char *const envp[])
{
    int i;
    char buffer[1024];
    int len;

    len = snprintf(buffer, sizeof(buffer), "Path: %s\n", path);
    write(STDERR_FILENO, buffer, len);

    write(STDERR_FILENO, "Arguments:\n", 11);
    for (i = 0; argv[i] != NULL; i++)
    {
        len = snprintf(buffer, sizeof(buffer), "argv[%d]: %s\n", i, argv[i]);
        write(STDERR_FILENO, buffer, len);
    }

    //write(STDERR_FILENO, "Environment:\n", 13);
    //for (i = 0; envp[i] != NULL; i++)
    //{
      ///  len = snprintf(buffer, sizeof(buffer), "envp[%d]: %s\n", i, envp[i]);
        //write(STDERR_FILENO, buffer, len);
    //}
}*/
