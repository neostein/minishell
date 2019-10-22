/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:05:12 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 00:30:30 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*loop_unset(char **argv, t_env *tmp, t_env **prev, t_env **envirs)
{
	if (ft_strequ(*argv, tmp->var))
	{
		if (!*prev)
		{
			free((*envirs)->data);
			free((*envirs)->var);
			(*envirs) = (*envirs)->next;
			free(tmp);
			tmp = (*envirs);
		}
		else
		{
			free(tmp->data);
			free(tmp->var);
			(*prev)->next = tmp->next;
			free(tmp);
			tmp = *prev;
		}
	}
	(*prev) = tmp;
	if (tmp)
		tmp = tmp->next;
	return (tmp);
}

void		cmd_setenv_normal(char **argv, t_env **envirs)
{
	int		i;
	char	*tmp;

	i = -1;
	while (argv[1][++i])
		if (!ft_isalnum(argv[1][i]) && argv[1][i] != '_')
		{
			print_error(argv[1], "invalid string: ");
			return ;
		}
	if (argv[2] == NULL)
		tmp = ft_strdup("=");
	else
		tmp = ft_strtrimchr(argv[2], '"');
	ft_listmyadd(envirs, ft_listmynew(argv[1], tmp));
	free(tmp);
}

void		built_setenv(t_env **envirs, char **argv)
{
	t_env	*tmp;
	char	*data;

	if (ft_2dstrlen(argv) > 3)
		ft_putendl("setenv: too many arguments");
	else
	{
		if (argv[1] == NULL)
			ft_putendl("setenv: You miss an argument : unsetenv var value");
		else if ((tmp = listsearch(*envirs, argv[1])))
		{
			data = ft_strjoin(argv[1], "=");
			free(tmp->data);
			tmp->data = ft_strjoin(data, argv[2]);
			free(data);
		}
		else
			cmd_setenv_normal(argv, envirs);
	}
}

void		built_unsetenv(t_env **envirs, char **argv)
{
	t_env	*prev;
	t_env	*tmp;

	tmp = (*envirs);
	if (argv[1] == NULL)
		ft_putendl("You miss an argument: usage: unsetenv variable");
	else
		while (*argv)
		{
			prev = NULL;
			tmp = (*envirs);
			while (tmp)
				tmp = loop_unset(argv, tmp, &prev, envirs);
			argv++;
		}
}

void		built_env(t_env *envirs)
{
	while (envirs)
	{
		ft_putendl(envirs->data);
		envirs = envirs->next;
	}
}
