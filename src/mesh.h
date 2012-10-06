#ifndef MESH_H
#define MESH_H

#include "config.h"
#include <memory>
#include "material.h"
#include <list>


namespace sandista {

	class Renderer;
	class Mesh;


	
	class SubMesh {
	protected:
		friend class Renderer;
		friend class Mesh;
		unsigned vao;
		int verts;
		struct attribList {std::string name; unsigned vbo; int vsize; float* val;};
		std::list<attribList> attribs;
		unsigned indexvbo;
		int inds;
		unsigned* index;
	private:
		bool baked;
		
	public:
		SubMesh(std::shared_ptr<Material> material, int verts, int inds);
		void addAtrib(std::string name, int vsize, float* val);
		void setIndexAttrib(unsigned* index);
		
		std::shared_ptr<Material> material;
		void bake();
		void bind();
		
	};

	class Mesh {
	private:
		

	};

}

#endif