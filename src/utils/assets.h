#ifndef ASSETS_H
#define ASSETS_H


#include "../config.h"
#include "../texture2d.h"
#include <memory>
#include <string>
#include <list>

namespace sandista {
	
	struct texturePair {
		std::string name;
		std::weak_ptr<Texture2d> ptr;
	};

	class Assets {
	private:
		std::list<texturePair> textures;
    public:
        std::shared_ptr<Texture2d> getTexture2d(std::string name);
		inline std::shared_ptr<Texture2d> getTexture2d(const char* name) {
			return getTexture2d(std::string(name));
		}
    
    private:
    };

}

#endif