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
#include "Monster.h"
#include "Monster_Bullet.h"
#include "Text.h"

//Screen dimension constants
extern const int SCREEN_WIDTH = 1400;
extern const int SCREEN_HEIGHT = 800;
//The window we'll be rendering to
extern SDL_Window* gWindow;
//The window renderer
extern SDL_Renderer* gRenderer;
//Globally used font
extern TTF_Font *gFont;
extern TTF_Font *gFont2;
//Character
extern Character gCharacter;
//Map
extern Map gMap[3];
extern int stage_number;

//Weapon
extern Bullet* gBullet;
extern Monster_Bullet *mBullet;
extern int Bullet_number;
extern int Bullet_canuse;

extern int Mon_Bullet_number;

extern Monster* gMonster;
extern int Monster_number;

extern Text Text_Hp; 
extern Text Text_Stage;

extern Mix_Chunk* sHurt;
extern Mix_Chunk* sAttack;
extern Mix_Music *mUsual;
extern Mix_Music *mBoss; 

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Escape The Loop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				
				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	//Load Character's texture
	if( !gCharacter.loadFromFile( "./image\\character.png") )
	{
		printf( "Failed to load Archer texture image!\n" );
		success = false;
	}
	
	//Load map texture
	if( !gMap[0].loadFromFile( "./image\\map\\Map-1.png" ) )
	{
		printf( "Failed to load map texture image!\n" );
		success = false;
	}
		if( !gMap[1].loadFromFile( "./image\\map\\Map-2.png" ) )
	{
		printf( "Failed to load map texture image!\n" );
		success = false;
	}
		if( !gMap[2].loadFromFile( "./image\\map\\Map-3.png" ) )
	{
		printf( "Failed to load map texture image!\n" );
		success = false;
	}
	
	//Load bullet texture
	for(int i=0;i<Bullet_number;i++)
	if( !gBullet[i].loadFromFile( "./image\\bullet.png" ) )
	{
		printf( "Failed to load bullet texture image!\n" );
		success = false;
	}
	
	//mBullet = new Monster_Bullet [Mon_Bullet_number];
	for(int i=0;i<Mon_Bullet_number;i++)
	if( !mBullet[i].loadFromFile( "./image\\bullet1.png" ) )
	{
		printf( "Failed to load bullet texture image!\n" );
	}
	
	//Load Text
	gFont = TTF_OpenFont( "./textfile\\alphbeta.ttf", 72 );
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	
	gFont2 = TTF_OpenFont( "./textfile\\advanced_pixel-7.ttf", 120 );
	if( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	
	sAttack = Mix_LoadWAV( "./soundEffect\\attack_1.wav" );
	if( sAttack == NULL )
	{
	printf( "Failed to load attack sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	success = false;
	}
	
	sHurt = Mix_LoadWAV( "./soundEffect\\hurt_4.wav" );
	if( sHurt == NULL )
	{
	printf( "Failed to load hurt sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	success = false;
	}
	
	mUsual = Mix_LoadMUS( "./soundEffect\\usual.wav" );
	if( mUsual == NULL )
	{
	printf( "Failed to load usual background music! SDL_mixer Error: %s\n", Mix_GetError() );
	success = false;
	}
	
	mBoss = Mix_LoadMUS( "./soundEffect\\boss.wav" );
	if( mBoss == NULL )
	{
	printf( "Failed to load boss background music! SDL_mixer Error: %s\n", Mix_GetError() );
	success = false;
}
	
	return success;
}

void close()
{
	//Free loaded images
	gCharacter.free();
	for(int i=0;i<3;i++)
	gMap[i].free();
	for(int i=0;i<Bullet_number;i++)
	gBullet[i].free();
	for(int i=0;i<Mon_Bullet_number;i++)
	mBullet[i].free();
	
	
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	TTF_CloseFont( gFont );
	gFont = NULL;
	gFont2 = NULL;
	gWindow = NULL;
	gRenderer = NULL;
	sHurt = NULL;
	sAttack = NULL;
	mUsual = NULL;
	mBoss = NULL; 

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void render_all()
{
	//std::cout<<gBullet[bCounter].get_x()<<std::endl;
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//Clear screen
	SDL_RenderClear( gRenderer );
	//Render background texture to screen
	~gMap[stage_number/6];
	
	for(int i=0;i<Monster_number;i++)
	if(gMonster[i].alive)gMonster[i]++;
	//Render Character to the screen
	gCharacter.render();
	//Render Bullet
	for(int i=0;i<Mon_Bullet_number;i++)
	if(mBullet[i].move())  
	mBullet[i].render();
	 
	for(int i=0;i<Bullet_canuse;i++)
	if(gBullet[i].move())  
	gBullet[i].render();
	
	//Render text
	Text_Stage.render(1100,40); 
	Text_Hp.render(1100,100);
	
	//Update screen
	SDL_RenderPresent( gRenderer );
}

