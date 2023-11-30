
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <pthread.h>
# include <errno.h>
# include <termios.h>

# include "libft/libft.h"
#include "struct_minishell.h"

char			*find_next_sep(char **s);
t_grab_res		*grab(char **s);
t_quotes_res	*quotes(char **s);
int				escape(char	*s, char	*c);
t_tok			*create_tok(char **val, t_tok *tok_last);
t_parse_res		*parse_res_create(void);
t_quotes_tmp	*quote_tmp_create(void);
t_quotes_res	*quotes_res_create(void);
t_tok			*tok_create(char *val, t_tok_type type);
t_noeud			*noeud_create(t_tok *t, t_noeud *rec);
t_grab_res		*grab_res_create(void);
t_arg			*arg_create(t_tok	*t);
t_pipe			*t_pipe_create(void);
t_mismatch		*mismatch_res_create(void);

void			dbg_tab(char **t);

int				interprete(int piped, t_noeud *n, t_data *data);
char			**_tabbed_args_val(t_arg **args);
void			_dup_close_ios(t_noeud *n);
char			*find_exe(char *env_path, char *fname);
void			_interprete_equal(int b_global, t_noeud *n,
					t_env *new_entry, t_data *data);
int				run_exe(int piped, char *path, char *args[], t_data *data);
t_arg			**donne_moi_des_arguments(t_tok	*ct, t_noeud *n);
void			donne_moi_des_io(t_noeud *n, t_tok	*ct);
void			pipe_show(int piped, t_pipe	*pipe_ret, t_noeud	*n,
					t_data *data);
void			my_heredoc(t_noeud	*n);
void			my_error(char *s);
void			expand(t_noeud *n, t_env *env_lst, int last_exec_status);
char			*_find_in_pathes(char *env_path, char *fname);
int				_clean_vars(int i, char **env_path_expl);
int				_check_micmac(t_quotes_tmp *qr);

int				bi_cd(t_noeud *n, t_env *env_lst);
int				bi_pwd(void);
int				bi_export(t_tok *n, t_data *data);
int				bi_env(t_noeud *n, t_data *data);
int				bi_unset(t_noeud *n, t_data *data);
int				case_exit(t_noeud *n, t_data *data, char *str);

void			dbg_tree(t_noeud *root, char *pre);
void			debug_rebuild_cmdline(t_noeud *root);
void			dbg_tok(t_tok	*tok_root);
void			dbg_flat_arbre(t_noeud	*root);

void			kill_tok(t_tok *root);
void			kill_arbre(t_noeud *root);
void			kill_args(t_arg **args);
void			sortir_propre(t_noeud	*noeud_root, int exit_code);

void			ft_free(char **str);
void			ft_free_lstenv(t_env *lst);
void			ft_free_cell(t_env *lst);

t_env			*add_var_env(t_env *env_lst, t_env *var);
t_env			*remove_var_env(t_env *env_lst, t_env *var);

char			*get_var_env(t_env *env_lst, char *name);

t_env			*ft_lstlast(t_env *lst);
void			ft_lstadd_back(t_env **lst, t_env *new);
t_env			*lstnew_env(char *name, char *value, int b_global);
void			print_env_lst(t_env *env_lst);

char			*get_value(char *str);
char			*get_name(char *str);

int				ft_array_len(char **array);
char			*swap_value(char *old, char *new);

t_env			*init_env(char **env);
char			**new_env(t_env *env_lst);
char			*apply_string_env(const char *str1, const char *str2);
int				lst_size(t_env *env_lst);

void			ft_signal_handler(int num);
void			ft_sigquit_handler(void);
void			ft_init_signals(void);

void			_gestion_assignation_export(t_tok *t, t_data *data);
void			_gestion_export_var(t_tok *t, t_data *data);

# ifndef DEBUG_EXP
#  define DEBUG_EXP 0
# endif

# ifndef DEBUG_AST
#  define DEBUG_AST 0
# endif

# ifndef DEBUG_PARSE
#  define DEBUG_PARSE 0
# endif

# ifndef DEBUG_EXEC
#  define DEBUG_EXEC 0
# endif

# ifndef FL_MICMAC_CHECK
#  define FL_MICMAC_CHECK 1
# endif

# ifndef DEBUG_CLEAN
#  define DEBUG_CLEAN 0
# endif
# ifndef TOK_SEPS
#  define TOK_SEPS "|> <\n=\'\""
# endif

#endif
