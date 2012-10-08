#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include "../math/vec3.h"
#include "../math/quat.h"


namespace sandista {

	class Transform : public Component {
	public:
		Transform (Actor* actor);
		
		vec3 position;
		quat rotation;
	};

}

#endif