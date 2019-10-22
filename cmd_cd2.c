/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:18:15 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 18:54:44 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extra_telda_err(char *tmp)
{
	char		*slash;

	slash = ft_strdup(".");
	ft_putendl("Permission denied or non-exist path");
	free(tmp);
	return (slash);
}

char	*cmd_cd_telda(char *tmp, t_env *envirs)
{
	struct stat	buf;
	char		*slash;
	t_env		*node;

	if ((node = listsearch(envirs, "HOME")))
	{
		if (*(tmp + 1) == '/' || *(tmp + 1) == '\0')
			slash = ft_strjoin(node->data + 5, tmp + 1);
		else
		{
			tmp = ft_strjoin("/Users/", tmp + 1);
			if (lstat(tmp, &buf) == -1)
				slash = extra_telda_err(tmp);
			else
				slash = tmp;
		}
	}
	else
	{
		slash = ft_strdup(".");
		ft_putendl("HOME not set !");
	}
	return (slash);
}

void	oldpwd_actualisation(char *oldpath, t_env *envirs, char *slash)
{
	t_env	*node;

	if (chdir(slash) == -1)
		print_error(slash, "cd: file not exist Or permission denied: ");
	else if ((node = listsearch(envirs, "OLDPWD")))
	{
		free(node->data);
		node->data = ft_strjoin("OLDPWD=", oldpath);
	}
	else
		ft_listmyadd(&envirs, ft_listmynew("OLDPWD", oldpath));
	free(oldpath);
	pwd_actualisation(envirs);
}

void	pwd_actualisation(t_env *envirs)
{
	char	*currentpwd;
	t_env	*node;

	if ((currentpwd = getcwd(NULL, MAXPATHLEN)) == NULL)
		currentpwd = ft_strdup("/");
	else
	{
		if ((node = listsearch(envirs, "PWD")))
		{
			free(node->data);
			node->data = ft_strjoin("PWD=", currentpwd);
		}
		else
			ft_listmyadd(&envirs, ft_listmynew("PWD", currentpwd));
	}
	free(currentpwd);
}

int		ft_indixchar(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
