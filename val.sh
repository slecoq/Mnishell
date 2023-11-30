
clear;rm *.gch 2> /dev/null
#cd src
rm minishell minishell_prof 2> /dev/null
make \
 &&valgrind --leak-check=full --show-leak-kinds=all ./minishell cdes.txt
 	