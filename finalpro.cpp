#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

// ================= LINKED LIST =================
struct Contact {

    char firstName[30];
    char lastName[30];
    char gender[10];
    char city[30];
    char phone[20];

    struct Contact *next;
};

// ================= BST NODE =================
struct TreeNode {

    char firstName[30];
    char lastName[30];
    char gender[10];
    char city[30];
    char phone[20];

    struct TreeNode *left;
    struct TreeNode *right;
};

struct Contact *head = NULL;
struct TreeNode *root = NULL;

// ================= DESIGN =================
void line() {

    printf("=========================================\n");
}

// ================= NAME VALIDATION =================
int isValidName(char name[]) {

    for(int i = 0; name[i] != '\0'; i++) {

        if(!isalpha(name[i])) {

            return 0;
        }
    }

    return 1;
}

// ================= CREATE BST NODE =================
struct TreeNode* createNode(char fname[],
                            char lname[],
                            char gender[],
                            char city[],
                            char phone[]) {

    struct TreeNode *newNode;

    newNode =
    (struct TreeNode*)malloc(sizeof(struct TreeNode));

    strcpy(newNode->firstName, fname);
    strcpy(newNode->lastName, lname);
    strcpy(newNode->gender, gender);
    strcpy(newNode->city, city);
    strcpy(newNode->phone, phone);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// ================= INSERT INTO BST =================
struct TreeNode* insertBST(struct TreeNode *node,
                           char fname[],
                           char lname[],
                           char gender[],
                           char city[],
                           char phone[]) {

    if(node == NULL) {

        return createNode(fname,
                          lname,
                          gender,
                          city,
                          phone);
    }

    if(strcmp(fname,
       node->firstName) < 0) {

        node->left =
        insertBST(node->left,
                  fname,
                  lname,
                  gender,
                  city,
                  phone);
    }

    else {

        node->right =
        insertBST(node->right,
                  fname,
                  lname,
                  gender,
                  city,
                  phone);
    }

    return node;
}

// ================= SAVE CONTACT TO FILE =================
void saveToFile(char fname[],
                char lname[],
                char gender[],
                char city[],
                char phone[]) {

    FILE *fp;

    fp = fopen("contacts.txt", "a");

    if(fp == NULL) {

        printf("\nFile Error!\n");

        return;
    }

    fprintf(fp,
            "%s %s %s %s %s\n",
            fname,
            lname,
            gender,
            city,
            phone);

    fclose(fp);
}

// ================= LOAD CONTACTS FROM FILE =================
void loadFromFile() {

    FILE *fp;

    char fname[30];
    char lname[30];
    char gender[10];
    char city[30];
    char phone[20];

    struct Contact *newContact, *temp;

    fp = fopen("contacts.txt", "r");

    if(fp == NULL) {

        return;
    }

    while(fscanf(fp,
          "%s %s %s %s %s",
          fname,
          lname,
          gender,
          city,
          phone) != EOF) {

        newContact =
        (struct Contact*)
        malloc(sizeof(struct Contact));

        strcpy(newContact->firstName,
               fname);

        strcpy(newContact->lastName,
               lname);

        strcpy(newContact->gender,
               gender);

        strcpy(newContact->city,
               city);

        strcpy(newContact->phone,
               phone);

        newContact->next = NULL;

        if(head == NULL) {

            head = newContact;
        }

        else {

            temp = head;

            while(temp->next != NULL) {

                temp = temp->next;
            }

            temp->next = newContact;
        }

        root = insertBST(root,
                         fname,
                         lname,
                         gender,
                         city,
                         phone);
    }

    fclose(fp);
}

// ================= REWRITE FILE =================
void rewriteFile() {

    FILE *fp;

    struct Contact *temp;

    fp = fopen("contacts.txt", "w");

    temp = head;

    while(temp != NULL) {

        fprintf(fp,
                "%s %s %s %s %s\n",
                temp->firstName,
                temp->lastName,
                temp->gender,
                temp->city,
                temp->phone);

        temp = temp->next;
    }

    fclose(fp);
}

// ================= ADD CONTACT =================
void addContact() {

    struct Contact *newContact, *temp;

    char fname[30];
    char lname[30];
    char gender;
    char city[30];
    char phone[20];

    printf("\nEnter First Name : ");
    scanf("%s", fname);

    // FIRST NAME VALIDATION
    if(!isValidName(fname)) {

        printf("\nInvalid First Name!\n");
        printf("Only Alphabets Allowed.\n");

        return;
    }

    printf("Enter Last Name  : ");
    scanf("%s", lname);

    // LAST NAME VALIDATION
    if(!isValidName(lname)) {

        printf("\nInvalid Last Name!\n");
        printf("Only Alphabets Allowed.\n");

        return;
    }

    // GENDER VALIDATION
    printf("Enter Gender (M/F) : ");
    scanf(" %c", &gender);

    gender = toupper(gender);

    if(gender != 'M' &&
       gender != 'F') {

        printf("\nInvalid Gender!\n");
        printf("Enter Only M or F.\n");

        return;
    }

    printf("Enter City : ");
    scanf("%s", city);

    printf("Enter Phone Number : ");
    scanf("%s", phone);

    // PHONE LENGTH CHECK
    if(strlen(phone) != 10) {

        printf("\nInvalid Phone Number!\n");
        printf("Phone Number Must Contain Exactly 10 Digits.\n");

        return;
    }

    // DIGIT CHECK
    for(int i = 0; i < 10; i++) {

        if(!isdigit(phone[i])) {

            printf("\nInvalid Phone Number!\n");
            printf("Only Numbers Allowed.\n");

            return;
        }
    }

    // ADD +91
    char finalPhone[20] = "+91";

    strcat(finalPhone, phone);

    strcpy(phone, finalPhone);

    newContact =
    (struct Contact*)
    malloc(sizeof(struct Contact));

    strcpy(newContact->firstName,
           fname);

    strcpy(newContact->lastName,
           lname);

    if(gender == 'M') {

        strcpy(newContact->gender,
               "Male");
    }

    else {

        strcpy(newContact->gender,
               "Female");
    }

    strcpy(newContact->city,
           city);

    strcpy(newContact->phone,
           phone);

    newContact->next = NULL;

    if(head == NULL) {

        head = newContact;
    }

    else {

        temp = head;

        while(temp->next != NULL) {

            temp = temp->next;
        }

        temp->next = newContact;
    }

    // BST INSERT
    root = insertBST(root,
                     fname,
                     lname,
                     newContact->gender,
                     city,
                     phone);

    // SAVE TO FILE
    saveToFile(fname,
               lname,
               newContact->gender,
               city,
               phone);

    printf("\nContact Added Successfully!\n");
}

// ================= DISPLAY CONTACTS =================
void displayContacts() {

    struct Contact *temp;

    if(head == NULL) {

        printf("\nNo Contacts Found!\n");

        return;
    }

    temp = head;

    line();

    printf("           CONTACT LIST\n");

    line();

    while(temp != NULL) {

        printf("First Name : %s\n",
               temp->firstName);

        printf("Last Name  : %s\n",
               temp->lastName);

        printf("Gender     : %s\n",
               temp->gender);

        printf("City       : %s\n",
               temp->city);

        printf("Phone      : %s\n",
               temp->phone);

        line();

        temp = temp->next;
    }
}

// ================= SEARCH CONTACT =================
void searchContact() {

    char key[30];

    struct TreeNode *temp;

    printf("\nEnter First Name To Search : ");
    scanf("%s", key);

    temp = root;

    while(temp != NULL) {

        if(strcmp(key,
           temp->firstName) == 0) {

            printf("\nContact Found!\n");

            printf("First Name : %s\n",
                   temp->firstName);

            printf("Last Name  : %s\n",
                   temp->lastName);

            printf("Gender     : %s\n",
                   temp->gender);

            printf("City       : %s\n",
                   temp->city);

            printf("Phone      : %s\n",
                   temp->phone);

            return;
        }

        else if(strcmp(key,
                temp->firstName) < 0) {

            temp = temp->left;
        }

        else {

            temp = temp->right;
        }
    }

    printf("\nContact Not Found!\n");
}

// ================= DELETE CONTACT =================
void deleteContact() {

    char key[30];

    struct Contact *temp, *prev;

    printf("\nEnter First Name To Delete : ");
    scanf("%s", key);

    if(head == NULL) {

        printf("\nPhonebook Empty!\n");

        return;
    }

    temp = head;
    prev = NULL;

    if(strcmp(temp->firstName,
       key) == 0) {

        head = temp->next;

        free(temp);

        rewriteFile();

        printf("\nContact Deleted!\n");

        return;
    }

    while(temp != NULL &&
          strcmp(temp->firstName,
          key) != 0) {

        prev = temp;

        temp = temp->next;
    }

    if(temp == NULL) {

        printf("\nContact Not Found!\n");

        return;
    }

    prev->next = temp->next;

    free(temp);

    rewriteFile();

    printf("\nContact Deleted Successfully!\n");
}

// ================= ADMIN LOGIN =================
int adminLogin() {

    char username[20];
    char password[20];

    char ch;

    int i = 0;

    line();

    printf("         >>> ADMIN LOGIN <<<\n");

    line();

    printf("Enter Username : ");
    scanf("%s", username);

    printf("Enter Password : ");

    // PASSWORD HIDE
    while((ch = getch()) != 13) {

        if(ch == 8 && i > 0) {

            i--;

            printf("\b \b");
        }

        else {

            password[i] = ch;

            i++;

            printf("*");
        }
    }

    password[i] = '\0';

    if(strcmp(username, "admin") == 0 &&
       strcmp(password, "1234") == 0) {

        printf("\n\nLogin Successful!\n");

        return 1;
    }

    printf("\n\nInvalid Username or Password!\n");

    return 0;
}

// ================= USER MENU =================
void userMenu() {

    int choice;

    do {

        line();

        printf("      PHONEBOOK MANAGEMENT\n");

        line();

        printf("[1] Add Contact\n");
        printf("[2] Display Contacts\n");
        printf("[3] Search Contact\n");
        printf("[4] Delete Contact\n");
        printf("[5] Exit\n");

        line();

        printf("Enter Choice : ");

        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addContact();
                break;

            case 2:
                displayContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                deleteContact();
                break;

            case 5:
                printf("\nExiting Program...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 5);
}

// ================= MAIN FUNCTION =================
int main() {

    int choice;
    printf("=========================================\n");
    printf("        PHONEBOOK MANAGEMENT SYSTEM\n");
    printf("=========================================\n\n");

    printf("=========================================\n\n");
    system("pause");

    // LOAD SAVED CONTACTSi
    loadFromFile();

    do {

        system("cls");

        line();

        printf("      >>> LOGIN INTO SYSTEM <<<\n");

        line();

        printf("[1] Administrator\n");
        printf("[2] User Profile\n");
        printf("[3] EXIT\n");

        line();

        printf("Enter The Number & Hit ENTER : ");

        scanf("%d", &choice);

        switch(choice) {

            case 1:

                if(adminLogin()) {

                    userMenu();
                }

                break;

            case 2:

                printf("\nWELCOME USER\n");

                displayContacts();

                break;

            case 3:

                printf("\nProgram Closed!\n");

                break;

            default:

                printf("\nInvalid Choice!\n");
        }

        printf("\n");

        system("pause");

    } while(choice != 3);

    return 0;
}