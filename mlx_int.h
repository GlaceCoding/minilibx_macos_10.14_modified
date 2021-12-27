//
// mlx_int.h for minilibx
//
// ol@staff.42.fr
//
// include opengl needed before mlx_int.h
//

#include "mlx_def.h"
#include "mlx_event.h"

#define	MAX_EVENT	32
#define MAX_PIXEL_NB	200000
#define UNIQ_BPP	4


typedef int (*func_t)();

/* structs */

typedef struct	glsl_info_s
{
  GLuint	pixel_vshader;
  GLuint	pixel_fshader;
  GLuint	pixel_program;
  GLint		loc_pixel_position;
  GLint		loc_pixel_texture;
  GLint		loc_pixel_winhalfsize;

  GLuint	image_vshader;
  GLuint	image_fshader;
  GLuint	image_program;
  GLint		loc_image_position;
  GLint		loc_image_winhalfsize;
  GLint		loc_image_texture;
  GLint		loc_image_pos;
  GLint		loc_image_size;

  GLuint	font_vshader;
  GLuint	font_fshader;
  GLuint	font_program;
  GLint		loc_font_position;
  GLint		loc_font_winhalfsize;
  GLint		loc_font_texture;
  GLint		loc_font_color;
  GLint		loc_font_posinwin;
  GLint		loc_font_posinatlas;
  GLint		loc_font_atlassize;
} glsl_info_t;


// proto

int	mlx_shaders(glsl_info_t *glsl);
char    **mlx_int_str_to_wordtab(char *str);
int     mlx_int_str_str(char *str,char *find,int len);
int     mlx_int_str_str_cote(char *str,char *find,int len);
int	mlx_destroy_image(mlx_ptr_t *mlx_ptr, mlx_img_list_t *img_ptr);
mlx_img_list_t	*mlx_new_image();
mlx_img_list_t    *mlx_xpm_to_image(mlx_ptr_t *xvar,char **xpm_data,int *width,int *height);
int	mlx_do_sync(mlx_ptr_t *mlx_ptr);
