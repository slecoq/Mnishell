
#include "minishell.h"

int	_check_micmac(t_quotes_tmp *qr)
{
	if (qr->p_quote_deb && qr->p_dquote_deb
		&& qr->p_quote_deb < qr->p_dquote_deb
		&& qr->p_quote_fin > qr->p_dquote_fin)
	{
		return (1);
	}
	if (qr->p_quote_deb && qr->p_dquote_deb
		&& qr->p_quote_deb > qr->p_dquote_deb
		&& qr->p_quote_fin < qr->p_dquote_fin)
	{
		return (1);
	}
	return (0);
}
