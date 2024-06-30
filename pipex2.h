/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:51:26 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/30 15:04:55 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX2_H
# define PIPEX2_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

char	**ft_getenv(char *env[]);
int		ft_fork(char *env[], char *argv[], int i, int *fd);
char	*ft_slash(char *argv, char *split_res[]);
char	**create_command(char *argv);
void	open_file(char *infile);
void	ft_continuar(char*env[], char *argv[], int i);
void	free_paths(char **path);
void	print_fail(char *str, int i, int ex, char *cmd);
char	*check_space(char *tmp);
void	ft_execute(char *env[], char *argv[], char **cmd, char *path, char *split_res[]);
void	ft_output(char *argv[], char **cmd, char **split_res, char *path);
int		check_status(char *argv[], int argc, int status);

#endif
