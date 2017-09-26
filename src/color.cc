/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:39:05 by rfulop            #+#    #+#             */
/*   Updated: 2017/09/26 22:39:06 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

const SDL_Color Color::get_color(int color)
{
  switch (color)
  {
    case GRID_COLOR:
      return grey;
    case PLAYER_X_COLOR:
      return red;
    case PLAYER_O_COLOR:
      return blue;
    case TIE_COLOR:
      return grey;
    default:
      return black;
  }
}
