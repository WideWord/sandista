#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>
#include <stdint.h>




#if _WIN32 || _WIN64
#if _WIN64
#define SANDISTA_ENV64
#else
#define SANDISTA_ENV32
#endif
#endif

#if __GNUC__
#if __x86_64__ || __ppc64__
#define SANDISTA_ENV64
#else
#define SANDISTA_ENV32
#endif
#endif


#if _WIN32 || _WIN64
#define SANDISTA_WINDOWS
#endif

#if __linux
#define SANDISTA_LINUX
#endif






#endif


