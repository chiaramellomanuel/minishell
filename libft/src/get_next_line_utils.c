/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiaram <mchiaram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:15:48 by mchiaram          #+#    #+#             */
/*   Updated: 2024/03/21 15:06:58 by mchiaram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *) s);
		s++;
	}
	if (*s == (char)c)
		return ((char *) s);
	return (NULL);
}

/*size_t	ft_strlen(const char *s)
{
	size_t	size;

	if (!s)
		return (0);
	size = 0;
	while (s[size])
		size++;
	return (size);
}*/

char	*ft_freejoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
		s1 = ft_calloc(1, sizeof(*s1));
	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(((ft_strlen(s1) + ft_strlen(s2) + 1)), sizeof(*s1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i++] = *s2;
		s2++;
	}
	free ((char *)s1);
	return (str);
}

/*void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	len;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	len = 0;
	while (len < nmemb)
	{
		ptr[len] = '\0';
		len++;
	}
	return (ptr);
}*/
