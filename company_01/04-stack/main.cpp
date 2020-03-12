

#include <fstream>
#include <iostream>
#include <limits.h>
#include <streambuf>
#include <string.h>
#include <string>

struct element
{
    int data; // um valor exemplo para testes
    struct element* next;
};
struct stack
{
    struct element* root;
};

typedef struct stack Stack;
Stack*
stackNew(void);
void
stackFree(Stack* p);
void
stackPush(Stack* p, int data);
int
stackPop(Stack* p);
int
stackEmpty(Stack* p);

void
stackRemoveEven(Stack* p);

Stack*
stackNew()
{
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    ret->root = nullptr;
    return ret;
}
void
stackFree(Stack* p)
{
    if (p) {
        element* entry = p->root;
        element* tmp;
        while (entry) {
            tmp = entry;
            std::cout << "free " << entry->data << std::endl;
            entry = entry->next;
            free(tmp);
        }
        free(p);
    }
}
void
stackPush(Stack* p, int data)
{
    if (p) {
        element* entry = (element*)malloc(sizeof(element));
        entry->data = data;
        entry->next = nullptr;
        if (p->root) {
            entry->next = p->root;
        }
        p->root = entry;
    }
}
int
stackPop(Stack* p)
{
    element* entry;
    int data = INT_MAX; // representando valor nao encontrado
    if (p && p->root) {
        entry = p->root;
        data = p->root->data;
        p->root = p->root->next;
        free(entry);
    }
    return data;
}
int
stackEmpty(Stack* p)
{
    if (p && p->root) {
        return 0;
    } else {
        return 1;
    }
}
void
stackRemoveEven(Stack* p)
{
    element** entry;
    element* tmp;
    if (!p) {
        return;
    }
    entry = &(p->root);
    while (*entry) {
        if (!((*entry)->data % 2)) {
            tmp = *entry;
            std::cout << "removing data " << (*entry)->data << std::endl;
            *entry = (*entry)->next;
            free(tmp);
        } else {
            entry = &((*entry)->next);
        }
    }
}
int
main(int argc, char** argv)
{
    Stack* p = stackNew();
    std::cout << p << std::endl;
    if (stackEmpty(p)) {
        std::cout << "stack is empty!" << std::endl;
    }
    stackPush(p, 1);
    if (!stackEmpty(p)) {
        std::cout << "stack not empty!" << std::endl;
    }
    stackPush(p, 2);
    stackPush(p, 3);
    stackPush(p, 4);
    stackPush(p, 5);
    stackPush(p, 6);
    stackRemoveEven(p);
    /*std::cout << "pop: " << stackPop(p) << std::endl;
    std::cout << "pop: " << stackPop(p) << std::endl;
    std::cout << "pop: " << stackPop(p) << std::endl;
    std::cout << "pop: " << stackPop(p) << std::endl;
    std::cout << "pop: " << stackPop(p) << std::endl;
    std::cout << "pop: " << stackPop(p) << std::endl;*/
    if (stackEmpty(p)) {
        std::cout << "stack is empty!" << std::endl;
    }
    stackFree(p);
    return 0;
}
