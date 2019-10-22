/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:29:17 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 00:31:23 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	listfree2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int		ft_2dstrlen(char **array)
{
	int	i;

	i = 0;
	while (*array)
	{
		i++;
		array++;
	}
	return (i);
}

int		endvar(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '"' || str[i] == '$' || str[i] == '/')
			return (i);
		i++;
	}
	return (i);
}

char	*print_var(char *buf, t_env *envirs)
{
	char	*tmp;

	buf++;
	tmp = ft_strsub(buf, 0, endvar(buf));
	if (!*buf)
		ft_putchar('$');
	while (envirs && *buf)
	{
		if (ft_strequ(tmp, envirs->var))
		{
			ft_putstr(envirs->data + ft_strlen(envirs->var) + 1);
		}
		envirs = envirs->next;
	}
	free(tmp);
	return (buf + ft_strlen(tmp));
}

char	*str_replace_tabs(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	return (str);
}
