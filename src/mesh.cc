#include "mesh.h"

#include <GL/glew.h>
#ifdef SANDISTA_WINDOWS
#include <GL/wglew.h>
#endif
#ifdef SANDISTA_LINUX
#include <GL/glxew.h>
#endif
#define GLFW_NO_GLU
#include <GL/glfw.h>

namespace sandista {

	SubMesh::SubMesh(std::shared_ptr<Material> material, int verts, int inds) 
		: material(material), verts(verts), inds(inds) {
		baked = false;
		index = new unsigned[inds * 3];	
	}

	void SubMesh::addAtrib(std::string name, int vsize, float* val) {
		if (baked) return;
		attribList attr;
		attr.name = name;
		attr.val = new float[vsize * verts];
		memcpy(attr.val, val, sizeof(float) * vsize * verts);
		attr.vsize = vsize;
		attribs.push_back(attr);
	}

	void SubMesh::setIndexAttrib(unsigned* index) {
		if (baked) return;
		memcpy(this->index, index, sizeof(unsigned) * inds * 3);
	}

	void SubMesh::bake () {
		if (baked) return;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &indexvbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexvbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds * sizeof(unsigned) * 3, index, GL_STATIC_DRAW);

		for (auto attr = attribs.begin(); attr != attribs.end(); ++attr) {
			GLuint vbo;
			glGenBuffers(1, &vbo);
			attr->vbo = vbo;
			glBindBuffer(GL_ARRAY_BUFFER, attr->vbo);
			glBufferData(GL_ARRAY_BUFFER, verts * sizeof(float) * attr->vsize, attr->val, GL_STATIC_DRAW);
		}

		baked = true;

	}

	void SubMesh::bind () {
		if (!baked) bake();

		material->bind();

		glBindVertexArray(vao);

		for (auto attr = attribs.begin(); attr != attribs.end(); ++attr) {
			glBindBuffer(GL_ARRAY_BUFFER, attr->vbo);
			GLint loc = glGetAttribLocation(material->shader, attr->name.c_str());
			if (loc != -1) {
				glVertexAttribPointer(loc, attr->vsize, GL_FLOAT, GL_FALSE, attr->vsize * sizeof(float), 0);
				glEnableVertexAttribArray(loc);
			}
		}

	}

};