#pragma once

#include "SDL2\SDL.h" 
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"
#include "basic.h"


class Character : public basic
{
	public:
		//consturctor
	    Character();
	    //destructor
	    ~Character();
		virtual bool loadFromFile(std::string path, int = 8, int = 2);
		//Renders texture at Character position
		virtual void render();
		//change character position and sprite by keyboard event
		void move(SDL_Event*);
		//attack
		bool attack(SDL_Event*);
		//initialize characetr position
		void set_Pos();
		//Gets image dimensions
		bool change_hp(int);		
		int get_Hp();		
	private:
	    SDL_Rect * Character_SpriteClips; 
		int		   Character_Hp;
		
};
