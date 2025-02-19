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

#define LETTER_FAST 30
#define LETTER_SLOW 10
#define GAME_LETTER_HEIGHT 90
#define GAME_LETTER_WIDTH  80
#define GAME_LETTER_SPACE 2
#define SHUFFLE_BOX_Y 107
#define BOX_START_X 80
#define ANSWER_BOX_Y 243

struct element {
	SDL_Texture *t;
	SDL_Rect w;
	int x, y;
};

struct sprite {
	struct element *spr;
	int numSpr;
	char letter;
	int x,y,w,h;
	int toX, toY;
	struct sprite* next;
	int index;
	int box;
};

void moveSprites(SDL_Renderer** screen, struct sprite** letters, int LetterSpeed);
int nextBlankPosition(int box, int *index);
void destroyLetters(struct sprite **letters);
int anySpritesMoving(struct sprite **letters);
