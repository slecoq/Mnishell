
#include "minishell.h"

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	if (!str[i + 1])
	{
		new_str = (char *)malloc(sizeof(char) * 1);
		new_str[0] = '\0';
		return (new_str);
	}
	i++;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}

char	*get_name(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	new_str = (char *)malloc(sizeof(char ) * (i + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i] != '=' && str[i] != '\0')
		new_str[i] = str[i];
	new_str[i] = '\0';
	return (new_str);
}

char	*get_value_if_global(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)) && env->b_global)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (name);
}
