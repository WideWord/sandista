#include "component.h"
#include "actor.h"

namespace sandista {

	Component::Component(Actor* parent) : actor(parent) {
		actor->list.push_back(this);
	}

	Component::~Component() {	

	}

}