#include <stdio.h>
#include <stdlib.h>

struct BST {
    int data;
    struct BST *lchild;
    struct BST *rchild;
};

typedef struct BST *NODE;

NODE create() {
    NODE temp;
    temp = (NODE)malloc(sizeof(struct BST));
    printf("\nEnter The value: ");
    scanf("%d", &temp->data);
    temp->lchild = NULL;
    temp->rchild = NULL;
    return temp;
}

void insert(NODE root, NODE newnode) {
    /* Note: if newnode->data == root->data it will be skipped. No duplicate nodes are allowed */
    if (newnode->data < root->data) {
        if (root->lchild == NULL)
            root->lchild = newnode;
        else
            insert(root->lchild, newnode);
    } else if (newnode->data > root->data) {
        if (root->rchild == NULL)
            root->rchild = newnode;
        else
            insert(root->rchild, newnode);
    }
}

void inorder(NODE root) {
    if (root != NULL) {
        inorder(root->lchild);
        printf("%d\t", root->data);
        inorder(root->rchild);
    }
}

void preorder(NODE root) {
    if (root != NULL) {
        printf("%d\t", root->data);
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

void postorder(NODE root) {
    if (root != NULL) {
        postorder(root->lchild);
        postorder(root->rchild);
        printf("%d\t", root->data);
    }
}

void search(NODE root) {
    int key;
    NODE current = root;
    printf("\nEnter element to be searched: ");
    scanf("%d", &key);
    while (current != NULL) {
        if (key == current->data) {
            printf("Element %d found in the tree.\n", key);
            return;
        } else if (key < current->data)
            current = current->lchild;
        else
            current = current->rchild;
    }
    printf("Element %d not found in the tree.\n", key);
}

int main() {
    int ch;
    NODE root = NULL, newnode;

    while (1) {
        printf("\n**** BINARY SEARCH TREE ****\n");
        printf("1. Create\n");
        printf("2. Insert\n");
        printf("3. Search\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                root = create();
                break;
            case 2:
                newnode = create();
                if (root == NULL)
                    root = newnode;
                else
                    insert(root, newnode);
                break;
            case 3:
                search(root);
                break;
            case 4:
                if (root == NULL)
                    printf("Tree is empty\n");
                else {
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;
            case 5:
                if (root == NULL)
                    printf("Tree is empty\n");
                else {
                    printf("Preorder Traversal: ");
                    preorder(root);
                    printf("\n");
                }
                break;
            case 6:
                if (root == NULL)
                    printf("Tree is empty\n");
                else {
                    printf("Postorder Traversal: ");
                    postorder(root);
                    printf("\n");
                }
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
