#ifndef HASHING_H
#define HASHING_H

#include <stdint.h>
#include <stdlib.h>


uint32_t jenkins_32_hash(size_t length, const uint8_t* key);

#endif
