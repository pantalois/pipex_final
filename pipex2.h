/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@42.barcel>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:51:26 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/26 12:44:46 by loigonza         ###   ########.fr       */
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
int		ft_fork(char *env[], char *argv[]/*, int argc*/, int i);
char	*ft_slash(char *argv, char *split_res[]);
char	**create_command(char *argv);
void	open_file(/*char *outfile, */char *infile);
void	ft_continuar(char*env[], char *argv[], /*int argc, */int i);
void	free_paths(char **path);
void	print_fail(char *str, int i, int ex, char *cmd);
void write_execve_args(const char *path, char *const argv[]/*, char *const envp[]*/);
char	*check_space(char *tmp);

#endif
