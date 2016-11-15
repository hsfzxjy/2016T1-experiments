#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int length = 0;
int array[10000] = {0};

const char mainMenu[] =
    "======= MENU =======\n"
    "0) Exit\n"
    "1) Configuration\n"
    "2) Generate samples\n"
    "3) Display\n"
    "4) Delete\n"
    "5) Insert\n\n";

const char *subMenus[] = {
    "", "",
    "0) with random numbers\n"
    "1) with inputs\n"
    "2) with single value\n"
    "3) with arithmetic sequences\n\n",
    "\n",
    "0) by index\n"
    "1) by value\n"
    "2) by ranges\n\n",
    "0) by index\n"
    "1) into a sorted array\n\n"
};

const int ranges[6][2] = {{0}, {0}, {0, 3}, {0}, {0, 2}, {0, 1}};

typedef void (*operation)();

void halt () {
    exit(0);
}

void digest () {
    while (getchar() != 10);
}

void getIndex (int* index, int max) {
    do {
        printf("Index(0~%d): ", max);
        scanf("%d", index);
    } while (*index < 0 || *index > max);
}

void getValue (int* value) {
    printf("Value: ");
    scanf("%d", value);
}

int showMenuAndChoose (const char *menu, int min, int max) {
    int choice = -1;
    printf("%s", menu);
    do {
        printf("Make a choice(%d~%d): ", min, max);
        scanf("%d", &choice);
        digest();
    } while (choice < min || choice > max);
    printf("\n");
    return choice;
}

void config () {
    int l = -1;
    printf("Enter the new length: ");
    scanf("%d", &l);
    digest();
    if (0 <= l && l <= 10000) length = l;
}

void fillWithRandom () {
    int min = 0, max = 0, i;
    do {
        printf("Enter min & max: ");
        scanf("%d%d", &min, &max);
    } while (min >= max);
    srand((unsigned) time(NULL));
    for (i = 0; i < length; i++) array[i] = min + (rand() % (max - min + 1));
}

void fillWithInputs () {
    int i;
    for (i = 0; i < length; i++) scanf("%d", &array[i]);
}

void fillWithValue () {
    int i, value;
    getValue(&value);
    for (i = 0; i < length; i++) array[i] = value;
}

void fillWithSeq () {
    int start, step, i;
    printf("Start, step: ");
    scanf("%d%d", &start, &step);
    for (i = 0; i < length; i++) array[i] = start + step * i;
}

void display () {
    int i;
    printf("Length: %d\n", length);
    for (i = 0; i < length; i++) printf("(%d)\t%d\n", i, array[i]);
}

void move (int start, int offset) {
    int i;
    if (offset > 0)
        for (i = length - 1; i >= start; i--) array[i + offset] = array[i];
    else if (offset < 0)
        for (i = start; i < length; i++) array[i + offset] = array[i];
    length += offset;
}

void deleteByIndex () {
    if (!length) return;
    int index;
    getIndex(&index, length - 1);
    move(index + 1, -1);
}

void deleteByValue () {
    int value, count = 0, i;
    getValue(&value);
    for (i = 0; i < length; i++)
        if (value == array[i]) count++;
        else array[i - count] = array[i];
    length -= count;
}

void deleteByRange () {
    int min, max;
    do {
        printf("Start, end: ");
        scanf("%d%d", &min, &max);
    } while (!(0 <= min && min <= max && max < length));
    move(max + 1, min - max - 1);
}

void insertByIndex () {
    int index, value;
    getIndex(&index, length);
    getValue(&value);
    move(index, 1);
    array[index] = value;
}

int getOrder () {
    int i = 0;
    while (i < length - 1 && array[i] == array[i + 1]) i++;
    if (i == length-1) return 1;
    int order = array[i] < array[i + 1] ? 1 : -1;
    for (; i < length-1; i++)
        if (array[i] != array[i+1] && array[i] < array[i + 1] ^ order > 0) return 0;
    return order;
}

void insertIntoSorted () {
    int value, order, i = 0;
    if (!(order = getOrder())) {
        printf("UNSORTED!\n");
        return;
    }
    getValue(&value);
    while (i < length && value <= array[i] ^ order > 0) i++;
    move(i, 1);
    array[i] = value;
}

const operation operations[6][4] = {
    {halt, NULL}, {config, NULL},
    {fillWithRandom, fillWithInputs, fillWithValue, fillWithSeq},
    {display, NULL},
    {deleteByIndex, deleteByValue, deleteByRange, NULL},
    {insertByIndex, insertIntoSorted, NULL}
};

int main () {
    while (1) {
        int choice = showMenuAndChoose(mainMenu, 0, 5);
        operation func;
        if (!ranges[choice][1]) func = operations[choice][0];
        else func = operations[choice][showMenuAndChoose(subMenus[choice], ranges[choice][0], ranges[choice][1])];
        func();
        printf("\n");
    }
    return 0;
}
