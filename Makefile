#
#

SRC			= mlx_shaders.c \
			  mlx_new_window.m \
			  mlx_init_loop.m \
			  mlx_new_image.m \
			  mlx_xpm.c \
		  	  mlx_int_str_to_wordtab.c

SRCS  		= $(SRC:.c=.o)

OBJS  		= $(SRCS:.m=.o)

NAME		= libmlx.a

CFLAGS		= -O2 -Wno-deprecated

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
