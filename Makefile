CC = gcc
OPTIONS = -Wall -Wextra -Werror

main: main.c 
	$(CC) -Wall main.c -o bin/main
	./bin/main

server: server.c 
	$(CC) -Wall server.c -o bin/server
	./bin/server

course: course.c
	$(CC) -Wall course.c -o bin/course
	./bin/course

temp: temp.c
	$(CC) -Wall temp.c -o bin/temp
	./bin/temp

name: name.c
	$(CC) -Wall -g name.c -o bin/name
	./bin/name

build:
	@$(CC) -Wall -g $(MODULE).c -o bin/$(MODULE)
	@./bin/$(MODULE)

