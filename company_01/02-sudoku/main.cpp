
#include "jsmn/jsmn.h"
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string.h>
#include <string>

// options
int auto_test = 0;
int debug = 0;
int color = 0;
std::string jsonFilename;

#define IFDBG if (debug)

#define COLOR_START "\33["
#define COLOR_RED "31;49m"    /*RED*/
#define COLOR_GREEN "32;49m"  /*GREEN*/
#define COLOR_YELLOW "33;49m" /*YELLOW*/
#define COLOR_BLUE "34;49m"   /*BLUE*/
#define COLOR_PURPLE "35;49m" /*PURPLE*/
#define COLOR_CYAN "36;49m"   /*CYAN*/
#define COLOR_END "\33[m"

bool
isValidSquare(int _x, int _y, int tbl[9][9])
{
    int flags = 0;
    for (int y = _y; y < _y + 3; y++) {
        for (int x = _x; x < _x + 3; x++) {
            if (flags & (1 << tbl[y][x])) {
                std::cerr << "square test - failed value [" << tbl[y][x]
                          << "] at[" << y << "][" << x << "]" << std::endl;
                return false;
            } else {
                flags |= 1 << tbl[y][x];
            }
            IFDBG std::cout << tbl[y][x] << " ";
        }
        IFDBG std::cout << std::endl;
    }
    return true;
}
bool
validSudokuSquares(int tbl[9][9])
{
    for (int y = 0; y <= 6; y += 3) {
        for (int x = 0; x <= 6; x += 3) {
            if (!isValidSquare(x, y, tbl)) {
                return false;
            } else {
                IFDBG
                std::cout << "valid square" << std::endl;
            }
        }
    }
    return true;
}
bool
isValidVLine(int _y, int _x, int tbl[9][9])
{
    int flags = 0;
    for (int y = _y; y < 9; y++) {
        int x = _x;
        if (flags & (1 << tbl[y][x])) {
            std::cerr << "vertical line test - failed value [" << tbl[y][x]
                      << "] at[" << y << "][" << x << "]" << std::endl;
            return false;
        } else {
            flags |= 1 << tbl[y][x];
        }
        IFDBG std::cout << tbl[y][x] << " ";
    }
    IFDBG std::cout << std::endl;
    return true;
}
bool
isValidHLine(int _y, int _x, int tbl[9][9])
{
    int flags = 0;
    for (int x = _x; x < 9; x++) {
        int y = _y;
        if (flags & (1 << tbl[y][x])) {
            std::cerr << "horizontal line test - failed value [" << tbl[y][x]
                      << "] at[" << y << "][" << x << "]" << std::endl;
            return false;
        } else {
            flags |= 1 << tbl[y][x];
        }
        IFDBG std::cout << tbl[y][x] << " ";
    }
    IFDBG std::cout << std::endl;
    return true;
}
bool
validSudokuVerticalLines(int tbl[9][9])
{
    for (int x = 0; x < 9; x++) {
        int y = 0;
        if (!isValidVLine(y, x, tbl)) {
            return false;
        } else {
            IFDBG
            std::cout << "valid vertical line" << std::endl;
        }
    }
    return true;
}
bool
validSudokuHorizontalLines(int tbl[9][9])
{
    for (int y = 0; y < 9; y++) {
        int x = 0;
        if (!isValidHLine(y, x, tbl)) {
            return false;
        } else {
            IFDBG
            std::cout << "valid horizontal line" << std::endl;
        }
    }
    return true;
}
bool
validSudoku(int tbl[9][9])
{
    if (!validSudokuHorizontalLines(tbl)) {
        return false;
    }
    if (!validSudokuVerticalLines(tbl)) {
        return false;
    }
    if (!validSudokuSquares(tbl)) {
        return false;
    }
    return true;
}
void
usage()
{
    std::cout << "Usage: program [option]\n"
              << "\t-h --help\t\t\t:show this message\n"
              << "\t-d --debug\t\t\t:enable debug information\n"
              << "\t-j <filename> --json <filename>\t:load json with sudoku\n"
              << "\t-t\t\t\t\t:run embedded sudoku validation test\n"
              << "\t-c\t\t\t\t:enable color output\n"
              << std::flush;
}
bool
validateFilename(const char* name)
{
    int pos, len;
    if (!name) {
        return false;
    }
    for (pos = 0, len = strlen(name); pos < len; pos++) {
        if (!isalnum(name[pos]) && name[pos] != '.' && name[pos] != '_' &&
            name[pos] != '-') {
            return false;
        }
    }
    return true;
}
bool
parseCommandLine(int argc, char** argv)
{
    bool ok;
    int pos = 1;
    if (argc < 2) {
        return false;
    }
    while (pos <= argc) {
        if (argv[pos]) {
            IFDBG std::cout << "pos " << pos << ":" << argc << " [" << argv[pos]
                            << "]" << std::endl;
            if (std::string("-h") == argv[pos] ||
                std::string("--help") == argv[pos]) {
                IFDBG std::cout << "Found help option" << std::endl;
                usage();
                exit(0);
            }
            if (std::string("-d") == argv[pos] ||
                std::string("--debug") == argv[pos]) {
                IFDBG std::cout << "Found debug option" << std::endl;
                debug = 1;
            }
            if (std::string("-j") == argv[pos] ||
                std::string("--json") == argv[pos]) {
                IFDBG std::cout << "Found json option" << std::endl;
                if (pos < argc - 1) {
                    ++pos;
                    ok = validateFilename(argv[pos]);
                    if (ok) {
                        jsonFilename = argv[pos];
                        IFDBG
                        std::cout << "Json filename [" << jsonFilename << "]"
                                  << std::endl;
                    } else {
                        std::cerr << "Invalid son filename [" << argv[pos]
                                  << "]" << std::endl;
                    }
                } else {
                    std::cerr << "Unable to find json filename in command line!"
                              << std::endl;
                }
            }
            if (std::string("-t") == argv[pos]) {
                IFDBG std::cout << "Found test option" << std::endl;
                auto_test = 1;
            }
            if (std::string("-c") == argv[pos]) {
                IFDBG std::cout << "Found color option" << std::endl;
                color = 1;
            }
        } else {
            IFDBG std::cout << "pos [null]" << std::endl;
        }
        ++pos;
    }
    return true;
}
static int
jsoneq(const char* json, jsmntok_t* tok, const char* s)
{
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
        strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}
bool
loadJson(const std::string& filename, int* sudoku)
{
    std::ifstream fileStream(filename);
    std::string json((std::istreambuf_iterator<char>(fileStream)),
                     std::istreambuf_iterator<char>());
    int r, i, pos = 0;
    jsmn_parser p;
    jsmntok_t t[128]; /* We expect no more than 128 tokens */

    jsmn_init(&p);
    r =
      jsmn_parse(&p, json.c_str(), json.length(), t, sizeof(t) / sizeof(t[0]));
    if (r < 0) {
        std::cerr << "Failed to parse JSON: " << r << std::endl;
        return false;
    }

    /* Assume the top-level element is an object */
    if (r < 1 || t[0].type != JSMN_OBJECT) {
        std::cerr << "Object expected\n";
        return false;
    }
    for (i = 1; i < r; i++) {
        if (jsoneq(json.c_str(), &t[i], "sudoku") == 0) {
            int j;
            if (t[i + 1].type != JSMN_ARRAY) {
                continue; /* We expect sudoku to be an array of integers */
            }
            for (j = 0; j < t[i + 1].size; j++) {
                jsmntok_t* g = &t[i + j + 2];
                std::string token(json.c_str() + g->start, g->end - g->start);
                if (!isdigit(token[0])) {
                    std::cerr << "invalid digit in sudoku array\n";
                    exit(1);
                }
                sudoku[pos] = atoi(token.c_str());
                if (sudoku[pos] > 9 || sudoku[pos] < 1) {
                    std::cerr << "Digit[" << sudoku[pos]
                              << "] out of range in sudoku array\n";
                    exit(1);
                }
                ++pos;
            }
            i += t[i + 1].size + 1;
        } else {
            std::string token(json.c_str() + t[i].start, t[i].end - t[i].start);
            std::cerr << "Unexpected key:" << token << std::endl;
            ;
        }
    }
    return true;
}
int
main(int argc, char** argv)
{
    bool ok = parseCommandLine(argc, argv);
    if (!ok) {
        usage();
        return 1;
    }
    if (auto_test) {
        int sudoku[9][9] = {
            { 5, 3, 4, 6, 7, 8, 9, 1, 2 }, { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
            { 1, 9, 8, 3, 4, 2, 5, 6, 7 }, { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
            { 4, 2, 6, 8, 5, 3, 7, 9, 1 }, { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
            { 9, 6, 1, 5, 3, 7, 2, 8, 4 }, { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
            { 3, 4, 5, 2, 8, 6, 1, 7, 9 }

        };
        if (validSudoku(sudoku)) {
            if (color) {
                std::cout << "<" << COLOR_START COLOR_GREEN "Valid" COLOR_END
                          << " sudoku found>" << std::endl;
            } else {
                std::cout << "<Valid sudoku found>" << std::endl;
            }
        } else {
            if (color) {
                std::cout << "<" << COLOR_START COLOR_RED "Invalid" COLOR_END
                          << " sudoku found>" << std::endl;
            } else {
                std::cout << "<Invalid sudoku found>" << std::endl;
            }
        }
    }
    if (!jsonFilename.empty()) {
        std::cout << "Loading json from file [" << jsonFilename << "]"
                  << std::endl;
        int sudoku[9][9];
        memset(&sudoku, 0, sizeof(int) * 9 * 9);
        ok = loadJson(jsonFilename, reinterpret_cast<int*>(&sudoku[0]));
        if (ok && validSudoku(sudoku)) {
            if (color) {
                std::cout << "<" << COLOR_START COLOR_GREEN "Valid" COLOR_END
                          << " sudoku found>" << std::endl;
            } else {
                std::cout << "<Valid sudoku found>" << std::endl;
            }
        } else {
            if (color) {
                std::cout << "<" << COLOR_START COLOR_RED "Invalid" COLOR_END
                          << " sudoku found>" << std::endl;
            } else {
                std::cout << "<Invalid sudoku found>" << std::endl;
            }
        }
    }
    return 0;
}
