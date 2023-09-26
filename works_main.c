#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *right;
  struct node *left;
} Node;

void add_node(Node **node , int value) {
  if (*node == NULL) {
    printf("address of root node %p\n", node);
    Node *new_node = (Node *)malloc(sizeof(Node));
    printf("address new node %p\n", new_node);
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    *node = new_node;
    printf("address node %p\n", node);
    printf("Node added with value %d \n", (*node)->data);
  }
  else if (value < (*node)->data) {
    add_node(&(*node)->left, value);
    printf("Node added to left\n");
  }
  else if (value >= (*node)->data) {
    add_node(&(*node)->right, value);
    printf("Node added to right\n");
  }
}


void display_tree(Node *node){
  if (node == NULL) {
    return;
  }
  else {
    if (node->left != NULL){
      display_tree(node->left);
    }
    printf("value at node - %d \n", node->data);
    if (node->right != NULL){
      display_tree(node->right);
    }
  }
}

Node *root;
int main(int argc, char *argv[]) {
  printf("Creating a tree\n");
  int data;
  printf("value at root %p \n", root);
  for (int i=0; i<5; i++) {
    printf("\nEnter int data :- ");
    scanf("%d",&data);
    printf("address  at root %p \n", &root);
    add_node(&root, data);
    printf("back in the loop \n");
    printf("value at root %p \n", root);
    printf("Node adde with data %d", root->data);
  }
  display_tree(root);
  return 0;
}


