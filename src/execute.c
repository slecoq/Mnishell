/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slecoq <slecoq@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:23:28 by fbourgue          #+#    #+#             */
/*   Updated: 2023/11/29 14:13:14 by slecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**_tabbed_args_val(t_arg **args)
{
	char	**tab_val;
	char	**ret;
	int		nb;
	t_arg	**save;
	char	*val;

	nb = 0;
	save = args;
	while (*args++)
		nb++;
	args = save;
	tab_val = malloc(sizeof(t_arg) * (nb + 1));
	ret = tab_val;
	while (*args)
		*tab_val++ = (*args++)->val;
	*tab_val = NULL;
	return (ret);
}

void	_interprete_equal(int b_global, t_noeud *n, t_env *new_entry,
			t_data *data)
{
	if (DEBUG_EXEC)
	{
		dprintf (2, "\n***process EQUAL %s\n", n->str_valeur);
		dprintf (2, "%s -> %s\n", n->noeud_droit->str_valeur,
			n->noeud_gauche->str_valeur);
	}
	b_global = 0;
	new_entry = lstnew_env (ft_strdup (n->noeud_gauche->str_valeur),
	ft_strdup (n->noeud_droit->str_valeur), b_global);
	add_var_env (data->env_lst, new_entry);
	ft_free_cell(new_entry);
}

void	_dup_close_ios(t_noeud *n)
{
	if (n->fd_output)
	{
		dup2 (n->fd_output, STDOUT_FILENO);
		close (n->fd_output);
	}
	if (n->fd_input)
	{
		dup2 (n->fd_input, STDIN_FILENO);
		close (n->fd_input);
	}
}
