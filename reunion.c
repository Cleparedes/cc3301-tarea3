#include <pthread.h>
#include <stdlib.h>

#include "reunion.h"

typedef struct reunion {
  pthread_mutex_t m;
  pthread_cond_t c;
  int cnt;
} Reunion;

Reunion *nuevaReunion(){
  Reunion *r = malloc(sizeof(Reunion));
  pthread_mutex_init(&r->m, NULL);
  pthread_cond_init(&r->c, NULL);
  r->cnt = 0;
  return r;
}

void entrar(Reunion *r){
  pthread_mutex_lock(&r->m);
  r->cnt++;
  pthread_mutex_unlock(&r->m);
}

void concluir(Reunion *r){
  pthread_mutex_lock(&r->m);
  r->cnt--;
  while(r->cnt>0)
    pthread_cond_wait(&r->c, &r->m);
  pthread_cond_broadcast(&r->c);
  pthread_mutex_unlock(&r->m);
}