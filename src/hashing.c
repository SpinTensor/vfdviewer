#include <stdint.h>
#include <stdlib.h>

// jenkins 32bit hash implementation
// Taken unchanged from wikipedia
//    (https://en.wikipedia.org/wiki/Jenkins_hash_function)
// Published on wikipedia under the creative commons licence
//    (https://creativecommons.org/licenses/by-sa/3.0/)
uint32_t jenkins_32_hash(size_t length, const uint8_t* key) {
  uint32_t hash = 0;
  for (size_t i=0; i < length; i++) {
    hash += key[i];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

