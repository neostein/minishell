/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_buf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:57:25 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 00:54:23 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_buf(char *buf)
{
	int	singl;
	int	doubl;

	singl = 0;
	doubl = 0;
	while (*buf)
	{
		if (*buf == '"')
			doubl++;
		if (*buf == '\'')
			singl++;
		if (*buf == ';' && ((doubl % 2 == 0) && (singl % 2 == 0)))
			*buf = -3;
		buf++;
	}
}

void	init_buf(int argc, char *buf)
{
	ft_memset((void *)buf, '\0', 1024);
	ft_putstr("root$> ");
	argc = read(1, buf, 1024);
	g_prompt = 1;
	if (argc == 0)
		exit(1);
	buf[argc - 1] = '\0';
}

char	*ft_dirjoin(char *dir)
{
	char *tmp;

	tmp = ft_strjoin(dir, "/");
	return (tmp);
}

int		validcmdpath(char **paths, char *envpath, char **slash, char *cmd)
{
	struct stat	buf;
	char		*exepath;
	int			i;

	i = 0;
	while (paths[i])
	{
		exepath = ft_dirjoin(paths[i]);
		envpath = ft_strjoin(exepath, cmd);
		free(exepath);
		if (lstat(envpath, &buf) == 0)
		{
			*slash = ft_strdup(envpath);
			free(envpath);
			listfree2d(paths);
			return (1);
		}
		free(envpath);
		i++;
	}
	return (0);
}

int		searchcmd2(char *cmd, char **slash, t_env *envirs)
{
	char	**paths;
	char	*envpath;

	if (!access(cmd, X_OK))
	{
		*slash = ft_strdup(cmd);
		return (1);
	}
	if ((envirs = listsearch(envirs, "PATH")) == NULL)
		return (0);
	envpath = envirs->data + 5;
	paths = ft_strsplit(envpath, ':');
	if (validcmdpath(paths, envpath, slash, cmd))
		return (1);
	listfree2d(paths);
	return (0);
}
