# Better minilibx (modified version 2022)

This minilibx version use Cocoa (AppKit) and OpenGL without X11. It is a fast writing library which try to reproduce partial X11 usage.

I decide to customize minilibx to improve support of functionnality like event supported.

Changes:
  - Add function to hide/unhide cursor.
  - Add funnction to change the cursor icon.
  - Better mousewheel event with speed (deltaX and deltaY).
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

### mlx_hook

Remove unused/deprecated `x_mask` argument in mlx_hook. New prototype:

```c
int	mlx_hook(void *win_ptr, int x_event, int (*funct)(), void *param);
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

## Added API

### mlx_toggle_cursor(int display)

Hide or display the cursor.

### void mlx_set_cursor(int cursor)

Change the actual cursor icon, according to [appkit documentation](https://developer.apple.com/documentation/appkit/nscursor?language=objc).

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
```

