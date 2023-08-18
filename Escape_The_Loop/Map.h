#pragma once

#include "SDL2\SDL.h" 
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"
#include "basic.h"

enum MapSprite
{
	MapSprite_waiting = 0,
	MapSprite_stage1 = 1,
	MapSprite_temple = 2,
	MapSprite_stage2 = 3,
	MapSprite_shop = 4,
	MapSprite_boss = 5,
	MapSprite_TOTAL = 6,
};

class Map : public basic 
{
	public:
		//Initializes variables
		Map();
		//Deallocates memory
		~Map();
		//Loads image at specified path
		virtual bool loadFromFile( std::string path );
		virtual void render();
		//detect collison
		bool collison_check( float & x, float & y);
		
		void operator~ ();
};
