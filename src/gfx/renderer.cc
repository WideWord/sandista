#include "renderer.h"
#include "../mesh.h"

#include "../math/mat4.h"


#include <GL/glew.h>
#ifdef SANDISTA_WINDOWS
#include <GL/wglew.h>
#endif
#ifdef SANDISTA_LINUX
#include <GL/glxew.h>
#endif
#define GLFW_NO_GLU
#include <GL/glfw.h>

#include <iostream>

namespace sandista {

	Renderer::Renderer (int w, int h, bool full) : maxTextureSize(_maxTextureSize) {
		
		int e;
		e = glfwInit();
		if (e != GL_TRUE) {
			ErrorManager::getSingleton()->
				pushError("s.renderer.init.glfwInit", "glfwInit" );
			return;
		}

		e = glfwOpenWindow(w, h, 8, 8, 8, 8, 16, 1, full?GLFW_FULLSCREEN:GLFW_WINDOW);
		if (e != GL_TRUE) {
			ErrorManager::getSingleton()->
				pushError("s.renderer.init.glfwOpenWindow", "glfwInit" );
			return;
		}

		e = glewInit();
		if (e != GLEW_OK) {
			ErrorManager::getSingleton()->
				pushError("s.renderer.init.glewInit", std::string( (char*)glewGetErrorString(e)) );
			return;
		}

	
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);

		glDrawBuffer(GL_BACK);

		glViewport(0,0,w,h);
		glShadeModel( GL_SMOOTH );
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth( 1.0f );
		glEnable( GL_DEPTH_TEST );
		glDepthFunc( GL_LEQUAL );
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); 
		glClearColor(1,0,0,1);
	}

	

	Renderer::~Renderer () {
		glfwTerminate();
	}

	void Renderer::updateWindow () {
		glfwSwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	

	void Renderer::drawSubMesh(SubMesh* subMesh) {
		subMesh->bind();
		GLuint shader = subMesh->material->shader;
		

		glDrawElements(GL_TRIANGLES, subMesh->inds * 3, GL_UNSIGNED_INT, 0);
	}


}