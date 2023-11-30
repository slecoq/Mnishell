
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
	free(t);
	t = NULL;
}
