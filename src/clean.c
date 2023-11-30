/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slecoq <slecoq@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:27:13 by fbourgue          #+#    #+#             */
/*   Updated: 2023/11/29 13:32:53 by slecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*_kill_tok_suivants(t_tok *t)
{
	while (t)
	{
		if (t->suivant)
		{
			if (DEBUG_CLEAN)
				dprintf(2, "TOK killing %s\n", t->suivant->val);
			if (t->suivant->val)
				free(t->suivant->val);
			free(t->suivant);
			t->suivant = NULL;
		}
		if (t->precedent)
			t = t->precedent;
		else
			break ;
	}
	return (t);
}

void	kill_tok(t_tok *tok_depart)
{
	t_tok	*t;

	t = tok_depart;
	if (!t)
		return ;
	while (t && t->suivant)
		t = t->suivant;
	t = _kill_tok_suivants(t);
	if (DEBUG_CLEAN)
		dprintf(2, "-TOK killing %s\n", t->val);
	if (t && t->val)
		free(t->val);
//	if (t)
		free(t);
		t = NULL;
}

void	sortir_propre(t_noeud	*n, int exit_code)
{
	if (DEBUG_CLEAN)
				dprintf(2, "sortir_propre : t=%s n=%s\n", n->tok->val, n->str_valeur);
	kill_tok(n->tok);
	kill_arbre(n);
	exit(exit_code);
}
