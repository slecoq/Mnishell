
#include "minishell.h"

void	kill_args(t_arg **args)
{
	t_arg	**args_save;

	args_save = args;
	while (args && *args)
	{
		if ((*args)->b_val_a_free)
			free ((*args)->val);
		free (*args++);
	}
	if (args)
		free (*args);
	free(args_save);
}

void	kill_noeud(t_noeud *n)
{
	if (DEBUG_CLEAN)
		dprintf(2, "killing %s\n", n->str_valeur);
	kill_args(n->args);
	if (n->fd_input)
		close (n->fd_input);
	if (n->fd_output)
		close (n->fd_output);
	free(n->str_valeur);
	free(n);
	n = NULL;
}

t_noeud*	_kill_noeuds_suivants(t_noeud *n)
{
	while (n)
	{
		if (n->suivant)
		{
			kill_noeud(n->suivant);
		}
		if (n->precedent)
			n = n->precedent;
		else
			break ;
	}
	return (n);
}

void	kill_arbre(t_noeud *noeud_depart)
{
	t_noeud	*n;

	n = noeud_depart;
	if (!n)
		return ;
	while (n && n->suivant)
		n = n->suivant;
	n = _kill_noeuds_suivants(n);
	if (DEBUG_CLEAN)
		dprintf(2, "-killing %s\n", n->str_valeur);
	kill_noeud(n);
}
