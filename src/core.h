#ifndef CORE_H
#define CORE_H

#include "config.h"

namespace sandista {

	class Renderer;
	class Assets;

	class Core {
	private:
		Core();
		static Core* _singleton;
	public:
		inline static Core* getSingleton() {
			if (_singleton == nullptr) _singleton = new Core();
			return _singleton;
		}
		~Core();

		Renderer* const renderer;
		Assets* const assets;

		void run();
	};

}

#endif