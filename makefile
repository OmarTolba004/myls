make: func.c myls.c 
	@gcc -g func.c myls.c -o myls
	
clean : 
	@rm -f myls
