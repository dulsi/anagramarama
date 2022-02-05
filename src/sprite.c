/*
Anagramarama - A word game.  Like anagrams?  You'll love anagramarama!
Copyright (C) 2003  Colm Gallagher

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact Details: colm@coralquest.com
		 12 Weston Terrace, West Kilbride, KA23 9JX.  Scotland.
*/

#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "sprite.h"
#include "sdlscale.h"

/********************************************************************/
static void
showSprite(SDL_Renderer **screen, struct sprite **movie)
{
    SDL_Rect rect;

	rect.x = (*movie)->x;
	rect.y = (*movie)->y;
	rect.w = (*movie)->w;
	rect.h = (*movie)->h;

	// display the image in new location
	for (int i = 0; i < (*movie)->numSpr; i++) {
		rect.x = (*movie)->x + (*movie)->spr[i].x;
		rect.y = (*movie)->y + (*movie)->spr[i].y;
		rect.w = (*movie)->spr[i].w.w;
		rect.h = (*movie)->spr[i].w.h;
		SDLScale_RenderCopy(*screen, (*movie)->spr[i].t, &(*movie)->spr[i].w, &rect);
	}
}

/********************************************************************/
static int
isSpriteMoving(struct sprite *p)
{
    /* returns true if this sprite needs to move */
	return (p->y != p->toY) ||  (p->x != p->toX);
}

int
anySpritesMoving(struct sprite **letters)
{
    struct sprite *current;
    for (current = *letters; current != NULL; current = current->next) {
        if (isSpriteMoving(current))
            return 1;
    }
    return 0;
}

/********************************************************************/
static void
moveSprite(SDL_Renderer** screen, struct sprite** movie, int letterSpeed)
{
    int i;
    int x, y;
    int Xsteps;

	// move a sprite from it's curent location to the new location
	if( (  (*movie)->y != (*movie)->toY )  ||  (   (*movie)->x != (*movie)->toX )   ){

		x = (*movie)->toX - (*movie)->x;
		y = (*movie)->toY - (*movie)->y;
		if (y){
			if (x<0) x *= -1;
			if (y<0) y *= -1;
			Xsteps = (x / y) * letterSpeed;
		}
		else{
			Xsteps = letterSpeed;
		}

		for (i = 0; i<Xsteps; i++){
			if((*movie)->x < (*movie)->toX){
				(*movie)->x++;
			}
			if((*movie)->x > (*movie)->toX){
				(*movie)->x--;
			}
		}

		for (i=0;i<letterSpeed; i++){
			if((*movie)->y < (*movie)->toY){
				(*movie)->y++;
			}
			if((*movie)->y > (*movie)->toY){
				(*movie)->y--;
			}
		}
	}
}

/********************************************************************/
void
moveSprites(SDL_Renderer** screen, struct sprite** letters, int letterSpeed)
{
    struct sprite* current;

	current= *letters;
	while(current!=NULL){
		moveSprite(&(*screen), &current, letterSpeed);
		current = current->next;
	}
	current = *letters;
	while(current!=NULL){
		showSprite(&(*screen), &current);
		current=current->next;
	}
	SDL_RenderPresent(*screen);
}

/********************************************************************/
void
destroyLetters(struct sprite **letters)
{
    struct sprite *current = *letters;
	while (current != NULL) {
		struct sprite *tmp = current;
		if (current->numSpr > 0)
			free(current->spr);
		current = current->next;
		free(tmp);
	}
	*letters = NULL;
}

/*
 * Local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * End:
 */
