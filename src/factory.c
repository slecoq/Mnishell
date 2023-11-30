
#include "minishell.h"

t_tok	*tok_create(char *val, t_tok_type type)
{
	t_tok	*tok;

	tok = (t_tok *)ft_calloc(1, sizeof(t_tok));
	if (!tok)
		return (NULL);
	tok->val = ft_strdup(val);
	tok->type = type;
	tok->precedent = NULL;
	tok->suivant = NULL;
	tok->arg_util = 0;
	tok->b_expanse_allowed = 1;
	return (tok);
}

t_node_type	_from_tok_type_to_cmd_type(t_tok_type t_type)
{
	if (t_type == TOK_PIPE)
		return(PIPE);
	else if (t_type == TOK_GRAND)
		return(REDIRECTION);
	else if (t_type == TOK_PETIT)
		return(REDIRECTION);
	else if (t_type == TOK_DOUBLE_GRAND)
		return(REDIRECTION);
	else if (t_type == TOK_DOUBLE_PETIT)
		return(HEREDOC);
	else if (t_type == TOK_EQUAL)
		return(EQUAL);
	else if (t_type == TOK_LIT)
	{
		return(LITTERAL);
	}
		return(INCONNU);

}

t_parse_res	*parse_res_create()
{
	t_parse_res *pr;

	pr = malloc(sizeof(t_parse_res));
	pr->deb_post = NULL;
	pr->fin_pre = NULL;
	pr->s_captured = NULL;
	pr->s_pre = NULL;
	pr->s_rempl = ft_strdup("");
	return (pr);
}


t_quotes_res	*quotes_res_create()
{
	t_quotes_res *pr;

	pr = malloc(sizeof(t_quotes_res));
	pr->quote_deb = NULL;
	pr->quote_fin = NULL;
	pr->b_in_single_quotes = 0;
	return (pr);
}

t_grab_res	*grab_res_create()
{
	t_grab_res *pr;

	pr = malloc(sizeof(t_grab_res));
	pr->b_expanse_allowed = 1;
	pr->val = NULL;
	return (pr);
}

t_arg	*arg_create(t_tok	*t)
{
	t_arg *pr;

	pr = malloc(sizeof(t_arg));
	pr->b_expanse_allowed = t->b_expanse_allowed;
	pr->val = t->val;
	pr->b_val_a_free = 0;
	return (pr);
}

t_pipe	*t_pipe_create()
{
	t_pipe *pr;

	pr = malloc(sizeof(t_pipe));
	pr->pid_droit = -1;
	pr->pid_gauche = -1;
	pr->res_droit = -1;
	pr->res_gauche = -1;
	return (pr);
}

t_quotes_tmp	*quote_tmp_create()
{
	t_quotes_tmp *pr;

	pr = malloc(sizeof(t_quotes_tmp));
	pr->p_quote_deb = NULL;
	pr->p_quote_fin = NULL;
	pr->p_dquote_deb = NULL;
	pr->p_dquote_fin = NULL;
	return (pr);
}

t_noeud	*noeud_create(t_tok *t, t_noeud *prec)
{
	t_noeud	*n;

	n = (t_noeud *)ft_calloc(1, sizeof(t_noeud));
	if (!n)
		return (NULL);
	n->type = _from_tok_type_to_cmd_type(t->type);
	n->precedent = prec;
	n->delim_heredoc = NULL;
//	n->fd_heredoc = 0;
	n->fd_input = 0;
	n->fd_output = 0;
	n->str_valeur = ft_strdup(t->val);
	n->tok = t;
	n->b_expanse_allowed = t->b_expanse_allowed;
	if (t->type == TOK_LIT)
		n->args = donne_moi_des_arguments(t);
	if (n->type == REDIRECTION || n->type == HEREDOC)
		donne_moi_des_io(n->precedent, t);
	return (n);
}
