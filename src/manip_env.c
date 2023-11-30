
#include "minishell.h"

char	*get_var_env(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (name);
}

t_env	*add_var_env(t_env *env_lst, t_env *var)
{
	t_env	*head;
	t_env	*new;

	head = env_lst;
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, var->name, ft_strlen(env_lst->name)))
		{
			env_lst->value = swap_value(env_lst->value, var->value);
			return (head);
		}
		env_lst = env_lst->next;
	}
	new = lstnew_env(ft_strdup(var->name), ft_strdup(var->value), \
	var->b_global);
	ft_lstadd_back(&head, new);
	env_lst = head;
	return (env_lst);
}

t_env	*init_env(char **env)
{
	t_env	*new;
	t_env	*env_lst;
	int		b_global;
	int		i;

	b_global = 1;
	i = -1;
	env_lst = NULL;
	while (env[++i])
	{
		new = lstnew_env(get_name(env[i]), get_value(env[i]), b_global);
		ft_lstadd_back(&env_lst, new);
	}
	return (env_lst);
}

char	*apply_string_env(const char *str_name, const char *str_val)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(str_name)
				+ ft_strlen(str_val) + 2));
	if (!dest)
		return (NULL);
	while (*str_name++)
		dest[i++] = *str_name;
	dest[i++] = '=';
	if (! str_val)
	{
		dest[i] = '\0';
		return (dest);
	}
	while (*str_val++)
		dest[i++] = *str_val;
	dest[i] = '\0';
	return (dest);
}

char	**new_env(t_env *env_lst)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (lst_size(env_lst) + 1));
	while (env_lst)
	{
		new_env[i++] = apply_string_env(env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
	new_env[i] = 0;
	return (new_env);
}
