/////////////////////////////////////////////////////////////////////////////
// Utils.h
/////////////////////////////////////////////////////////////////////////////

#ifndef UTILS_H_
#define UTILS_H_

/////////////////////////////////////////////////////////////////////////////
// Macros
/////////////////////////////////////////////////////////////////////////////

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// Macro for removing unreferenced arguments from compiler warnings
#ifndef UNREFERENCED_ARGUMENT
#define UNREFERENCED_ARGUMENT(arg) (0, arg)
#endif

#endif /* UTILS_H_ */