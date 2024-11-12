#pragma once

#ifndef CURVES_USE_ASSERTIONS //define it to use <assert.h> (ONLY DEBUG) instead of exceptions
    #include <stdexcept>    
#endif

#if !defined(NDEBUG) || defined(_DEBUG) 
    #include <assert.h>
    #define CURVES_ASSERT(exp, msg) assert((exp) && (msg))
    #define _CURVES_DEBUG
#else
    #define CURVES_ASSERT(exp, msg) (void(0))
#endif


#if defined( CURVES_STATIC_LINK )
	#define CURVES_API
	#define CURVES_API_EXPORT
#elif defined( CURVES_FOREXPORT ) && defined( _WIN32) && defined( _MSC_VER )
	#define CURVES_API  __declspec( dllexport )
	#define CURVES_API_EXPORT __declspec( dllexport )
#elif defined( CURVES_FOREXPORT ) && !defined( _WIN32 )
	#define CURVES_API __attribute__((visibility("default")))
	#define CURVES_API_EXPORT
#elif !defined( CURVES_FOREXPORT ) && defined( _MSC_VER ) 
	#define CURVES_API __declspec( dllimport )
	#define CURVES_API_EXPORT __declspec( dllexport )
#else 
	#define CURVES_API
	#define CURVES_API_EXPORT
#endif

#define CURVES_EXTERN_C extern "C" CURVES_API