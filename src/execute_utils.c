
#include "minishell.h"

int _execve (int res, char *path, char *args[], t_data *data)
{
	ft_init_signals ();
	res = execve (path, args, data->env);
	my_error ("execve");
	return res;
}

int	run_exe(int piped, char *path, char *args[], t_data *data)
{
	pid_t	pid;
	int	status;
	char	***p_args;
	int		res;

	res = 0;
	if (! piped)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			res = _execve (res, path, args, data);
		else
			waitpid(pid, &(data->status), 0);
	}
	else
	{
		res = execve(path, args, data->env);
		my_error("piped execve");
	}
	free(path);
	p_args = &args;
	return (res);
}

char	*_find_in_pathes(char *env_path, char *fname)
{
	char	*path;
	char	*path_tmp;
	char	**env_path_expl;
	char	*cur_env_path;
	int	i;

	path = NULL;
	env_path_expl = ft_split(env_path, ':');
	i = -1;
	while (env_path_expl[++i])
	{
		cur_env_path = env_path_expl[i];
		if (ft_strrchr(cur_env_path, '/') != &(cur_env_path[ft_strlen(cur_env_path) - 1]))
			path_tmp = ft_strjoin(env_path_expl[i], "/");
		else
			path_tmp = env_path_expl[i];
		free(env_path_expl[i]);
		path = ft_strjoin(path_tmp, fname);
		free(path_tmp);
		if (access(path, F_OK) == 0)
		{
				while (env_path_expl[++i])
					free(env_path_expl[i]);
				free(env_path_expl[i]);
				free(env_path_expl);
				errno = 0;
				return (path);
		}
		free (path);
		path = NULL;
	}
	free(env_path_expl);
	return (path);
}

char	*find_exe(char *env_path, char *fname)
{
	char	*path;
	struct	stat	st;
	pid_t	pid;
	int	status;

	if (access(fname, F_OK) == 0)
	{
		errno = 0;
		return (ft_strdup(fname));
	}
	path = _find_in_pathes(env_path, fname);
	return (path);
}

void	donne_moi_des_io(t_noeud *n_redir, t_tok	*tok_redir)
{
	t_tok	*tok_path;
	char*	fpath;

	tok_path = tok_redir->suivant;
	if(tok_path && tok_path->type == TOK_LIT)
	{
		fpath = tok_path->val;
		if (tok_redir->type == TOK_GRAND)
		{
			n_redir->fd_output = open(fpath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (n_redir->fd_output == -1)
			{
			}
		}
		else if (tok_redir->type == TOK_PETIT)
		{
			if (!n_redir)
				return ;
			n_redir->fd_input= open(fpath, O_RDONLY);
			if (n_redir->fd_input == -1)
			{
			}
		}
		else if (tok_redir->type == TOK_DOUBLE_GRAND)
		{
			n_redir->fd_output = open(fpath, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (n_redir->fd_output == -1)
			{
			}
		}
		else if (tok_redir->type == TOK_DOUBLE_PETIT)
		{
			n_redir->delim_heredoc = tok_redir->suivant->val;
			tok_redir->suivant->arg_util = 1;
			if (n_redir->fd_output == -1)
			{
			}
		}
		tok_path->arg_util = 1;
		tok_redir->arg_util = 1;
	}
}

t_arg	**donne_moi_des_arguments(t_tok	*t)
{
	t_arg		**args;
	t_tok			*save;
	int		nb_args;
	int		i;

	nb_args = 0;
	save = t;
	t = t->suivant;
	while(t && t->type == TOK_LIT)
	{
		nb_args++;
		t = t->suivant;
	}
	t = save;
	args = ft_calloc(nb_args + 1 + 1, sizeof(t_arg));
	args[0] = arg_create(t);
	if (nb_args > 0)
	{
		i = 0;
		t = t->suivant;
		while(t && t->type == TOK_LIT)
		{
			args[++i] = arg_create(t);
			t->arg_util = 1;
			t = t->suivant;
		}
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
