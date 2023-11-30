
#include "minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_free_lstvar(t_env *lst)
{
	t_env	*cur;
	t_env	*next;

	cur = lst;
	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		cur = next;
	}
}

void	ft_free_lstenv(t_env *lst)
{
	t_env	*cur;
	t_env	*next;

	cur = lst;
	while (cur)
	{
		next = cur->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		cur = next;
	}
}

void	ft_free_cell(t_env *lst)
{
	free(lst->name);
	free(lst->value);
	free(lst);
}

int	case_exit(t_noeud *n, t_data *data, char *str)
{
	ft_putstr_fd(1, str);
	ft_free_lstenv(data->env_lst);
	ft_free(data->env);
	kill_tok(n->tok);
	kill_arbre(n);
	exit(0);
}
