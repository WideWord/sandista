#ifndef RENDERER_H
#define RENDERER_H

#include "../config.h"
#include "../error.h"
#include <string>


namespace sandista {


	class SubMesh;

	class Renderer {
	private:
		int _maxTextureSize;
	public:
		Renderer(int w = 800, int h = 600, bool fullscreen = false);
		~Renderer();

		void updateWindow();
		void drawSubMesh(SubMesh* subMesh);

		const int& maxTextureSize;
	};

}

#endif