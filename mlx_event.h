/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:06:24 by gphilipp          #+#    #+#             */
/*   Updated: 2021/12/27 01:56:25 by gphilipp         ###   ########.fr       */
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
	ON_VISIBILITYCHANGE,
	ON_DESTROY
};

typedef struct s_xpoint {
	float		x;
	float		y;
}			t_xpoint;

#endif
