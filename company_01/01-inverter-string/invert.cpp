#include "invert.h"
#include <string.h>

void
invertString(char* string)
{
    char save;
    size_t len, index = 0;
    size_t total;
    if (!string || !string[0]) {
        return;
    }
    len = strlen(string) - 1;
    total = len / 2;
    do {
        save = string[index];
        string[index++] = string[len];
        string[len--] = save;
    } while (index <= total);
}
void
invert_01(const char* in, char* out)
{
    size_t len = strlen(in) - 1, index = 0;
    size_t total = len;
    if (!in || !out) {
        return;
    }
    do {
        out[index++] = in[len--];
    } while (index <= total);
    out[index] = '\0';
}
void
invert_01_with_size(const char* in, size_t len, char* out)
{
    size_t index = 0;
    size_t total = len;
    if (!in || !out) {
        return;
    }
    do {
        out[index++] = in[len--];
    } while (index <= total);
    out[index] = '\0';
}
void
invert_append(const char* in, std::string& out)
{
    int len;
    if (!out.empty()) {
        out.clear();
    }
    for (len = strlen(in) - 1; len >= 0; len--) {
        out += in[len];
    }
}
void
invert_reverse_iterator(std::string& in, std::string& out)
{
    if (!out.empty()) {
        out.clear();
    }
    std::copy(
      in.rbegin(), in.rend(), std::back_insert_iterator<std::string>(out));
}
