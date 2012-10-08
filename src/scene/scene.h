#ifndef SCENE_H
#define SCENE_H

#include "../config.h"
#include <list>

namespace sandista {

	class Actor;
	class Renderer;


	class Scene {
	private:
		std::list<Actor*> actors;
	public:
		Scene();
		~Scene();

		void render(Renderer* renderer);
		
		Actor* createActor();

		
	};


}

#endif