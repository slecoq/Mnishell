/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slecoq <slecoq@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:57:45 by fbourgue          #+#    #+#             */
/*   Updated: 2023/11/29 14:56:44 by slecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_interprete_pipe(int piped, t_noeud *n, t_pipe *pipe_ret, t_data *data)
{
	if (DEBUG_EXEC)
		dprintf (2, "\n***process PIPE %s\n", n->str_valeur);
	pipe_ret = t_pipe_create();
	pipe_show (piped, pipe_ret, n, data);
	if (DEBUG_EXEC)
	{
		dprintf (2, "***FIN process PIPE %s\n", n->str_valeur);
		dprintf (2, "Retour de pipe : %d et %d\n", pipe_ret->res_gauche,
			pipe_ret->res_droit);
	}
	free (pipe_ret);
}

int	_interpret_ext(int piped, t_noeud	*n, t_data *data)
{
	int		res;
	char	*exe_path;
	char	*path_env;
	char	**args;

	res = -1;
	path_env = getenv("PATH");
	exe_path = find_exe(path_env, n->str_valeur);
	args = _tabbed_args_val(n->args);
	if (exe_path != NULL)
	{
		if (DEBUG_EXEC)
		{
			dprintf(2, "\t\t\tRUN\t%s ", exe_path);
			dbg_tab(args);
			dprintf(2, "\n");
		}
		_dup_close_ios (n);
		if (n->delim_heredoc)
		{
			my_heredoc(n);
			dup2(n->fd_input, STDIN_FILENO);
			close(n->fd_input);
		}
		res = run_exe(piped, exe_path, args, data);
		my_error("_interpret_ext");
	}
	else
		my_error("Commande introuvable ");
	if (args && *args)
		free (args);
	return (res);
}

int	_interpret_bi(t_noeud	*n, t_data *data)
{
	int	res;

	res = 1;
	if (ft_strncmp(n->str_valeur, "cd", ft_strlen(n->str_valeur)) == 0)
		res = bi_cd(n, data->env_lst);
	else if (ft_strncmp(n->str_valeur, "pwd", ft_strlen(n->str_valeur)) == 0)
		res = bi_pwd();
	else if (ft_strncmp(n->str_valeur, "export", ft_strlen(n->str_valeur)) == 0)
		res = 0;
	else if (ft_strncmp(n->str_valeur, "env", ft_strlen(n->str_valeur)) == 0)
		res = bi_env(n, data);
	else if (ft_strncmp(n->str_valeur, "unset", ft_strlen(n->str_valeur)) == 0)
		res = bi_unset(n, data);
	else if (ft_strncmp(n->str_valeur, "exit", ft_strlen(n->str_valeur)) == 0)
		case_exit(n, data, "exit\n");
//	else if (ft_strncmp(n->str_valeur, "=", ft_strlen(n->str_valeur)) ==0)
//		res = bi_equal(n, data);
//	if(res != -1)
//		ct->arg_utilisé = 1;
	return (res);
}

int	_interprete_litteral(int res, int piped, t_noeud *n, t_data *data)
{
	expand (n, data->env_lst, data->status);
	res = _interpret_bi (n, data);
	if (res == 1)
	{
		if (DEBUG_EXEC)
			dprintf (2, "\t\tDEB process EXTERNE %s\n", n->str_valeur);
		res = _interpret_ext (piped, n, data);
		if (DEBUG_EXEC)
			dprintf (2, "\t\tFIN process EXTERNE %s\n", n->str_valeur);
	}
	if (res == -1)
	{
		my_error ("[interprete]");
	}
	return (res);
}

int	interprete(int piped, t_noeud *n, t_data *data)
{
	int		res;
	t_pipe	*pipe_ret;
	int		b_global;
	t_env	*new_entry;

	if (!n || !n->str_valeur)
		return (-1);
	res = -1;
	if (n->type == LITTERAL)
		res = _interprete_litteral(res, piped, n, data);
	else if (n->type == EQUAL)
		_interprete_equal(b_global, n, new_entry, data);
	else if (n->type == PIPE)
		_interprete_pipe (piped, n, pipe_ret, data);
	else if (n->type == REDIRECTION)
	{
		if (DEBUG_EXEC)
			dprintf(2, "\n***process REDIRECTION %s\n", n->str_valeur);
	}
	my_error("");
	return (res);
}