//
// Created by fedelonghi on 08/11/17.
//

#ifndef PROYECTO2_UTILS_H
#define PROYECTO2_UTILS_H

#include <cstring>

#define EXIT(){\
  std::cout << "error en " << __LINE__ << ": " << strerror(errno) << '\n';\
  exit(1);\
}

#endif //PROYECTO2_UTILS_H
