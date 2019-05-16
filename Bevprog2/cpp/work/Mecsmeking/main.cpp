#include "mm.hpp"
#include <iostream>

using namespace std;


int main()
{	
	ENV env (700,600,false); // Fix méretű ablak, fix koordináták és méretek.
	if(!env.kepek_beolvas("sp.bmp")) gout << text("Nem talalhato a kep!");
	env.timer(20);

	OBJ *mm = new MM(0,0,0,0); env.addObj(mm);

	while(gin >> env.ev and env.ev.keycode!=key_escape) {
		env.UpdateDrawHandle();
	}
	
	return 0;
}
