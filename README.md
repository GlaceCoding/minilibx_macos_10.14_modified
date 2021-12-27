# Better minilibx (modified version 2022)

The based version of this minilibx use Cocoa (AppKit) and OpenGL without X11. It was a fast writing library which try to reproduce partial X11 usage. Too partial for me, that why I decided to add some part for my project.

I have decided to customize minilibx to improve support of functionnalities and system events.

Changes:
  - Added `mlx_toggle_cursor` function to hide/unhide cursor.
  - Added `mlx_set_cursor` function to change the cursor icon.
  - Better mousewheel listener with speed (deltaX and deltaY), we only had the direction without the speed before my change.
  - News&fix events (because the minilibx macOS update without X11 was a partial copy of X11 api).
  - Shared define of mlx structures to use them directly (and replace `void` by the proper type). `mlx_get_data_addr` is deprecated.
  - mlx_hook prototype: remove deprecated `x_mask` argument.
  - Remove useless argument `mlx_ptr` for mlx_put_image_to_window, mlx_clear_window and mlx_pixel_put
  - Better Makefile & no relinks.

## Installation

### Add & Include file

Include `./mlx.h`.

### Configure your MAKEFILE

```make
all: libs $(NAME)

# [...]

MINILIBX = vendor/minilibx/

libs: $(MINILIBX)libmlx.a

$(MINILIBX)libmlx.a:
    make -C $(MINILIBX)

libs_clean:
    make -C $(MINILIBX) clean

libs_fclean: libs_clean
    make -C $(MINILIBX) fclean

# [...]

fclean: libs_fclean clean
    rm -f $(NAME)
```

Add this flag: `-L$(MINILIBX) -lmlx -framework OpenGL -framework AppKit` to compile your application.

Add `libs libs_clean libs_fclean` to `.PHONY`rule.

## Modified API

### mlx_hook

Remove unused/deprecated `x_mask` argument in mlx_hook. New prototype:

```c
int    mlx_hook(void *win_ptr, int x_event, int (*funct)(), void *param);
```

### x_event

New event system/code. See [mlx_event.h](./mlx_event.h):

```c
/*
** ON_EVENT
*/
enum {
    ON_KEYDOWN,
    ON_KEYUP,
    ON_MOUSEDOWN,
    ON_MOUSEUP,
    ON_MOUSEMOVE,
    ON_MOUSEWHEEL,
    ON_FOCUSCHANGE,
    ON_VISIBILITYCHANGE,
    ON_DESTROY
};
```

### mlx_put_image_to_window, mlx_clear_window and mlx_pixel_put

Remove useless `mlx_ptr` argument.

```c
int    mlx_put_image_to_window(mlx_win_list_t *win_ptr, mlx_img_list_t *img_ptr, int x, int y);
int    mlx_clear_window(mlx_win_list_t *win_ptr);
int    mlx_pixel_put(mlx_win_list_t *win_ptr, int x, int y, int color);
```

## Added API

### mlx_toggle_cursor(int display)

Hide or display the cursor.

```c
void    mlx_toggle_cursor(int display);
```

### void mlx_set_cursor(int cursor)

Change the actual cursor icon, according to [appkit documentation](https://developer.apple.com/documentation/appkit/nscursor?language=objc).

```c
void    mlx_set_cursor(int cursor);
```

NOTE: All app on your mac use the same API to change cursor, if your app loses the focus, you have to recall this function (to be sure to have the good cursor).

```c
/*
** CURSOR ICON
*/ 
enum {
    ARROW_CURSOR,
    IBEAM_CURSOR,
    CROSSHAIR_CURSOR,
    CLOSEDHAND_CURSOR,
    OPENHAND_CURSOR,
    POINTINGHAND_CURSOR,
    RESIZELEFT_CURSOR,
    RESIZERIGHT_CURSOR,
    RESIZELEFTRIGHT_CURSOR,
    RESIZEUP_CURSOR,
    RESIZEDOWN_CURSOR,
    RESIZEUPDOWN_CURSOR,
    DISAPPEARINGITEM_CURSOR,
    IBEAM_CURSOR_FORVERTICALLAYOUT,
    OPERATIONNOTALLOWED_CURSOR,
    DRAGLINK_CURSOR,
    DRAGCOPY_CURSOR,
    CONTEXTUALMENU_CURSOR
};

int onmousemove(t_xpoint point, void *vars)
{
    mlx_set_cursor(OPENHAND_CURSOR);
    (void) point;
    (void) vars;
    return (0);
}
```

### Why this minilibx version ?

#### More event

```c
// MINILIBX WHEEL EVENT / SCROLL EVENT
int onmousewheel(t_xwheel wheel, t_xpoint point, void *vars)
{
    printf("wheel:%f %f pos: %d %d \n", wheel.dx, wheel.dy, point.x, point.y);
    (void) vars;
    return (0);
}
// wheel:-0.917145 0.000000 pos: 319 449
// wheel:-3.855789 0.000000 pos: 321 449
// wheel:-5.527893 0.000000 pos: 325 450

int onfocuschange(int visible, t_app *app)
{
    printf("focus change: %d\n", visible);
    low_mode(app);
    return (0);
}

int onvisiblitychange(int visible, t_app *app)
{
    printf("visiblity change: %d\n", visible);
    low_mode(app);
    return (0);
}

int close(t_app *app)
{
    (void) app;
    exit(0);
    return (0);
}

mlx_hook(app.win, ON_MOUSEWHEEL, onmousewheel, &app);
mlx_hook(app.win, ON_FOCUSCHANGE, onfocuschange, &app);
mlx_hook(app.win, ON_VISIBILITYCHANGE, onvisiblitychange, &app);
mlx_hook(app.win, ON_DESTROY, close, &app);
```

#### Improve your app FPS, and draw string on mlx_img instead mlx_win

With this version, we can access to `app->mlx` properties and make an advanced usage of the minilibx.

```c
void    draw_char(t_img *img, t_point pos, char letter)
{
    t_app       *app;
    int         i;
    int         j;
    int         k;

    app = get_app();
    i = 0;
    while (i < FONT_WIDTH * FONT_HEIGHT)
    {
        j = (i % FONT_WIDTH) + (i / FONT_WIDTH) * WIDTH
            + (WIDTH * pos.y) + pos.x;
        k = (i % FONT_WIDTH) + (i / FONT_WIDTH) * IMG_FONT_SIZE
            + (FONT_WIDTH + 2) * (letter - 32);
        pixel_add_color(&img->buffer[4 * j], &app->mlx->font->buffer[4 * k]);
        i++;
    }
}

draw_char(img, (t_point){4, 2}, 'A');
```

#### Easy-use: Use mlx_img without custom middle-structure

We can directly use the `mlx_img_list_t` to get easiest api than before without declaring another structure.

##### BEFORE

```c
typedef struct s_dimg {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_dimg;

void    draw_stats(t_app *app)
{
    t_img   *img;
    dimg.img = mlx_new_image(app->mlx, STATS_W, STATS_H);
    dimg.addr = mlx_get_data_addr(dimg.img, &dimg.bits_per_pixel,
            &dimg.line_length, &dimg.endian);
    draw_stats_bg(&dimg);
    mlx_put_image_to_window(app->mlx, app->win, img.img, 0, 0);
}
```

##### AFTER

```c
typedef mlx_img_list_t  t_img;

void    draw_stats(t_app *app)
{
    t_img   *img;
    img = mlx_new_image(app->mlx, STATS_W, STATS_H);
    draw_stats_bg(img);
    mlx_put_image_to_window(app->win, img, 0, 0);
}
```

##### BEFORE

```c
typedef struct s_dimg {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_dimg;

static void draw(t_dimg *img)
{
    int             *dpixel;
    int             x;
    int             i;

    i = 0;
    while (i < STATS_H * img->line_length)
    {
        dpixel = img->addr + i;
        x = i % img->line_length / (img.bits_per_pixel / 8);
        if (x < 10)
        {
            dpixel = ((int *)img->addr) + i;
            *dpixel = GRAPH_BG;
        }
        i += (img.bits_per_pixel / 8);
    }
}
```

##### AFTER

```c
typedef mlx_img_list_t  t_img;

static void draw(t_img *img)
{
    int             *dpixel;
    int             x;
    int             i;

    i = 0;
    while (i < img->width * img->height)
    {
        x = i % img->width;
        if (x < 10)
        {
            dpixel = ((int *)img->buffer) + i;
            *dpixel = GRAPH_BG;
        }
        i++;
    }
}
```
