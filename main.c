#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
  int data;
  struct node *right;
  struct node *left;
} Node;

// Global variables
Node *root;
int wf = 16;
int hf = 9;
int factor = 50;

void add_node(Node **node, int value) {
  if (*node == NULL) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    *node = new_node;
    printf("node added with val %d\n", (*node)->data);
  } else if (value < (*node)->data) {
    add_node(&(*node)->left, value);
    printf("Node added to left\n");
  } else if (value >= (*node)->data) {
    add_node(&(*node)->right, value);
    printf("Node added to right\n");
  }
}

void display_tree(Node *node) {
  if (node == NULL) {
    return;
  } else {
    if (node->left != NULL) {
      display_tree(node->left);
    }
    printf("value at node - %d \n", node->data);
    if (node->right != NULL) {
      display_tree(node->right);
    }
  }
}

void display_visually(Node *node, float shift, float depth) {
  if (node == NULL) {
    return;
  } else {
    if (node->left != NULL) {
      // on return the value at stack was already updated for the root node :?
      shift -= 0.8;
      depth += 0.8;
      // float x = ((wf / 2.0) + shift) * factor;
      // float y = (1 + depth) * factor;
      // printf("left circle at %f , %f ,  value at node - %d \n", x, y,
             // node->data);
      display_visually(node->left, shift, depth);
      // reset for after if ***IMP***
      shift += 0.8;
      depth -= 0.8;
    }
    float x = ((wf / 2.0) + shift) * factor;
    float y = (1 + depth) * factor;
    DrawCircle(x, y, 20,PURPLE);
    char str[10];
    sprintf(str, "%d", node->data);
    DrawText(str, x-10, y-10, 20, DARKGRAY);
    // printf("drew circle at %f , %f ,  value at node - %d \n", x, y, node->data);
    if (node->right != NULL) {
      shift += 0.8;
      depth += 0.8;
      // float x = ((wf / 2.0) + shift) * factor;
      // float y = (1 + depth) * factor;
      // printf("right circle at %f , %f ,  value at node - %d \n", x, y,
             // node->data);
      display_visually(node->right, shift, depth);
    }
  }
}

void render() {
  InitWindow(factor * wf, factor * hf, "Tree");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // update the music stream buffer // this moves it ahead
    Vector2 ballPos = GetMousePosition();
    Color ballColor;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      ballColor = MAROON;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      ballColor = DARKBLUE;

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("PRESS P to PAUSE/PLAY Music ", 20, 25, 20, DARKGRAY);
    DrawText("PRESS F to enable/disable effects ", 20, 45, 20, DARKGRAY);
    // On pause, we draw a blinking message
    DrawFPS(10, 10);
    display_visually(root, 0.0, 0.0);

    EndDrawing();
  }

  // De-Initialization
  //---------------------------------------------------------
  CloseWindow();
  //----------------------------------------------------------
}

int main(int argc, char *argv[]) {
  printf("Creating a tree\n");
  int data;
  printf("value at root %p \n", root);
  for (int i = 0; i < 3; i++) {
    printf("\nEnter int data :- ");
    scanf("%d", &data);
    add_node(&root, data);
  }
  display_tree(root);
  render();
  return 0;
}