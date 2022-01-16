#pragma once

typedef struct node node_t;
typedef struct queue queue_t;
typedef bool (*queue_handler_t)(const void *data, size_t size, void *param);

/**
 * Cria uma lista vazia.
 * 
 * @param size Tamanho para uma fila de comprimento fixo.
 * 
 * @return Ponteiro para o identificador da fila.
 * @return NULL se houver algum erro.
*/
queue_t *queue_create(size_t size);

/**
 * Destroi uma fila, liberando a memoria alocada. Caso exista itens,
 * a memoria deles tambem sera liberada.
 * 
 * @param queue Ponteiro para o identificador da fila.
*/
void queue_destroy(queue_t *queue);

/**
 * Obtem o tamanho atual da fila (numero de itens armazenados).
 * 
 * @param queue Ponteiro para o identificador da fila.
 * 
 * @return Tamanho atual da fila.
*/
size_t queue_size(const queue_t *queue);

/**
 * Coloca um item na fila.
 * 
 * @param queue Ponteiro para o identificador da fila.
 * @param data Ponteiro para os dados.
 * @param size Tamanho em bytes dos dados.
 * 
 * @return true Se for bem sucedida.
 * @return false Se houver algum erro.
*/
bool queue_push(queue_t *queue, const void *data, size_t size);

/**
 * Remove um item da fila.
 * 
 * @param queue Ponteiro para o identificador da fila.
 * @param size Ponteiro que recebe o tamanho dos dados. Pode ser NULL se
 * nao for necessario.
 * 
 * @return Ponteiro para os dados (deve ser liberado usando free()).
 * @return NULL Se houver algum erro.
*/
void *queue_pop(queue_t *queue, size_t *size);

/**
 * Chama a funcao apontada por handler para manipular cada item da fila.
 * 
 * @param queue Ponteiro para o identificador da fila.
 * @param handler Ponteiro para a funcao manipularoda.
 * @param param Ponteiro para uma variavel que sera passada ao manipulador.
 * 
 * @return true Se for bem sucedida.
 * @return false Se houver algum erro.
*/
bool queue_handler(queue_t *queue, queue_handler_t handler, void *param);