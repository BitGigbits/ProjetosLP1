#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedidos{
    int CodAli;
    int QuantPed;
    struct Pedidos *proxP;
}Pedidos;

typedef struct Mesas{
    int numMesa;
    int codGar;
    float total;
    struct Mesas *antM, *proxM;
    struct Pedidos *Pedido;
}Mesas;

typedef struct{
    char nome[30];
    int codAlim;
    float preco;
}Alimentos;

typedef struct{
    char nome[15];
    int codG;
}Garcom;

typedef struct{
    struct Mesas *inicio;
}lista;

int gravar_alimentos(Alimentos *A, int quant){
    FILE *arq = fopen("cardapio.txt", "wb");
    if (arq){
    	fprintf(arq, "Total: %d", quant);
    	fwrite(A, sizeof(Alimentos), quant, arq);
    	fclose(arq);
    	return 1;
	}else{
		printf("Nao foi possivel abrir o arquivo para gravacao.\n");
		return 0;
	}
}

int gravar_garcons(Garcom *G, int quant){
    FILE *arq = fopen("funcionarios.txt", "wb");
    if (arq){
    	fprintf(arq, "Total: %d", quant);
    	fwrite(G, sizeof(Garcom), quant, arq);
    	fclose(arq);
    	return 1;
	}else{
		printf("Nao foi possivel abrir o arquivo para gravacao.\n");
		return 0;
	}
}

int insere_alimentos(Alimentos *A, int *quant, int MAX){
	if(*quant < MAX){
		Alimentos aux;
		printf("Insira o nome do prato/bebida: ");
		fflush(stdin);
		fgets(aux.nome, 30, stdin);
		printf("Insira o codigo desse alimento: ");
		scanf("%d", &aux.codAlim);
		printf("Insira o preco desse alimento: ");
		scanf("%g", &aux.preco);
		A[*quant] = aux;
		*quant = *quant + 1;
	}else{
		printf("Mais alimentos do que o suportado pelo sistema.\n");
		return 0;
	}

	gravar_alimentos(A, *quant);
	return 1;
}

int insere_garcom(Garcom *G, int *quant, int MAX){
	if(*quant < MAX){
		Garcom aux;
		printf("Insira o nome do Garcom: ");
		fflush(stdin);
		fgets(aux.nome, 30, stdin);
		printf("Insira o codigo do novo Garcom: ");
		scanf("%d", &aux.codG);
		G[*quant] = aux;
		*quant = *quant + 1;
	}else{
		printf("Mais garcons registrados do que o suportado pelo sistema.\n");
		return 0;
	}

	gravar_garcons(G, *quant);
	return 1;
}

int imprime_alimentos(Alimentos *A, int quant){
	int i;
	system("cls");
	if(quant <= 0){
		printf("Sem alimentos no cardapio, por favor insira um.\n");
		system("pause");
		return 0;
	}else{
		for (i = 0; i < quant; i++){
        	printf("Nome: %s", A[i].nome);
        	printf("Codigo: %d\n", A[i].codAlim);
        	printf("Preco: %.2f\n\n", A[i].preco);
    	}
	}
	printf("\n");
	system("pause");
	return 1;
}

int remover_alimentos(Alimentos *A, int *quant){
	int i, j, pesquisa;
	char a;

	printf("\nDeseja imprimir todo o cardapio para verificar o codigo do prato a ser removido? Digite 's' para sim, ou outra coisa para nao: ");
	fflush(stdin);
	scanf("%c", &a);
	printf("\n");
	if (a == 's'){
		imprime_alimentos(A, *quant);
	}
	system("cls");

	if (*quant > 0){
		printf("Insira o codigo do alimento que deseja remover: ");
		fflush(stdin);
		scanf("%d", &pesquisa);
		for (i = 0; i < *quant; i++){
			if(A[i].codAlim == pesquisa){
				for (j = i; j < *quant; j++){
					A[j] = A[j+1];
				}
				printf("Removido com sucesso.\n");
				*quant = *quant - 1;
				gravar_alimentos(A, *quant);
				return 1;
			}
		}
	}else{
		printf("Sem alimentos no cardapio.\n");
		system("pause");
		return 0;
	}
	printf("Falha na remocao, verifique o codigo novamente.\n");
	return -1;
}

int imprime_garcons(Garcom *G, int quant){
	int i;
	system("cls");
	if(quant <= 0){
		printf("Sem funcionarios registrados, por favor registre um.\n");
		return 0;
	}else{
		for (i = 0; i < quant; i++){
        	printf("Nome: %s", G[i].nome);
        	printf("Codigo: %d\n", G[i].codG);
    	}
	}
	printf("\n");
	system("pause");
	return 1;
}

int remover_garcons(Garcom *G, int *quant){
	int i, j, pesquisa;
	char a;

	printf("\nDeseja imprimir todos os funcionarios para verificar o codigo a ser removido? Digite 's' para sim, ou outra coisa para nao: ");
	fflush(stdin);
	scanf("%c", &a);
	printf("\n");
	if (a == 's'){
		imprime_garcons(G, *quant);
	}
	system("cls");

	if (*quant > 0){
		printf("Insira o codigo do garcom que deseja remover do sistema: ");
		fflush(stdin);
		scanf("%d", &pesquisa);
		for (i = 0; i < *quant; i++){
			if(G[i].codG == pesquisa){
				for (j = i; j < *quant; j++){
					G[j] = G[j+1];
				}
				printf("Removido com sucesso.\n");
				*quant = *quant - 1;
				gravar_garcons(G, *quant);
				return 1;
			}
		}
	}else{
		printf("Sem funcionarios registrados.\n");
		return 0;
	}
	printf("Falha na remocao, verifique o codigo novamente.\n");
	return -1;
}

int alterar_alimentos(Alimentos *A, int quant){
	int s, i, pesquisa;
	char a;
	printf("\nDeseja imprimir todo o cardapio para verificar o codigo do prato a ser alterado? Digite 's' para sim, ou outra coisa para nao: ");
	fflush(stdin);
	scanf("%c", &a);
	printf("\n");
	if (a == 's'){
		imprime_alimentos(A, quant);
	}
	system("cls");
	if (quant > 0){
		printf("Digite o codigo do prato que quer alterar: ");
		fflush(stdin);
		scanf("%d", &pesquisa);
		for (i = 0; i < quant; i++){
			if (pesquisa == A[i].codAlim){
				do{
					printf("\nO que deseja alterar?\n");
					printf("1) Nome\n2) Codigo\n3) Preco\n");
					scanf("%d", &s);
					system("cls");
					switch(s){
						case 1:
							printf("Digite o nome novo: ");
							fflush(stdin);
							fgets(A[i].nome, 30, stdin);
							gravar_alimentos(A, quant);
							break;
						case 2:
							printf("Digite o codigo novo: ");
							fflush(stdin);
							scanf("%d", &A[i].codAlim);
							gravar_alimentos(A, quant);
							break;
						case 3:
							printf("Digite o preco novo: ");
							fflush(stdin);
							scanf("%f", &A[i].preco);
							gravar_alimentos(A, quant);
							break;
						default:
							printf("Opcao invalida. Tente novamente");
					}
					printf("\nDeseja alterar mais algo? Digite 's' para sim ou qualquer outra coisa para nao.\n\n");
					fflush(stdin);
					scanf("%c", &a);
				}while(a == 's');
				return 1;
			}
		}
	}else{
		printf("Sem alimentos no cardapio.\n");
		return 0;
	}
}

int alterar_garcons(Garcom *G, int quant){
	int s, i, pesquisa;
	char a;
	printf("\nDeseja imprimir todos os funcionarios para verificar o codigo do que precisa ser alterado? Digite 's' para sim, ou outra coisa para nao: ");
	fflush(stdin);
	scanf("%c", &a);
	printf("\n");
	if (a == 's'){
		imprime_garcons(G, quant);
	}
	system("cls");
	if (quant > 0){
		printf("Digite o codigo do garcom que quer alterar as infos: ");
		scanf("%d", &pesquisa);
		for (i = 0; i < quant; i++){
			if (pesquisa == G[i].codG){
				do{
					printf("\nO que deseja alterar?\n");
					printf("1) Nome\n2) Codigo\n");
					scanf("%d", &s);
					system("cls");
					switch(s){
						case 1:
							printf("Digite o nome novo: ");
							fflush(stdin);
							fgets(G[i].nome, 15, stdin);
							gravar_garcons(G, quant);
							break;
						case 2:
							printf("Digite o codigo novo: ");
							fflush(stdin);
							scanf("%d", &G[i].codG);
							gravar_garcons(G, quant);
							break;
						default:
							printf("Opcao invalida. Tente novamente");
					}
					printf("\nDeseja alterar mais algo? Digite 's' para sim ou qualquer outra coisa para nao.\n\n");
					fflush(stdin);
					scanf("%c", &a);
				}while(a == 's');
				return 1;
			}
		}
	}else{
		printf("Sem funcionarios registrados.\n");
		return 0;
	}
}

void lerDados(Alimentos *A, Garcom *G, int *quantA, int *quantG){
	FILE *arq1 = fopen("cardapio.txt", "rb");
	FILE *arq2 = fopen("funcionarios.txt", "rb");

	if (arq1){
		fscanf(arq1, "Total: %d", &*quantA);
		fread(A, sizeof(Alimentos), *quantA, arq1);
		fclose(arq1);
	}else{
		printf("Nao foi possivel abrir o arquivo de cardapio.\n\n");
	}

	if (arq2){
		fscanf(arq2, "Total: %d", &*quantG);
		fread(G, sizeof(Garcom), *quantG, arq2);
		fclose(arq2);
	}else{
		printf("Nao foi possivel abrir o arquivo de funcionarios.\n\n");
	}
    printf("\n");
}

int menu(Alimentos *A, int *quantA, Garcom *G, int *quantG, int MAX_A, int MAX_G){
	int YY;

	do{
		printf("0) Voltar ao menu principal\n1) Inserir um novo alimento/bebida no cardapio\n");
		printf("2) Remover um alimento/bebida no cardapio\n3) Alterar uma descricao de um alimento/bebida\n");
		printf("4) Cadastrar um novo garcom no sistema \n5) Descadastrar um garcom do sistema\n");
		printf("6) Alterar uma descricao de um garcom do sistema\n7) Mostrar todos os garcons\n8) Mostrar o cardapio completo\n");
		scanf("%d", &YY);

		switch(YY){
			case 0:
				break;
			case 1:;
				insere_alimentos(A, quantA, MAX_A);
				break;
			case 2:
				remover_alimentos(A, quantA);
				printf("\n");
				system("pause");
				break;
			case 3:
				alterar_alimentos(A, *quantA);
				break;
			case 4:
				insere_garcom(G, quantG, MAX_G);
				break;
			case 5:
				remover_garcons(G, quantG);
				printf("\n");
				system("pause");
				break;
			case 6:
				alterar_garcons(G, *quantG);
				break;
			case 7:
				imprime_garcons(G, *quantG);
				break;
			case 8:
				imprime_alimentos(A, *quantA);
				break;
			default:
				printf("Opcao invalida.\n");
				system("pause");
		}
        system("cls");

	}while(YY != 0);
}

float BuscaPreco(Alimentos *A, int quant, int codProcura){
	int i;
	for (i = 0; i < quant; i++){
		if (codProcura == A[i].codAlim){
			return A[i].preco;
		}
	}
}

int pedido_novo(lista *R, Alimentos *A, int quant){
	int n;
	Mesas *m;
	Pedidos *p = (Pedidos*)malloc(sizeof(Pedidos));
	Pedidos *confere;

	printf("Insira o numero da mesa: ");
	fflush(stdin);
	scanf("%d", &n);

	m = R->inicio;
	if (m == NULL){
		printf("Nenhuma mesa ainda adicionada.\n\n");
		system("pause");
		return -1;
	}

	while (m->numMesa != n){
		m = m->proxM;
		if (m == NULL){
			printf("Mesa nao encontrada.\n\n");
			system("pause");
			return -1;
		}
	}
	confere = m->Pedido;
	printf("Insira o codigo do alimento pedido: ");
	scanf("%d", &p->CodAli);
	while (confere != NULL){
		if (confere->CodAli == p->CodAli){
			printf("Insira a quantidade: ");
			scanf("%d", &p->QuantPed);
			confere->QuantPed = confere->QuantPed + p->QuantPed;
			m->total = m->total + (p->QuantPed * BuscaPreco(A, quant, p->CodAli));
			free(p);
			return 1;
		}
		confere = confere->proxP;
	}
	printf("Insira a quantidade: ");
	scanf("%d", &p->QuantPed);
	m->total = m->total + (p->QuantPed * BuscaPreco(A, quant, p->CodAli));

	p->proxP = m->Pedido;
	m->Pedido = p;
	return 1;
}

void mesa_nova(lista *R){
	system("cls");
	Mesas *m = (Mesas*)malloc(sizeof(Mesas));
	printf("Digite o numero da mesa: ");
	fflush(stdin);
	scanf("%d", &m->numMesa);
	printf("Digite o codigo do garcom que esta atendendo essa mesa: ");
	fflush(stdin);
	scanf("%d", &m->codGar);
	m->total = 0;
	m->Pedido = NULL;
	m->antM = NULL;
	m->proxM = R->inicio;
	if(m->proxM != NULL){
		m->proxM->antM = m;
	}
	R->inicio = m;
}

void BuscaAlimento(Alimentos *A, int quant, int codProcura, char *string){
	int i;
	for (i = 0; i < quant; i++){
		if (codProcura == A[i].codAlim){
			strcpy(string, A[i].nome);
			break;
		}
	}
}

void BuscaGarcom(Garcom *G, int quant, int codProcura, char *string){
	int i;
	for (i = 0; i < quant; i++){
		if (codProcura == G[i].codG){
			strcpy(string, G[i].nome);
			break;
		}
	}
}

int remover_lista(lista *R, Alimentos *A, int quant){
	int resp, num, num2, i;
	Mesas *m, *b;
	Pedidos *p, *rem;
	m = R->inicio;
	if (m == NULL){
			printf("Sem mesas registradas\n");
			system("pause");
			return -1;
	}
	printf("Voce deseja remover um pedido ja feito ou remover uma mesa?\n\n");
	printf("1) Remover uma mesa\n2) Remover um pedido");
	fflush(stdin);
	scanf("%d", &resp);
	if (resp == 1){
		system("cls");
		b = NULL;
		printf("Digite o numero da mesa a remover: ");
		fflush(stdin);
		scanf("%d", &num);
		while (m->numMesa != num){
			b = m;
			m = m->proxM;
			if (m == NULL){
				printf("Mesa nao encontrada");
				return -1;
			}
		}
		if (b == NULL){
			R->inicio = R->inicio->proxM;
			if (R->inicio != NULL){
				R->inicio->antM = NULL;
			}
		}else if (m->proxM == NULL){
			b->proxM = NULL;
		}else{
			b->proxM = m->proxM;
			m->proxM->antM = b;
		}
		free(m);
		printf("Sucesso na remocao!\n");
		system("pause");
		return 1;
	}else if(resp == 2){
		printf("Digite o numero da mesa para remover um pedido: ");
		fflush(stdin);
		scanf("%d", &num);
		while (m->numMesa != num){
			m = m->proxM;
			if (m == NULL){
				printf("Mesa nao encontrada");
				return -1;
			}
		}
		system("cls");
		rem = m->Pedido;
		if (rem == NULL){
			printf("Sem pedidos na mesa\n");
			system("pause");
			return -1;
		}
		printf("Agora, digite o codigo do alimento a ser removido: ");
		fflush(stdin);
		scanf("%d", &num2);
		p = NULL;
		rem = m->Pedido;
		while (rem->CodAli != num2){
			p = rem;
			rem = rem->proxP;
			if (rem == NULL){
				printf("Alimento nao encontrado nesse pedido.");
				system("pause");
				return -1;
			}
		}
		m->total = m->total - (m->Pedido->QuantPed * BuscaPreco(A, quant, num2));
		system("cls");
		if(p == NULL){
			m->Pedido = rem->proxP;
		}else{
			p->proxP = p->proxP->proxP;
		}
		free(rem);
		printf("Sucesso na remocao!\n");
		system("pause");
		return 1;
	}else{
		printf("Opcao invalida, tente novamente");
		system("pause");
		return 0;
	}
}

int alterar_lista(lista *R, Garcom *G, int quantG, Alimentos *A, int quantA){
	int resp, n = 0, n2, n3;
	char t[15];
	Mesas *m, *aux;
	Pedidos *p;
	m = R->inicio;
	if (m == NULL){
		printf("Sem mesas registradas\n");
		system("pause");
		return -1;
	}
	printf("Voce deseja alterar um pedido ja feito ou alterar infos de uma mesa?\n\n");
	printf("1) Alterar uma mesa\n2) Alterar um pedido");
	fflush(stdin);
	scanf("%d", &resp);
	system("cls");
	if (resp == 1){
		aux = m;
		do{
			printf("As mesas serao apresentadas uma a uma, selecione a mesa desejada apertando 1, ou 2 para");
			printf(" apresentar a proxima mesa ou 3 para retroceder uma mesa:\n\n");

			if (m == NULL){
				printf("Fim da lista, aperte 3 para voltar para a mesa anterior: ");
			}else{
				printf("Mesa: %d\n", m->numMesa);
				BuscaGarcom(G, quantG, m->codGar, t);
				printf("Garcom: %s", t);
				printf("Total: %.2f\n\n", m->total);
			}
			fflush(stdin);
			scanf("%d", &n);

			if (n == 1){
				break;
			}else if (n == 2){
				aux = m;
				m = m->proxM;
			}else if(n == 3){
				if(m == NULL){
					m = aux;
					aux = m->antM;
				}else if(m->antM != NULL){
					aux = aux->antM;
					m = m->antM;
				}else{
					continue;
				}
			}else{
				printf("Opcao invalida");
			}
			system("cls");
		}while (n != 1);
		printf("O que deseja alterar?\n\n");
		printf("1) Numero da mesa\n2) Garcom da mesa\n");
		fflush(stdin);
		scanf("%d", &n);
		if(n == 1){
			printf("Digite o novo numero da mesa: ");
			scanf("%d", &m->numMesa);
			printf("Alterado com sucesso\n");
			system("pause");
			return 1;
		}else if(n == 2){
			printf("Digite o codigo do novo garcom");
			scanf("%d", &m->codGar);
			printf("Alterado com sucesso\n");
			system("pause");
			return 1;
		}else{
			printf("Opcao invalida");
			system("pause");
			return 0;
		}
	}else if(resp == 2){
		printf("Digite o numero da mesa para se alterar o pedido: ");
		fflush(stdin);
		scanf("%d", &n);
		while (m->numMesa != n){
			m = m->proxM;
			if (m == NULL){
				printf("Mesa nao encontrada");
				return -1;
			}
		}
		system("cls");
		printf("O que deseja alterar?\n\n");
		printf("1) Tudo\n2) Somente a quantidade");
		scanf("%d", &n2);
		p = m->Pedido;
		if (n2 == 1){
			printf("Insira o codigo do alimento de um dos pedidos: ");
			scanf("%d", &n);
			while (p->CodAli != n){
				p = p->proxP;
				if (p == NULL){
					printf("Alimento nao encontrado");
					return -1;
				}
			}
			printf("\nAgora insira o novo codigo de alimento que esse mesmo ira se tornar: ");
			scanf("%d", &n2);
			p->CodAli = n2;
			system("cls");
			printf("\nFeito isso, insira agora a quantidade: ");
			scanf("%d", &n3);
			p->QuantPed = n3;
		}else if(n2 == 2){
			printf("Insira o codigo do alimento de um dos pedidos: ");
			scanf("%d", &n2);
			while (p->CodAli != n2){
				p = p->proxP;
				if (p == NULL){
					printf("Alimento nao encontrado");
					return -1;
				}
			}
			printf("\nFeito isso, insira agora a NOVA quantidade (se tem 2 e voce quer que tenha 4, insira o numero 4.)\n");
			scanf("%d", &n3);
			m->total = m->total - ((p->QuantPed - n3) * BuscaPreco(A, quantA, n2));
			p->QuantPed = n3;
		}else{
			printf("Opcao invalida, tente novamente.\n");
			system("pause");
			return 0;
		}
		system("cls");
		printf("Sucesso na alteracao!\n");
		system("pause");
		return 1;
	}else{
		printf("Opcao invalida, tente novamente");
		system("pause");
		return 0;
	}
}

int notafiscal(lista *R, Alimentos *A, int quantA, Garcom *G, int quantG){
	Mesas *im;
	Pedidos *pp;
	char s[30];
	char t[15];
	int num;

	printf("Digite o numero da mesa para imprimir a nota fiscal: ");
	fflush(stdin);
	scanf("%d", &num);
	im = R->inicio;

	if (im == NULL){
		printf("Sem mesas adicionadas ainda.\n\n");
		system("pause");
		return -1;
	}

	while (im->numMesa != num){
		im = im->proxM;
		if (im == NULL){
			printf("Mesa nao encontrada.\n\n");
			system("pause");
			return -1;
		}
	}
	system("cls");
	pp = im->Pedido;

	printf("Mesa: %d\n", im->numMesa);
	BuscaGarcom(G, quantG, im->codGar, t);
	printf("Garcom: %s", t);
	printf("Total: %.2f\n\n", im->total);
	while (pp != NULL){
		printf("%d - ", pp->QuantPed);
		printf("%.2f - ", pp->QuantPed*BuscaPreco(A, quantA, pp->CodAli));
		BuscaAlimento(A, quantA, pp->CodAli, s);
		printf("%s", s);
		pp = pp->proxP;
	}
    system("pause");
    system("cls");
	return 1;
}

void destruir(lista *R){
    Pedidos *p, *pp;
    Mesas *m, *mm;
    mm = R->inicio;
    pp = R->inicio->Pedido;
    while (mm != NULL){
        while (pp != NULL){
            p = pp;
            pp = pp->proxP;
            free(p);
        }
        m = mm;
        mm = mm->proxM;
        free(m);
    }
    printf("Saindo...\n");
}

int main(){
	int resp, quantA = 0, quantG = 0;
	int MAX_A = 100, MAX_G = 30;
	lista R;
	Alimentos A[MAX_A];
	Garcom G[MAX_G];
	R.inicio = NULL;

	lerDados(A, G, &quantA, &quantG);

	do{
		printf("Bem vindo ao programa de controle de comandas.\n");
        printf("Insira a opcao desejada: \n\n");
        printf("0) Sair do Programa\n1) Criar uma nova comanda\n2) Inserir pedidos numa mesa\n");
        printf("3) Remover um pedido ou fechar uma mesa\n4) Alterar o pedido ou os dados de uma mesa\n");
        printf("5) Imprimir nota fiscal de uma mesa\n6) Abrir o menu de alimentos e garcons\n");
        scanf("%d", &resp);
        system("cls");

		switch(resp){
            case 0:
                break;
            case 1:
            	mesa_nova(&R);
                break;
            case 2:
            	pedido_novo(&R, A, quantA);
                break;
            case 3:
				remover_lista(&R, A, quantA);
                break;
            case 4:
				alterar_lista(&R, G, quantG, A, quantA);
                break;
            case 5:
            	notafiscal(&R, A, quantA, G, quantG);
                break;
            case 6:
            	menu(A, &quantA, G, &quantG, MAX_A, MAX_G);
            	break;
            default:
                printf("Opcao invalida, tente novamente.");
        }
        system("cls");

	}while(resp != 0);
	destruir(&R);

	return 0;
}
