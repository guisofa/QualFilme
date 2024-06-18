#ifndef _trie_n_aria_
#define _trie_n_aria_

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


#define NUMELEMENTOS 39 // /0, ' ', 0-9, a-z, ?
#define TAMMAX 128 // tamanho maximo do titulo  

typedef struct Nodo *ApNodo;
typedef struct Nodo {
	ApNodo prox[NUMELEMENTOS];
} Nodo;

char* PadronizaString (char *entrada);
char* PadronizaComando (char *entrada);

ApNodo CriaTrie();
ApNodo CriaNodo(); 

ApNodo LiberaTrie (ApNodo t);

int insere (ApNodo t, char* palavra);

void escreve (ApNodo raiz);
void escreveRec (ApNodo nodo, char *titulo, int profundidade, const char ind[]);

void prefixo(ApNodo t, char* p);

void tituloMaisLongo(ApNodo t, char* p);

void padrao(ApNodo trie, char* p);
void padraoRec(ApNodo t, char* p, char* titulo, int profundidade, const int ind[]);





#endif