#include "trie.h"

FILE* abreArquivo (int argc, char** argv) {
	if(argc != 2) {
		printf("Erro nos argumentos da chamada\n");
		printf("Chamada: ./qualFilme nomeArqFilmes\n");
		return NULL;
	}
	return fopen(argv[1], "r");
}

int main (int argc, char** argv) {

	FILE *arq = abreArquivo(argc, argv);
	if(arq == NULL) {
		printf("Erro na abertura do arquivo\n");
		return 1;
	}

	char* local = setlocale(LC_ALL, "pt_BR.UTF-8");
    if (local == NULL) {
    	return -1;
    }

	ApNodo trie = CriaTrie();

	int status; unsigned long tam;
	char *titulo = NULL;
	char *result = NULL;

	while ( (status = getline(&titulo, &tam, arq)) != -1) {
	result = PadronizaString(titulo); 
    insere(trie, result);
    free(result);
	}


	char *comando = NULL;

	while ( (status = getline(&comando, &tam, stdin)) != -1) {
		result = PadronizaComando(comando);
		if (result[1] != ' ')
			*result = '0';
		switch (result[0]) {
			case 'p': 
				prefixo(trie, result + 2);
				break;
			case 'l':
				tituloMaisLongo(trie, result + 2);
				break;
			/*case 'c':
				padrao(trie, result + 2);
				break;*/
			default:
				printf("Comando Invalido\n");
				printf("Comandos Validos:\n'p prefixo'\n");
				printf("'l titulo'\n");
				printf("'c padrao'\n");
				break;			
		}
		free(result);
	}

	free(comando);
	free(titulo);
	LiberaTrie(trie);
	fclose(arq);

	return 0;
}
