LIBFT = libft/libft.a
LIBFT_MAKE = make --no-print-directory -C libft #Para no printear lo que hay dentro del directorio


NAME = pipex

SRC = pipex2.c \
	  pipex_utils_2.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

RM = rm -f

INCLUDE = pipex2.h Makefile

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): libft $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

libft: 
	$(LIBFT_MAKE)

clean:
		$(RM) $(OBJ)
		$(LIBFT_MAKE) clean

fclean: clean
		$(RM) $(NAME)
		$(LIBFT_MAKE) fclean

re: fclean all

.PHONY: all clean fclean re libft

