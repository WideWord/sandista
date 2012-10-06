#ifndef ERROR_H
#define ERROR_H

#include "config.h"

#include <list>
#include <string>

namespace sandista {

	struct Error {
		std::string type;
		std::string what;
	};

	class ErrorManager {
	private:
		static ErrorManager* _singleton;
		ErrorManager();
		std::list<Error> list;
	public:
		inline static ErrorManager* getSingleton() {
			if (_singleton == nullptr) _singleton = new ErrorManager();
			return _singleton;
		}

		void pushError(std::string type, std::string what);
		bool existError(std::string type);
		std::string getError(std::string type);


	};

};

#endif