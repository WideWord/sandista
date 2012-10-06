#include "config.h"
#include "gfx/renderer.h"
#include "core.h"
#include "material.h"
#include "utils/assets.h"
#include <iostream>

using namespace sandista;

int main () {
	
	Core* c = Core::getSingleton();

	if (ErrorManager::getSingleton()->existError("s.renderer.init")) return 1;

	std::shared_ptr<Texture2d> t = c->assets->getTexture2d("rust_01.png");
	
	t->bake();

	std::shared_ptr<Material> m = std::make_shared<Material>(std::string(""), std::string(""));

	m->bind();

	c->run();
	
	getchar();

	return 0;
}