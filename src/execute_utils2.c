
#include "minishell.h"

int	_count_args(int nb_args, t_tok *t)
{
	while (t && t->type == TOK_LIT)
	{
		t = t->suivant;
		nb_args++;
	}
	return (nb_args);
}

t_arg	**donne_moi_des_arguments(t_tok	*t, t_noeud *n)
{
	t_arg		**args;
	t_tok		*save;
	int			nb_args;
	int			i;

	nb_args = 0;
	save = t;
	t = t->suivant;
	nb_args = _count_args (nb_args, t);
	t = save;
	args = ft_calloc(nb_args + 1 + 1, sizeof(t_arg));
	args[0] = arg_create(t);
	if (nb_args > 0)
	{
		i = 0;
		t = t->suivant;
		while (t && t->type == TOK_LIT)
		{
			args[++i] = arg_create(t);
			t->arg_util = 1;
			t = t->suivant;
		}
		args[++i] = NULL;
	}
	return (args);
}

void	my_error(char *s)
{
	if (errno != 0)
	{
		if (! s)
			perror("");
		else
			perror(s);
	}
	errno = 0;
}

void	donne_moi_des_io(t_noeud *n_redir, t_tok	*tok_redir)
{
	t_tok	*tok_path;
	char	*fpath;

	tok_path = tok_redir->suivant;
	if (tok_path && tok_path->type == TOK_LIT)
	{
		fpath = tok_path->val;
		if (tok_redir->type == TOK_GRAND)
			n_redir->fd_output = open(fpath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (tok_redir->type == TOK_PETIT)
			n_redir->fd_input= open(fpath, O_RDONLY);
		else if (tok_redir->type == TOK_DOUBLE_GRAND)
			n_redir->fd_output = open(fpath, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (tok_redir->type == TOK_DOUBLE_PETIT)
		{
			n_redir->delim_heredoc = tok_redir->suivant->val;
			tok_redir->suivant->arg_util = 1;
		}
		tok_path->arg_util = 1;
		tok_redir->arg_util = 1;
	}
}

char	*_normalize_slash(int i, char *cur_path, char *path_tmp,
			char **env_path_expl)
{
	if (ft_strrchr (cur_path, '/')  != &(cur_path[ft_strlen (cur_path) - 1]))
		path_tmp = ft_strjoin (env_path_expl[i], "/");
	else
		path_tmp = env_path_expl[i];
	free (env_path_expl[i]);
	return (path_tmp);
}

char	*_find_in_pathes(char *env_path, char *fname)
{
	char	*path;
	char	*path_tmp;
	char	**env_path_expl;
	char	*cur_env_path;
	int		i;

	path = NULL;
	env_path_expl = ft_split(env_path, ':');
	i = -1;
	while (env_path_expl[++i])
	{
		cur_env_path = env_path_expl[i];
		path_tmp = _normalize_slash (i, cur_env_path, path_tmp, env_path_expl);
		path = ft_strjoin(path_tmp, fname);
		free(path_tmp);
		if (access(path, F_OK) == 0)
		{
			i = _clean_vars (i, env_path_expl);
			return (path);
		}
		free (path);
		path = NULL;
	}
	free(env_path_expl);
	return (path);
}
