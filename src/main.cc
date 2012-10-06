#include "config.h"
#include "gfx/renderer.h"
#include "core.h"
#include "material.h"
#include "utils/assets.h"
#include "mesh.h"
#include <iostream>

using namespace sandista;

int main () {
	
	Core* c = Core::getSingleton();

	if (ErrorManager::getSingleton()->existError("s.renderer.init")) return 1;


	std::shared_ptr<Material> m = std::make_shared<Material>(std::string(""), std::string(""));
	
	SubMesh* me = new SubMesh(m, 3, 1);
	float pos[] = {
		1, 0,0,
		-1, 0, 0,
		0, 0, 0
	};
	unsigned ind[] = {0, 1, 2};

	me->addAtrib("std_position", 3, pos);
	me->setIndexAttrib(ind);
	me->bake();

	while (true) {
		c->renderer->drawSubMesh(me);
		c->renderer->updateWindow();
	}
	
	getchar();

	return 0;
}