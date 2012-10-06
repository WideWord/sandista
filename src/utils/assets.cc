#include "assets.h"
#include "stb_image.h"

namespace sandista {

	std::shared_ptr<Texture2d> Assets::getTexture2d(std::string name) {
		auto end = textures.end();
		for (auto it = textures.begin(); it != end; ++it) {
			if (it->name.compare(name) == 0) {
				if (it->ptr.expired()) {
					textures.erase(it);
					break;
				} else {
					return std::shared_ptr<Texture2d>(it->ptr);
				}
			}
		}


		int x, y, comp;
		stbi_uc* uc = stbi_load(name.c_str(), &x, &y, &comp, STBI_default);

		Texture2d::DataFormat format;

		if (comp == STBI_rgb) format = Texture2d::DataFormat::rgb;
		if (comp == STBI_rgb_alpha) format = Texture2d::DataFormat::rgba;

		std::shared_ptr<Texture2d> res = std::make_shared<Texture2d>(x, y);

		res->setData(uc, format);
		stbi_image_free(uc);

		texturePair p;
		p.name = name;
		p.ptr = std::weak_ptr<Texture2d>(res);
		textures.push_back(p);

		return res;
	}

}