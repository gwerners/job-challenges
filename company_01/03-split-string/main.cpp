

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string.h>
#include <string>

#define CHECK(...)                                                             \
    if (!(__VA_ARGS__)) {                                                      \
        std::cerr << "\t\tfailed expression [" << #__VA_ARGS__ << "]"              \
                  << std::endl;                                                \
                  ret=false; \
    }

char**
stringSplit(const char* text, char separator, int* length)
{
    const char *begin, *end;
    int count = 0;
    if (!text) {
        return nullptr;
    }
    begin = end = text;
    do {
        if (*end == separator) {
            if (begin != end) {
                // token valido
                ++count;
            }
            ++end;
            begin = end;
        } else {
            if (*end) {
                ++end;
            }
        }
    } while (*end);
    // ultimo token caso exista
    if (begin != end) {
        ++count;
    }
    // descobriu o numero de tokens
    if (length) {
        *length = count;
    }
    if (count > 0) {
        // cria espaco para tokens
        char** ret = (char**)malloc(count * sizeof(char*));
        char** entry = ret;
        // preenche tokens
        begin = end = text;
        do {
            if (*end == separator) {
                if (begin != end) {
                    int len = end - begin;
                    *entry = (char*)malloc(len + 1);
                    strncpy(*entry, begin, end - begin);
                    (*entry)[len] = '\0';
                    ++entry;
                }
                ++end;
                begin = end;
            } else {
                if (*end) {
                    ++end;
                }
            }
        } while (*end);
        if (begin != end) {
            int len = end - begin;
            *entry = (char*)malloc(len + 1);
            strncpy(*entry, begin, end - begin);
            (*entry)[len] = '\0';
        }
        return ret;
    } else {
        return nullptr;
    }
}
bool
test(const char* text, const char* expectedString, int expectedLength)
{
    bool ret = true;
    int length = 0;
    char** root = stringSplit(text, '/', &length);
    char** entry = root;
    if (root == nullptr && !text) {
        return true;
    }
    std::cout << "\ttest " << text << " " << expectedLength << std::endl;
    if (length != expectedLength) {
        std::cerr << "\t\terror:length " << length << " expectedLength " << expectedLength
                  << std::endl;
        return false;
    }
    for (; length > 0; length--) {
        if (strcmp(expectedString, *entry) != 0) {
            std::cerr << "\t\terror:expectedString " << expectedString << " entry "
                      << *entry << std::endl;
            ret = false;
        }
        free(*entry);
        ++entry;
    }
    free(root);
    return ret;
}

bool
allTests()
{
  bool ret=true;
    CHECK(test(nullptr, nullptr, 0));
    CHECK(test("", "", 0));
    CHECK(test("/", "", 0));
    CHECK(test("//", "", 0));
    CHECK(test("///", "", 0));
    
    CHECK(test("bla", "bla", 1));
    CHECK(test("/bla", "bla", 1));
    CHECK(test("////////bla", "bla", 1));
    CHECK(test("bla/", "bla", 1));
    CHECK(test("bla////////", "bla", 1));

    CHECK(test("bla/bla", "bla", 2));
    CHECK(test("bla/bla/", "bla", 2));
    CHECK(test("/bla/bla", "bla", 2));
    CHECK(test("bla/bla//////", "bla", 2));
    CHECK(test("//////bla/bla", "bla", 2));

    CHECK(test("bla///bla", "bla", 2));
    CHECK(test("bla///bla/", "bla", 2));
    CHECK(test("/bla///bla", "bla", 2));
    CHECK(test("bla///bla//////", "bla", 2));
    CHECK(test("//////bla///bla", "bla", 2));
    return ret;
}
int
main(int argc, char** argv)
{
    const char* text = "tk1/tk2//tk3//tk4////";
    int length = 0;
    char** root = stringSplit(text, '/', &length);
    char** entry = root;
    std::cout << "number of tokens: " << length << std::endl;
    for (; length > 0; length--) {
        std::cout << "entry " << *entry << std::endl;
        free(*entry);
        ++entry;
    }
    free(root);

    if(allTests()){
      std::cout << "ALL tests passed with SUCESS" << std::endl;
    }else{
      std::cout << "Error found on one or more tests" << std::endl;
    }
    return 0;
}
