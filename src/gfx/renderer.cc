#include "renderer.h"


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


	}

	

	Renderer::~Renderer () {
		glfwTerminate();
	}

	void Renderer::updateWindow () {
		glfwSwapBuffers();
	}


}