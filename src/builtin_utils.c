
#include "minishell.h"

void	_gestion_assignation_export(t_tok *t, t_data *data)
{
	t_env	*new_entry;

	if (!ft_strncmp(t->val, "=", 1))
	{
		if (!ft_strncmp(t->precedent->val, "export", ft_strlen("export")))
			return ;
		else if (t->suivant)
		{
			new_entry = lstnew_env(ft_strdup(t->precedent->val), \
			ft_strdup(t->suivant->val), 1);
			add_var_env(data->env_lst, new_entry);
			ft_free_cell(new_entry);
			t->suivant->arg_util = 1;
		}
		else
		{
			new_entry = lstnew_env(ft_strdup(t->precedent->val), \
			ft_strdup(""), 1);
			add_var_env(data->env_lst, new_entry);
		}
		t->arg_util = 1;
		t->precedent->arg_util = 1;
		ft_free(data->env);
		data->env = new_env(data->env_lst);
	}
}

void	_gestion_export_var(t_tok *t, t_data *data)
{
	t_env	*head_lst;

	head_lst = data->env_lst;
	while (t)
	{
		while (data->env_lst)
		{
			if (!ft_strncmp(t->val, data->env_lst->name, ft_strlen(t->val)))
			{
				data->env_lst->b_global = 1;
				t->arg_util = 1;
			}
			data->env_lst = data->env_lst->next;
		}
		data->env_lst = head_lst;
		t = t->suivant;
	}
}
