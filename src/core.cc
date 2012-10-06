#include "core.h"
#include "gfx/renderer.h"
#include "utils/assets.h"
#include "error.h"

namespace sandista {

	Core::Core () : renderer(new Renderer()), assets(new Assets()) {

		
	}

	void Core::run () {
		while (true) {
			renderer->updateWindow();
		}
	}

	Core::~Core () {
		delete renderer;
	}

	Core* Core::_singleton = nullptr;

}