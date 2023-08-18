#include "Map.h"
#include "Character.h"

extern SDL_Renderer* gRenderer;
extern int stage_number;

Map::Map(){
	Pos_x = 0;
	Pos_y = 0;
}

Map::~Map(){
	
	free();
}

bool Map::loadFromFile( std::string path )
{
	bool ans = basic::loadFromFile(path);
	Height /= 3;
	return ans;
}


void Map::render()
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad2 = { 0, 0, Width, Height };
	if(stage_number%4 == 1) 	 renderQuad2.y = 1600;
	else if(stage_number%4 == 3) renderQuad2.y = 800;
	basic::render(&renderQuad2);
}

void Map::operator~ ()
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad2 = { 0, 0, Width, Height };
	if(stage_number%4 == 1) 	 renderQuad2.y = 1600;
	else if(stage_number%4 == 3) renderQuad2.y = 800;
	basic::render(&renderQuad2);
}


bool Map::collison_check( float & pos_x, float & pos_y )
{	
	//stage num 0-17
	//w = 80 h = 96 
	bool ans = false;
	if(stage_number%2 == 0){

		if(pos_x < 450) ans = true, pos_x = 450;
		else if(pos_x + 50 > 450 + 510) ans = true, pos_x = 910;
		if(pos_y < 110) ans = true, pos_y = 110;
		else if(pos_y + 60 > 110 + 500) ans = true, pos_y = 550;
		
	}else if(stage_number%2 == 1){
		if(stage_number%4 == 1){
			if(pos_x + 50 > 200 + 760) ans = true, pos_x = 910;
			if(pos_y + 60 > 250 + 360) ans = true, pos_y = 550;
			
			if(pos_x < 210) ans = true, pos_x = 210;
			if(pos_y < 120) ans = true, pos_y = 120;
			
			if(pos_y <= 240 && pos_y >= 120){
				if(pos_x < 450 && pos_x > 430) ans = true, pos_x = 451;
			}
			if(pos_x <= 450 && pos_x >= 200 && !ans){
				if(pos_y < 240 && pos_y > 220) ans = true, pos_y = 241;
			}
		}else if(stage_number%4 == 3){
			if(pos_x + 50 > 200 + 760) ans = true, pos_x = 910;
			if(pos_y + 60 > 250 + 360) ans = true, pos_y = 550;
			
			if(pos_x < 210) ans = true, pos_x = 210;
			if(pos_y < 120) ans = true, pos_y = 120;
			
			if(pos_y <= 240 && pos_y >= 120){
				if(pos_x < 680 && pos_x > 660) ans = true, pos_x = 659;
			}
			if(pos_x <= 960 && pos_x >= 660 && !ans){
				if(pos_y < 240 && pos_y > 220) ans = true, pos_y = 241;
			}
		}
	}
	return ans;
}
