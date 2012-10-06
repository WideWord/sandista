#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "config.h"

namespace sandista {

	class Texture2d {
	public:
		enum DataFormat {
			rgb,
			rgba,
			bgr,
			bgra,
			f32
		};
		
		

	private:
		unsigned _id; /// OpenGL texture id
		size_t dataLen;
		DataFormat dataFormat;
		void* data;
		bool baked;
	public:

		
		void setData(void* data, DataFormat dataFormat); /// set texture image, call before bake(); 
		void bake(); /// creating OpenGL texture, call only in OpenGL thread

		Texture2d (int w, int h);
		~Texture2d();

		const unsigned& id; /// readonly OpenGL texture id
		const int w; /// readonly width of texture
		const int h; /// readonly height of texture
	};


	
}

#endif