#pragma once

#include "SDL2\SDL.h" 
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"

class basic{
	public:
		virtual bool loadFromFile( std::string path,Uint8 = 0x00, Uint8 = 0x00, Uint8 = 0xFF );
		virtual void render(SDL_Rect * = NULL);
		void free();
		int  getWidth();
		int  getHeight();
		int  getPos_x();
		int  getPos_y();

	protected:
		SDL_Texture * Texture;
		int   Width;
		int   Height;
		float Pos_x;
		float Pos_y;
		float Vel_x;
		float Vel_y;
};
