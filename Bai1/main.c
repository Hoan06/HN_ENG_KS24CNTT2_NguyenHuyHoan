#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char title[100];
    int priority;
    char deadline[100];
} Task;

typedef struct SNode {
    Task task;
    struct SNode *next;
} SNode;

typedef struct DNode {
    Task task;
    struct DNode *next;
    struct DNode *prev;
} DNode;

DNode *completedHead = NULL, *completedTail = NULL;

void initList(SNode *head) {
    head = NULL;
}

SNode *createTask(SNode *head) {
    SNode *newNode = (SNode *) malloc(sizeof(SNode));
    printf("Nhap id nhiem vu : ");
    scanf("%d", &newNode->task.id);
    getchar();
    if (newNode->task.id <= 0) {
        printf("Hay nhap id lon hon 0 nhe !!!\n");
        return NULL;
    }
    printf("Nhap title : ");
    fgets(newNode->task.title, 100,stdin);
    newNode->task.title[strcspn(newNode->task.title, "\n")] = '\0';
    printf("Nhap muc do uu tien cua nhiem vu : ");
    scanf("%d", &newNode->task.priority);
    getchar();
    printf("Nhap deadline : ");
    fgets(newNode->task.deadline, 100,stdin);
    newNode->task.deadline[strcspn(newNode->task.deadline, "\n")] = '\0';
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        SNode *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Them nhiem vu thanh cong !!!\n");
    return head;
}

void showList(SNode *head) {
    SNode *temp = head;
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List task : \n");
    while (temp != NULL) {
        printf("Id : %d\n", temp->task.id);
        printf("Title : %s\n", temp->task.title);
        printf("Priority : %d\n", temp->task.priority);
        printf("Deadline : %s\n", temp->task.deadline);
        temp = temp->next;
    }
}

SNode *deleteTask(SNode **head) {
    int id;
    printf("Nhap id nhiem vu muon xoa : ");
    scanf("%d", &id);
    getchar();

    SNode *temp = *head;
    SNode *prev = NULL;

    while (temp != NULL) {
        if (temp->task.id == id) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Xoa nhiem vu thanh cong !!!\n");
            return *head;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Khong tim thay nhiem vu !!!\n");
    return *head;
}

void *updateTask(SNode *head) {
    int id;
    char newTitle[100];
    int newPriority;
    char newDeadline[100];
    SNode *temp = head;
    printf("Nhap id nhiem vu muon cap nhat : ");
    scanf("%d", &id);
    getchar();

    int flag = 0;
    while (temp != NULL) {
        if (temp->task.id == id) {
            printf("Nhap ten nhiem vu moi : ");
            fgets(newTitle, 100, stdin);
            newTitle[strcspn(newTitle, "\n")] = '\0';
            printf("Nhap do uu tien moi : ");
            scanf("%d", &newPriority);
            getchar();
            printf("Nhap deadline moi : ");
            fgets(newDeadline, 100, stdin);
            newDeadline[strcspn(newDeadline, "\n")] = '\0';
            strcpy(temp->task.title, newTitle);
            temp->task.priority = newPriority;
            strcpy(temp->task.deadline, newDeadline);
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (flag == 1) {
        printf("Cap nhat thanh cong !\n");
    } else {
        printf("Khong tim thay nhiem vu !\n");
    }
}

void tickTask(SNode **head) {
    int id;
    printf("Nhap id nhiem vu da hoan thanh : ");
    scanf("%d", &id);
    getchar();
    SNode *temp = *head;
    SNode *prev = NULL;
    while (temp != NULL) {
        if (temp->task.id == id) {
            DNode *newNode = (DNode *) malloc(sizeof(DNode));
            newNode->task = temp->task;
            newNode->next = NULL;
            newNode->prev = NULL;

            if (completedHead == NULL) {
                completedHead = completedTail = newNode;
            } else {
                newNode->prev = completedTail;
                completedTail->next = newNode;
                completedTail = newNode;
            }

            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Da danh dau nhiem vu hoan thanh !\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Khong tim thay nhiem vu !!!\n");
}

void sortTask(SNode **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    SNode *i, *j;
    for (i = *head; i != NULL;i = i->next) {
        for (j = i->next; j != NULL;j = j->next) {
            if (i->task.priority > j->task.priority) {
                Task temp = j->task;
                j->task = i->task;
                i->task = temp;
            }
        }
    }
    printf("Da sap xep xong !\n");
}

void searchTask(SNode *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    char checkTitle[100];
    printf("Moi ban nhap ten nhiem vu muon tim : ");
    fgets(checkTitle, 100, stdin);
    checkTitle[strcspn(checkTitle, "\n")] = '\0';
    while (head != NULL) {
        if (strcmp(head->task.title, checkTitle) == 0) {
            printf("Ket qua : \n");
            printf("Id : %d\n", head->task.id);
            printf("Title : %s\n", head->task.title);
            printf("Priority : %d\n", head->task.priority);
            printf("Deadline : %s\n", head->task.deadline);
            return;
        }
        head = head->next;
    }
    printf("Khong tim thay nhiem vu !\n");
}

int main(void) {
    SNode *head = NULL;
    initList(&head);
    int choice;
    do {
        printf("=======MENU======\n");
        printf("1. Them nhiem vu \n");
        printf("2. Hien thi danh sach nhiem vu \n");
        printf("3. Xoa nhiem vu \n");
        printf("4. Cap nhat thong tin nhiem vu \n");
        printf("5. Danh dau nhiem vu hoan thanh \n");
        printf("6. Sap xep nhiem vu \n");
        printf("7. Tim kiem nhiem vu \n");
        printf("8. Thoat chuong trinh \n");
        printf("Lua chon cua ban : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                head = createTask(head);
                break;
            case 2:
                showList(head);
                break;
            case 3:
                head = deleteTask(&head);
                break;
            case 4:
                updateTask(head);
                break;
            case 5:
                tickTask(&head);
                break;
            case 6:
                sortTask(&head);
                break;
            case 7:
                searchTask(head);
                break;
            case 8:
                printf("Chuong trinh ket thuc !!!");
                break;
            default:
                printf("Lua chon khong hop le !!! Hay chon lai .\n");
        }

    } while (choice != 8);
    return 0;
}