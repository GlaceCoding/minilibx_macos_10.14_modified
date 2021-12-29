/*
** mlx.h for MinilibX in 
** 
** Made by Charlie Root
** Login   <ol@staff.42.fr>
** 
** Started on  Mon Jul 31 16:37:50 2000 Charlie Root
** Last update Tue Oct 01 16:23:28 2014 Olivier Crouzet
*/

/*
**   MinilibX -  Please report bugs
*/

/*
** FR msg - FR msg - FR msg
**
** MacOSX
** La MinilibX utilise 2 frameworks Mac : OpenGL et AppKit
**    qu'il faut ajouter a la compilation :
**   -framework OpenGL -framework AppKit
**
** UNIX / Linux
** La MinilibX utilise 2 librairies supplementaires qu'il
**      est necessaire de rajouter a la compilation :
**   -lmlx -lXext -lX11
**
** La MinilibX permet le chargement des images de type Xpm.
** Notez que cette implementation est incomplete.
**
** Il y a des differences entre X11 et MacOS.
** les numeros des touches ne sont pas les memes,
** les numeros des boutons souris ne sont pas les memes.
** Egalement l'expose est gere differemment, et sous MacOS
** il est preferable d'entrer le plus tot possible dans mlx_loop,
** il est normal que les fenetres n'apparaissent pas avant mlx_loop
** (ou bien forcez avec mlx_do_sync mais c'est pas genial).
** Sous MacOS, l'octet Alpha est pris en compte dans toutes les
** images, et represente la transparence et non l'opacite comme
** c'est normalement le cas.
*/

#ifndef MLX_H
# define MLX_H

# include "mlx_def.h"
# include "mlx_event.h"

mlx_ptr_t		*mlx_init(void);
/*
**  needed before everything else.
**  return (void *)0 if failed
*/

/*
** Basic actions
*/

mlx_win_list_t	*mlx_new_window(mlx_ptr_t *mlx_ptr, int width, int height,
					char *title);
/*
**  return void *0 if failed
*/
int				mlx_clear_window(mlx_win_list_t *win_ptr);
int				mlx_pixel_put(mlx_win_list_t *win_ptr, int x, int y, int color);
/*
**  origin for x & y is top left corner of the window
**  y down is positive
**  color is 0x00RRGGBB
*/

/*
** Image stuff
*/

mlx_img_list_t	*mlx_new_image(mlx_ptr_t *mlx_ptr, int width, int height);
/*
**  return void *0 if failed
*/
unsigned char	*mlx_get_data_addr(mlx_img_list_t *img_ptr, int *bits_per_pixel,
					int *size_line, int *endian);

/*
**  endian : 0 = sever X is little endian, 1 = big endian
**  endian : useless on macos, client and graphical framework have the same
**           endian
*/

int				mlx_put_image_to_window(mlx_win_list_t *win_ptr,
					mlx_img_list_t *img_ptr, int x, int y);
unsigned int	mlx_get_color_value(mlx_ptr_t *mlx_ptr, int color);

/*
** dealing with Events
**
** mouse events :
**		int hook(int button, t_xpoint point, void *param)
** mouse wheels :
**		int hook(t_xwheel wheel, t_xpoint point, void *param)
** key events :
** 		int hook(int keycode, void *param)
** expose event :
**		int (*funct_ptr)(void *param)
*/

int				mlx_hook(mlx_win_list_t *win_ptr, int x_event, int (*funct)(),
					void *param);
int				mlx_loop_hook(mlx_ptr_t *mlx_ptr, int fps,
					int (*funct_ptr)(), void *param);
				// 	int (*funct_ptr)(void *param)
int				mlx_loop(mlx_ptr_t *mlx_ptr);

/*
**  generic hook system for all events, and minilibX functions that
**    can be hooked. Some macro and defines from X11/X.h are needed here.
*/

int				mlx_hook(mlx_win_list_t *win_ptr, int x_event, int (*funct)(),
					void *param);

int				mlx_do_key_autorepeatoff(mlx_ptr_t *mlx_ptr);
int				mlx_do_key_autorepeaton(mlx_ptr_t *mlx_ptr);
int				mlx_do_sync(mlx_ptr_t *mlx_ptr);

/*
** Custom:
*/

void			mlx_set_cursor(int cursor);
void			mlx_toggle_cursor(int display);

/*
**  Utils…
*/

int				mlx_string_put(mlx_ptr_t *mlx_ptr, mlx_win_list_t *win_ptr,
					int x, int y, int color, char *string);
mlx_img_list_t	*mlx_xpm_to_image(mlx_ptr_t *mlx_ptr, char **xpm_data,
					int *width, int *height);
mlx_img_list_t	*mlx_xpm_file_to_image(mlx_ptr_t *mlx_ptr, char *filename,
					int *width, int *height);
int				mlx_destroy_window(mlx_ptr_t *mlx_ptr, mlx_win_list_t *win_ptr);
int				mlx_destroy_image(mlx_ptr_t *mlx_ptr, mlx_img_list_t *img_ptr);

#endif /* MLX_H */
