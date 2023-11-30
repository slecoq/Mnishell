
#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>

typedef enum e_tok_type
{
	INCONNU,
	TOK_EQUAL,
	TOK_PIPE,
	TOK_LIT,
	TOK_GRAND,
	TOK_PETIT,
	TOK_DOUBLE_GRAND,
	TOK_DOUBLE_PETIT
}	t_tok_type;

typedef struct s_mismatch_res
{
	char	quote_manquante;
	int		b_no_mismatch;
}	t_mismatch;

typedef struct s_quotes_temp
{
	char		*p_quote_deb;
	char		*p_quote_fin;
	char		*p_dquote_deb;
	char		*p_dquote_fin;
	t_mismatch	*mismatch_res;
	int						b_quote_err_micmac;
}	t_quotes_tmp;

typedef struct s_quotes_res
{
	char	*quote_deb;
	char	*quote_fin;
	int		b_in_single_quotes;
	int		b_quote_err_micmac;
}	t_quotes_res;

typedef struct s_got_q_param
{
	char	**p_quote_deb;
	char	**p_quote_fin;
	char	c;
}	t_got_q_param;

typedef struct s_grab_res
{
	char	*val;
	int		b_quote_err_micmac;
	int		b_expanse_allowed;
}	t_grab_res;

typedef struct s_parse_res
{
	char	*fin_pre;
	char	*s_captured;
	char	*deb_post;
	char	*s_rempl;
	char	*s_pre;
}	t_parse_res;

typedef struct s_tok
{
	t_tok_type				type;
	char					*val;
	int						b_expanse_allowed;
	int						arg_util;
	struct s_tok			*precedent;
	struct s_tok			*suivant;
	struct s_mismatch_res	*mismatch_res;
	int											b_quote_err_micmac;
}	t_tok;

typedef enum e_node_type
{
	NODE_TYPE_INCONNU,
	PIPE,
	LITTERAL,
	REDIRECTION,
	HEREDOC,
	EQUAL
}	t_node_type;

typedef struct s_pipe
{
	int		fds[2];
	pid_t	pid_gauche;
	pid_t	pid_droit;
	int		res_gauche;
	int		res_droit;
}	t_pipe;

typedef struct s_arg
{
	char	*val;
	int		b_val_a_free;
	int		b_expanse_allowed;
}	t_arg;

typedef struct s_noeud
{
	t_tok			*tok;
	t_node_type		type;
	char			*str_valeur;
	struct s_noeud	*noeud_gauche;
	struct s_noeud	*noeud_droit;
	t_arg			**args;
	struct s_noeud	*precedent;
	struct s_noeud	*suivant;
	int				fd_output;
	int				fd_input;
	char			*delim_heredoc;
	int				b_expanse_allowed;
	int				b_quote_micmac;
}	t_noeud;

typedef struct s_heredoc_data
{
	int		fd_pipe[2];
	int		pid;
	int		status;
	char	*line;
	char	*acc;
	char	*tmp;
}	t_heredoc_data;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				b_global;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char			**env;
	struct s_env	*env_lst;
	int				status;
}	t_data;

#endif
