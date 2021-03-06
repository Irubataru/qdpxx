#ifndef QDP_CONFIG_H
#define QDP_CONFIG_H


/* Undef the unwanted from the environment -- eg the compiler command line */
#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef VERSION

/* Include the stuff generated by autoconf */
#include "qdp_config_internal.h"

namespace QDP {

/* Prefix everything with QDP_ */
static const char* const QDP_PACKAGE(PACKAGE);
static const char* const QDP_PACKAGE_BUGREPORT(PACKAGE_BUGREPORT);
static const char* const QDP_PACKAGE_NAME(PACKAGE_NAME);
static const char* const QDP_PACKAGE_STRING(PACKAGE_STRING);
static const char* const QDP_PACKAGE_TARNAME(PACKAGE_TARNAME);
static const char* const QDP_PACKAGE_VERSION(PACKAGE_VERSION);
static const char* const QDP_VERSION(VERSION);

} // namespace QDP 


/* Undef the unwanted */
#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef VERSION
#endif
