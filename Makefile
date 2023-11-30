

NAME = minishell
SRCS =   main.c token.c factory.c builtin.c execute.c execute_utils.c \
	pipe.c debug.c clean.c parse_utils.c quotes.c free.c manip_env.c \
	manip_lst.c manip_var.c utils.c expand.c signal.c heredoc.c clean_arbre.c \
	interprete.c builtin_utils.c execute_utils2.c factory2.c quotes2.c
	
OBJS = $($(addprefix src/,${SRCS}):.c=.o)
INC  = src/minishell.h /usr/include/readline/readline.h src/struct_minishell.h

LIBFT_NAME = lib/libft.a
LIBFT = src/libft
LIBFT_SRCS = src/libft/*.c 
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

CC = gcc
CFLAGS =-g # -Wall -Wextra -Werror -g #-fsanitize=thread
LFLAGS =-lreadline 

RM = rm -rf

all:
	@make -C ${LIBFT} libft.a
	
	cp src/libft/libft.a $(LIBFT_NAME)
	@make comp

$(NAME):  
	@make -C ${LIBFT} libft.a
	cp src/libft/libft.a $(LIBFT_NAME)
	@make comp

comp:
	$(CC) ${INC} $(CFLAGS) $(addprefix src/,${SRCS}) $(LIBFT_NAME) $(LFLAGS) -lpthread -o $(NAME) -g

prof:
	$(CC) ${INC} $(CFLAGS) $(addprefix src/,${SRCS}) $(LIBFT_NAME) $(LFLAGS) -lpthread -o $(NAME)_prof -g -pg
	
clean:
	@make -C ${LIBFT} clean
	rm -f $(OBJS)
	rm -f src/libft/*.gch
	

fclean: clean
	@make -C ${LIBFT} fclean
	rm -f $(NAME)
	rm -f debug

re_libft:
	@make -C ${LIBFT} re

re: fclean all

