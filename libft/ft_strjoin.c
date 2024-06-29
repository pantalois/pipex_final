/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loigonza <loigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:17:09 by loigonza          #+#    #+#             */
/*   Updated: 2024/06/29 18:10:04 by loigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	idx;
	size_t	idx_ptr;
	char	*ptr;

	idx_ptr = 0;
	if (!s1 && !s2)
		return (0);
	ptr = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!ptr)
		return (0);
	idx = -1;
	while (s1[++idx] != '\0')
	{
		ptr[idx_ptr] = s1[idx];
		idx_ptr++;
	}
	idx = -1;
	while (s2[++idx] != '\0')
	{
		ptr[idx_ptr] = s2[idx];
		idx_ptr++;
	}
	ptr[idx_ptr] = '\0';
	return (ptr);
}

char	*ft_free_strjoin(char *s1, char *s2)
{
	size_t	idx;
	size_t	idx_ptr;
	char	*ptr;

	idx_ptr = 0;
	if (!s1 && !s2)
		return (0);
	ptr = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!ptr)
		return (0);
	idx = -1;
	while (s1[++idx] != '\0')
	{
		ptr[idx_ptr] = s1[idx];
		idx_ptr++;
	}
	idx = -1;
	while (s2[++idx] != '\0')
	{
		ptr[idx_ptr] = s2[idx];
		idx_ptr++;
	}
	ptr[idx_ptr] = '\0';
	return (free(s1), ptr);
}
/*
char	*ft_free_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	j = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i] != '\0')
		ptr[i] = s1[i];
	while (s2[j] != '\0')
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (free(s1), ptr);
}*/

/*
int	main(void)
{
	const char *s1 = "hola ";
	const char *s2 = "mundo";
	printf("s3: %s\n", ft_strjoin(s1, s2));
	return (0);
}
*/
