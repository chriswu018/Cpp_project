#include "SDL2\SDL.h" 
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"
#include "Character.h"
#include "Bullet.h"
#include "Text.h"

extern SDL_Renderer* gRenderer;
extern Character gCharacter;
extern int stage_number;
extern int Bullet_canuse;
extern int bDamage;
extern int bSpeed;
//1000 600 280 400(200*2)
static SDL_Texture* board = NULL;
static SDL_Texture* speup = NULL;
static SDL_Texture* damup = NULL;
static SDL_Texture* canup = NULL;
static SDL_Texture* heaup = NULL;

Text Text_item;

SDL_Rect bigpos  = {200,100,1000,600};
SDL_Rect bigclip1 = {0,0,1000,600};
SDL_Rect bigclip2 = {0,600,1000,600};

SDL_Rect smallpos1  = {520,400,280,200};
SDL_Rect smallpos2  = {840,400,280,200};
SDL_Rect smallclip1 = {0,0,280,200};
SDL_Rect smallclip2 = {0,200,280,200};
//320 300 640 300
int item[18] = {0,0,  1,4,  2,4,  3,4,  1,4,  2,4,  3,4,  1,4,  2,4,};

void Speed_Up(int num)
{
	bSpeed += num;	
}

void Damage_Up(int num)
{                      
	bDamage += num;
}

void Canuse_Up(int num)
{
	Bullet_canuse += num;	
}

void Helath_Up(int num)
{
	gCharacter.change_hp(-num);
}

void Buff(bool lr)
{
	if(stage_number%6==0){
		if(lr){
			Helath_Up(30);
		}else{
			Canuse_Up(1);
		}
	}else{
		if(lr){
			Helath_Up(20);
		}else if(stage_number%6==2){
			Speed_Up(1);
		}else{
			Damage_Up(1);
		}
	}
}

static SDL_Texture* loadFromFile(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(  path.c_str()  );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str() , SDL_GetError() );
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Return 
	return newTexture;
}

void render(const int & which, const bool & touch, const bool & lr){
	SDL_Rect clip = smallclip1;
	SDL_Rect pos = smallpos1;
	if(touch) clip = smallclip2;
	if(lr) pos = smallpos2;
	
	if(which==1) SDL_RenderCopy( gRenderer, speup, &clip, &pos );
	else if(which==2) SDL_RenderCopy( gRenderer, damup, &clip, &pos );
	else if(which==3) SDL_RenderCopy( gRenderer, canup, &clip, &pos );
	else if(which==4) SDL_RenderCopy( gRenderer, heaup, &clip, &pos );
}

void texton(int which)
{
	if(which==1){
		if(stage_number%6==2) Text_item.loadFromRenderedText2("Bullet Speed UP" , Text_item.setColor(93,3,17) );
		if(stage_number%6==4) Text_item.loadFromRenderedText2("Bullet Damage UP" , Text_item.setColor(93,3,17) );
		if(stage_number%6==0) Text_item.loadFromRenderedText2("Bullet Number UP" , Text_item.setColor(93,3,17) );
	}
	if(which==2) Text_item.loadFromRenderedText2("HP UP" , Text_item.setColor(93,3,17) );
	Text_item.render(460,165);
}

void Shopping(bool & shopping)
{
	static bool initial = false;
	static bool finish = false;
	static int x,y;
	static SDL_Event e;
	
	if(!initial){
		board = loadFromFile("./image\\store\\store2.png");
		speup = loadFromFile("./image\\store\\bulletSpeed.png");
		damup = loadFromFile("./image\\store\\attack.png");
		canup = loadFromFile("./image\\store\\bulletNumber.png");
		heaup = loadFromFile("./image\\store\\hpAdd.png");
		initial = true;
	}
	
	while(!finish){
		while(!finish && SDL_PollEvent( &e ) != 0 ){
			SDL_GetMouseState( &x, &y );
			
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderClear( gRenderer );
			
			if(x>520&&x<800&&y>400&&y<600){
				SDL_RenderCopy( gRenderer, board, &bigclip2, &bigpos );
				render(item[stage_number],1,0);
				render(item[stage_number+1],0,1);
				texton(1);
				if(e.type == SDL_MOUSEBUTTONDOWN){
					finish = true;
					Buff(0);
				}
			}else if(x>840&&x<1120&&y>400&&y<600){
				SDL_RenderCopy( gRenderer, board, &bigclip2, &bigpos );
				render(item[stage_number],0,0);
				render(item[stage_number+1],1,1);
				texton(2);
				if(e.type == SDL_MOUSEBUTTONDOWN){
					finish = true;
					Buff(1);
				}
			}else{
				SDL_RenderCopy( gRenderer, board, &bigclip1, &bigpos );
				render(item[stage_number],0,0);
				render(item[stage_number+1],0,1);
			}
			SDL_RenderPresent( gRenderer );
		}
	}
	shopping = false, finish = false;
}
	
