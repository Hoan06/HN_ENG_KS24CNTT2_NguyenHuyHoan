#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char str[100];
    struct Node* next;
} Node;

typedef struct Stack1 {
    Node *top;
} Stack1;


typedef struct Stack2 {
    Node *top;
} Stack2;

Node *insertStr(Stack1 *historyStack) {
    char newStr[100];
    printf("Moi ban nhap chuoi moi : ");
    fgets(newStr, 100, stdin);
    newStr[strcspn(newStr, "\n")] = 0;
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->str, newStr);
    newNode->next = historyStack->top;
    printf("Da them !!!\n");
    return newNode;
}

void undoStack(Stack1 *historyStack,Stack2 *redoStack) {
    Node *temp = historyStack->top;
    if (historyStack->top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    historyStack->top = historyStack->top->next;
    temp->next = redoStack->top;
    redoStack->top = temp;
    printf("Da undo !\n");
}

void redoStackStr(Stack1 *historyStack,Stack2 *redoStack) {
    if (redoStack->top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    Node *temp = redoStack->top;
    redoStack->top = temp->next;
    temp->next = historyStack->top;
    historyStack->top = temp;
    printf("Da redo !\n");
}

void showStack(Stack1 *historyStack) {
    Node *temp = historyStack->top;
    if (historyStack->top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Cac chuoi la : \n");
    while (temp != NULL) {
        printf("%s \n", temp->str);
        temp = temp->next;
    }
}

int main(void) {
    Stack1 historyStack;
    historyStack.top = NULL;
    Stack2 redoStack;
    redoStack.top = NULL;
    int choice;
    do {
        printf("=======MENU=======\n");
        printf("1. INSERT \n");
        printf("2. UNDO \n");
        printf("3. REDO \n");
        printf("4. Hien thi \n");
        printf("5. EXIT \n");
        printf("Lua chon cua ban : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                historyStack.top = insertStr(&historyStack);
                break;
            case 2:
                undoStack(&historyStack, &redoStack);
                break;
            case 3:
                redoStackStr(&historyStack, &redoStack);
                break;
            case 4:
                showStack(&historyStack);
                break;
            case 5:
                printf("Chuong trinh ket thuc !!!\n");
                break;
            default:
                printf("Lua chon khong hop le . Vui long chon lai !!!\n");
        }
    } while (choice != 5);
    return 0;
}