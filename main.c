#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define RAYGUI_IMPLEMENTATION
#include "./src/raygui.h"

typedef struct node {
  int data;
  struct node *right;
  struct node *left;
} Node;

// Global variables
Node *root;
int wf = 25;
int hf = 12;
int factor = 50;

void add_node(Node **node, int value) {
  if (*node == NULL) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    *node = new_node;
    // printf("node added with val %d\n", (*node)->data);
  } else if (value < (*node)->data) {
    add_node(&(*node)->left, value);
    // printf("Node added to left\n");
  } else if (value >= (*node)->data) {
    add_node(&(*node)->right, value);
    // printf("Node added to right\n");
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

Vector2 display_visually(Node *node, float shift, float depth) {
  float x, y;
  Vector2 vec;
  bool from_left = false;
  if (node == NULL) {
    Vector2 v0;
    return v0;
  } else {
    if (node->left != NULL) {
      // on return the value at stack was already updated for the root node :?
      shift -= 0.8;
      depth += 0.8;
      // float x = ((wf / 2.0) + shift) * factor;
      // float y = (1 + depth) * factor;
      // printf("left circle at %f , %f ,  value at node - %d \n", x, y,
      // node->data);
      vec = display_visually(node->left, shift, depth);
      // reset for after if ***IMP***
      shift += 0.8;
      depth -= 0.8;
      from_left = true;
    }
    x = ((wf / 2.0) + shift) * factor;
    y = (1 + depth) * factor;
    DrawCircle(x, y, 20, BEIGE);

    char str[10];
    sprintf(str, "%d", node->data);
    DrawText(str, x - 10, y - 10, 20, DARKGRAY);
    if (from_left) {
      from_left = false;
      DrawLineBezier(vec, (Vector2){x, y}, 3.0, GRAY);
    }
    // printf("vec %f , vec2 %f", vec.x, x);
    // printf("drew circle at %f , %f ,  value at node - %d \n", x, y,
    // node->data);
    if (node->right != NULL) {
      shift += 0.8;
      depth += 0.8;
      // float x = ((wf / 2.0) + shift) * factor;
      // float y = (1 + depth) * factor;
      // printf("right circle at %f , %f ,  value at node - %d \n", x, y,
      // node->data);
      Vector2 vec2 = display_visually(node->right, shift, depth);
      DrawLineBezier(vec2, (Vector2){x, y}, 3.0, GRAY);
      // DrawLineV(vec2, (Vector2){x, y}, DARKPURPLE);
    }
  }
  return (Vector2){x, y};
}

void render() {
  InitWindow(factor * wf, factor * hf, "Tree");
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  // Main game loop
  bool input;
  int val = 0;
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // update the music stream buffer // this moves it ahead
    //
    //
    DrawText("Press \"i\" to enter an integer value to tree ", 10, 10, 20,
             RAYWHITE);
    float x = (wf)*factor;
    float y = (hf)*factor;
    Rectangle rec = (Rectangle){x - 300, y - 70, 50, 30};

    if (IsKeyPressed(KEY_I)) {
      input = true;
    }
    if (input) {
      DrawText("Enter integer value", x - 300, y - 100, 20, RAYWHITE);
      GuiValueBox(rec, NULL, &val, 0, 255, true);
      char str0[10];
    }
    if (IsKeyPressed(KEY_ENTER)) {
      input = false;
      printf("value %d \n", val);
      add_node(&root, val);
      val = 0;
    }

    Vector2 ballPos = GetMousePosition();
    Color ballColor;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      ballColor = MAROON;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      ballColor = DARKBLUE;

    BeginDrawing();

    ClearBackground(DARKGRAY);
    // On pause, we draw a blinking message
    // DrawFPS(10, 10);
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
  bool add = false;
  // display_tree(root);
  render();
  return 0;
}
