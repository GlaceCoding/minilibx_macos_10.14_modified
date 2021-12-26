/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:06:24 by gphilipp          #+#    #+#             */
/*   Updated: 2021/12/27 00:08:02 by gphilipp         ###   ########.fr       */
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
	ON_DESTROY
};

#endif