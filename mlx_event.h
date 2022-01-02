/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:06:24 by gphilipp          #+#    #+#             */
/*   Updated: 2022/01/02 15:57:35 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EVENT_H
# define MLX_EVENT_H

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
	ON_KEYFOCUSCHANGE,
	ON_VISIBILITYCHANGE,
	ON_DESTROY
};

typedef struct s_xpoint {
	int			x;
	int			y;
}			t_xpoint;

typedef struct s_xwheel {
	float		dx;
	float		dy;
}			t_xwheel;

// https://developer.apple.com/documentation/appkit/nscursor?language=objc
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

#endif
