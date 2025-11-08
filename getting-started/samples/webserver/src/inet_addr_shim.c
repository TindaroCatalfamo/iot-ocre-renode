#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

// WASI does not provide inet_addr, so we implement it using inet_aton
in_addr_t inet_addr(const char *cp) {
    struct in_addr inp;
    if (inet_aton(cp, &inp)) {
        return inp.s_addr;
    }
    return INADDR_NONE;
}