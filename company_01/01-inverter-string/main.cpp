#include <algorithm>
#include <benchmark/benchmark.h>
#include <iostream>
#include <iterator>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>

#include "invert.h"

static const char* in =
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
  "tempor incididunt ut labore et dolore magna aliqua.";
static const char* in_inverted =
  ".auqila angam erolod te erobal tu tnudidicni ropmet domsuie od des ,tile "
  "gnicsipida rutetcesnoc ,tema tis rolod muspi meroL";

static void
BM_invertString(benchmark::State& state)
{
    int counter = 0;
    char out[125];
    strcpy(&out[0], in);
    for (auto _ : state) {
        invertString(&out[0]);
    }
    IFDBG
    {
        if (counter % 2) {
            if (strcmp(out, in_inverted) != 0) {
                printf("failed to invert string in [%s]\n", __FUNCTION__);
                printf("[%s]\n", out);
            }
        } else {
            if (strcmp(out, in) != 0) {
                printf("failed to invert string in [%s]\n", __FUNCTION__);
                printf("[%s]\n", out);
            }
        }
    }
}
BENCHMARK(BM_invertString);

static void
BM_c_invert(benchmark::State& state)
{
    char out[125];
    for (auto _ : state) {
        invert_01(in, &out[0]);
    }
    IFDBG
    {
        if (strcmp(out, in_inverted) != 0) {
            printf("failed to invert string in [%s]\n", __FUNCTION__);
            printf("[%s]\n", out);
        }
    }
}
BENCHMARK(BM_c_invert);

static void
BM_c_invert_with_size(benchmark::State& state)
{

    char out[125];
    size_t len = strlen(in) - 1;
    for (auto _ : state) {
        invert_01_with_size(in, len, &out[0]);
    }
    IFDBG
    {
        if (strcmp(out, in_inverted) != 0) {
            printf("failed to invert string in [%s]\n", __FUNCTION__);
            printf("[%s]\n", out);
        }
    }
}
BENCHMARK(BM_c_invert_with_size);

static void
BM_cpp_invert_append(benchmark::State& state)
{

    std::string out;
    // out.resize(strlen(in)+1);
    for (auto _ : state) {
        invert_append(in, out);
    }
    IFDBG
    {
        if (out != std::string(in_inverted)) {
            std::cout << "failed to invert string in [" << __FUNCTION__ << "]"
                      << std::endl;
            std::cout << out << std::endl;
        }
    }
}
BENCHMARK(BM_cpp_invert_append);

static void
BM_cpp_invert_reverse_iterator(benchmark::State& state)
{
    std::string _in(in);
    std::string out("");
    for (auto _ : state) {
        invert_reverse_iterator(_in, out);
    }
    IFDBG
    {
        if (out != std::string(in_inverted)) {
            std::cout << "failed to invert string in [" << __FUNCTION__ << "]"
                      << std::endl;
            std::cout << out << std::endl;
        }
    }
}
BENCHMARK(BM_cpp_invert_reverse_iterator);
BENCHMARK_MAIN();
