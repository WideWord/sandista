#ifndef ACTOR_H
#define ACTOR_H

#include "../config.h"
#include "component.h"
#include <list>

namespace sandista {

	class Component;
	class Scene;

	class Actor {
	protected:
		friend class Scene;
		friend class Component;
		Actor(Scene* parent);
		std::list<Component*> list;
	public:
		Scene* const scene;

		
	};

}

#endif