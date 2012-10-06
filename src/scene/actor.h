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
		Actor(Scene* parent);
		std::list<Component*> list;
	public:
		Scene* const scene;

		template<class T> inline T* createComponent() {
			T* t = new T();
			if (dynamic_cast<Component*>(t) == nullptr) {
				delete t;
				return;
			}
			list.push_back(t);
		}
	};

}

#endif