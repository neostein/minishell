/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:09:07 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 18:51:58 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **envp, t_env **envirs)
{
	if (envp[0] == NULL)
		return ;
	(*envirs) = NULL;
	while (*envp)
	{
		ft_listmyadd(envirs, ft_listmynew(*envp, NULL));
		envp++;
	}
}

void	hundler(int t)
{
	t = t + 0;
	if (g_prompt == 0)
		ft_putstr("\nroot$> ");
	else
		ft_putchar('\n');
}

void	fork_involve(char *slash, char **argv, t_env *envirs)
{
	pid_t	father;
	char	**array;

	array = list_2darray(envirs);
	if (access(slash, X_OK))
	{
		ft_putstr("minishell: permession denied: ");
		ft_putendl(argv[0]);
	}
	father = fork();
	if (father < 0)
	{
		ft_putendl("Fork error.");
		exit(1);
	}
	if (father > 0)
		wait(NULL);
	if (father == 0)
		execve(slash, argv, array);
	free(slash);
	listfree2d(array);
}

void	ft_minishell(char **argv, t_env **envirs, char *comma)
{
	char *tmp;
	char *slash;

	tmp = ft_strtrim(comma);
	str_replace_tabs(tmp);
	argv = ft_strsplit(tmp, ' ');
	if (ft_strequ(argv[0], "exit") && argv[0])
		exit(0);
	if (ft_strequ(argv[0], "unsetenv"))
		built_unsetenv(envirs, argv);
	else if (ft_strequ(argv[0], "setenv"))
		built_setenv(envirs, argv);
	else if (ft_strequ(argv[0], "env"))
		built_env(*envirs);
	else if (ft_strequ(argv[0], "cd"))
		built_cmd(argv, *envirs);
	else if (ft_strequ(argv[0], "echo"))
		built_echo2(tmp, *envirs);
	else if (searchcmd2(argv[0], &slash, *envirs))
		fork_involve(slash, argv, *envirs);
	else
		print_error(argv[0], "Minishell: command not found: ");
	free(tmp);
	listfree2d(argv);
}

int		main(int argc, char **argv, char **envp)
{
	char	buf[1024];
	char	*tmp;
	char	**comma;
	t_env	*envirs;

	signal(SIGINT, hundler);
	init_env(envp, &envirs);
	while (1337)
	{
		g_prompt = 0;
		init_buf(argc, buf);
		tmp = ft_strtrim(buf);
		if (*tmp)
		{
			prepare_buf(tmp);
			comma = ft_strsplit(tmp, -3);
			argc = 0;
			while (comma[argc])
				ft_minishell(argv, &envirs, comma[argc++]);
			listfree2d(comma);
		}
		free(tmp);
	}
	return (0);
}
