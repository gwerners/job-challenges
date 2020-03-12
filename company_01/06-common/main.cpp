#include <iostream>
#include <stdio.h>

enum err_t
{
    ERR_OK = 0,
    ERR_INVALID_INPUT_PARAMETER,
    ERR_INVALID_INPUT_PARAMETERS_SIZE,
    ERR_INVALID_OUTPUT_PARAMETER,
    ERR_INVALID_OUTPUT_PARAMETER_SIZE
};
err_t
findCommon(int* list1,
           int numElem1,
           int* list2,
           int numElem2,
           int* result,
           int* resultSize)
{
    int iBig = (numElem1 > numElem2) ? numElem1 : numElem2;
    int* lst1 = (numElem1 > numElem2) ? list1 : list2;
    int* lst2 = (numElem1 > numElem2) ? list2 : list1;
    int iShort = 0;
    int iRet = 0;
    if (!list1 || !list2) {
        return ERR_INVALID_INPUT_PARAMETER;
    }
    if (!numElem1 || !numElem2) {
        return ERR_INVALID_INPUT_PARAMETERS_SIZE;
    }
    if (!result) {
        return ERR_INVALID_OUTPUT_PARAMETER;
    }
    if (!resultSize) {
        return ERR_INVALID_OUTPUT_PARAMETER_SIZE;
    }
    while (iBig--) {
        iShort = (numElem1 > numElem2) ? numElem2 : numElem1;
        while (iShort--) {
            if (lst1[iBig] == lst2[iShort]) {
                result[iRet++] = lst1[iBig];
            }
        }
    }
    *resultSize = iRet;
    return ERR_OK;
}
void
printList(int* lst, int size)
{
    if (!lst)
        return;
    while (size--) {
        // printf(">%d\n", *lst);
        std::cout << ">" << *lst << std::endl;
        ++lst;
        ;
    }
}
int
main(int argc, char** argv)
{
    int list1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int list2[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
    int ret[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int retSize;
    printList(&list1[0], 10);
    // printf("_______________________\n");
    std::cout << "_______________________" << std::endl;
    printList(&list2[0], 10);
    // printf("_______________________\n");
    std::cout << "_______________________" << std::endl;
    if (findCommon(&list1[0], 10, &list2[0], 10, &ret[0], &retSize) == ERR_OK) {
        printList(&ret[0], retSize);
    }
    return 0;
}
