
#include "minishell.h"

int	_execve(int res, char *path, char *args[], t_data *data)
{
	ft_init_signals ();
	res = execve (path, args, data->env);
	my_error ("execve");
	return (res);
}

int	run_exe(int piped, char *path, char *args[], t_data *data)
{
	pid_t	pid;
	int		status;
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

int	_clean_vars(int i, char **env_path_expl)
{
	while (env_path_expl[++i])
		free (env_path_expl[i]);
	free (env_path_expl[i]);
	free (env_path_expl);
	errno = 0;
	return (i);
}

char	*find_exe(char *env_path, char *fname)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (access(fname, F_OK) == 0)
	{
		errno = 0;
		return (ft_strdup(fname));
	}
	path = _find_in_pathes(env_path, fname);
	return (path);
}
