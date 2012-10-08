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



	while (true) {
		c->renderer->updateWindow();
	}
	
	getchar();

	return 0;
}