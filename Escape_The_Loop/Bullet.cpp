#include "Bullet.h"
#include "Character.h"
#include "Map.h"
#include <cmath>

extern int stage_number;
extern SDL_Renderer* gRenderer;
extern Character gCharacter;
extern int bSpeed;

Bullet::Bullet(){

	Pos_x = 0;
	Pos_y = 800;
	Vel_x = 0;
	Vel_y = 0;
}

Bullet::~Bullet(){
	free();
}

void Bullet::set_v( int des_x, int des_y){
	
	static double dis,dx,dy;
	
	Pos_x = gCharacter.getPos_x() + 30;
	Pos_y = gCharacter.getPos_y() + 40;
	
	dx = (des_x - Width/2  - Pos_x);
	dy = (des_y - Height/2 - Pos_y);
	dis = sqrt(dx*dx+dy*dy);
	//std::cout<<"dis = "<<dis<<std::endl;
	Vel_x = dx / dis;
	Vel_y = dy / dis;
	//std::cout<<"set_v"<<v_x<<' '<<v_y<<std::endl;
}

bool Bullet::move()
{
	if(Vel_x==0&&Vel_y==0){
		return false;
	}else{
		Pos_x += Vel_x*bSpeed;
		Pos_y += Vel_y*bSpeed;
		check_edge();
		return true;
	}
}

void Bullet::check_edge()
{
	bool ans = false;

	if(stage_number%2 == 0){
		if(Pos_x < 450) ans = true;
		else if(Pos_x > 950) ans = true;
		if(Pos_y < 100) ans = true;
		else if(Pos_y > 600) ans = true;
	}else if(stage_number%2 == 1){
		if(Pos_x > 950) ans = true;
		if(Pos_y > 600) ans = true;
		if(Pos_x < 200) ans = true;
		if(Pos_y < 100) ans = true;
		
		if(stage_number%4 == 1){
			if(Pos_y <= 240 && Pos_y >= 100){
				if(Pos_x < 450 && Pos_x > 430) ans = true;
			}
			if(Pos_x <= 450 && Pos_x >= 200 && !ans){
				if(Pos_y < 240 && Pos_y > 220) ans = true;
			}
		}else if(stage_number%4 == 3){
			if(Pos_y <= 240 && Pos_y >= 100){
				if(Pos_x < 710 && Pos_x > 690) ans = true;
			}
			if(Pos_x <= 960 && Pos_x >= 690 && !ans){
				if(Pos_y < 240 && Pos_y > 220) ans = true;
			}
		}
	}
	if(ans){
		Vel_x = 0, Vel_y = 0;
		Pos_x = 0, Pos_y = 800;
	}else{
		return;
	}
}

bool Bullet::check_hit(int x, int y)
{
	if(Pos_x+Width/2 < x+80 && Pos_x+Width/2 > x+40 && Pos_y+Height/2 < y+75 && Pos_y+Height/2 > y+10){
		Vel_x = 0, Vel_y = 0;
		Pos_x = 0, Pos_y = 800;
		return true;
	}else{
		return false;
	}
}

