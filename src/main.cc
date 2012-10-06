#include "config.h"
#include "gfx\renderer.h"
#include "core.h"
#include "utils/assets.h"
#include <iostream>

using namespace sandista;

int main () {
	
	Core* c = Core::getSingleton();

	if (ErrorManager::getSingleton()->existError("s.renderer.init")) return 1;

	std::shared_ptr<Texture2d> t = c->assets->getTexture2d("rust_01.png");
	
	t->bake();

	c->run();
	
	getchar();

	return 0;
}