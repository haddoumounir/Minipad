
NAME = minipad
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`
SRC = src/main.c src/editor.c src/file_io.c
OBJDIR = obj
OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)
RM = rm -f


all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)


clean:
	$(RM) $(OBJ)


fclean: clean
	$(RM) $(NAME)


re: fclean all


.PHONY: all clean fclean re

# Pattern rule to build object files in obj/ from src/
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
