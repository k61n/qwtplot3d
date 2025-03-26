#ifndef QWT3D_GLOBAL_H
#define QWT3D_GLOBAL_H

#include <QtOpenGL>

#include <qglobal.h>

#define QWT3D_MAJOR_VERSION 0
#define QWT3D_MINOR_VERSION 3
#define QWT3D_PATCH_VERSION 0

#if defined(_MSC_VER) && defined(QWT3D_MAKEDLL)
#define QWT3D_EXPORT  __declspec(dllexport)
#elif defined(_MSC_VER)
#define QWT3D_EXPORT  __declspec(dllimport)
#else
#define QWT3D_EXPORT
#endif

#endif
