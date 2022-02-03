#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
		char nome[40];
		char tipo[25];
		char local[40];
		char quali[20];
		char resumo[110];
	}Agenda;
	
int GravarArquivo(Agenda *regiao, int *quant, char *nome){
	FILE *arq = fopen(nome, "wb");
	if (arq){
		fprintf(arq, "Quantidade: %d", *quant);
		fwrite(regiao, sizeof(Agenda), *quant, arq);
		return 1;
	}else{
		printf("Nao foi possivel abrir o arquivo");
		return 0;
	}
}
	
int novaAtracao(Agenda *regiao, int MAX, int *quant, char *nome){
	if (*quant < MAX){
		Agenda j;
		fflush(stdin);
		printf("Insira o nome da atracao: ");
		fgets(j.nome, 40, stdin);
		fflush(stdin);
		printf("Insira o tipo de atracao: ");
		fgets(j.tipo, 25, stdin);
		fflush(stdin);
		printf("Insira o local da atracao: ");
		fgets(j.local, 40, stdin);
		fflush(stdin);
		printf("Insira a avaliacao da atracao: ");
		fgets(j.quali, 20, stdin);
		fflush(stdin);
		printf("Insira um resumo da atracao: ");
		fgets(j.resumo, 110, stdin);
		fflush(stdin);
		regiao[*quant] = j;	
		*quant = *quant + 1;
		system("cls");
	}else{
		printf("Essa regiao ja esta cheia, remova alguma atracao antes de adicionar uma nova.\n");
		return 0;
	}
	
	GravarArquivo(regiao, quant, nome);
	
	return 1;
}

int remover(Agenda *regiao, int *quant, char *nome){
	char procura[40];
	int i, j;
	if (*quant > 0){
		printf("Insira o NOME da atracao que deseja remover: ");
		fgets(procura, 40, stdin);
		for (i = 0; i < *quant; i++){
			if (strcmp(procura, regiao[i].nome) == 0){
				for (j = i; j < *quant; j++){
					regiao[j] = regiao[j+1];
				}
				printf("Removido com sucesso.\n");
				*quant = *quant - 1;
				GravarArquivo(regiao, quant, nome);
				return 1;
			}
		}
	}else{
		printf("Sem atracoes nessa regiao, adicione alguma primeiro.\n");
		return 0;
	}
	printf("Falha na remocao, verifique o nome novamente.\n");
	return 0;
}

int alterar(Agenda *regiao, int *quant, char *nome){
	system("cls");
	char procura[40];
	char opc, a;
	int i;
	Agenda K;
	if (quant > 0){
		printf("Insira o NOME da atracao que deseja alterar: ");
		fgets(procura, 40, stdin);
		for (i = 0; i < *quant; i++){
			if (strcmp(procura, regiao[i].nome) == 0){
				do{
					printf("O que deseja alterar da atracao?\n");
					printf("1) Nome\n2) Tipo de atracao\n3) Local\n4) Avaliacao\n5) Resumo da atracao\n");
					fflush(stdin);
					opc = getch();
					system("cls");
					switch(opc){
						case '1':
							printf("Digite o nome novo: ");
							fgets(K.nome, 40, stdin);
							strcpy(regiao[i].nome, K.nome);
							fflush(stdin);
							GravarArquivo(regiao, quant, nome);
							break;
						case '2':
							printf("Digite o tipo novo: ");
							fgets(K.tipo, 25, stdin);
							strcpy(regiao[i].tipo, K.tipo);
							fflush(stdin);
							GravarArquivo(regiao, quant, nome);
							break;
						case '3':
							printf("Digite o local novo: ");
							fgets(K.local, 40, stdin);
							strcpy(regiao[i].local, K.local);
							fflush(stdin);
							GravarArquivo(regiao, quant, nome);
							break;
						case '4':
							printf("Digite a nova avaliacao: ");
							fgets(K.quali, 20, stdin);
							strcpy(regiao[i].quali, K.quali);
							fflush(stdin);
							GravarArquivo(regiao, quant, nome);
							break;
						case '5':
							printf("Digite o novo resumo novo: ");
							fgets(K.resumo, 110, stdin);
							strcpy(regiao[i].resumo, K.resumo);
							fflush(stdin);
							GravarArquivo(regiao, quant, nome);
							break;
						default:
							printf("Opcao invalida. Tente novamente");
					}
					printf("\nDeseja alterar mais algo? Digite 's' para sim ou qualquer outra coisa para nao.\n\n");
					a = getch();
					fflush(stdin);
				}while(a == 's');
				return 1;
			}
		}
	}else{
		printf("Sem atracoes nessa regiao, adicione alguma primeiro.\n");
		return 0;
	}
	printf("Falha na remocao, verifique o nome novamente.\n");
	return 0;
}

void imprimir_atrac(Agenda *regiao, int quant){
	system("cls");
	int i;
	for (i = 0; i < quant; i++){
		printf("Nome: %s", regiao[i].nome);
		printf("Tipo: %s", regiao[i].tipo);
		printf("Local: %s", regiao[i].local);
		printf("Avaliacao: %s", regiao[i].quali);
		printf("Resumo: %s\n", regiao[i].resumo);
	}
}

void mostra_atrac(Agenda *regiao, int quant){
	system("cls");
	int i = rand () % quant;
	printf("Nome: %s", regiao[i].nome);
	printf("Tipo: %s", regiao[i].tipo);
	printf("Local: %s", regiao[i].local);
	printf("Avaliacao: %s", regiao[i].quali);
	printf("Resumo: %s\n", regiao[i].resumo);
}

void lerDados(Agenda *regiao, int *quant, char *nome){
	FILE *arq = fopen(nome, "rb");
	if (arq){
		fscanf(arq, "Quantidade: %d", &*quant);
		fread(regiao, sizeof(Agenda), quant, arq);
	}else{
		printf("Nao foi possivel abrir o arquivo");
	}
}
	
int MenuPrincipal(Agenda *regiao, int MAX, int *quant, char *nome){
	int acao;
	lerDados(regiao, quant, nome);
	
	do{
		printf("O que deseja fazer?\n\n");
		printf("1) Trocar de regiao\n2) Consultar os dados da regiao\n3) Incluir uma descricao\n4) Alterar uma descricao\n5) Excluir uma descricao\n");
		printf("6) Mostrar uma descricao\n7) Mostrar todas as descricoes\n");
		printf("0) Sair do programa\n");
		acao = -1;
		scanf("%d", &acao);
		fflush(stdin);

		switch(acao){
			case 0:
				printf("Obrigado e bom passeio!\n");
				exit(1);
				break;
			case 1:
				system("cls");
				return 0;
				break;
			case 2:
				printf("Nessa regiao temos %d atracoes de um maximo de %d\n\n", *quant, MAX);
				break;
			case 3:
				system("cls");
				novaAtracao(regiao, MAX, quant, nome);
				break;
			case 4:
				alterar(regiao, quant, nome);
				break;
			case 5:
				remover(regiao, quant, nome);
				break;
			case 6:
				mostra_atrac(regiao, *quant);
				break;
			case 7:
				imprimir_atrac(regiao, *quant);
				break;
			default:
				printf("Opcao invalida\n");
		}
		system("pause");
		system("cls");
		
	}while(acao != 0);
	
	return 0;
}
	
int main (){
	int quantSul = 0; 
	int quantSud = 0; 
	int quantCen = 0; 
	int quantNord = 0; 
	int quantNor = 0;
	int MAX = 20;

	Agenda sul[MAX];
	Agenda sudeste[MAX];
	Agenda centro[MAX];
	Agenda nordeste[MAX];
	Agenda norte[MAX];
	
	int escReg;
	char s = 's';
	
	do{
		printf("Bem vindo a Agenda de Atracoes Turisticas do Brasil.\nEscolha a regiao:\n\n");
		printf("1) Sul\n2) Sudeste\n3) Centro Oeste\n4) Nordeste\n5) Norte\n\n");
		escReg = 0;
		scanf("%d", &escReg);
		system("cls");
		switch(escReg){
			case 1:;
				char nome[] = "sul.txt";
				MenuPrincipal(sul, MAX, &quantSul, nome);
				break;
			case 2:;
				char nome1[] = "sudeste.txt";
				MenuPrincipal(sudeste, MAX, &quantSud, nome1);
				break;
			case 3:;
				char nome2[] = "centrooeste.txt";
				MenuPrincipal(centro, MAX, &quantCen, nome2);
				break;
			case 4:;
				char nome3[] = "nordeste.txt";
				MenuPrincipal(nordeste, MAX, &quantNord, nome3);
				break;
			case 5:;
				char nome4[] = "norte.txt";
				MenuPrincipal(norte, MAX, &quantNor, nome4);
				break;
			default:
				printf("Opcao invalida. Tente novamente");
		}
		system("cls");
		
	}while(s == 's');

	return 0;
}
