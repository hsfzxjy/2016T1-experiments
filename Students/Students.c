#include <stdio.h>
#include <stdlib.h>

typedef struct student_ {
    long no;
    char name[20];
    double score;
    struct student_* next;
} student;

typedef void (*operation)();

#define cntMenu 6

const char mainMenu[] =
    "======== MENU ========\n"
    "0) Exit\n"
    "1) Create from\n"
    "2) Print\n"
    "3) Search\n"
    "4) Insert\n"
    "5) Stats\n\n";

const char *subMenus[] = {
    "",
    "0) head\n"
    "1) tail\n"
    "2) file\n\n",
    "", "",
    "0) by index\n"
    "1) into ordered list\n\n",
    ""
};

const int ranges[cntMenu] = {0, 3, 0, 0, 2, 0};

student* head = 0;

student* alloc () {
    return (student*) calloc(1, sizeof(student));
}

int choose (const char* menu, int cnt) {
    int choice = -1;
    printf("%s", menu);
    do {
        printf("Make a choice(%d~%d): ", 0, cnt-1);
        scanf("%d", &choice);
        while (getchar() != 10);
    } while (choice < 0 || choice >= cnt);
    printf("\n");
    return choice;
}

student* getStudent () {
    student* stu = alloc();
    printf("No., name, score: ");
    scanf("%ld%s%lf", &stu->no, stu->name, &stu->score);
    return stu;
}

void dispose () {
    student* p;
    for (p = head; p; p = p->next) free(p);
    head = 0;
}

void halt () {
    exit(0);
}

void createFromTail () {
    int i;
    student* p, *p2;
    printf("Input 3 students(ordered by No.)\n");
    dispose();
    for (i = 0; i < 3; i++) {
        p2 = getStudent();
        if (i)
            p->next = p2;
        else
            head = p = p2;
        p = p2;
    }
}

void createFromHead () {
    int i;
    student* p = 0, *p2;
    printf("Input 3 students\n");
    dispose();
    for (i = 0; i < 3; i++) {
        p2 = getStudent();
        p2->next = p;
        p = p2;
    }
    head = p;
}

void createFromFile () {
    char fn[256];
    student* tp, *p = 0;
    printf("Filename: ");
    scanf("%s", fn);
    FILE *f = fopen(fn, "r");
    dispose();
    while (!feof(f)) {
        tp = alloc();
        if (fscanf(f, "%ld %s %lf", &tp->no, tp->name, &tp->score) != 3) break;
        if (!head) head = p = tp;
        else p = p->next = tp;
    }
    fclose(f);
}

void print () {
    student* p;
    for (p = head; p; p = p->next)
        printf("%ld\t%s\t%lf\n", p->no, p->name, p->score);
}

void search () {
    long no;
    printf("No. to search: ");
    scanf("%ld", &no);
    student* p;
    for (p = head; p; p = p->next)
        if (p->no == no)
            printf("%ld\t%s\t%lf\n", p->no, p->name, p->score);
}

void stats () {
    long cnt = 0;
    student* p;
    for (p = head; p; p = p->next) cnt++;
    printf("Count: %ld\n", cnt);
}

void insert (student* prev, student* stu) {
    if (prev) {
        stu->next = prev->next;
        prev->next = stu;
    } else {
        stu->next = head;
        head = stu;
    }
}

void insertByIndex () {
    long index;
    student* prev = 0, *p = head;
    printf("Index: ");
    scanf("%ld", &index);
    while (index-->0 && p) p = (prev = p)->next;
    insert(prev, getStudent());
}

void insertByNo () {
    printf("Order(-1 for DESC and 1 for ASC) ");
    int order;
    scanf("%d", &order);
    student* stu = getStudent(), *prev = 0, *p = head;
    while (p && ((p->no < stu->no) ^ (order < 0))) p = (prev = p)->next;
    insert(prev, stu);
}

const operation operations[cntMenu][3] = {
    {halt},
    {createFromHead, createFromTail, createFromFile},
    {print}, {search},
    {insertByIndex, insertByNo},
    {stats}
};

int main () {
    while (1) {
        int choice = choose(mainMenu, cntMenu);
        operation func;
        if (!ranges[choice]) func = operations[choice][0];
        else func = operations[choice][choose(subMenus[choice], ranges[choice])];
        func();
        printf("\n");
    }
    return 0;
}
