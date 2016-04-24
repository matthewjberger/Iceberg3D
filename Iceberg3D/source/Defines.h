#ifndef DEFINES_H
#define DEFINES_H

#if defined(ICEBERG_DLL) && defined(ICEBERG_BUILD_DLL)
/*!
* ICEBERG_DLL must be defined by applications that are linking against the DLL version of the Iceberg library.
* ICEBERG_BUILD_DLL is defined when compiling the DLL version of the library.
*/
#error "You may not have both ICEBERG_DLL and ICEBERG_BUILD_DLL defined"
#endif

/*!
* ICEBERGAPI is used to declare public API classes / functions for export from the DLL / shared library / dynamic library
*/
#if defined(_WIN32) && defined(ICEBERG_BUILD_DLL)
// We are building Iceberg as a Win32 DLL
#define ICEBERGAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(ICEBERG_DLL)
// We are calling Iceberg as a Win32 DLL
#define ICEBERGAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(ICEBERG_BUILD_DLL)
// We are building Iceberg as a shared / dynamic library
#define ICEBERGAPI __attribute__((visibility("default")))
#else
// We are building or calling Iceberg as a static library
#define ICEBERGAPI
#endif

#endif