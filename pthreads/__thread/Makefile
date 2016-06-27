CC = cc
CFLAGS = -lpthread -fsanitize=thread -fPIE -pie -g

.PHONY: clean
clean:
	find ./ -type f -executable | xargs -v rm
