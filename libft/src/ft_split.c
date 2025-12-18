/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:57:26 by alacroix          #+#    #+#             */
/*   Updated: 2025/12/18 12:15:52 by alacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	ft_freeme(char **tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(tab[i]);
		i++;
	}
	free (tab);
}

static int	ft_put_word(char **dest, char const *src, char c, int start)
{
	int		end;
	char	*tab;
	int		i;

	i = 0;
	end = 0;
	tab = NULL;
	while (src[start] == c)
		start++;
	while (src[start + end] != c && src[start + end] != '\0')
		end++;
	tab = (char *)malloc((end + 1) * sizeof(char));
	if (tab == NULL)
		return (-1);
	tab[0] = '\0';
	while (src[start] != c && src[start] != '\0')
	{
		tab[i] = src[start];
		start++;
		i++;
	}
	tab[i] = '\0';
	*dest = tab;
	return (start);
}

static int	ft_split_pt2(char **tab, char const *s, char c, int words)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		j = ft_put_word(&tab[i], s, c, j);
		if (j == -1)
		{
			ft_freeme(tab, i);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;

	if (s == NULL)
		return (NULL);
	tab = NULL;
	words = ft_count_words(s, c);
	tab = (char **) malloc ((words + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (ft_split_pt2(tab, s, c, words) == -1)
	{
		free(tab);
		return (NULL);
	}
	tab[words] = NULL;
	return (tab);
}
