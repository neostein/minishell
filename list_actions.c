/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:49:11 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 00:31:55 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		listmynew_normal(t_env *new, char *str)
{
	char	**array;

	new->data = ft_strdup(str);
	if (ft_strchr(str, '='))
	{
		array = ft_strsplit(str, '=');
		new->var = ft_strdup(array[0]);
		listfree2d(array);
	}
	else
	{
		new->var = NULL;
	}
}

t_env		*ft_listmynew(char *str, char *str2)
{
	t_env	*new;
	char	*tmp;

	if ((new = (t_env *)malloc(sizeof(t_env))) == NULL)
		exit(1);
	if (str2 == NULL)
	{
		listmynew_normal(new, str);
	}
	else if (!ft_strequ(str2, "="))
	{
		tmp = ft_strjoin(str, "=");
		new->data = ft_strjoin(tmp, str2);
		free(tmp);
		new->var = ft_strdup(str);
	}
	else
	{
		new->data = ft_strjoin(str, str2);
		new->var = ft_strdup(str);
	}
	return (new);
}

void		ft_listmyadd(t_env **envirs, t_env *new)
{
	t_env	*tmp;

	tmp = (*envirs);
	if ((*envirs) == NULL)
	{
		(*envirs) = new;
		new->next = NULL;
	}
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->next = NULL;
	}
}

t_env		*listsearch(t_env *envirs, char *str)
{
	while (envirs)
	{
		if (ft_strequ(envirs->var, str))
			return (envirs);
		envirs = envirs->next;
	}
	return (0);
}
