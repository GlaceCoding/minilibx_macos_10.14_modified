//
// mlx_int_shared.h for minilibx and app using minilibx
//
// splitted by gphilipp

#ifndef MLX_DEF_H
# define MLX_DEF_H

# define FONT_WIDTH		10
# define FONT_HEIGHT	20

// (FONT_WIDTH + 2) * 95
# define IMG_FONT_SIZE	1140

typedef unsigned int			GLuint;
typedef float					GLfloat;

typedef struct mlx_img_list_s	mlx_img_list_t;
typedef struct mlx_img_ctx_s	mlx_img_ctx_t;
typedef struct mlx_win_list_s	mlx_win_list_t;

struct mlx_img_list_s
{
	int					width;
	int					height;
	unsigned char		*buffer;
	GLfloat				vertexes[8];
	mlx_img_list_t		*next;
};

struct mlx_img_ctx_s
{
	GLuint				texture;
	GLuint				vbuffer;
	mlx_img_list_t		*img;
	mlx_img_ctx_t		*next;
};

struct mlx_win_list_s
{
	void				*winid;
	mlx_img_ctx_t		*img_list;
	int					nb_flush;
	int					pixmgt;
	mlx_win_list_t		*next;
};

typedef struct mlx_ptr_s
{
	void				*appid;
	mlx_win_list_t		*win_list;
	mlx_img_list_t		*img_list;
	void				(*loop_hook)(void *);
	void				*loop_hook_data;
	void				*loop_timer;
	mlx_img_list_t		*font;
	int					main_loop_active;
}				mlx_ptr_t;

#endif
