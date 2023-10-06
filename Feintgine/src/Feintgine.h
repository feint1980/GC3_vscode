#ifdef F_DEBUGMODE 
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define FLOG(log) std::cout << "!!!FLOG : " << log << " in line " << __LINE__ << " in file " << __FILE__ << " !!!\n";
#else
#define FLOG(log)
#endif

#ifdef _WIN32

#elif __linux__ 

#define _snprintf_s(a,b,c,...) snprintf(a,b,__VA_ARGS__)

#endif


#ifndef _FEINTGINE_H_
#define _FEINTGINE_H_
namespace Feintgine
{

	extern int initFeint();

}

#endif
