#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "queue.h"

struct node
{
  void *data;   // Ponteiro para os dados.
  size_t size;  // Tamanho dos dados.
  node_t *next; // Proximo item da fila.
};

struct queue
{
  size_t capacity; // Capacidade total.
  size_t length;   // Numero de itens atualmente armazenados.
  bool empty;      // Vazia?
  bool full;       // Cheia?
  node_t *root;    // Primeiro item da fila.
  node_t *last;    // Ultimo item da fila.
};

queue_t *queue_create(size_t size)
{
  queue_t *queue = malloc(sizeof(struct queue));
  if(queue)
  {
    queue->capacity = size;
    queue->length   = 0;
    queue->empty    = true;
    queue->full     = false; /* para uma fila de tamanho fixo (queue->length == queue->capacity) ? true : false; */
    queue->root     = NULL;
    queue->last     = NULL;
  }
  return queue;
}

void queue_destroy(queue_t *queue)
{
  if(!queue->empty)
  {
    void *p = NULL;
    while(queue->length) if((p = queue_pop(queue, NULL))) free(p);
  }
  free(queue);
}

size_t queue_size(const queue_t *queue)
{
  return queue->length;
}

bool queue_push(queue_t *queue, const void *data, size_t size)
{
  bool ok = false;
  if(!queue->full)
  {
    node_t *new = malloc(sizeof(struct node));
    if(new)
    {
      new->data = malloc(size);
      if(new->data)
      {
        memcpy(new->data, data, size);
        new->next = NULL;
        new->size = size;

        if(queue->empty)
        {
          queue->empty = false;
          queue->root  = new;
          queue->last  = new;
        }
        else
        {
          queue->last->next = new;
          queue->last       = new;
        }

        queue->length++;
        if(queue->length == queue->capacity) queue->full = true;

        ok = true;
      }
      else free(new);
    }
  }
  return ok;
}

void *queue_pop(queue_t *queue, size_t *size)
{
  void *data = NULL;
  if(!queue->empty)
  {
    data = malloc(queue->root->size);
    if(data)
    {
      memcpy(data, queue->root->data, queue->root->size);

      if(size) *size = queue->root->size;
      queue->root = queue->root->next;
      queue->full = false;

      queue->length--;
      if(!queue->length) queue->empty = true;
    }
  }
  return data;
}

bool queue_handler(queue_t *queue, queue_handler_t handler, void *param)
{
  bool ok = false;
  if(!queue->empty)
  {
    void *p;
    size_t size;

    while(queue->length)
    {
      if((p = queue_pop(queue, &size))) if(handler(p, size, param))
      {
        free(p);
        continue;
      }
      break;
    }
    if(queue->empty) ok = true;
  }
  return ok;
}