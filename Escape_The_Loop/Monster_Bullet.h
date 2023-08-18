#pragma once

#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"
#include "Bullet.h"

class Monster_Bullet : public Bullet
{
	public:
		Monster_Bullet();
		virtual void set_v(int, int, int = 0, float = 1);
		virtual bool check_hit(int x, int y);
		virtual void check_edge();
		virtual bool move(); 
		void set_bullet(bool, int, int, int);
		void change_v();
		
		bool track;
		bool bullet_bounce;
		int  get_damage();
	private:
		int  bullet_type;
		int  speed;
		int  damage;
};
