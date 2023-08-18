#include "SDL2\SDL.h" 
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"
#include "Character.h"
#include "Monster.h"
#include "Monster_Bullet.h"

extern SDL_Renderer* gRenderer;
extern Character gCharacter;
extern Monster* gMonster;
extern int timer;
extern int Mon_Bullet_number;
extern Monster_Bullet *mBullet;

static SDL_Texture* Next = NULL;

static int Monster_setup [19] = { 0, 3, 0, 4, 0, 1,
								  0, 3, 0, 4, 0, 5,
								  0, 3, 0, 4, 0, 1, 0 };

								  
static void loadFromFile()
{
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( "./image\\Transition\\next.png" );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", "./image\\Next.png", IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", "./image\\Next.png" , SDL_GetError() );
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Return success
	Next = newTexture;
}

void Create_Monster(int Monster_number, int stage_number)
{
	delete [] gMonster;
	gMonster = new Monster [Monster_number];
	
	if(stage_number==1){
		gMonster[0].set_Monster(300,500,1,1,15);
		gMonster[1].set_Monster(400,400,2,1,15);
		gMonster[2].set_Monster(700,200,3,1,15);
	}else if(stage_number==3){
		gMonster[0].set_Monster(300,500,1,1,15);
		gMonster[1].set_Monster(400,400,2,1,15);
		gMonster[2].set_Monster(700,300,3,1,15);
		gMonster[3].set_Monster(800,250,2,1,15);
	}else if(stage_number==5){
		gMonster[0].set_Monster(400,400,4,4,50);
	}else if(stage_number==7){
		gMonster[0].set_Monster(300,500,1,2,20);
		gMonster[1].set_Monster(400,300,2,2,20);
		gMonster[2].set_Monster(700,400,3,2,20);
	}else if(stage_number==9){
		gMonster[0].set_Monster(300,500,1,2,20);
		gMonster[1].set_Monster(400,400,2,2,20);
		gMonster[2].set_Monster(700,300,3,2,20);
		gMonster[3].set_Monster(800,250,2,2,20);
	}else if(stage_number==11){
		gMonster[0].set_Monster(0,800,7,7,20);
		gMonster[1].set_Monster(0,800,7,7,20);
		gMonster[2].set_Monster(0,800,7,7,20);
		gMonster[3].set_Monster(0,800,7,7,20);
		gMonster[4].set_Monster(400,400,5,5,60);
	}else if(stage_number==13){
		gMonster[0].set_Monster(200,500,1,3,25);
		gMonster[1].set_Monster(500,450,2,3,25);
		gMonster[2].set_Monster(700,400,3,3,25);
	}else if(stage_number==15){
		gMonster[0].set_Monster(300,500,1,3,25);
		gMonster[1].set_Monster(400,400,2,3,25);
		gMonster[2].set_Monster(700,300,3,3,25);
		gMonster[3].set_Monster(800,250,2,3,25);
	}else if(stage_number==17){
		gMonster[0].set_Monster(400,400,6,6,70);
	}
	
	//set_bullet(bool bounce, int spe, int dama, int type);
	if(stage_number==1){
		for(int i=0; i<Mon_Bullet_number ;i++)
		mBullet[i].set_bullet(0,5,3,1);
	}else if(stage_number==5){
		for(int i=0; i<Mon_Bullet_number ;i++)
		mBullet[i].set_bullet(0,8,5,2);
	}else if(stage_number==7){
		for(int i=0; i<Mon_Bullet_number ;i++)
		mBullet[i].set_bullet(0,6,4,3);
	}else if(stage_number==11){
		for(int i=0; i<Mon_Bullet_number ;i++)
		mBullet[i].set_bullet(0,9,6,4);
	}else if(stage_number==13){
		for(int i=0; i<Mon_Bullet_number ;i++)
		mBullet[i].set_bullet(0,7,5,5);
	}else if(stage_number==17){
		for(int i=0; i<Mon_Bullet_number ;i++)
		mBullet[i].set_bullet(1,9,7,6);
	}
	
}


void goto_next(int & Monster_number, int & stage_number, int & alive_number){
	if(alive_number!=0) return;
	
	static bool check = false;
	
	if(gCharacter.getPos_y()==110 && stage_number%2 == 0 ){
			if(gCharacter.getPos_x() > 680 && gCharacter.getPos_x() < 720 ){
				check = true;
			}
	}else if(gCharacter.getPos_y()==120){
		if(stage_number%4 == 1){
			if(gCharacter.getPos_x() > 680 && gCharacter.getPos_x() < 720 ){
				check = true;
			}
		}else if(stage_number%4 == 3){
			if(gCharacter.getPos_x() > 370 && gCharacter.getPos_x() < 410 ){
				check = true;
			}
		}
	}
	
	if(check){ 
		if(Next==NULL) loadFromFile();
		//animation
		//SDL_Delay(500);
		if(stage_number<17){
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderClear( gRenderer );
			SDL_RenderCopy( gRenderer, Next, NULL, NULL );
			SDL_RenderPresent( gRenderer );
		}
	
		//change map
		stage_number++;

		gCharacter.set_Pos();
		
		Monster_number = Monster_setup[stage_number];
		alive_number = Monster_number;
		
		if(stage_number%2 == 1) Create_Monster(Monster_number, stage_number);
		
		if(stage_number<18)SDL_Delay(2000);
		
		timer = 0;
		
		check = false;
	}
}
