/*
 * Anagramarama - A word game.  Like anagrams?  You'll love anagramarama!
 * Copyright (C) 2003  Colm Gallagher
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Contact Details: colm@coralquest.com
 *  	 12 Weston Terrace, West Kilbride, KA23 9JX.  Scotland.
 */

#include <SDL.h>
#include "sdlscale.h"

static double scalew = 1;
static double scaleh = 1;

void SDLScale_MouseEvent(SDL_Event *event)
{
	event->button.x = event->button.x / scalew;
	event->button.y = event->button.y / scaleh;
}

void SDLScale_RenderCopy(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect)
{
	SDL_Rect dstreal;
	if (dstrect) {
		dstreal.x = dstrect->x * scalew;
		dstreal.y = dstrect->y * scaleh;
		dstreal.h = dstrect->h * scaleh;
		dstreal.w = dstrect->w * scalew;
		SDL_RenderCopy(renderer, texture, srcrect, &dstreal);
	}
	else
		SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

void SDLScale_Set(double w, double h)
{
	scalew = w;
	scaleh = h;
}
