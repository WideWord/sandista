#ifndef COMPONENT_H
#define COMPONENT_H

#include "../config.h"

namespace sandista {

	class Actor;

	class Component {
	protected:
		Component(Actor* parent);
		virtual ~Component ();
	public:
		Actor* const actor;
	};

}

#endif