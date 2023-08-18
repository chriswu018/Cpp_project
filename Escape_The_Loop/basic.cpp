#include "basic.h"

extern SDL_Renderer* gRenderer;

bool basic::loadFromFile( std::string path ,Uint8 R,Uint8 G ,Uint8 B)
{
	//Get rid of preexisting texture
	free();
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, R, G, B ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			Width = loadedSurface->w;
			Height = loadedSurface->h;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Return success
	Texture = newTexture;
	return Texture != NULL;
}

void basic::render(SDL_Rect * clips)
{
	SDL_Rect renderQuad = { Pos_x, Pos_y, Width, Height };
	SDL_RenderCopy(gRenderer, Texture, clips, &renderQuad);
}

void basic::free()
{
	if(Texture != NULL){
		SDL_DestroyTexture( Texture );
		Texture = NULL;
	}
}

int basic::getWidth()
{
	return Width;
}

int basic::getHeight()
{
	return Height;
}

int basic::getPos_x()
{
	return Pos_x;
}

int basic::getPos_y()
{
	return Pos_y;
}
