#include "trie.h"

const int ind[128] = 
{
	['\0'] =  0, [' '] =  1, ['0'] =  2, ['1'] =  3, ['2'] =  4, ['3'] =  5, 
	 ['4'] =  6, ['5'] =  7, ['6'] =  8, ['7'] =  9, ['8'] = 10, ['9'] = 11,
	 ['a'] = 12, ['b'] = 13, ['c'] = 14, ['d'] = 15, ['e'] = 16, ['f'] = 17,
	 ['g'] = 18, ['h'] = 19, ['i'] = 20, ['j'] = 21, ['k'] = 22, ['l'] = 23,
	 ['m'] = 24, ['n'] = 25, ['o'] = 26, ['p'] = 27, ['q'] = 28, ['r'] = 29,
	 ['s'] = 30, ['t'] = 31, ['u'] = 32, ['v'] = 33, ['w'] = 34, ['x'] = 35,
	 ['y'] = 36, ['z'] = 37, ['?'] = 38, ['\n'] = 0
};

const char ind[NUMELEMENTOS] = 
{
	'\0', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
	 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
	 'y', 'z', '?'
};

char* PadronizaString(char* entrada)
{
  size_t tam, wctam;
  wchar_t *letra, *palavra;
  char *nova, *p;
  char *r, *w;
  const char idx[256] =    // mapeia [A-Z,0-9,tab] para [a-z,0-9,' ']
                           // e outros caracteres para '?' (63) 
    {
      0,   1,   2,   3,   4,   5,   6,   7,   8,  32,   0,  11,  12,  13,  14,  15,  // 000-015
     16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  // 016-031
     32,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 032-047
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  63,  63,  63,  63,  63,  63,  // 048-063
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 064-079
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63,  63,  // 080-095
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 096-111
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63, 127,  // 112-127
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 128-143
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 144-159
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 160-175
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 176-191
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 192-207
    100, 110, 111, 111, 111, 111, 111, 120,  48, 117, 117, 117, 117, 121,  63,  63,  // 208-223
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 224-239
    111, 110, 111, 111, 111, 111, 111,  63,  48, 117, 117, 117, 117, 121, 112, 121   // 240-255
    }; 

  tam= strlen( entrada);
  wctam= (tam+1)*4;
  nova = (char*) malloc(tam+1);
  palavra = (wchar_t*) malloc(wctam); 
  mbstowcs( palavra, entrada, wctam );
  p = nova; letra = palavra;
  while (*letra != '\0')
    if(*letra >= 0 && *letra <= 255)
      *p++ = idx[*letra++];
    else{
      *p++ = 63;                     // coloca '?' nos caracteres fora do intervalo [0,255]
      letra++;
    }
  *p = '\0';
  free( palavra );

  /* remove espaços brancos consecutivos. String termina com '\n' ou '\0' */
  r = w = nova;
  while( *r == ' ' && *r!='\0' && *r!='\n') r++;
  while( *r != '\0' && *r!='\n'){
    *w++= *r++;
    if( *r == ' ' ){
      while( *r == ' ' ) r++;
      if( *r != '\0' && *r!= '\n' )
	*w++ = ' ';
    }
  }  
  *w= '\0';
  return nova;
}

char* PadronizaComando(char* entrada)
{
  size_t tam, wctam;
  wchar_t *letra, *palavra;
  char *nova, *p;
  char *r, *w;
  const char idx[256] =    // mapeia [A-Z,0-9,tab] para [a-z,0-9,' ']
                           // e outros caracteres para '?' (63) 
    {
      0,   1,   2,   3,   4,   5,   6,   7,   8,  32,   0,  11,  12,  13,  14,  15,  // 000-015
     16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  // 016-031
     32,  63,  63,  63,  63,  63,  63,  63,  63,  63,  42,  63,  63,  63,  46,  63,  // 032-047
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  63,  63,  63,  63,  63,  63,  // 048-063
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 064-079
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63,  63,  // 080-095
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 096-111
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63, 127,  // 112-127
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 128-143
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 144-159
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 160-175
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 176-191
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 192-207
    100, 110, 111, 111, 111, 111, 111, 120,  48, 117, 117, 117, 117, 121,  63,  63,  // 208-223
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 224-239
    111, 110, 111, 111, 111, 111, 111,  63,  48, 117, 117, 117, 117, 121, 112, 121   // 240-255
    }; 

  tam= strlen( entrada);
  wctam= (tam+1)*4;
  nova = (char*) malloc(tam+1);
  palavra = (wchar_t*) malloc(wctam); 
  mbstowcs( palavra, entrada, wctam );
  p = nova; letra = palavra;
  while (*letra != '\0')
    if(*letra >= 0 && *letra <= 255)
      *p++ = idx[*letra++];
    else{
      *p++ = 63;                     // coloca '?' nos caracteres fora do intervalo [0,255]
      letra++;
    }
  *p = '\0';
  free( palavra );

  /* remove espaços brancos consecutivos. String termina com '\n' ou '\0' */
  r = w = nova;
  while( *r == ' ' && *r!='\0' && *r!='\n') r++;
  while( *r != '\0' && *r!='\n'){
    *w++= *r++;
    if( *r == ' ' ){
      while( *r == ' ' ) r++;
      if( *r != '\0' && *r!= '\n' )
	*w++ = ' ';
    }
  }  
  *w= '\0';
  return nova;
}

ApNodo CriaTrie() {
	return CriaNodo();
}

ApNodo CriaNodo() {
	ApNodo novo = malloc(sizeof(Nodo));
	if (novo == NULL)
		return NULL;
	
	for (int i = 0; i < NUMELEMENTOS; i++)
        novo->prox[i] = NULL;
    
    return novo;
}

ApNodo LiberaTrie (ApNodo t) {

	if (t == NULL)
		return NULL;

	for (int i = 0; i < NUMELEMENTOS; i++) {
		LiberaTrie(t->prox[i]);
	}
	free(t);
	return NULL;
}

int insere (ApNodo t, char* titulo) {
	const int ind[128] = 
	{
		['\0'] =  0, [' '] =  1, ['0'] =  2, ['1'] =  3, ['2'] =  4, ['3'] =  5, 
		 ['4'] =  6, ['5'] =  7, ['6'] =  8, ['7'] =  9, ['8'] = 10, ['9'] = 11,
		 ['a'] = 12, ['b'] = 13, ['c'] = 14, ['d'] = 15, ['e'] = 16, ['f'] = 17,
		 ['g'] = 18, ['h'] = 19, ['i'] = 20, ['j'] = 21, ['k'] = 22, ['l'] = 23,
		 ['m'] = 24, ['n'] = 25, ['o'] = 26, ['p'] = 27, ['q'] = 28, ['r'] = 29,
		 ['s'] = 30, ['t'] = 31, ['u'] = 32, ['v'] = 33, ['w'] = 34, ['x'] = 35,
		 ['y'] = 36, ['z'] = 37, ['?'] = 38, ['\n'] = 0
	};

	int i = 0;
	int indice;
	int tam = strlen(titulo) + 1;

	while (i < tam) {
		indice = ind[ (int) titulo[i]];
		if (t->prox[indice] == NULL ) {
			t->prox[indice] = CriaNodo();
			if (t->prox[indice] == NULL)
				return 0;
		}

		t = t->prox[indice];
		i++;
	}

	return 1;
}

void prefixo(ApNodo t, char* p) {
	const int ind[128] = 
	{
		['\0'] =  0, [' '] =  1, ['0'] =  2, ['1'] =  3, ['2'] =  4, ['3'] =  5, 
		 ['4'] =  6, ['5'] =  7, ['6'] =  8, ['7'] =  9, ['8'] = 10, ['9'] = 11,
		 ['a'] = 12, ['b'] = 13, ['c'] = 14, ['d'] = 15, ['e'] = 16, ['f'] = 17,
		 ['g'] = 18, ['h'] = 19, ['i'] = 20, ['j'] = 21, ['k'] = 22, ['l'] = 23,
		 ['m'] = 24, ['n'] = 25, ['o'] = 26, ['p'] = 27, ['q'] = 28, ['r'] = 29,
		 ['s'] = 30, ['t'] = 31, ['u'] = 32, ['v'] = 33, ['w'] = 34, ['x'] = 35,
		 ['y'] = 36, ['z'] = 37, ['?'] = 38, ['\n'] = 0
	};
	char titulo[TAMMAX];
	int depth = 0;

	while (*p != '\0') {
		titulo[depth] = *p;
		if (t->prox[ind[(int)(*p)]] == NULL) {
			printf("\n");
			return;
		}
		t = t->prox[ind[(int)(*p)]];
		depth++;
		p++;
	}
	const char indParaEsc[NUMELEMENTOS] = 
	{
		'\0', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		 'y', 'z', '?'
	};
	escreveRec(t, titulo, depth, indParaEsc);
}

void tituloMaisLongo(ApNodo t, char* p) {
	const int ind[128] = 
	{
		['\0'] =  0, [' '] =  1, ['0'] =  2, ['1'] =  3, ['2'] =  4, ['3'] =  5, 
		 ['4'] =  6, ['5'] =  7, ['6'] =  8, ['7'] =  9, ['8'] = 10, ['9'] = 11,
		 ['a'] = 12, ['b'] = 13, ['c'] = 14, ['d'] = 15, ['e'] = 16, ['f'] = 17,
		 ['g'] = 18, ['h'] = 19, ['i'] = 20, ['j'] = 21, ['k'] = 22, ['l'] = 23,
		 ['m'] = 24, ['n'] = 25, ['o'] = 26, ['p'] = 27, ['q'] = 28, ['r'] = 29,
		 ['s'] = 30, ['t'] = 31, ['u'] = 32, ['v'] = 33, ['w'] = 34, ['x'] = 35,
		 ['y'] = 36, ['z'] = 37, ['?'] = 38, ['\n'] = 0
	};
	char titulo[TAMMAX];
	char maior[TAMMAX] = "";
	int i = 0;

	while (*p != '\0') {
		titulo[i] = *p;
		titulo[i+1] = '\0';
		if (t->prox[ind[(int)(*p)]] == NULL)
			break;
		t = t->prox[ind[(int)(*p)]];
		i++;
		p++;
		if (t->prox[0] != NULL)
			strcpy(maior, titulo);
	}
	printf("%s\n", maior);
}

void padrao(ApNodo trie, char* padrao) {
	const char ind[NUMELEMENTOS] = 
	{
		'\0', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		 'y', 'z', '?'
	};
	char titulo[TAMMAX];
	padraoRec(trie, padrao, titulo, 0, ind);
}

void padraoRec(ApNodo nodo, char* padrao, char* titulo, int profundidade, const int ind[]) {
	if (*padrao == '\0') {
		if (nodo->prox[0] != NULL) {
			titulo[profundidade] = '\0';
			printf("%s\n", titulo);
		}
		return;
	}

	if (*padrao == '*') {
		padraoRec(nodo, padrao + 1, titulo, profundidade, ind);
		for (int i = 0; i < NUMELEMENTOS; i++) {
            if (nodo->prox[i] != NULL) {
                titulo[profundidade] = ind[i];
                padraoRec(nodo->prox[i], padrao, titulo, profundidade + 1);
            }
        }
	} else if (*pattern == '?') {
        for (int i = 0; i < NUMELEMENTOS; i++) {
            if (nodo->prox[i]) {
                titulo[profundidade] = ind[i];
                padraoRec(nodo->prox[i], padrao + 1, titulo, profundidade + 1);
            }
        }
     } else {
        int index = *pattern - 'a';
        if (node->children[index]) {
            buffer[depth] = *pattern;
            searchWithWildcards(node->children[index], pattern + 1, buffer, depth + 1);
        }
    }

}

void escreveRec(ApNodo nodo, char *titulo, int profundidade, const char ind[]) {
    if (nodo == NULL) 
        return;

    if (nodo->prox[0] != NULL) {
        titulo[profundidade] = '\0';
        printf("%s\n", titulo);
    }

    for (int i = 1; i < NUMELEMENTOS; i++) {
        if (nodo->prox[i] != NULL) {
            char letra;
            letra = ind[i];
            titulo[profundidade] = letra;
            escreveRec(nodo->prox[i], titulo, profundidade + 1, ind);
        }
    }
}

void escreve(ApNodo trie) {
	const char ind[NUMELEMENTOS] = 
	{
		'\0', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		 'y', 'z', '?'
	};
    char titulo[TAMMAX];
    escreveRec(trie, titulo, 0, ind);
}
