#pragma once
#include "SDL2/SDL.h"
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"
#include "basic.h"
#include "Monster_Bullet.h"

enum MonsterSprite
{
	MonsterSprite_right = 0,
	MonsterSprite_left = 1,
};

class Monster: public basic{
	public:
		//constructor
	    Monster(int, int, int);
	    Monster();
	    //destructor
	    ~Monster();
		//change character position and sprite
		void move();
		//load from file
		bool loadFromFileSmall(std::string path);

  		bool loadFromFileBig(std::string path);

		bool edge_check( float & pos_x, float & pos_y );

		void change_hp(int);

		void set_Monster(const int &, const int &, const int &,const int &, const int &);

		void set_Pos(float pos_x, float pos_y, bool lr);

		bool alive;

        void operator++(int );
	private:

	    SDL_Rect *	Monster_SpriteClips;
		int         Monster_type;
		int 		Monster_Hp;
        MonsterSprite movestate;
        bool attack_1;
        bool attack_2;
};
