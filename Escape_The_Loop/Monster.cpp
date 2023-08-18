#include "Monster.h"
#include "Monster_Bullet.h"
#include "Character.h"
#include <cmath>

//extern Map gMap[3];
extern SDL_Renderer* gRenderer;
extern Character gCharacter;
extern int stage_number;
extern int timer;
extern int alive_number;
extern Monster_Bullet *mBullet;

extern int Mon_Bullet_number;
static int Bulletct = 0;

extern Monster* gMonster;

bool Monster::edge_check(float & pos_x, float & pos_y )
{
	bool ans = false;
	if(stage_number%4 == 1){

		if(pos_x + 80 > 200 + 760) {
            ans = true;
            pos_x = 880;
            Vel_x *= -1;
            movestate = MonsterSprite_left;
		}
		if(pos_y + 60 > 250 + 360) {
            ans = true;
            pos_y = 550;
            Vel_y *= -1;
		}

		if(pos_x < 180) {
            ans = true;
            pos_x = 180;
            Vel_x *= -1;
            movestate = MonsterSprite_right;
		}


		if(pos_y < 100) {
            ans = true;
            pos_y = 100;
            Vel_y *= -1;
		}

		if(pos_y <= 220 && pos_y >= 100){
			if(pos_x < 420 && pos_x > 400) {
                ans = true;
                pos_x = 421;
                Vel_x *= -1;
                movestate = MonsterSprite_right;
			}
		}
		if(pos_x <= 420 && pos_x >= 160 && !ans){
			if(pos_y < 220 && pos_y > 200) {
                ans = true;
                pos_y = 221;
                Vel_y *= -1;
			}
		}
	}else if(stage_number%4 == 3){
		if(pos_x + 80 > 200 + 760) {
            ans = true;
            pos_x = 880;
            Vel_x *= -1;
            movestate = MonsterSprite_left;
		}

		if(pos_y + 60 > 250 + 360) {
            ans = true;
            pos_y = 550;
            Vel_y *= -1;
		}

		if(pos_x < 180) {
            ans = true;
            pos_x = 180;
            Vel_x *= -1;
            movestate = MonsterSprite_right;
		}

		if(pos_y < 100) {
            ans = true;
            pos_y = 100;
            Vel_y *= -1;
		}

		if(pos_y <= 220 && pos_y >= 100){
			if(pos_x < 650 && pos_x > 630) {
                ans = true;
                pos_x = 629;
                Vel_x *= -1;
                movestate = MonsterSprite_right;
			}
		}

		if(pos_x <= 930 && pos_x >= 630 && !ans){
			if(pos_y < 220 && pos_y > 200) {
                ans = true;
                pos_y = 221;
                Vel_y *= -1;
			}
		}

	}
	return ans;
}

Monster::Monster() //argument
{
	//Initialize
	Texture = NULL;
	//set_Pos
    Pos_x=0;
    Pos_y=0;
    //type of monster
    Monster_type = 1;
    Monster_Hp = 5;
	alive = true;
}

Monster::~Monster()
{
	//Deallocate
	free();
}

//for small monster, include monster called by boss 2 (eight clips)
bool Monster::loadFromFileSmall(std::string path)
{
	Monster_SpriteClips = new SDL_Rect [8];
    bool ans = basic::loadFromFile(path);
    Width = Width / 4;
    Height = Height / 2;

    //set monster's rectangle
    for (int i=0; i<8; i++){
        Monster_SpriteClips[i].x = Width*(i%4);
        Monster_SpriteClips[i].y = (i/4)*Height;
        Monster_SpriteClips[i].w = Width;
        Monster_SpriteClips[i].h = Height;
    }
    return ans;
}

//for boss (twelve clips)
bool Monster::loadFromFileBig(std::string path)
{
	Monster_SpriteClips = new SDL_Rect [12];
    bool ans = basic::loadFromFile(path);
    Width = Width / 4;
    Height = Height / 3;

    //set monster's rectangle
    for (int i=0; i<12; i++){
        Monster_SpriteClips[i].x = Width*(i%4);
        Monster_SpriteClips[i].y = (i/4)*Height;
        Monster_SpriteClips[i].w = Width;
        Monster_SpriteClips[i].h = Height;
    }
    return ans;
}


void Monster::operator++(int a){
    if(!alive) return;
	//Set rendering space and render to screen
	//scale = 0.7
	SDL_Rect renderQuad = { Pos_x, Pos_y, Width, Height };

	//left
	if (movestate == MonsterSprite_right){
        SDL_RenderCopyEx( gRenderer, Texture, &Monster_SpriteClips[ attack_1*4+attack_2*8+(timer/5)%4 ], &renderQuad ,0,NULL,SDL_FLIP_HORIZONTAL);
															//attack_1*4+attack_2*8
	}

	//right
	else if (movestate == MonsterSprite_left){
         SDL_RenderCopy( gRenderer, Texture, &Monster_SpriteClips[ attack_1*4+attack_2*8+(timer/5)%4], &renderQuad);
															//attack_1*4+attack_2*8
	}
}
void Monster::move()
{
	edge_check(Pos_x, Pos_y);
	if(!alive) return;
	static int dx=1;
	static int dy=1;
	static float theta=1;
	static int keep = 0;

	switch (Monster_type){
        case 1:
            if(timer%80 == 79){
				mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y);
				Bulletct++;
				attack_1 = true;
			}
			if(timer%80 == 19) attack_1 = false;
        	break;
        case 2:
        	if(timer%80 == 60){
				mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y);
				Bulletct++;
				attack_1 = true;
			}
			if(timer%80 == 0) attack_1 = false;
        	break;
        case 3:
        	if(timer%80 == 40){
				mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y);
				Bulletct++;
				attack_1 = true;
			}
			if(timer%80 == 60) attack_1 = false;
        	break;
        case 4:
        	//if(timer == 150) Bulletct = 0;
        	if(timer%200 == 100){
        		for(int i=-8;i<9;i++){
        			mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, i*8, 0.7);
					Bulletct++;
					attack_2 = true;
				}
			}
			if(timer%200 == 120) attack_2 = false;
			if(timer%200 == 140){
        		for(int i=-4;i<5;i++){
        			mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, i*1.5, 1.1);
					Bulletct++;
					attack_1 = true;
				}
			}
			if(timer%200 == 160) attack_1 = false;
        	break;

        case 5:
        	if(timer%400 == 20){
        		if(!gMonster[keep%4].alive){
    			alive_number++;
        		attack_2 = true;
        		attack_1 = false;
        		gMonster[keep%4].alive = true;
        		if(Vel_x>0)gMonster[keep%4].set_Pos(Pos_x, Pos_y, 1);
        		else gMonster[keep%4].set_Pos(Pos_x, Pos_y, 0);
        		keep++;
				}
			}
        	if(timer%400 == 40) attack_2 = false;
        	if(timer%300 == 180) attack_1 = true;
        	if(timer%300 == 280) attack_1 = false;
        	if(timer%300 > 180 ){
        		if(timer%24 == 9)
        		mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, 10, 1), Bulletct++;
				if(timer%24 == 11)
        		mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, -10, 1.25), Bulletct++;
        		if(timer%24 == 13)
        		mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, 0, 1.25), Bulletct++;
        		if(timer%24 == 15)
        		mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, -5, 1.25), Bulletct++;
        		if(timer%24 == 17)
        		mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, 5, 1), Bulletct++;

			}
        	break;
        case 6:
        	for(int i=0;i<5;i++){
        		if(timer == 100+i*10){
	        		mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, 0, 1);
	        		Bulletct++;
	        		if(i==0) attack_1 = true;
	        		if(i==4) attack_1 = false;
				}
			}

        	if(timer%400 == 230) attack_2 = true;
        	if(timer%400 == 250){
        		for(int i=-9;i<9;i++){
        			mBullet[Bulletct%Mon_Bullet_number].set_v(Pos_x, Pos_y, i*20, 0.7);
					Bulletct++;
				}
			}
        	if(timer%400 == 270) attack_2 = false;

        	if(timer == 400){
        		keep = Bulletct%Mon_Bullet_number;
				attack_1 = true;
			}
        	for(int i=0;i<5;i++){
        		if(timer == 450+10*i){
	        		mBullet[(keep+i)%Mon_Bullet_number].set_v(Pos_x, Pos_y, 0, 0.5);
        			mBullet[(keep+i)%Mon_Bullet_number].bullet_bounce = false;
					mBullet[(keep+i)%Mon_Bullet_number].track = true, Bulletct++;
				}
			}

        	if(timer==500) attack_1 = false;
			if(timer>500 && timer < 700){
				for(int i=0;i<5;i++)
        		mBullet[(keep+i)%Mon_Bullet_number].change_v();
			}

			if(timer == 700){
				for(int i=0;i<5;i++)
        		mBullet[(keep+i)%Mon_Bullet_number].bullet_bounce = true;
			}

        	break;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(Monster_type!=7)
    switch (Monster_type%2){
        case 0://square
        {
        	if (timer%400 == 0 ){
                movestate=MonsterSprite_left;
                Vel_x=-5;
                Vel_y=-1;
           }

           if (timer%400 == 50 ){
                movestate=MonsterSprite_right;
                Vel_x=3;
                Vel_y=-1;
           }

           //timer 201-300
           else if (timer%400 == 150 ){
                movestate=MonsterSprite_left;
                Vel_x=-3;
                Vel_y=2;
           }
           //timer 301-400

            else if (timer%400 == 250 ){
                movestate=MonsterSprite_right;
                Vel_x=4;
                Vel_y=-2;
            }

            else if (timer%400 == 350 ){
            	movestate=MonsterSprite_left;
                Vel_x=-3;
                Vel_y=-1;
            }
            Pos_x+=Vel_x;
            Pos_y+=Vel_y;
            //edge_check(Pos_x, Pos_y);
        }
        break;

        case 1://not yet finish
        {
        	if (timer%400 == 0 ){
                movestate=MonsterSprite_left;
                Vel_x=-5;
                Vel_y=2;
           }
            if (timer%400 ==40){
                movestate = MonsterSprite_left;
                Vel_x=-2;
                Vel_y=4;
            }
            else if (timer%400 ==120 ){
                Vel_x=0;
                Vel_y=-2;
            }
            else if (timer%400 ==200 ){
            	movestate=MonsterSprite_right;
                Vel_x=4;
                Vel_y=3;
            }
            else if (timer%400 ==280 ){
            	movestate=MonsterSprite_right;
                Vel_x=2;
                Vel_y=-2;
            }

            else if (timer%400 ==360 ){
                movestate=MonsterSprite_left;
                Vel_x=-2;
                Vel_y=-4;
            }

            Pos_x+=Vel_x;
            Pos_y+=Vel_y;
            //edge_check(Pos_x, Pos_y);
        }
        break;
    }
    else{
    	if (timer%25 == 0 ){
    		dx = gCharacter.getPos_x() - Pos_x;
    		dy = gCharacter.getPos_y() - Pos_y;
    		if(dx==0){
    			theta = 0.785;
    			if(dy<0) theta = -0.785;
			}else theta = atan(dy/dx) ;
			if(dx<0&&dy>0) theta+=3.14;
			if(dx<0&&dy<0) theta-=3.14;
			Vel_x = cos(theta);
			Vel_y = sin(theta);
			if(dx>0)movestate=MonsterSprite_right;
			else movestate=MonsterSprite_left;
			if (timer%50 == 0 )
			if(sqrt(dx*dx+dy*dy)< 100 ){
				gCharacter.change_hp(5);
				attack_1 = true;
			}
		}
		if (timer%25 == 20)attack_1 = false;
		Pos_x+=Vel_x*5;
        Pos_y+=Vel_y*5;
	}

}

void Monster::change_hp(int num)
{
	if(Monster_Hp > 0){
		Monster_Hp -= num;
		if(Monster_Hp <= 0){
			Pos_x = 1600, Pos_y = 0;
			Vel_x = 0, Vel_y = 0;
			alive = false;
			alive_number--;
			if(Monster_type==5){
				alive_number = 0;
				for(int i=0;i<4;i++){
					gMonster[i].alive = false;
		        	gMonster[i].set_Pos(float(10.0), float(800.0), false);
				}
			}
		}
	}
}

void Monster::set_Monster( const int & x, const int & y, const int & type, const int & which,const int & hp)
{
	Pos_x=x;
    Pos_y=y;
    Monster_type = type;
    attack_1 = false;
    attack_2 = false;
    Monster_Hp = hp;

    if(which==1) this->loadFromFileSmall( "./image\\monster\\mon1.png" );
    if(which==2) this->loadFromFileSmall( "./image\\monster\\mon2.png" );
    if(which==3) this->loadFromFileSmall( "./image\\monster\\mon3.png" );
    if(which==4) this->loadFromFileBig( "./image\\monster\\boss4.png" );
    if(which==5) this->loadFromFileBig( "./image\\monster\\boss5.png" );
    if(which==6) this->loadFromFileBig( "./image\\monster\\boss6.png" );
    if(which==7){
  		this->loadFromFileSmall( "./image\\monster\\mon7.png" );
		alive = false;
	}
}
void Monster::set_Pos(float pos_x, float pos_y, bool lr)
{
	if(lr) Pos_x = pos_x + 10;
	else Pos_x = pos_x - 10;
    Pos_y = pos_y;
	Monster_Hp = 20;
}
