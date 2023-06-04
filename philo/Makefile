RED = \033[0;31m
NOCOLOR = \033[0m
GREEN = \033[0;32m
RED = \033[1;31m

PATH_SRC =			./srcs/
PATH_OBJS =			./objs/

NAME = philo

FILES = $(PATH_SRC)main.c $(PATH_SRC)not_libft.c $(PATH_SRC)threads_control.c $(PATH_SRC)philo_behavior.c $(PATH_SRC)utils.c $(PATH_SRC)init_and_error.c
OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(FILES))

CC = clang
CFLAGS = -Wall -Wextra -pthread #-fsanitize=thread -g3 -O1
RM = rm -rf

all: logo $(NAME)

logo :
			@tput setaf 2; cat ascii_art/42philo; tput setaf default

$(NAME): $(OBJS)
	@echo "Assembling $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${GREEN}✓${NOCOLOR}"
	@echo "$(GREEN)Compilation is done$(NOCOLOR)"

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@echo "Compiling $^: "
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "${GREEN}✓${NOCOLOR}"

clean:
	@echo "${RED}Cleaning objects in $(NAME) : ${NOCOLOR}"
	@$(RM) $(PATH_OBJS)
	@echo "${GREEN}✓${NOCOLOR}"

fclean: clean
	@echo "${RED}Cleaning all in $(NAME) : ${NOCOLOR}"
	@$(RM) $(NAME)
	@echo "${GREEN}✓${NOCOLOR}"

re: fclean all

norme: 
	norminette $(PATH_SRC) ./includes

.PHONY: re all fclean clean norme