#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void** data;
    size_t count;
    size_t capacity;
} Vector;

void vectorPrint(Vector* vector){
  printf("========================================\n");

  printf("Vector count: %zu\n", vector->count);
  printf("Vector capacity: %zu\n", vector->capacity);

  for (int i = 0; i < vector->count; i++){
    printf("[%d]: %d\n", i, *(int*)vector->data[i]);
  }

  printf("\n");
}

Vector* vectorCreate(){
  Vector* vector = (Vector*)malloc(sizeof(Vector));

  vector->count = 0;
  vector->capacity = 0;
  vector->data = malloc(vector->capacity * sizeof(void*));

  return vector;
}

void vectorPush(Vector* vector, void* item){
  vector->count++;
  vector->capacity++;

  vector->data = realloc(vector->data, vector->capacity * sizeof(void*));

  vector->data[vector->count - 1] = item;
}

void vectorPop(Vector* vector){
  vector->count--;
  vector->capacity--;

  vector->data = realloc(vector->data, vector->capacity * sizeof(void*));
}

void vectorShift(Vector* vector){

  vector->count--;
  vector->capacity--;

  for (int i = 0; i < vector->count; i++){
    vector->data[i] = vector->data[i + 1];
  }

  vector->data = realloc(vector->data, vector->capacity * sizeof(void*));
}

void vectorUnshift(Vector* vector, void* item){
  vector->count++;
  vector->capacity++;

  vector->data = realloc(vector->data, vector->capacity * sizeof(void*));

  for (int i = vector->count; i >= 0; i--){
    vector->data[i] = vector->data[i - 1];
  }

  vector->data[0] = item;
}

void vectorSet(Vector* vector, int index, void* item){
  vector->data[index] = item;
}

void vectorInsert(Vector* vector, int index, void* item){
  vector->count++;
  vector->capacity++;

  vector->data = realloc(vector->data, vector->capacity * sizeof(void*));


  for (int i = vector->count; i >= 0; i--){
    if(i == index){
      vector->data[i] = item;
    } else if(i < index) {
      vector->data[i] = vector->data[i];
    } else {
      vector->data[i] = vector->data[i - 1];
    }
  }
}

void vectorRemove(Vector* vector, int index){
  vector->count--;
  vector->capacity--;

  for (int i = 0; i < vector->count; i++){
    if( i >= index){
      vector->data[i] = vector->data[i + 1];
    } else {
      vector->data[i] = vector->data[i];
    }
  }

  vector->data = realloc(vector->data, vector->capacity * sizeof(void*));
}

int main(){

  // Create an init
  Vector* vector = createVector();

  int x1 = 10;
  vectorPush(vector, &x1);

  int x2 = 20;
  vectorPush(vector, &x2);

  int x3 = 30;
  vectorPush(vector, &x3);

  int x4 = 40;
  vectorPush(vector, &x4);

  int x5 = 50;
  vectorPush(vector, &x5);

  printf("Initial state\n");
  vectorPrint(vector);

  return 0;
}