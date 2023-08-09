CC = gcc
OPTIONS = -Wall -Wextra -Werror

all: server main course memory

main: main.c 
	$(CC) -Wall main.c -o bin/main

server: server.c 
	$(CC) -Wall server.c -o bin/server
	
server_user: server_user.c 
	$(CC) -Wall server_user.c -o bin/server_user
	./bin/server_user


course: course.c
	$(CC) -Wall course.c -o bin/course

temp: temp.c
	$(CC) -Wall temp.c -o bin/temp

memory: main_memory.c
	$(CC) -Wall -g main_memory.c -o bin/memory

a: generate_random.c
	$(CC) -Wall -g generate_random.c -o bin/a

b: generate_regular.c
	$(CC) -Wall -g generate_regular.c -o bin/b

clear: 
	rm disk operation_queue.txt waiting_queue output.txt

clear2: 
	rm disk log.txt

# build:
# 	@$(CC) -Wall -g $(MODULE).c -o bin/$(MODULE)
# 	@./bin/$(MODULE)

