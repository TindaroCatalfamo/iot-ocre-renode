#ifndef INET_ADDR_SHIM_H
#define INET_ADDR_SHIM_H

#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

in_addr_t inet_addr(const char *cp);

#ifdef __cplusplus
}
#endif

#endif // INET_ADDR_SHIM_H