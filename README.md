# minilibx modified

This minilibx version use Cocoa (AppKit) and OpenGL without X11. It is a fast writing library which try to reproduce partial X11 usage.

I decide to customize minilibx to improve support of functionnality like event supported.

Changes:
  - News&fix events (because the minilibx macOS update without X11 is partial copy of X11 api).
  - mlx_hook prototype: remove deprecated `x_mask` argument.
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

## mlx_hook

Remove unused/deprecated `x_mask` argument in mlx_hook. New prototype:

```c
int	mlx_hook(void *win_ptr, int x_event, int (*funct)(), void *param);
```

## x_event

See [mlx_event.h](./mlx_event.h):

```
/*
** ON_EVENT
*/
enum {
	ON_KEYDOWN,
	ON_KEYUP,
	ON_MOUSEDOWN,
	ON_MOUSEUP,
	ON_MOUSEMOVE,
	ON_FOCUSCHANGE,
	ON_VISIBILITYCHANGE,
	ON_DESTROY
};
```
