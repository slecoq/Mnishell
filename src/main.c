
#include "minishell.h"

int g_received_signal;

void	on_spaces(char **s_init)
{
	char	*c;
	char	**s = s_init;

	while (*s && (
			**s == ' ' || **s == '\t' || **s == '\n'
		)
	)
		(*s)++;
}


t_tok	*parse(char *s_init)
{
	char		*tok_val;
	t_grab_res *gr;
	char	*save_tok_val;
	t_tok	*tok;
	t_tok	*tok_root;
	t_tok	*tok_last;
	char	**s = &s_init;

	// char *toto=ft_strdup(*s_init);
//	s = s_init;
	tok_root = NULL;
	tok_last = tok_root;
	while (**s && *s)
	{
		on_spaces(s);
		if(! **s)
			break ;
		gr =grab(s);
		tok_val = gr->val;
		save_tok_val = tok_val;
		tok = create_tok(&tok_val, tok_last);
		tok->b_expanse_allowed = gr->b_expanse_allowed;
//		if (gr->b_val_a_free)
//			free (gr->val);
		free (gr);
		free (save_tok_val);
		if (!tok_root)
			tok_root = tok;
		else
		{
		}
		tok_last = tok;
	}
	return (tok_root);
}

t_noeud	*create_AST(t_tok *tok_root, t_data *data)
{
	t_noeud	*n;
	t_noeud	*root;
	t_noeud	*prec;
	t_tok	*t;
	t_tok	*tmp;
	t_tok	*head;
	t_noeud	*pipe;

	t = tok_root;
	root = NULL;
	prec = NULL;
	while(t != NULL)
	{
		n = noeud_create(t, prec);
		if (root == NULL)
			root = n;
		if (prec && prec->type == PIPE)
		{
			pipe = prec;
			pipe->noeud_gauche = pipe->precedent;
			pipe->noeud_droit = n;

			if (root->type != PIPE)
				root = pipe;
			else
			{
				pipe->noeud_gauche = root;
				root = pipe;
			}
		}
		else if (!ft_strncmp(t->val, "export", ft_strlen(t->val)))
			bi_export(t, data);
		else if (prec && prec->type == EQUAL)
		{
			pipe = prec;
			pipe->noeud_gauche = pipe->precedent;
			pipe->noeud_droit = n;

			if (root->type != PIPE)
				root = pipe;
			else
			{
				pipe->noeud_gauche = root;
				root = pipe;
			}
		}
		if (prec)
			prec->suivant = n;
		prec = n;
		t = t->suivant;
		while (t && t->arg_util == 1)
			t = t->suivant;
	}
	return (root);
}

t_data *get_data(t_data *d)
{
	static t_data *data;
	if (d)
		data = d;
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_tok		*tok_root;
	t_noeud	*noeud_root;
	t_data data;
	char	*line;
	int save_in;
	int	save_out;

	g_received_signal = 0;
	line = NULL;
//	************************** DEBUT ***********************************
//	if (ac >= 2)
//		return (ft_printf("Aucun argument n'est necessaire pour lancer minishell\n"), 0);
//	************************* FIN ***********************************
	save_in = dup(0);
	save_out = dup(1);
	ft_memset(&data, 0, sizeof(t_data));
	data.env_lst = init_env(env);
	data.env = new_env(data.env_lst);
	get_data(&data);
//	************************** DEBUT ***********************************
	int	fd ;
	if (ac==2)
		 		fd = open(av[1], O_RDONLY);
//	************************* FIN ***********************************
	while(1)
	{
		ft_init_signals();

//	************************** DEBUT ***********************************
		if (ac==2){
			if(fd!=-1)
				line = get_next_line(fd);
		}

		if (ac!=2 || fd==-1)//******* FIN ****************************
			line = readline("$>");
		if (!line)
		{
			ft_sigquit_handler();
			break ;
		}
		add_history(line);
		tok_root = parse(line);
		free(line);
		noeud_root = create_AST(tok_root, &data);
		dup2(1, save_out);
		dup2(0, save_in);
		interprete(0, noeud_root, &data);
		kill_tok(tok_root);
		kill_arbre(noeud_root);

//	************************** DEBUT ***********************************
		if (ac==2)
			line = get_next_line(fd);
//	************************* FIN ***********************************
		dup2(save_out, 1);
		dup2(save_in, 0);
	}
	ft_free_lstenv(data.env_lst);
	ft_free(data.env);
	if (ac==2)
		if(fd != -1)
		 		close(fd);
}
