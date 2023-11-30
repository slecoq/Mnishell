/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slecoq <slecoq@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:46:11 by fbourgue          #+#    #+#             */
/*   Updated: 2023/11/29 14:54:34 by slecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc_delim(char *s, char	*p_fin)
{
	int	found;
	int	sz;

	sz = ft_strlen(p_fin);
	found = ft_strncmp(s, p_fin, sz);
	return (found == 0);
}

void	_heredoc_child(t_noeud	*n,t_heredoc_data	*hd)
{
	t_data *data;
	hd->acc = ft_strdup("");
	close(hd->fd_pipe[0]);
	while (1)
	{
		hd->line = readline("> ");
		hd->tmp = hd->acc;
		if (is_heredoc_delim(hd->line, n->delim_heredoc))
			break ;
		else
		{
			ft_putstr_fd(hd->fd_pipe[1], hd->line);
			ft_putstr_fd(hd->fd_pipe[1], "\n");
		}
	}
	free (hd);
	data = get_data(NULL);
	ft_free(data->env);
	ft_free_lstenv(data->env_lst);
	sortir_propre(n, 0);
}

void	my_heredoc(t_noeud	*n)
{
	t_heredoc_data	*hd;

	hd = malloc (sizeof(t_heredoc_data));
	pipe(hd->fd_pipe);
	hd->pid = fork();
	if (hd->pid == 0)
		_heredoc_child(n, hd);
	else
	{
		waitpid(hd->pid, &hd->status, 0);
		n->fd_input = hd->fd_pipe[0];
		close(hd->fd_pipe[1]);
	}
	free (hd);
}
