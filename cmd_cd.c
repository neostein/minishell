/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:35:12 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 18:51:13 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strunjoin(char *str, char *un)
{
	if (!str || !un)
		return (0);
	while (*str != '\0')
	{
		while (*str == *un)
		{
			str++;
			un++;
		}
		if (*un == '\0')
			return (str);
		str++;
	}
	return (0);
}

void	oldpwd(t_env *envirs, char **slash)
{
	t_env	*node;
	char	*tmp;

	if ((node = listsearch(envirs, "OLDPWD")) == NULL)
	{
		*slash = ft_strdup(".");
		return ;
	}
	*slash = ft_strdup((*node).data + 7);
	if ((node = listsearch(envirs, "HOME")))
	{
		if ((tmp = strunjoin(*slash, node->data + 5)))
			print_error(tmp, "~");
	}
	else
		ft_putendl(*slash);
}

char	*normal_cd(char *tmp, char *argv1)
{
	char	*slash;
	char	*tmp2;

	if ((tmp2 = getcwd(NULL, MAXPATHLEN)) == NULL)
		slash = ft_strdup("/");
	else
	{
		tmp = ft_dirjoin(tmp2);
		free(tmp2);
		slash = ft_strjoin(tmp, argv1);
		free(tmp);
	}
	return (slash);
}

char	*cmd_exec(char **argv, t_env *envirs)
{
	char	*slash;
	char	*tmp;

	if (ft_strequ(argv[1], "-"))
		oldpwd(envirs, &slash);
	else if ((tmp = ft_strchr(argv[1], '~')))
	{
		slash = cmd_cd_telda(tmp, envirs);
	}
	else if (argv[1][0] == '/')
		slash = ft_strdup(argv[1]);
	else if (ft_strchr(argv[1], '$'))
		slash = cmd_cd_dolar(argv, envirs);
	else
		slash = normal_cd(tmp, argv[1]);
	return (slash);
}

void	built_cmd(char **argv, t_env *envirs)
{
	char	*slash;
	t_env	*node;
	char	*oldpath;

	if (argv[1] != NULL && argv[2] != NULL)
	{
		print_error(argv[2], "cd: string not in pwd: ");
		return ;
	}
	if (argv[1])
		slash = cmd_exec(argv, envirs);
	else
	{
		if ((node = listsearch(envirs, "HOME")))
			slash = ft_strdup(node->data + 5);
		else
		{
			slash = ft_strdup(".");
			ft_putendl("cd: HOME not set");
		}
	}
	if ((oldpath = getcwd(NULL, MAXPATHLEN)) == NULL)
		oldpath = ft_strdup("/");
	oldpwd_actualisation(oldpath, envirs, slash);
	free(slash);
}
