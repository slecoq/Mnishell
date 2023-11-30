
clear;rm *.gch 2> /dev/null
#cd src
rm minishell minishell_prof 2> /dev/null
make -s
# \
#&&  ./philo 2 4000 1000 2000 5

 #&&valgrind --leak-check=full --show-leak-kinds=all 