
#include "minishell.h"

char	*_got_q(t_quotes_res **quotes_res, char **s, t_got_q_param *param)
{
	char	*save;

	*param->p_quote_deb = ft_strchr(*s, param->c);
	if (*param->p_quote_deb)
	{
		if (escape(*s, *param->p_quote_deb))
		{
			save = (*param->p_quote_deb) + 1;
			return (_got_q(quotes_res, &save, param));
		}
		*param->p_quote_fin = ft_strchr(*param->p_quote_deb + 1, param->c);
		(*quotes_res)->b_in_single_quotes = param->c == '\'';
	}
	else
		*param->p_quote_deb = NULL;
	return (*param->p_quote_deb);
}

t_quotes_res	*_q_ou_dq(t_quotes_res *quotes_res, t_quotes_tmp *qr)
{
	if (qr->p_quote_deb)
	{
		quotes_res->quote_deb = qr->p_quote_deb;
		quotes_res->quote_fin = qr->p_quote_fin;
		quotes_res->b_in_single_quotes = 1;
	}
	else if (qr->p_dquote_deb)
	{
		quotes_res->quote_deb = qr->p_dquote_deb;
		quotes_res->quote_fin = qr->p_dquote_fin;
		quotes_res->b_in_single_quotes = 0;
	}
	quotes_res->b_quote_err_micmac = qr->b_quote_err_micmac;
	return (quotes_res);
}

t_quotes_res	*_q_et_dq(t_quotes_res *quotes_res, t_quotes_tmp *qr)
{
	if (qr->p_quote_deb < qr->p_dquote_deb)
	{
		quotes_res->quote_deb = qr->p_quote_deb + 1;
		quotes_res->quote_fin = qr->p_quote_fin;
		quotes_res->b_in_single_quotes = 1;
	}
	else if (qr->p_quote_deb > qr->p_dquote_deb)
	{
		quotes_res->quote_deb = qr->p_dquote_deb + 1;
		quotes_res->quote_fin = qr->p_dquote_fin;
		quotes_res->b_in_single_quotes = 0;
	}
	quotes_res->b_quote_err_micmac = qr->b_quote_err_micmac;
	return (quotes_res);
}

void	_magic_quotes(t_quotes_tmp *qr,
				t_quotes_res **quotes_res, char **s)
{
	t_got_q_param	*param;

	param = malloc (sizeof(t_got_q_param));
	param->p_quote_deb = &qr->p_quote_deb;
	param->p_quote_fin = &qr->p_quote_fin;
	param->c = '\'';
	_got_q (&*quotes_res, s, param);
	if (&qr->p_quote_deb)
		(*quotes_res)->b_in_single_quotes = 1;
	param->p_quote_deb = &qr->p_dquote_deb;
	param->p_quote_fin = &qr->p_dquote_fin;
	param->c = '\"';
	_got_q (&*quotes_res, s, param);
	if (&qr->p_quote_deb)
		(*quotes_res)->b_in_single_quotes = 0;
	free (param);
}

t_quotes_res	*quotes(char **s)
{
	t_quotes_tmp	*qr;
	t_quotes_res	*quotes_res;
	t_mismatch		*mismatch_res1;
	t_mismatch		*mismatch_res2;

	qr = quote_tmp_create();
	quotes_res = quotes_res_create();
	_magic_quotes (qr, &quotes_res, s);
	if (_check_micmac(qr))
		qr->b_quote_err_micmac = 1;
	if ((qr->b_quote_err_micmac) && FL_MICMAC_CHECK)
	{
		free (qr);
		errno = 22;
		perror("Minishell : problème d'apostrophes et de guillemets ");
		return (NULL);
	}
	if (qr->p_quote_deb && qr->p_dquote_deb)
		_q_et_dq(quotes_res, qr);
	else
		_q_ou_dq(quotes_res, qr);
	free (qr);
	return (quotes_res);
}
