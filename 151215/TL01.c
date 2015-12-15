#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXNOME 100
#define MAXREGISTROS 1000

typedef struct TipoAgenda_ {
	char nome[MAXNOME];
	int matricula;
	int DDD;
	int telefone;
	char tipo; //'C' para celular ou 'F' para fixo
} TipoAgenda	;

char Menu() {
	char escolha, upper;
	
	printf("-------------------------------\n\n");
	printf(" B - Buscar telefone pelo nome\n");
	printf(" I - Inserir novo registro\n");
	printf(" A - Apagar registro pelo nome\n");
	printf(" L - Listar nomes na agenda\n");
	printf(" O - Ordenar nomes na agenda\n");
	printf(" S - Sair\n");
	printf("-------------------------------\n\n");
	printf(" Escolha uma das opções\n> ");
	scanf("%c", &escolha);
	if(escolha >= 'a' && escolha <= 'z'){
		return ('A' + escolha - 'a');
	}
	else{
		return escolha;
	}
}

int BuscarPorNomeNaAgenda(TipoAgenda *lista_de_contatos[]) {
	char nomeBuscado[MAXNOME], error;
	int i = 0;
	
	system("clear");
	
	printf("Digite o nome do contato\n");
	scanf("%c", &error);
	fgets(nomeBuscado,MAXNOME,stdin);
	strtok(nomeBuscado, "\n");
	system("clear");
	for(i = 0; i < MAXREGISTROS; i++) {
		if(lista_de_contatos[i] != NULL) {
			if(strcmp(lista_de_contatos[i]->nome,nomeBuscado) == 0) {
				printf("> %s - (%d) %d (%c)\n", lista_de_contatos[i]->nome, lista_de_contatos[i]->DDD, lista_de_contatos[i]->telefone, lista_de_contatos[i]->tipo);
				return i;
			}
		}
	}
	printf("> Contato não encontrado\n");
	return -1;
}

int ListarNomesDaAgenda(TipoAgenda *lista_de_contatos[]) {
	int i = 0, cont = 1;
	char error; 
	
	system("clear");
	
	for(i = 0; i < MAXREGISTROS; i++) {
		if(lista_de_contatos[i] != NULL) {
			printf("%d - %s\n", (cont++),lista_de_contatos[i]->nome);
		}
	}
	scanf("%c", &error);
}

int BuscarEspacoVazio(TipoAgenda *lista_de_contatos[]) {
	int i;
	for(i = 0; i < MAXREGISTROS; i++) {
		if(lista_de_contatos[i] == NULL) {
			return i;
		}
	}
	printf("> Ops! A lista está cheia\n");
	return -1;
}

TipoAgenda* NovoContato() {
	char nome[MAXNOME], tipo, error;
	int matricula, DDD, telefone;
	TipoAgenda *novoContato;
	novoContato = (TipoAgenda *)malloc(sizeof(TipoAgenda));
	
	printf("Matrícula: ");
	scanf("%d", &matricula);
	printf("Nome: ");
	scanf("%c", &error);
	fgets(nome,MAXNOME,stdin);
	strtok(nome, "\n");
	printf("DDD: ");
	scanf("%d", &DDD);
	printf("Telefone: ");
	scanf("%d", &telefone);
	printf("Tipo: ");
	scanf("%c", &error);
	scanf("%c", &tipo);
	scanf("%c", &error);
	
	novoContato->matricula = matricula;
	strcpy(novoContato->nome,nome);
	novoContato->DDD = DDD;
	novoContato->telefone = telefone;
	novoContato->tipo = tipo;
	
	return novoContato;
}

int OrdenarLista(TipoAgenda *lista_de_contatos[]) {
	char error;
	int i=0, j=0, estaCompleto = 0;
	TipoAgenda *temp;
	scanf("%c", &error);
	temp = (TipoAgenda *)malloc(sizeof(TipoAgenda));
	system("clear");
	
	for(i = 0; i < MAXREGISTROS; i++) {
		if(lista_de_contatos[i] != NULL) {
			for(j = i; j < MAXREGISTROS; j++) {
				if(lista_de_contatos[j] != NULL) {
					if(strcmp(lista_de_contatos[i]->nome,lista_de_contatos[j]->nome) > 0) {
						temp = lista_de_contatos[i];
						lista_de_contatos[i] = lista_de_contatos[j];
						lista_de_contatos[j] = temp;
					}
				}
			}
		}
	}
}

int main (int narg, char *argv[]) {
	
	FILE *arq;
	char buffer[100];
	int cont = 0, sair = 1, tamanho_agenda = 0, posicao, i;
	char escolha;
	TipoAgenda *lista_de_contatos[MAXREGISTROS], contatoVazio;
	
	//Inicializando o vetor
	for(i = 0; i < MAXREGISTROS; i++) {
		lista_de_contatos[i] = NULL;
	}
	
	system("clear");
	
	if(narg > 1) {
		arq = fopen(argv[1],"r");
		
		if(arq == NULL) {
			printf("Erro lendo o arquivo.\n");
			return EXIT_FAILURE;
		}
		
		while(!feof(arq)) {
			if(fgets(buffer,100,arq)) {
				lista_de_contatos[cont] = (TipoAgenda *)malloc(sizeof(TipoAgenda));
				buffer[strlen(buffer) - 1] = '\0';
				lista_de_contatos[cont]->matricula = atoi(buffer);
			}
			if(fgets(buffer,100,arq)) {
				buffer[strlen(buffer) - 1] = '\0';
				strcpy(lista_de_contatos[cont]->nome, buffer);
			}
			if(fgets(buffer,100,arq)) {
				buffer[strlen(buffer) - 1] = '\0';
				lista_de_contatos[cont]->DDD = atoi(buffer);
			}
			if(fgets(buffer,100,arq)) {
				buffer[strlen(buffer) - 1] = '\0';
				lista_de_contatos[cont]->telefone = atoi(buffer);
			}
			if(fgets(buffer,100,arq)) {
				buffer[strlen(buffer) - 1] = '\0';
				lista_de_contatos[cont++]->tipo = buffer[0];
			}
		}
		printf("> %d contatos adicionados.\n\n", cont);
		
		fclose(arq);	
	}
	do {
		switch (Menu())
		{
			case 'B':
				BuscarPorNomeNaAgenda(lista_de_contatos);
				break;
			case 'I':
				posicao = BuscarEspacoVazio(lista_de_contatos);
				if(posicao > 0) {
					lista_de_contatos[posicao] = NovoContato();
					printf("> Contato adicionado com sucesso!\n");
				}
				break;
			case 'A':
				posicao = BuscarPorNomeNaAgenda(lista_de_contatos);
				if(posicao > 0) {
					lista_de_contatos[posicao] = NULL;
					printf("> Contato removido com sucesso!\n");
				}
				break;
			case 'L':
				ListarNomesDaAgenda(lista_de_contatos);
				break;
			case 'O':
				OrdenarLista(lista_de_contatos);
				printf("> Contato ordenados alfabeticamente!\n");
				break;
			case 'S':
				sair = 0;
				printf("Saindo...\n");
				break;

			default:
				system("clear");
				printf("Opção inválida, tente novamente\n");
		}
	
	} while(sair);
	
	return EXIT_SUCCESS;
}
