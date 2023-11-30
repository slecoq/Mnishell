
#include "minishell.h"

t_mismatch	*mismatch_res_create(void)
{
	t_mismatch	*pr;

	pr = malloc(sizeof(t_mismatch));
	pr->quote_manquante = 0;
	pr->b_no_mismatch = 1;
	return (pr);
}

t_arg	*arg_create(t_tok	*t)
{
	t_arg	*pr;

	pr = malloc(sizeof(t_arg));
	pr->b_expanse_allowed = t->b_expanse_allowed;
	if (t->type == TOK_LIT)
		pr->val = t->val;
		pr->b_val_a_free = 0;
	return (pr);
}

t_pipe	*t_pipe_create(void)
{
	t_pipe	*pr;

	pr = malloc(sizeof(t_pipe));
	pr->pid_droit = -1;
	pr->pid_gauche = -1;
	pr->res_droit = -1;
	pr->res_gauche = -1;
	return (pr);
}

t_quotes_tmp	*quote_tmp_create(void)
{
	t_quotes_tmp	*pr;

	pr = malloc(sizeof(t_quotes_tmp));
	pr->p_quote_deb = NULL;
	pr->p_quote_fin = NULL;
	pr->p_dquote_deb = NULL;
	pr->p_dquote_fin = NULL;
	pr->b_quote_err_micmac = 0;
	return (pr);
}

t_grab_res	*grab_res_create(void)
{
	t_grab_res	*pr;

	pr = malloc(sizeof(t_grab_res));
	pr->b_expanse_allowed = 1;
	pr->val = NULL;
	pr->b_quote_err_micmac = 0;
	return (pr);
}
