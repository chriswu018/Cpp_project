#include "SDL2\SDL.h" 
#include <iostream>
#include <memory>
#include "SDL2/SDL_image.h"


extern SDL_Renderer* gRenderer;

static SDL_Texture* Start = NULL;
static SDL_Texture* End  = NULL;
static SDL_Texture* Lose  = NULL;

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

bool opening()
{
	Start = loadFromFile("./image\\Transition\\Start.png");
	//loop flag
	bool finish = false;
	if(Start==NULL) finish = true;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !finish )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE ) return false;
		else if(e.type == SDL_QUIT) return true;
		//Clear screen
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		SDL_RenderCopy( gRenderer, Start, NULL, NULL );
		//Update screen
		SDL_RenderPresent( gRenderer );
	}
}

bool ending()
{
	End = loadFromFile("./image\\Transition\\End.png");
	//loop flag
	bool finish = false;
	if(End==NULL) finish = true;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !finish )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE ) return true;
		else if(e.type == SDL_QUIT) return true;
		//Clear screen
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		SDL_RenderCopy( gRenderer, End, NULL, NULL );
		//Update screen
		SDL_RenderPresent( gRenderer );
	}
}

bool losing()
{
	Lose = loadFromFile("./image\\Transition\\Lose.png");
	//loop flag
	bool finish = false;
	if(Lose==NULL) finish = true;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !finish )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE ) finish = true;
		else if(e.type == SDL_QUIT) finish = true;
		//Clear screen
		SDL_RenderClear( gRenderer );
		//Render texture to screen
		SDL_RenderCopy( gRenderer, Lose, NULL, NULL );
		//Update screen
		SDL_RenderPresent( gRenderer );
		
	}
	
	SDL_DestroyTexture( Lose );
	Lose = NULL;
	
	return finish;
}
