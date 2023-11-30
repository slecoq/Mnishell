/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slecoq <slecoq@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:34:25 by slecoq            #+#    #+#             */
/*   Updated: 2023/11/29 17:25:05 by slecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_noeud *n, t_data *data)
{
	print_env_lst(data->env_lst);
	return (0);
}

int	bi_cd(t_noeud	*n, t_env *env_lst)
{
	int		ret;
	char	*dir;
	char	*old;
	t_env	*new_oldpwd;
	t_env	*new_pwd;

	old = getcwd(NULL, 0);
	if (!n->args[1])
		ret = chdir(get_var_env(env_lst, "HOME"));
	if (n && n->args[1] && n->args[1]->val)
	{
		dir = n->args[1]->val;
		if (ft_strnstr(n->args[1]->val, "~", 1) != 0)
			dir = get_var_env(env_lst, "HOME");
		else if (ft_strnstr(n->args[1]->val, "-", 1) != 0)
			dir = get_var_env(env_lst, "OLDPWD");
		ret = chdir(dir);
	}
	new_oldpwd = lstnew_env(ft_strdup("OLDPWD"), old, 1);
	new_pwd = lstnew_env(ft_strdup("PWD"), getcwd(NULL, 0), 1);
	add_var_env(env_lst, new_pwd);
	add_var_env(env_lst, new_oldpwd);
	ft_free_cell(new_oldpwd);
	ft_free_cell(new_pwd);
	return (ret);
}

int	bi_pwd(void)
{
	char	*sout;

	sout = getcwd(NULL, 0);
	if (! sout)
		return (-1);
	printf("%s\n", sout);
	free(sout);
	return (0);
}

int	bi_export(t_tok *t, t_data *data)
{
	t_tok	*head;
	t_env	*envlst_head;

	head = t;
	envlst_head = data->env_lst;
	t->arg_util = 1;
	while (t)
	{
		if (!head->suivant)
		{
			print_env_lst(data->env_lst);
			t->arg_util = 1;
			break ;
		}
		_gestion_assignation_export(t, data);
		t = t->suivant;
	}
	t = head;
	data->env_lst = envlst_head;
	_gestion_export_var(t, data);
	data->env_lst = envlst_head;
	ft_free(data->env);
	data->env = new_env(data->env_lst);
}

int	bi_unset(t_noeud *n, t_data *data)
{
	t_noeud	*tmp;
	t_env	*envlst_head;
	int		i;

	tmp = n;
	envlst_head = data->env_lst;
	i = -1;
	while (tmp)
	{
		while (data->env_lst)
		{
			while (tmp->args[++i])
			{
				if (ft_strncmp(data->env_lst->name, tmp->args[i]->val, \
				ft_strlen(data->env_lst->name)) == 0)
					data->env_lst->b_global = 0;
			}
			i = -1;
			data->env_lst = data->env_lst->next;
		}
		data->env_lst = envlst_head;
		tmp = tmp->suivant;
	}
	data->env_lst = envlst_head;
	return (0);
}
