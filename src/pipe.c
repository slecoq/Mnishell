/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slecoq <slecoq@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:36:58 by fbourgue          #+#    #+#             */
/*   Updated: 2023/11/29 15:00:24 by slecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__run_source(t_pipe *pipe_ret, t_noeud	*n, t_data *data)
{
	pipe_ret->pid_gauche = fork();
	if (pipe_ret->pid_gauche < 0)
		my_error("Fork child 1 ");
	else if (pipe_ret->pid_gauche == 0)
	{
		if (DEBUG_EXEC)
			dprintf(2, "\tEXEC noeud gauche\n");
		close(pipe_ret->fds[0]);
		dup2(pipe_ret->fds[1], 1);
		close(pipe_ret->fds[1]);
		pipe_ret->res_gauche = interprete(1, n->noeud_gauche, data);
		my_error("__run_source ");
		ft_free(data->env);
		ft_free_lstenv(data->env_lst);
		free(pipe_ret);
		sortir_propre(n, 0);
	}
}

void	__run_dest(t_pipe *pipe_ret, t_noeud	*n, t_data *data)
{
	pipe_ret->pid_droit = fork();
	if (pipe_ret->pid_droit < 0)
		my_error("Fork child 2 ");
	else if (! pipe_ret->pid_droit)
	{
		if (DEBUG_EXEC)
			dprintf(2, "\tEXEC noeud droit\n");
		close(pipe_ret->fds[1]);
		dup2(pipe_ret->fds[0], 0);
		close(pipe_ret->fds[0]);
		pipe_ret->res_droit = interprete(1, n->noeud_droit, data);
		my_error("__run_dest ");
		ft_free(data->env);
		ft_free_lstenv(data->env_lst);
		free(pipe_ret);
		sortir_propre(n, 0);
	}
}

void	pipe_show(int piped, t_pipe	*pipe_ret, t_noeud	*n, t_data *data)
{
	int	pid;
	int	status;

	if (pipe(pipe_ret->fds) == -1)
		my_error("Pipe ");
	__run_source(pipe_ret, n, data);
	__run_dest(pipe_ret, n, data);
	close(pipe_ret->fds[0]);
	close(pipe_ret->fds[1]);
	waitpid(pipe_ret->pid_gauche, &pipe_ret->res_gauche, 0);
	waitpid(pipe_ret->pid_droit, &pipe_ret->res_droit, 0);
}
