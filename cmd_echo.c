/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 02:00:09 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/17 13:55:10 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_echo_telda(t_env *envirs, char *buf)
{
	t_env		*node;
	char		*string;
	struct stat	bufff;

	if ((node = listsearch(envirs, "HOME")) == NULL)
		return (0);
	if (*(buf + 1) != '/' && *(buf + 1) != '\0' && *(buf + 1) != ' ')
	{
		string = ft_strjoin("/Users/", buf + 1);
		if (lstat(string, &bufff) == -1)
		{
			ft_putstr("~");
			ft_putstr(buf + 1);
		}
		else
			ft_putstr(string);
		buf = buf + ft_strlen(buf + 1);
		free(string);
	}
	else
		ft_putstr(node->data + 5);
	buf++;
	return (buf);
}

char	*cmd_echo_process(char *buf, char **tmp2, t_env *envirs)
{
	char	last;
	char	lastsingle;
	char	c;

	c = 0;
	lastsingle = 0;
	last = 0;
	while (*buf == ' ' && *buf != '\0')
		buf++;
	if (ft_strequ(tmp2[0], "-n"))
		buf += 3;
	if (*buf == '~')
		buf = cmd_echo_telda(envirs, buf);
	while (buf && *buf != '$' && *buf != '\0' && *buf != '~')
		buf = cmd_echo_print(buf, &c, &lastsingle, &last);
	if (buf && *buf == '$')
	{
		buf = print_var(buf, envirs);
		if (*buf != '$' && *buf != '/')
			ft_putchar(' ');
	}
	return (buf);
}

void	built_echo2(char *buf, t_env *envirs)
{
	char	**tmp2;

	buf = buf + 4;
	tmp2 = ft_strsplit(buf, ' ');
	while (buf && *buf != '\0')
	{
		buf = cmd_echo_process(buf, tmp2, envirs);
	}
	if (tmp2 && !ft_strequ(tmp2[0], "-n"))
		ft_putchar('\n');
	listfree2d(tmp2);
}

char	*cmd_echo_print(char *buf, char *c, char *lastsingle, char *last)
{
	if (*buf == '"' && (*c != 1 || *lastsingle % 2 == 0))
	{
		(*last)++;
		buf++;
		*c = 2;
	}
	else if (*buf == '\'' && (*c != 2 || *last % 2 == 0))
	{
		(*lastsingle)++;
		buf++;
		*c = 1;
	}
	else
	{
		if (*buf == ' ' && (*last % 2 == 0 && *lastsingle % 2 == 0))
		{
			ft_putchar(' ');
			while (*buf == ' ')
				buf++;
		}
		else
			ft_putchar(*buf++);
	}
	return (buf);
}
