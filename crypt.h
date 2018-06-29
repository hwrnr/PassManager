#ifndef CRYPT_H_SAFEWORD
#define CRYPT_H_SAFEWORD

#include <string>
#include "sha512.h"

void crypt(std::string &, const std::string &key);


#endif
