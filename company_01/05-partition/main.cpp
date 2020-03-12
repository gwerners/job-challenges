#include <iostream>

struct SingleLinkedListOfIntsNode
{
    int data;
    struct SingleLinkedListOfIntsNode* next;
};

SingleLinkedListOfIntsNode*
pushNewEntry(SingleLinkedListOfIntsNode* root, int x)
{
    SingleLinkedListOfIntsNode* entry =
      (SingleLinkedListOfIntsNode*)malloc(sizeof(SingleLinkedListOfIntsNode));
    entry->data = x;
    entry->next = nullptr;
    if (root) {
        entry->next = root;
    }
    return entry;
}

void
listPartition(SingleLinkedListOfIntsNode** head, int x)
{
    SingleLinkedListOfIntsNode *more = nullptr, *less = nullptr, *tmp,
                               *tail = nullptr;
    SingleLinkedListOfIntsNode* entry = *head;
    while (entry) {
        tmp = entry->next;
        if (entry->data > x) {
            entry->next = (more) ? more : nullptr;
            more = entry;
        } else {
            entry->next = (less) ? less : nullptr;
            if (!less) {
                tail = entry;
            }
            less = entry;
        }
        entry = tmp;
    }
    *head = less;
    if (tail) {
        tail->next = more;
    } else {
        *head = more;
    }
}
void
printList(SingleLinkedListOfIntsNode* root)
{
    while (root) {
        std::cout << "entry " << root->data << std::endl;
        root = root->next;
    }
    std::cout << "_____________________________________________________________"
                 "__________________"
              << std::endl;
}
void
freeList(SingleLinkedListOfIntsNode* root)
{
    SingleLinkedListOfIntsNode* tmp;
    while (root) {
        tmp = root;
        root = root->next;
        free(tmp);
    }
}
void
test_01()
{
    SingleLinkedListOfIntsNode* root = nullptr;
    root = pushNewEntry(root, 10);
    root = pushNewEntry(root, 20);
    root = pushNewEntry(root, 30);
    root = pushNewEntry(root, 40);
    root = pushNewEntry(root, 50);
    root = pushNewEntry(root, 60);
    std::cout << "initial list: " << std::endl;
    printList(root);
    listPartition(&root, 30);
    std::cout << "list after partitioning: " << std::endl;
    printList(root);
    freeList(root);
}
void
test_02()
{
    SingleLinkedListOfIntsNode* root = nullptr;
    root = pushNewEntry(root, 30);
    root = pushNewEntry(root, 40);
    root = pushNewEntry(root, 50);
    root = pushNewEntry(root, 60);
    std::cout << "initial list: " << std::endl;
    printList(root);
    listPartition(&root, 30);
    std::cout << "list after partitioning: " << std::endl;
    printList(root);
    freeList(root);
}
void
test_03()
{
    SingleLinkedListOfIntsNode* root = nullptr;
    root = pushNewEntry(root, 10);
    root = pushNewEntry(root, 20);
    root = pushNewEntry(root, 30);
    std::cout << "initial list: " << std::endl;
    printList(root);
    listPartition(&root, 30);
    std::cout << "list after partitioning: " << std::endl;
    printList(root);
    freeList(root);
}
void
test_04()
{
    SingleLinkedListOfIntsNode* root = nullptr;
    root = pushNewEntry(root, 10);
    root = pushNewEntry(root, 20);
    root = pushNewEntry(root, 25);
    std::cout << "initial list: " << std::endl;
    printList(root);
    listPartition(&root, 30);
    std::cout << "list after partitioning: " << std::endl;
    printList(root);
    freeList(root);
}
void
test_05()
{
    SingleLinkedListOfIntsNode* root = nullptr;
    root = pushNewEntry(root, 25);
    root = pushNewEntry(root, 40);
    root = pushNewEntry(root, 50);
    root = pushNewEntry(root, 60);
    std::cout << "initial list: " << std::endl;
    printList(root);
    listPartition(&root, 30);
    std::cout << "list after partitioning: " << std::endl;
    printList(root);
    freeList(root);
}
void
test_06()
{
    SingleLinkedListOfIntsNode* root = nullptr;
    root = pushNewEntry(root, 20);
    root = pushNewEntry(root, 18);
    root = pushNewEntry(root, 16);
    root = pushNewEntry(root, 14);
    root = pushNewEntry(root, 12);
    root = pushNewEntry(root, 11);
    root = pushNewEntry(root, 13);
    root = pushNewEntry(root, 15);
    root = pushNewEntry(root, 17);
    root = pushNewEntry(root, 19);
    std::cout << "initial list: " << std::endl;
    printList(root);
    listPartition(&root, 15);
    std::cout << "list after partitioning: " << std::endl;
    printList(root);
    freeList(root);
}
int
main(int argc, char** argv)
{
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    return 0;
}
