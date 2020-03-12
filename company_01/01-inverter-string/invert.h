#ifndef IMPLEMENTATION_TST
#define IMPLEMENTATION_TST

#include <string>

// habilitar debug caso queira verificar se o resultado da função está correto.
const int debug = 0;
#define IFDBG if (debug)

void
invertString(char* string);

// criados para comparar tempo:
void
invert_01(const char* in, char* out);
void
invert_01_with_size(const char* in, size_t len, char* out);
void
invert_append(const char* in, std::string& out);
void
invert_reverse_iterator(std::string& in, std::string& out);

#endif
