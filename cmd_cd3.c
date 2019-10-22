/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:50:57 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 18:54:17 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_cd_dolar(char **argv, t_env *envirs)
{
	char	*tmp;
	t_env	*node;
	char	*slash;
	char	*var;

	tmp = ft_strchr(argv[1], '$') + 1;
	if (strchr(tmp, '/'))
	{
		var = ft_strsub(tmp, 0, ft_indixchar(tmp, '/'));
		tmp = ft_strchr(tmp, '/');
		if ((node = listsearch(envirs, var)) != NULL)
			slash = ft_strjoin(node->data + ft_strlen(var) + 1, tmp);
		else
			slash = ft_strjoin(var, tmp);
		free(var);
	}
	else if ((node = listsearch(envirs, tmp)) != NULL)
		slash = ft_strdup(node->data + ft_strlen(tmp) + 1);
	else
		slash = ft_strdup(argv[1]);
	return (slash);
}
