NAME = minishell

FILES = main.c \
		built_in.c \
		prepare_buf.c \
		tools.c \
		error.c \
		cmd_cd.c \
		cmd_echo.c \
		list_actions.c \
		prepare_buf.c \
		cmd_cd2.c \
		list_actions2.c \
		cmd_cd3.c

OFILES = main.o \
		built_in.o \
		prepare_buf.o \
		tools.o \
		error.o \
		cmd_cd.o \
		cmd_echo.o \
		list_actions.o \
		prepare_buf.o \
		cmd_cd2.o \
		list_actions2.o \
		cmd_cd3.o


FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES)
		@make -C libft
		@gcc $(FLAG) -c $(FILES) 
		ar rc minishell.a $(OFILES)
		@gcc $(FLAG) main.c minishell.a \
	   	libft/libft.a -o $(NAME)


clean:
		@make fclean -C libft
		rm -f $(OFILES)

fclean: clean
		@rm -f $(NAME)

re:	fclean all