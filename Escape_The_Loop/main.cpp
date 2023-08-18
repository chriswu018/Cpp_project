//Using SDL, SDL_image, standard IO, and strings
#include "SDL2\SDL.h"  
#include "SDL2\SDL_image.h"
#include "SDL2\SDL_ttf.h"
#include "SDL2\SDL_mixer.h"
#include <stdio.h>
#include <string>
//class header file
#include "Character.h"
#include "Map.h"
#include "Bullet.h"
#include "LTimer.h"
#include "Monster.h"
#include "Monster_Bullet.h"
#include "Text.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;

//change stage
extern void goto_next(int &, int &, int &);
extern bool opening();
extern bool losing();
extern bool ending();

extern bool init();
extern bool loadMedia();
extern void close();
extern void render_all();

extern void Store_load();
extern void Shopping(bool &);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *gFont2 = NULL;
//SDL event
SDL_Event e;
//control closing
bool quit = false;

//timer
LTimer Frame_timer; 
int timer = 0;
int attack_timer = 0;

//Character
Character gCharacter;

//Map
Map gMap[3];
int stage_number = 0;

//Weapon
int Bullet_number = 8;
int bDamage = 5;
int bSpeed = 7;
Bullet* gBullet = NULL;
int Bullet_canuse = 4;

//monster
Monster* gMonster = NULL;
int Monster_number = 0;
int alive_number = 0;
Monster_Bullet *mBullet = NULL;
int Mon_Bullet_number = 30;

//Text
Text Text_Hp; 
std::stringstream Hp_num;
Text Text_Stage;
std::stringstream Stage_num;

//sound
Mix_Chunk* sHurt = NULL;
Mix_Chunk* sAttack = NULL;
Mix_Music* mUsual = NULL;
Mix_Music* mBoss = NULL; 

void timer_set()
{
	//set delay
	int t = Frame_timer.getTicks();
	if(t < 20) SDL_Delay(20 - t);
	
	if(++timer==800) timer=0;
	if(++attack_timer==40) attack_timer=0;
}

void judge()
{
	static bool Hurt = false;
	static int timesave = 0;
	for(int i=0;i<Mon_Bullet_number;i++)
	if(mBullet[i].check_hit( gCharacter.getPos_x(),gCharacter.getPos_y() )){
		if(gCharacter.change_hp(mBullet[i].get_damage()))
		quit = losing();
		Hurt = true;
		timesave = (timer+24)%800;
	}
	
	for(int i=0;i<Monster_number;i++)
	if(gMonster[i].alive){
		for(int j=0;j<Bullet_canuse;j++)
		if(gBullet[j].check_hit( gMonster[i].getPos_x(),gMonster[i].getPos_y() )){
			gMonster[i].change_hp(bDamage);
		}
	}
	
	//Set Text
	Hp_num.str("");
	Hp_num<<"HP : "<<gCharacter.get_Hp();
	if(Hurt&&timer%8<4) Text_Hp.loadFromRenderedText( Hp_num.str().c_str(), Text_Hp.setColor(255,0,0) );
	else Text_Hp.loadFromRenderedText( Hp_num.str().c_str(), Text_Hp.setColor(255,255,255) );
	if(timer==timesave) Hurt = false;
	
	Stage_num.str("");
	Stage_num<<"Stage"<<stage_number/6+1<<'-'<<stage_number%6+1;
	Text_Stage.loadFromRenderedText( Stage_num.str().c_str(), Text_Hp.setColor(255,255,255) );
}


int main( int argc, char* args[] )
{
	mBullet = new Monster_Bullet[Mon_Bullet_number];
	gBullet = new Bullet [Bullet_number];
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	/*	
		
		*/
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{				
			bool shopping = true;
			bool boss = true;
			quit = opening();
			while( !quit )
			{
				
				//set frame_timer
				Frame_timer.start();
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{

					//User requests quit
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}

					if(alive_number>0) gCharacter.attack( &e );
				}
				//move
				gCharacter.move( &e );

				for(int i=0;i<Monster_number;i++)
				gMonster[i].move();
				
				//JUDGE  
				judge();	
				
				if(!quit){
					//Render all
					render_all();
					//if next
					goto_next(Monster_number, stage_number, alive_number);
					//timer set
					timer_set();
					
				}
				if(stage_number==18) quit = ending();
				if(stage_number%6==5&&!boss){
					Mix_HaltMusic();
					Mix_PlayMusic(mBoss, -1);
					boss = true;
				}
				if(stage_number%6==0&&boss){
					Mix_HaltMusic();
					Mix_PlayMusic(mUsual, -1);
					boss = false;
				}
				if(stage_number>1&&stage_number%2==0&&(!quit)&&shopping){
					Shopping(shopping);
				}
				if(stage_number%2==1&&!shopping){
					shopping = true;
				}
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}
