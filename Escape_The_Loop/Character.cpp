#include "Character.h"
#include "Map.h"
#include "Bullet.h"
#include "SDL2\SDL_mixer.h"

extern Map gMap[3];
extern Bullet* gBullet;
extern SDL_Renderer* gRenderer;
extern int stage_number;
static const Uint8 *keystates = SDL_GetKeyboardState(NULL);
static int lr = 0, stp = 0,atk = 0;
extern int attack_timer;
extern int Bullet_canuse;
extern Mix_Chunk* sHurt;
extern Mix_Chunk* sAttack;


Character::Character()
{
	//Initialize
	Texture = NULL;
	Pos_x = 450;
	Pos_y = 450;
	Character_Hp = 100;
	Vel_x = 0;
	Vel_y = 0;
	Character_SpriteClips = new SDL_Rect[14];
}

Character::~Character()
{
	//Deallocate
	free();
}

bool Character::loadFromFile(std::string path, int w, int h)
{
	bool ans = basic::loadFromFile(path);
	Width /= w, Height /= h;
	for( int i = 0; i < 8; i++ ){
			Character_SpriteClips[ i ].x = (i%8)*Width;
			Character_SpriteClips[ i ].y = (i/8)*Height;
			Character_SpriteClips[ i ].w = Width;
			Character_SpriteClips[ i ].h = Height;
	}
	for( int i = 8; i < 14; i++ ){
			Character_SpriteClips[ i ].x = (i-8)%6*Width;
			Character_SpriteClips[ i ].y = ((i-8)/6+1)*Height;
			Character_SpriteClips[ i ].w = Width;
			Character_SpriteClips[ i ].h = Height;
	}
	return ans;
}

void Character::render()
{
	
	//Set rendering space and render to screen
	//scale = 0.7 
	SDL_Rect renderQuad = { Pos_x, Pos_y, Width, Height };
	//Character_SpriteClips[ mCurrentSprite ] control the sprite will show later
	//第三個RECT跟圖片本身擷取有關第四個RECT跟在螢幕上的哪裡有關 
	int sprite = atk*(8+attack_timer/7)+(!atk)*(+(attack_timer/5)*(!stp));
	if(lr) SDL_RenderCopyEx(gRenderer, Texture, &Character_SpriteClips[sprite], &renderQuad,0,NULL,SDL_FLIP_HORIZONTAL);
	else   SDL_RenderCopy(gRenderer, Texture, &Character_SpriteClips[sprite], &renderQuad);
	
	if(attack_timer>36) atk = 0;
	
}

void Character::move( SDL_Event* e )
{
	//Mouse is outside button
	if( !(gMap[stage_number/6]).collison_check(Pos_x, Pos_y) ){
		stp = 1;
		if(keystates[SDL_SCANCODE_W]) stp = 0, Vel_y = -10;
		if(keystates[SDL_SCANCODE_A]) stp = 0, Vel_x = -10, lr  =   0;
		if(keystates[SDL_SCANCODE_S]) stp = 0, Vel_y =  10;
		if(keystates[SDL_SCANCODE_D]) stp = 0, Vel_x =  10, lr  =   1;
	}else Vel_x = 0, Vel_y = 0;
		
	if(stp) Vel_x = 0, Vel_y = 0;
	else{
		Pos_x += Vel_x*0.5;
		Pos_y += Vel_y*0.5;
	}
}

bool Character::attack(SDL_Event* e){
	bool ans = false;
	static int ct = 0;
	if(e->type == SDL_MOUSEBUTTONDOWN){
		if(gBullet[ct%Bullet_canuse].getPos_y()==800){
			Mix_PlayChannel( -1, sAttack, 0 );
			atk = 1,attack_timer = 4;
			ans = true;
			int x,y;
			SDL_GetMouseState( &x, &y );
			
			gBullet[ct%Bullet_canuse].set_v(x, y);
			ct++;
		}
	}
	return ans;	
}
 
void Character::set_Pos()
{
	Pos_x = 900;
	Pos_y = 540;
	if(stage_number%2==0){
	}else if(stage_number%4==1){	
	}else if(stage_number%4==3){
	}
}

bool Character::change_hp(int num)
{
	if(Character_Hp > 0){
		if(num>0) Mix_PlayChannel( -1, sHurt, 0 );
		Character_Hp -= num;
	}
	if(Character_Hp <= 0){
		return true;
	}
	return false;
}

int Character::get_Hp()
{
	return Character_Hp;
}
