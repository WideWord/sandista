#include "texture2d.h"
#include "core.h"
#include "gfx/renderer.h"
#include "error.h"
#include <sstream>


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

	Texture2d::Texture2d (int w, int h) : id(_id), w(w), h(h) {
		Renderer* r = Core::getSingleton()->renderer;
		if (w > r->maxTextureSize) {
			std::stringstream ss;
			ss << "max size: " << r->maxTextureSize << "texture width: " << w;
			ErrorManager::getSingleton()->pushError("s.renderer.texture.create.size", ss.str());
			return;
		}
		if (h > r->maxTextureSize) {
			std::stringstream ss;
			ss << "max size: " << r->maxTextureSize << "texture height: " << h;
			ErrorManager::getSingleton()->pushError("s.renderer.texture.create.size", ss.str());
			return;
		}
		data = nullptr;
		baked = false;
		_id = -1;
	}

	Texture2d::~Texture2d () {
		if(baked) glDeleteTextures(1,&id);
		if(data != nullptr)delete data;
	}

	void Texture2d::setData (void* data, DataFormat f) {
		if (this->data != nullptr)delete this->data;
		this->data = new char[sizeof(char) * w * h * ((f==rgba||f==bgra)?4:3)];
		memcpy(this->data, data, sizeof(char) * w * h * ((f==rgba||f==bgra)?4:3));
		this->dataFormat = f;
		this->dataLen = sizeof(char) * w * h * (f==rgba||f==bgra)?4:3;
	}

	void Texture2d::bake () {
		if (baked) return;
		if (this->data == nullptr) return;
		
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


		bool usealpha;

		switch (dataFormat) {
		case rgb:
		case bgr:
			usealpha = false;
			break;
		case rgba:
		case bgra:
			usealpha = true;
			break;
		default:
			usealpha = true;
		}

		GLint internalFormat = usealpha?GL_RGB8 : GL_RGBA8;

		GLint format;
		switch (dataFormat) {
		 case bgr:
		 format = GL_BGR;
		 break;
		 case bgra:
		 format = GL_BGRA;
		 break;
		 case rgb:
		 format = GL_RGB;
		 break;
		 case rgba:
		 format = GL_RGBA;
		 break;
		 case f32:
		 internalFormat = GL_RGBA32F;
		 break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0,  internalFormat, w, h, 0, format,
                (dataFormat==f32)?GL_FLOAT:GL_UNSIGNED_BYTE, (const GLvoid*)(this->data));

		baked = true;
	}



}