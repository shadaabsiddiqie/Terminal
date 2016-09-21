main:shell.c shell_fun.c
	gcc -o main shell.c shell_fun.c -I.
#
# shell_fun.o:shell_fun.c shell_fun.h
# 	gcc shell_fun.c -c -o shell_fun.o
