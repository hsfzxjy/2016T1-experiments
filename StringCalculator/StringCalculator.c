#include <stdio.h>

void showMenu () {
    printf("======= MENU =======\n");
    printf("0) Exit\n");
    printf("1) Input a string\n");
    printf("2) Display the string\n");
    printf("3) Calculate the length of a string\n");
    printf("4) Concat two strings\n");
    printf("5) Compare two strings\n");
    printf("6) Copy a string\n");
    printf("7) Insert a sub-string into another string\n");
    printf("8) Truncate a string\n");
}

int makeAChoice () {
    int choice = -1;
    do {
        printf("Please make a choice (0~10): ");
        scanf("%d", &choice);
        while (getchar() != 0xa);
    } while (!(0 <= choice && choice <= 10));
    return choice;
}

void getString (int prompt, char* string) {
    printf("Please enter string %d: ", prompt);
    scanf("%s", string);
}

int len (char* string) {
    int result = 0;
    while (*(string + result)) ++result;
    return result;
}

void concat (char* str1, char* str2) {
    while (*str1) str1++;
    while (*str2) *(str1++) = *(str2++);
    *str1 = 0;
}

int compare (char* str1, char* str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void copy (char* str1, char* result) {
    while (*str1) *(result++) = *(str1++);
    *result = 0;
}

void move (char* str, int l, int offset) {
    char *p1, *p2;
    if (offset > 0) {
        p1 = str + l;
        p2 = str + l + offset;
        while (p1 >= str) *(p2--) = *(p1--);
    } else if (offset < 0) {
        p1 = str;
        p2 = str + offset;
        while (*p1) *(p2++) = *(p1++);
        *p2 = 0;
    }
}

void insert (char* str, int pos, char* sub) {
    int l = len(str);
    if (pos > l) pos = l;
    str += pos;
    move(str, l - pos, len(sub));
    while (*sub) *(str++) = *(sub++);
}

void substr (char* str, int pos, int n, char* result) {
    while (*str && pos--) str++;
    while (*str && n--) *(result++) = *(str++);
    *result = 0;
}

int main () {
    char strings[3][1024] = {0};
    int pos, n;
    while (1) {
        showMenu();
        switch (makeAChoice()) {
            case 0:
                return 0;
            case 1:
                scanf("%s", strings[0]);
                break;
            case 2:
                printf("The string you've entered is:\n%s\n\n", strings[0]);
                break;
            case 3:
                getString(1, strings[0]);
                printf("Length: %d\n\n", len(strings[0]));
                break;
            case 4:
                getString(1, strings[0]);
                getString(2, strings[1]);
                concat(strings[0], strings[1]);
                printf("Result: %s\n\n", strings[0]);
                break;
            case 5:
                getString(1, strings[0]);
                getString(2, strings[1]);
                printf("Result: %d\n\n", compare(strings[0], strings[1]));
                break;
            case 6:
                getString(1, strings[0]);
                copy(strings[0], strings[1]);
                printf("Result: %s\n\n", strings[1]);
                break;
            case 7:
                getString(1, strings[0]);
                printf("Enter the position: ");
                scanf("%d", &pos);
                getString(2, strings[1]);
                insert(strings[0], pos, strings[1]);
                printf("Result: %s\n\n", strings[0]);
                break;
            case 8:
                getString(1, strings[0]);
                printf("Enter the position and length: ");
                scanf("%d %d", &pos, &n);
                substr(strings[0], pos, n, strings[1]);
                printf("Result: %s\n\n", strings[1]);
                break;
        }
    }
    return 0;
}
