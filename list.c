#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List *list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  
  return list;
}

void * firstList(List * list) 
{
  list->current = list->head;
  if (list->current)
  {
    list->current = list->head;
    return list->current->data;
  }
  return NULL;
}

void * nextList(List * list) 
{
  if(list->current != NULL)
  {
    list->current = list->current->next;
  }
  if(list->current != NULL)
  {
    return list->current->data;
  }
  return NULL;
}

void * lastList(List * list) 
{
  if (list->head == NULL)
  {
    return NULL;
  }
  while (list->current->next != NULL)
  {
    list->current = list->current->next;
  }
  return list->current->data;
}

void * prevList(List * list) 
{
  if (list->head == NULL || list->current == list->head)
  {
    return NULL;
  }
  Node *nodoPrev = list->head;

  if(list->current == NULL)return NULL;

  while(nodoPrev->next != list->current)
  {
     nodoPrev = nodoPrev->next;
  }
  list->current = nodoPrev;
  return nodoPrev->data;
}

void pushFront(List * list, void * data) 
{
  Node *nodonuevo = (Node *)(malloc(sizeof(Node)));
  nodonuevo->prev = NULL;
  nodonuevo->data = data;
  nodonuevo->next = list->head;
  if (list->head != NULL)
  {
    list->head->prev = nodonuevo;
  }
  else
  {
    // Si la lista estaba vacía, el nuevo nodo es tanto la cabeza como la cola
    list->tail = nodonuevo;
  }
  list->head = nodonuevo;
}


void pushBack(List * list, void * data) 
{
  Node *nodonuevo = (Node *)(malloc(sizeof(Node)));
  
  list->current = list->tail;
  pushCurrent(list,data);  
}

void pushCurrent(List * list, void * data) 
{
    if (list->current == NULL) {
        pushFront(list, data);
        return;
    }

    Node *nodonuevo = (Node *)malloc(sizeof(Node));
    nodonuevo->data = data;
    nodonuevo->next = list->current->next;
    nodonuevo->prev = list->current;

    if (list->current->next != NULL) {
        list->current->next->prev = nodonuevo;
    } else {
        list->tail = nodonuevo;
    }

    list->current->next = nodonuevo;
}


void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    // Verificar si la lista está vacía o si no hay un nodo actual
    if (list == NULL || list->current == NULL)
        return NULL;

    // Guardar el dato del nodo actual
    void *data = list->current->data;

    // Guardar una referencia al nodo actual
    Node *currentNode = list->current;

    // Avanzar el current al siguiente nodo
    if (list->current->next != NULL) {
        list->current = list->current->next;
    } else {
        list->current = NULL;
    }

    // Actualizar los punteros prev y next de los nodos vecinos
    if (currentNode->prev != NULL) {
        currentNode->prev->next = currentNode->next;
    } else {
        // Si el nodo actual es la cabeza de la lista
        list->head = currentNode->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    }

    if (currentNode->next != NULL) {
        currentNode->next->prev = currentNode->prev;
    } else {
        // Si el nodo actual es la cola de la lista
        list->tail = currentNode->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    }

    // Liberar la memoria del nodo actual
    free(currentNode);

    // Devolver el dato del nodo eliminado
    return data;
}



void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}