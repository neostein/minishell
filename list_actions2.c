/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_actions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:55:31 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 00:29:11 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_2darray(t_env *envirs)
{
	char	**array;
	int		i;
	int		size;

	size = ft_listlen(envirs);
	if ((array = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		exit(1);
	i = 0;
	while (i < size)
	{
		array[i] = ft_strdup(envirs->data);
		i++;
		envirs = envirs->next;
	}
	array[i] = 0;
	return (array);
}

int		ft_listlen(t_env *envirs)
{
	int	i;

	i = 0;
	while (envirs)
	{
		i++;
		envirs = envirs->next;
	}
	return (i);
}
