
typedef struct pilha pilha_t;

pilha_t *cria_pilha();

void destruir_pilha(pilha_t *p);
int pilha_vazia(pilha_t *p);
int push(pilha_t *p, int x);
int pop(pilha_t *p, int *x);
int top(pilha_t *p, int *x);