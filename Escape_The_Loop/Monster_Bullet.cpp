#include "Monster_Bullet.h"
#include "Character.h"
#include <cmath>

extern int stage_number;
extern Character gCharacter;

Monster_Bullet::Monster_Bullet()
{
	Pos_x = 0;
	Pos_y = 800;
	Vel_x = 0;
	Vel_y = 0;
	damage = 5;
	speed = 6;
	bullet_bounce = false;
	bullet_type = 1;
};

void Monster_Bullet::set_bullet(bool bounce, int spe, int dama, int type)
{
	bullet_bounce = bounce;
	speed = spe;
	damage = dama;
	bullet_type = type;
	
	if(type==2) this->free(), this->loadFromFile( "./image\\bullet2.png" );
	else if(type==3) this->loadFromFile( "./image\\bullet3.png" );
	else if(type==5) this->loadFromFile( "./image\\bullet4.png" );
	
}

bool Monster_Bullet::move()
{
	if(Vel_x==0&&Vel_y==0){
		//std::cout<<"nomove"<<std::endl;
		return false;
	}else{
		Pos_x += Vel_x*speed;
		Pos_y += Vel_y*speed;
		check_edge();
		//std::cout<<"move"<<std::endl;
		return true;
	}
}

void Monster_Bullet::set_v(int Mon_Pos_x, int Mon_Pos_y, int angle, float speed)
{
	static double dis,dx,dy,theta;
	
	Pos_x = Mon_Pos_x + 30;
	Pos_y = Mon_Pos_y + 20;
	
	dx = (gCharacter.getPos_x() + gCharacter.getWidth()/2 - Width/2  - Pos_x);
	dy = (gCharacter.getPos_y() + gCharacter.getHeight()/2 - Height/2 - Pos_y);

	theta = atan(dy/dx) ; 
	//std::cout<<"dis = "<<dis<<std::endl;
	if(dx<0&&dy>0) theta+=3.14; 
	if(dx<0&&dy<0) theta-=3.14;
	theta += 3.14*angle/180.0;
	
	Vel_x = cos(theta)*speed;
	Vel_y = sin(theta)*speed;

}

bool Monster_Bullet::check_hit(int x, int y)
{
	if(Pos_x+15 < x+70 && Pos_x+15 > x+10 && Pos_y+15 < y+80 && Pos_y+15 > y+10){
		Vel_x = 0, Vel_y = 0;
		Pos_x = 0, Pos_y = 800;
		return true;
	}else{
		return false;
	}
}

void Monster_Bullet::check_edge()
{
	static int ct = 0;
	if(!bullet_bounce){
		Bullet::check_edge();
	}else{
		int ans = 0;
		if(stage_number%2 == 0){
			if(Pos_x < 450) ans = true;
			else if(Pos_x > 950) ans = true;
			if(Pos_y < 100) ans = 2;
			else if(Pos_y > 600) ans = 2;
		}else if(stage_number%2 == 1){
			if(Pos_x > 950) ans = true;
			if(Pos_y > 600) ans = 2;
			if(Pos_x < 200) ans = true;
			if(Pos_y < 100) ans = 2;
			
			if(stage_number%4 == 1){
				if(Pos_y <= 240 && Pos_y >= 100){
					if(Pos_x < 450 && Pos_x > 430) ans = true;
				}
				if(Pos_x <= 450 && Pos_x >= 200 && !ans){
					if(Pos_y < 240 && Pos_y > 220) ans = 2;
				}
			}else if(stage_number%4 == 3){
				if(Pos_y <= 240 && Pos_y >= 100){
					if(Pos_x < 710 && Pos_x > 690) ans = true;
				}
				if(Pos_x <= 960 && Pos_x >= 690 && !ans){
					if(Pos_y < 240 && Pos_y > 220) ans = 2;
				}
			}
		}
		if(ans){
			if(ct<2){
				if(ans==1) Vel_x *= -1;
				if(ans==2) Vel_y *= -1;
				ct++;
			}else{
				Vel_x = 0, Vel_y = 0;
				Pos_x = 0, Pos_y = 800;
				ct = 0;
			}
		}else{
			return;
		}
	}
}

void Monster_Bullet::change_v()
{
	if(!track) return;
	static double dx,dy,theta;
	if(Pos_y!=800){
		dx = (gCharacter.getPos_x() + gCharacter.getWidth()/2 - Width/2  - Pos_x);
		dy = (gCharacter.getPos_y() + gCharacter.getHeight()/2 - Height/2 - Pos_y);
		theta = atan(dy/dx) ; 
		if(dx<0&&dy>0) theta+=3.14; 
		if(dx<0&&dy<0) theta-=3.14;
	}
	if(sqrt(dx*dx+dy*dy)>150){
		//std::cout<<"endkp"<<abs(Vel_x)<<abs(Vel_y)<<std::endl;
		Vel_x = cos(theta)*0.4;
		Vel_y = sin(theta)*0.4;
	}
	if (sqrt(dx*dx+dy*dy)<150){
		Vel_x = cos(theta);
		Vel_y = sin(theta);
		track = false;
	}
}
int Monster_Bullet::get_damage()
{
	return damage;
}
