#include "error.h"
#include <iostream>

namespace sandista {

	ErrorManager::ErrorManager () {
		
	}

	void ErrorManager::pushError(std::string type, std::string what) {
		Error err;
		err.type = type;
		err.what = what;
		list.push_back(err);
		std::cerr << type << " : " << what << std::endl;
	}

	bool ErrorManager::existError(std::string type) {
		size_t len = type.length();
		for (auto it = list.begin(); it != list.end(); ++it) {
			std::string t = (*it).type;
			if (t.length() < len)continue;
			if(t.substr(0, len).compare(type) == 0) {
				if (t.length() == len) return true;
				if (t.at(len) == '.') return true;
			}
		}
		return false;
	}

	std::string ErrorManager::getError(std::string type) {
		size_t len = type.length();
		for (auto it = list.begin(); it != list.end(); ++it) {
			std::string t = (*it).type;
			if (t.length() < len)continue;
			if(t.substr(0, len).compare(type) == 0) {
				if (t.length() == len) {
					std::string res = (*it).what;
					list.erase(it);
					return res;
				}
				if (t.at(len) == '.') {
					std::string res = (*it).what;
					list.erase(it);
					return res;
				}
			}
		}
		return std::string("");
	}

	ErrorManager* ErrorManager::_singleton = nullptr;

}