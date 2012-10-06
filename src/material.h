#ifndef MATERIAL_H
#define MATERIAL_H

#include "config.h"
#include <string>
#include <list>
#include <memory>
#include "math/vec3.h"


namespace sandista {

	class ErrorManager;
	class Texture2d;
	

	class Material {
	
	private:
		struct Param {
			std::string name;
			enum {
				Texture2d_p,
				vec3_p,
				float_p
			} type;
			union {
				std::shared_ptr<Texture2d>* Texture2d_d;
				vec3* vec3_d;
				float float_d;
			} data;
		};

		std::list<Param> params;

		unsigned _shader;
	public:
		const unsigned& shader;

		Material(std::string fragDefines, std::string fragCode, ErrorManager* errorManager = nullptr);
		~Material();

		void addParam(std::string name, std::shared_ptr<Texture2d> param);
		void addParam(std::string name, vec3 param);
		void addParam(std::string name, float param);
	};

}

#endif