#include "material.h"
#include "error.h"

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

	Material::Material(std::string fragDefines, std::string fragCode, ErrorManager* em) : shader(_shader) {
		if (em == nullptr)em = ErrorManager::getSingleton();

		const char* vs = "#version 330 core\n\
			uniform mat4 std_m;\n\
			uniform mat4 std_vp;\n\
			in vec3 std_position;\n\
			in vec3 std_normal;\n\
			in vec2 std_texture_coord;\n\
			out vec2 _o_uv;\n\
			out vec3 _o_position;\n\
			out vec3 _o_normal;\n\
			\n\
			void main(void){\n\
			\n\
				vec4 vertex = std_m * vec4(std_position, 1);\n\
				_o_position = vec3(vertex);\n\
				_o_normal = mat3(std_m) * std_normal;\n\
				_o_uv = std_texture_coord;\n\
				gl_Position = std_vp * vertex;\n\
			}";

		std::string fs("#version 330 core\n\
			out vec4 _color;\n\
			in vec2 _o_uv;\n\
			in vec3 _o_position;\n\
			in vec3 _o_normal;\n\
			uniform int std_pointlight_num;\n\
			struct pointlightstruct {\n\
				vec3 position;\n\
				vec3 color;\n\
				float radius;\n\
				vec3 attenuation;\n\
			};\n\
			uniform pointlightstruct std_pointlight[16];\n\
			uniform vec3 std_viewposition;\n");

		fs += fragDefines;
		fs += "\n void main(void){\
			\n\
			vec2 _uv = _o_uv;\n\
			vec3 _position = _o_position;\n\
			vec3 _normal = _o_normal;\n";

		fs += fragCode;

		fs += "vec3 lightColor = vec3(0,0,0);\n\
			\n\
			for (int _i = 0; _i < std_pointlight_num; ++_i) {\n\
			vec3 _lDir = std_pointlight[_i].position - _position;\n\
			float _distance = length(_lDir);\n\
			float _attenuation = std_pointlight[_i].radius / (std_pointlight[_i].attenuation[0] + std_pointlight[_i].attenuation[1] * _distance + std_pointlight[_i].attenuation[2] * _distance * _distance);\n\
			\n\
			lightColor += std_pointlight[_i].color * max(0, dot(normalize(_lDir), normalize(_normal))) * _attenuation;\n\
			}\n\
			\n\
			_color *= vec4(lightColor,1);\n\
			}";

		_shader = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		size_t len = strlen(vs);
		glShaderSource(vertex, 1, (const GLchar**)&vs, (const GLint*)&len);
		glCompileShader(vertex);
		GLint status;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLsizei len;
			char buffer[1024];
			glGetShaderInfoLog(vertex, 1024, &len, buffer);
			em->pushError("s.material.create.shader.vertex.compilation", buffer); 
			return;
		}

		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		len = fs.length();
		const char* fs_c = fs.c_str();
		glShaderSource(fragment, 1, (const GLchar**)&fs_c, (const GLint*)&len);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLsizei len;
			char buffer[1024];
			glGetShaderInfoLog(fragment, 1024, &len, buffer);
			em->pushError("s.material.create.shader.fragment.compilation", buffer); 
			return;
		}

		glAttachShader(shader, vertex);
		glAttachShader(shader, fragment);
		glLinkProgram(shader);

		glGetProgramiv(shader, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLsizei len;
			char buffer[1024];
			glGetProgramInfoLog(shader, 1024, &len, buffer);
			em->pushError("s.material.create.shader.linking", buffer); 
			return;
		}

		glUseProgram(shader);
		glValidateProgram(shader);
    
		glGetProgramiv(shader, GL_VALIDATE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLsizei len;
			char buffer[1024];
			glGetProgramInfoLog(shader, 1024, &len, buffer);
			em->pushError("s.material.create.shader.validation", buffer); 
			return;
		}
		
	}

	Material::~Material () {
		for (auto p : params) {
			if (p.type == Param::Texture2d_p) {
				delete p.data.Texture2d_d;
			} else if (p.type == Param::vec3_p) {
				delete p.data.vec3_d;
			}
		}
	}

	void Material::addParam(std::string name, std::shared_ptr<Texture2d> param) {
		for (auto p : params) {
			if (p.name.compare(name) == 0) return;
		}
		Param p;
		p.name = name;
		p.type = Param::Texture2d_p;
		p.data.Texture2d_d = new std::shared_ptr<Texture2d>(param);
		params.push_back(p);
	}

	void Material::addParam(std::string name, vec3 param) {
		for (auto p : params) {
			if (p.name.compare(name) == 0) return;
		}
		Param p;
		p.name = name;
		p.type = Param::vec3_p;
		p.data.vec3_d = new vec3(param);
		params.push_back(p);
	}

	void Material::addParam(std::string name, float param) {
		for (auto p : params) {
			if (p.name.compare(name) == 0) return;
		}
		Param p;
		p.name = name;
		p.type = Param::float_p;
		p.data.float_d = param;
		params.push_back(p);
	}

}