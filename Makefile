NAME = so_long

SRC =	map_verif.c \
		map_verif2.c \
		map_verif3.c \
		map_verif4.c \
		map_verif5.c \
		map_verif6.c \
		so_long.c \
		so_long2.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra

LIB  = ar rcs $(NAME) ./includes/lib/mlx/libmlx.a ./includes/lib/libft.a

REMOVE = rm -f

DEPENDS = make -C includes/lib/libft

MLX = make -C includes/lib/mlx

COMPILE = gcc $(CFLAGS) -o $(NAME) -Iincludes/lib -Iincludes/lib/mlx -Lincludes/lib/mlx -Lincludes/lib/Libft -lft -lmlx -framework OpenGL -framework Appkit -D BUFFER_SIZE=1

all: $(NAME)

libft : 
	$(DEPENDS)
	$(MLX)

$(NAME): libft $(OBJ)
	@$(COMPILE) $(OBJ)

clean:
	$(REMOVE) $(OBJ) 
	make -C includes/lib/Libft clean
	make -C includes/lib/mlx clean

fclean:	clean
	$(REMOVE) $(NAME)
	make -C includes/lib/Libft fclean

re: fclean all

.PHONY: all clean fclean re