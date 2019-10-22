/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 23:18:53 by nsaber            #+#    #+#             */
/*   Updated: 2019/10/18 18:57:27 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <signal.h>
# include <readline/readline.h>
# include <setjmp.h>

char g_prompt;
typedef struct		s_env
{
	char			*data;
	char			*var;
	struct s_env	*next;
}					t_env;

void				built_cmd(char **argv, t_env *envirs);
char				*ft_dirjoin(char *dir);
void				ft_listmyadd(t_env **envirs, t_env *new);
t_env				*ft_listmynew(char *str, char *var);
void				built_env(t_env *envirs);
void				built_setenv(t_env **envirs, char **argv);
void				built_unsetenv(t_env **envirs, char **argv);
t_env				*listsearch(t_env *envirs, char *str);
void				listfree2d(char **array);
void				print_error(char *str, char *string);
char				*strunjoin(char *str, char *un);
char				*cmd_echo_process(char *buf, char **tmp2, t_env *envirs);
char				*cmd_echo_print(char *buf, char *c, char *lnu, char *last);
void				built_echo2(char *buf, t_env *envirs);
char				*print_var(char *buf, t_env *envirs);
int					endvar(char *str);
t_env				*loop_unset(char **av, t_env *tmp, t_env **pv, t_env **e);
void				prepare_buf(char *buf);
void				init_buf(int argc, char *buf);
int					searchcmd2(char *cmd, char **slash, t_env *envirs);
int					ft_2dstrlen(char **array);
void				cmd_setenv_normal(char **argv, t_env **envirs);
char				*str_replace_tabs(char *str);
void				oldpwd_actualisation(char *oldp, t_env *env, char *sla);
char				*cmd_echo_telda(t_env *envirs, char *buf);
char				*cmd_cd_telda(char *tmp, t_env *envirs);
char				**list_2darray(t_env *envirs);
int					ft_listlen(t_env *envirs);
void				fork_involve(char *slash, char **argv, t_env *envirs);
void				ft_minishell(char **argv, t_env **envirs, char *comma);
void				pwd_actualisation(t_env *envirs);
void				oldpwd_actualisation(char *oldp, t_env *env, char *sla);
char				*extra_telda_err(char *tmp);
char				*cmd_cd_dolar(char **argv, t_env *envirs);
int					ft_indixchar(char *str, char c);
#endif
