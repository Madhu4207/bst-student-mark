#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int marks;
    struct Student *left, *right;
};

// Create Node
struct Student* createNode(int roll, char name[], int marks) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    newNode->roll = roll;
    strcpy(newNode->name, name);
    newNode->marks = marks;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert
struct Student* insert(struct Student* root, int roll, char name[], int marks) {
    if (root == NULL)
        return createNode(roll, name, marks);

    if (roll < root->roll)
        root->left = insert(root->left, roll, name, marks);
    else if (roll > root->roll)
        root->right = insert(root->right, roll, name, marks);
    else
        printf("Duplicate roll number not allowed!\n");

    return root;
}

// Display (clean alignment)
void display(struct Student* root) {
    if (root != NULL) {
        display(root->left);

        printf("Roll: %d\tName: %s\tMarks: %d\n",
               root->roll, root->name, root->marks);

        display(root->right);
    }
}

// Search (your format)
void search(struct Student* root, int roll) {
    if (root == NULL) {
        printf("Student not found\n");
        return;
    }

    if (roll == root->roll) {
        printf("Student Found\n");
        printf("Roll: %d\n", root->roll);
        printf("Name: %s\n", root->name);
        printf("Marks: %d\n", root->marks);
        return;
    }
    else if (roll < root->roll)
        search(root->left, roll);
    else
        search(root->right, roll);
}

// Find Minimum
struct Student* findMin(struct Student* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete
struct Student* deleteNode(struct Student* root, int roll) {
    if (root == NULL) {
        printf("Student not found!\n");
        return NULL;
    }

    if (roll < root->roll)
        root->left = deleteNode(root->left, roll);
    else if (roll > root->roll)
        root->right = deleteNode(root->right, roll);
    else {
        printf("Student deleted successfully!\n");

        if (root->left == NULL) {
            struct Student* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Student* temp = root->left;
            free(root);
            return temp;
        }

        struct Student* temp = findMin(root->right);
        root->roll = temp->roll;
        strcpy(root->name, temp->name);
        root->marks = temp->marks;
        root->right = deleteNode(root->right, temp->roll);
    }
    return root;
}

int main() {
    struct Student* root = NULL;
    int choice, roll, marks;
    char name[50];

    while (1) {
        printf("\n===== Student Mark System (BST) =====\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll Number: ");
                scanf("%d", &roll);

                printf("Enter Name: ");
                scanf("%s", name);

                printf("Enter Marks: ");
                scanf("%d", &marks);

                root = insert(root, roll, name, marks);
                break;

            case 2:
                printf("Enter roll to delete: ");
                scanf("%d", &roll);
                root = deleteNode(root, roll);
                break;

            case 3:
                printf("Enter roll to search: ");
                scanf("%d", &roll);
                search(root, roll);
                break;

            case 4:

                printf("\nStudent Records:\n");
                display(root);
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
