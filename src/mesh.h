#ifndef MESH_H
#define MESH_H

#include "config.h"


namespace sandista {

	class Renderer;
	class Mesh;



	class SubMesh {
	protected:
		friend class Renderer;
		friend class Mesh;
		int vbo[4], vao;
		
	};

	class Mesh {
	private:
		

	};

}

#endif