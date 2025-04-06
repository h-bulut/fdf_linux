NAME			= fdf
CC				= cc 
RM				= rm -rf
FLAGS			= -Wall -Wextra -Werror
MLX_FLAGS		= -Lminilibx -lmlx -framework OpenGL -framework AppKit
SRCS			= utils_account.c utils_bresenham.c utils_check_arg.c utils_color.c utils_free.c utils_init.c utils_isometric_pro.c \
					utils_read_map.c utils_tools.c main.c

OBJ 			= $(SRCS:.c=.o)

all				: $(NAME)

$(NAME) 		: $(OBJ)
		$(MAKE) -C ./libft all
		$(MAKE) -C ./minilibx all
		$(CC) $(FLAGS) ./get_next_line/*.c minilibx/libmlx.a $(OBJ) ./libft/libft.a $(MLX_FLAGS) -o $(NAME)

clean			:
		$(MAKE) -C ./libft clean
		$(MAKE) -C ./minilibx clean
		$(RM) $(OBJ)

fclean 			: 
		$(MAKE) -C ./libft fclean	
		$(MAKE) -C ./minilibx clean
		$(RM) $(OBJ)
		$(RM) $(NAME)

re 				: fclean all

.PHONY		: make all clean fclean re