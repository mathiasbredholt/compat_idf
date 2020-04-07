#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>

#include "compat.h"

int getnameinfo(const struct sockaddr *addr, socklen_t addrlen, char *host,
                socklen_t hostlen, char *serv, socklen_t servlen, int flag) {
  if (flag & ~(NI_NUMERICHOST | NI_NUMERICSERV)) {
    return EAI_BADFLAGS;
  }

  const struct sockaddr_in *sinp = (const struct sockaddr_in *)addr;

  if (addr->sa_family == AF_INET) {
    if (flag & NI_NUMERICHOST) {
      if (inet_ntop(AF_INET, &sinp->sin_addr, host, hostlen) == NULL) {
        return EAI_OVERFLOW;
      }
    }
    if (flag & NI_NUMERICSERV) {
      if (snprintf(serv, servlen, "%d", ntohs(sinp->sin_port)) < 0) {
        return EAI_OVERFLOW;
      }
    }
  } else {
    return EAI_FAMILY;
  }
  return 0;
}
