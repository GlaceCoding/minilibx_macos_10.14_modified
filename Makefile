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

$(NAME): $(OBJS)
	ar -r $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: all clean fclean
