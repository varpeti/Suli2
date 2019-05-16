#include "env.hpp"

using namespace genv;

int main()
{
	ENV env (1300,600,false);
	if(!env.spriteok_beolvas("hal.bmp")) gout << text("Nem talalhato a kep!");
	
	ENV::SPRITE *szem = env.newSprite(300,-50,300,160,170,160);

	gin.timer(20);

	bool lenyomva = false;
	double kx=0,ky=0;

	while(gin >> env.ev and env.ev.keycode!=key_escape) {

		if (env.ev.type==ev_timer){
			env.kirajzol();
		} 
		else if (env.ev.type==ev_mouse)
		{
			if (env.ev.button==btn_left)
				for (int i = env.SPRITEOK.size()-1; i >= 0; i--)
					if (env.SPRITEOK[i]->BenneVan(env.ev.pos_x,env.ev.pos_y)) {
						env.SPRITEOK[i]->getPosition(kx,ky);
						kx-=env.ev.pos_x;
						ky-=env.ev.pos_y;
						lenyomva=true;
						env.SpriteKiemel(env.SPRITEOK[i]);
						break;
					}

			if (-env.ev.button==btn_left) {lenyomva=false; kx=0; ky=0;}

			if (env.ev.button==btn_right) {
				env.newSprite(env.ev.pos_x-175,env.ev.pos_y-100,250,200,SZIN(rand()%255,rand()%255,rand()%255));
			};

			if (env.ev.button==btn_wheelup) 
				for (int i = env.SPRITEOK.size()-1; i >= 0; i--)
					if (env.SPRITEOK[i]->BenneVan(env.ev.pos_x,env.ev.pos_y)) {
						double mx,my;
						env.SPRITEOK[i]->getMeret(mx,my); cout << mx << " " << my << endl;
						env.SPRITEOK[i]->setMeret(mx*1.01,my*1.01); 
						env.SpriteKiemel(env.SPRITEOK[i]);
						break;
					}
			if (env.ev.button==btn_wheeldown)
				for (int i = env.SPRITEOK.size()-1; i >= 0; i--)
					if (env.SPRITEOK[i]->BenneVan(env.ev.pos_x,env.ev.pos_y)) {
						double mx,my;
						env.SPRITEOK[i]->getMeret(mx,my);
						env.SPRITEOK[i]->setMeret(mx*0.99,my*0.99); 
						env.SpriteKiemel(env.SPRITEOK[i]);
						break;
					}

			if (lenyomva)
			{
				env.SPRITEOK[env.SPRITEOK.size()]->setPosition(env.ev.pos_x+kx,env.ev.pos_y+ky);
			}
		}
		else if (env.ev.type==ev_key)
		{
			szem->setPosition(rand()%200,rand()%200);
		}
		
	}
	return 0;
}
