clear
while IFS= read -r line
do 
	echo "=== $line ==="
	./minishell $line	
	echo "========================================"
done <<< $(cat cdes.txt)
