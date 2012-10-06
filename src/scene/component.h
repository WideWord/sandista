#ifndef COMPONENT_H
#define COMPONENT_H

#include "../config.h"

namespace sandista {

	class Actor;

	class Component {
	protected:
		inline Component(Actor* parent) : actor(parent) {}
	public:
		Actor* const actor;
	};

}

#endif