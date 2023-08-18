#pragma once

#include "SDL2\SDL.h" 
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"
#include "basic.h"

class Bullet : public basic
{
	//friend Character;
	public:
		//Initializes variables
		Bullet();
		//Deallocates memory
		~Bullet();
		//Loads image at specified path
		virtual void set_v(int,  int );
		virtual bool move();
		virtual void check_edge();	
		virtual bool check_hit(int , int);
		void buff(int, int);
};
