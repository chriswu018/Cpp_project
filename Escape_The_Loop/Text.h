#pragma once

#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"
#include "SDL2\SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <sstream> 
#include <cmath>

class Text
{
	public:
		//Initializes variables
		Text();
		//Deallocates memory
		~Text();
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		
		bool loadFromRenderedText2( std::string textureText, SDL_Color textColor );
		//Deallocates texture
		void free();
		//Set color modulation
		SDL_Color setColor( Uint8 red, Uint8 green, Uint8 blue );
		//Renders texture at given point
		void render( int x, int y );
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};
