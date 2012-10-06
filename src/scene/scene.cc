#include "actor.h"
#include "scene.h"

namespace sandista {

	Scene::Scene () {

	}

	Actor* Scene::createActor () {
		Actor* res = new Actor(this);
		actors.push_back(res);
		return res;
	}

}