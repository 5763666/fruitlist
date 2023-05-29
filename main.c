#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

struct Fruit {
    char name[20];
    struct Fruit* next;
};

struct Fruit* fruitList = NULL;
struct Fruit* deletedFruits = NULL;

void addFruit(const char* name) {
    struct Fruit* current = fruitList;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("%s already exists.\n", name);
            return;
        }
        current = current->next;
    }

    struct Fruit* newFruit = (struct Fruit*)malloc(sizeof(struct Fruit));
    strcpy_s(newFruit->name, name);
    newFruit->next = NULL;

    if (fruitList == NULL) {
        fruitList = newFruit;
        printf("%s has been added.\n", name);
        return;
    }

    current = fruitList;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newFruit;
    printf("%s has been added.\n", name);
}

void deleteFruit(const char* name) {
    struct Fruit* current = fruitList;
    struct Fruit* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            struct Fruit* deletedFruit = (struct Fruit*)malloc(sizeof(struct Fruit));
            strcpy_s(deletedFruit->name, current->name);
            deletedFruit->next = deletedFruits;
            deletedFruits = deletedFruit;

            if (prev == NULL) {
                fruitList = current->next;
            }
            else {
                prev->next = current->next;
            }

            printf("%s has been deleted.\n", name);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("%s is not ont the list.\n", name);
}

void printDeletedFruits() {
    printf("List of the deleted fruits: \n");

    if (deletedFruits == NULL) {
        printf("NULL\n");
        return;
    }

    struct Fruit* current = deletedFruits;
    while (current != NULL) {
        printf("%s->\n", current->name);
        current = current->next;
    }
}

void freeFruits(struct Fruit* list) {
    while (list != NULL) {
        struct Fruit* current = list;
        list = list->next;
        free(current);
    }
}

void cleanup() {
    freeFruits(fruitList);
    freeFruits(deletedFruits);
}

void printMenu() {
    printf("(1) Insert new fruit\n");
    printf("(2) Delete the fruit\n");
    printf("(3) Print the deleted list\n");
    printf("(0) Exit\n");
    printf("Enter the menu: ");
}

int main() {
    int menu;
    char nfruit[20];

    // 초기 과일 리스트 설정
    const char* Fruitslist[] = { "Mango", "Orange", "Apple", "Grape", "Cherry", "Plum", "Guava", "Raspberry", "Banana", "Peach" };
    int Fruitslistcount = sizeof(Fruitslist) / sizeof(Fruitslist[0]);

    // 초기 과일 리스트로 초기화
    for (int i = 0; i < Fruitslistcount; i++) {
        addFruit(Fruitslist[i]);
    }

    while (1) {
        printMenu();
        scanf_s("%d", &menu);

        switch (menu) {
        case 1:
            printf("Fruit name to add: ");
            scanf_s("%s", nfruit);
            printDeletedFruits(nfruit);
            break;
        case 2:
            printf("Fruit name to delete: ");
            scanf_s("%s", nfruit);
            deleteFruit(nfruit);
            break;
        case 3:
            printDeletedFruits();
            break;
        case 4:
            cleanup();
            printf("Exit the program.\n");
            return 0;
        default:
            printf("Invalid Menu. Please select again.\n");
            break;
        }
    }
}
