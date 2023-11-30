
#include "minishell.h"

char	*_got_q(t_quotes_res **quotes_res, char **s, char **p_quote_deb, char **p_quote_fin, char q)
{
	char	*save;

	*p_quote_deb = ft_strchr(*s, q);
	if (*p_quote_deb)
	{
		if (escape(*s, *p_quote_deb))
		{
			save = (*p_quote_deb) + 1;
			return (_got_q(quotes_res, &save, p_quote_deb, p_quote_fin, q));
		}
		*p_quote_fin = ft_strchr(*p_quote_deb + 1, q);
		(*quotes_res)->b_in_single_quotes = q == '\'';
	}
	else
		*p_quote_deb = NULL;
	return (*p_quote_deb);
}

//int	*_check_mismatch(char **s, char c)
//{
//	int	nb;
//	char	*deb;
//	int	ret;
//
//	ret = mismatch_res_create();
//	nb = 0;
//	deb = *s;
//	deb = ft_strchr(deb, c);
//	while (deb)
//	{
//		if (!escape(*s, deb))
//			nb++;
//		deb = ft_strchr(deb+1, c);
//	}
//	ret->quote_manquante = c;
//	if (nb == 0)
//		ret->b_no_mismatch = 1;
//	else
//		ret->b_no_mismatch = ! (nb % 2) ;
//	return ret;
//}

int	_check_micmac(t_quotes_tmp *qr)
{
	if (qr->p_quote_deb && qr->p_dquote_deb
			&& qr->p_quote_deb < qr->p_dquote_deb
			&& qr->p_quote_fin > qr->p_dquote_fin)
	{
		perror("A GERER !!! micmac dans les apostrophes et guillemets");
		return (0);
	}
	if (qr->p_quote_deb && qr->p_dquote_deb
			&& qr->p_quote_deb > qr->p_dquote_deb
			&& qr->p_quote_fin < qr->p_dquote_fin)
	{
		perror("A GERER !!! micmac dans les apostrophes et guillemets");
		return (0);
	}
	return (1);
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
	return (quotes_res);
}

t_quotes_res	*quotes(char **s)
{
	t_quotes_tmp	*qr;
	t_quotes_res	*quotes_res;

	qr = quote_tmp_create();
	quotes_res = quotes_res_create();
	_got_q(&quotes_res, s, &qr->p_quote_deb, &qr->p_quote_fin, '\'');
	_got_q(&quotes_res, s, &qr->p_dquote_deb, &qr->p_dquote_fin, '\"');
	if (! _check_micmac(qr))
		return (NULL);
	if (qr->p_quote_deb && qr->p_dquote_deb)
		_q_et_dq(quotes_res, qr);
	else
		_q_ou_dq(quotes_res, qr);
	free (qr);
	return (quotes_res);
}
