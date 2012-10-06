#ifndef SCENE_H
#define SCENE_H

#include "../config.h"
#include <list>

namespace sandista {

	class Actor;

	class Scene {
	private:
		std::list<Actor*> actors;
	public:
		Scene();
		~Scene();
		
		Actor* createActor();
		
	};

}

#endif