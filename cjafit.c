/*
Lila Maria Salvador Frazão                    M-510809
Paulo Victor Alves Fabrício                   M-511013
Pedro De Carvalho Chaaban                     M-511175
Rian Rodrigues Mourão                         M-508927
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clrscr(){ // Limpar tela
    system("@cls||clear");
}

//////////////////////////////////////////////////////VARIAVEIS E ESTRUTURAS///////////////////////////////////////////////////////
typedef struct instrutor{
    char *name;
    int diasDeOficio[5]; 
    char *cpf;
    char *senha;
    float salario;
    struct instrutor* prox;
}INSTRUTOR;

typedef struct cliente{
    char *nome;
    float peso;
    int altura; //em cm
    int plano; //guarda o indice correspondente ao plano escolhido
    INSTRUTOR *instrutor;
    char *cpf;
    char *senha;
    struct cliente* prox;
}CLIENTE;

CLIENTE *inicioCl = NULL;
int tamCl = 0;

INSTRUTOR *inicioIns = NULL;
int tamIns = 0;

// Guarda os preços de cada plano e o nome de cada um
double planos[5] = {55.89, 65.89, 75.79, 84.69, 92.69};
char *nomesPlanos[5] = {"Mensal", "Bimestral", "Trimestral", "Semestral", "Anual"};

char *osDiasDaSemana[5] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};

////////////////////////////////////////////////ARQUI/////////////////////////////////////////////////////////

//Gravação e Leitura Cliente:
void gravacao_arquivo_cliente(){
    FILE * arqGrv;
    CLIENTE * estrutura = inicioCl;
    int qtd_atual = tamCl;

    arqGrv = fopen("clientes.bin", "wb");
    if (arqGrv == 0){
        printf("Erro ao abrir o Arquivo\n");
    }

    fwrite(&qtd_atual, sizeof(int), 1, arqGrv);
    if(fwrite(&qtd_atual, sizeof(int), 1, arqGrv) != 1){
        printf("Erro ao escrever\n");
    }

    for (int i = 0; i < qtd_atual; i++){
        fwrite(estrutura, sizeof(CLIENTE), 1, arqGrv);
        estrutura = estrutura->prox;
    }

    printf("Passou na escrita\n");
    fclose(arqGrv);
}

void leitura_arquivo_cliente(){
    FILE * arqLtr;
    CLIENTE * estrutura;
    CLIENTE * aux_ltr;
    int qtd_atual;

    arqLtr = fopen("clientes.bin", "rb");
    if (arqLtr == 0){
        printf("Não foi possível abrir o arquivo\n");
    }
    
    fread(&qtd_atual, sizeof(int), 1, arqLtr);
    if(fread(&qtd_atual, sizeof(int), 1, arqLtr) != 1){
        printf("Erro ao ler\n");
    }

    tamCl = qtd_atual;

    for(int i = 0; i < qtd_atual; i++){
        estrutura = malloc(sizeof(CLIENTE));
        fread(estrutura, sizeof(CLIENTE), 1, arqLtr);
        
        if(inicioCl == NULL){
            inicioCl = estrutura;

        }else{
            aux_ltr = inicioCl;
            for(int y = 0; aux_ltr->prox != NULL; y++) aux_ltr = aux_ltr->prox;
            aux_ltr->prox = estrutura;
        }
    }
    printf("Passou na leitura\n");
    fclose(arqLtr);
    
}

//Gravação e Leitura de Instrutor:

void gravacao_arquivo_instrutor(){
    FILE * arqGrv;
    INSTRUTOR * estrutura = inicioIns;
    int qtd_atual = tamIns;

    arqGrv = fopen("instrutores.bin", "wb");
    if (arqGrv == 0){
        printf("Erro ao abrir o Arquivo\n");
    }

    fwrite(&qtd_atual, sizeof(int), 1, arqGrv);
    if(fwrite(&qtd_atual, sizeof(int), 1, arqGrv) != 1){
        printf("Erro ao escrever\n");
    }

    for (int i = 0; i < qtd_atual; i++){
        fwrite(estrutura, sizeof(INSTRUTOR), 1, arqGrv);
        estrutura = estrutura->prox;
    }
    
    fclose(arqGrv);
}

void leitura_arquivo_instrutor(){
    FILE * arqLtr;
    INSTRUTOR * estrutura;
    INSTRUTOR * aux_ltr;
    int qtd_atual;

    arqLtr = fopen("instrutores.bin", "rb");
    if (arqLtr == 0){
        printf("Não foi possível abrir o arquivo\n");
    }
    
    fread(&qtd_atual, sizeof(int), 1, arqLtr);
    if(fread(&qtd_atual, sizeof(int), 1, arqLtr) != 1){
        printf("Erro ao ler\n");
    }

    tamIns = qtd_atual;

    for(int i = 0; i < qtd_atual; i++){
        estrutura = malloc(sizeof(INSTRUTOR));
        fread(estrutura, sizeof(INSTRUTOR), 1, arqLtr);
        
        if(inicioIns == NULL){
            inicioIns = estrutura;

        }else{
            aux_ltr = inicioIns;
            for(int y = 0; aux_ltr->prox != NULL; y++) aux_ltr = aux_ltr->prox;
            aux_ltr->prox = estrutura;
        }
    }

    fclose(arqLtr);
    
}

/////////////////////////////////////////////////CADASTRO////////////////////////////////////////////////////////////

void cadastrarInstrutor(char nome[], int diasDaSemana[], float salario, char cpf[],char senha[]){
    INSTRUTOR *novo = malloc(sizeof(INSTRUTOR));
    novo->name = nome;
    novo->salario = salario;
    novo->cpf = cpf;
    novo->senha = senha;
    for (int i = 0; i < 5; i++){
        novo->diasDeOficio[i] = diasDaSemana[i];
    }
    novo->prox = NULL;
    
    if(tamIns == 0){
        inicioIns = novo;
        tamIns++;
    }
    else{
        INSTRUTOR *aux = inicioIns;
        //para no último elemento da lista
        for (int i = 0; aux->prox != NULL; i++){
            aux = aux->prox;
        }
        aux->prox = novo;
        tamIns++;
    }
}

void cadastrarCliente(char nome[], float peso, int altura, int plano, char cpf[],char senha[], INSTRUTOR *instructor){
    if(tamIns != 0){
        CLIENTE *novo = malloc(sizeof(CLIENTE));
        novo->nome = nome;
        novo->peso = peso;
        novo->altura = altura;
        novo->plano = plano;
        novo->cpf = cpf;
        novo->senha =  senha;
        novo->prox = NULL;
        novo->instrutor = instructor;

        if(tamCl == 0){
            inicioCl = novo;
            tamCl++;
        }
        else{
            CLIENTE *aux = inicioCl;
            //para no último elemento da lista
            for (int i = 0; aux->prox != NULL; i++){
                aux = aux->prox;
            }
            aux->prox = novo;
            tamCl++;
        }
    }
    else{
        printf("ERRO: Não há instrutores cadastrados no momento.\n");
    }
}


void menuCadastro(){
    int opcoes;
    printf("[1] Cliente\n");
    printf("[2] Instrutor\n");

    printf("N: ");
    scanf("%d", &opcoes);

    char nome[240]; // Cliente e Instrutor
    float peso; // Cliente
    int altura; // Cliente
    int plano = -1; // Cliente
    int diasDaSemana[5]; // Cliente e Instrutor
    float salario; // Instrutor
    char cpf[12];  // Cliente e Instrutor
    char senha[15]; //Cliente e Instrutor
    int cpflen;

    char *cpfR;
    int   sizeCpf;
    char *nomeR;
    int   sizeNome;
    char *senhaR;
    int   sizeSenha;

    INSTRUTOR *instructorDesejado;

    clrscr();
    switch (opcoes){
    case 1:
        printf("Digite o nome do Cliente: ");
        fflush(stdin);
        scanf("%[^\n]s", nome);

        sizeNome = strlen(nome);
        nomeR = (char*)malloc(sizeof(char)*(sizeNome+1));
        for(int a = 0; a <= sizeNome; a++)  nomeR[a]= '\0';
        strcpy(nomeR,nome);

        printf("Digite o peso do Cliente: ");
        fflush(stdin);
        scanf("%f", &peso);

        printf("Digite a altura do Cliente em cm: ");
        fflush(stdin);
        scanf("%d", &altura);

        printf("\n");

        for (int i = 0; i < 5; i++){
            printf("[%d] Plano %s = R$%.2f\n", i, nomesPlanos[i], planos[i]);
        }
        printf("Digite o plano que o Cliente deseja: ");
        while(plano < 0 || plano > 4){
            if(plano > 4){printf("O plano digitado não existe, tente novamente: ");}
            fflush(stdin);
            scanf("%d", &plano);
            }
        
        printf("\n");

        printf("Digite o CPF do cliente: ");
        fflush(stdin);
        scanf("%[^\n]", cpf);
        
        cpflen = strlen(cpf);
        if(cpflen!=11){
            printf("ERRO! CPF invalido\n");
             break;
             }
        else{
            for(int l = 0; l < 11; l++){
                if (cpf[l] >= '0' && cpf[l] <='9');

                else{
                    printf("ERRO! CPF possui caracters invalidos\n");
                    break;
                }
            }
        }
        sizeCpf = strlen(cpf);
        cpfR = (char*)malloc(sizeof(char)*(sizeCpf+1));
        for(int a = 0; a <= sizeCpf; a++)  cpfR[a]= '\0';
        strcpy(cpfR,cpf);

        printf("\n");

        printf("Digite a senha do cliente (até 14 digitos): ");
        fflush(stdin);
        scanf("%[^\n]s", senha);
        sizeSenha = strlen(senha);
        senhaR = (char*)malloc(sizeof(char)*(sizeSenha+1));
        for(int a = 0; a <= sizeSenha; a++)  senhaR[a]= '\0';
        strcpy(senhaR,senha);

        printf("\n");

        printf("Os instrutores disponíveis são:\n");

        int i = 0;

        for (INSTRUTOR *aux = inicioIns; aux != NULL; aux = aux->prox){
            printf("Instrutor: %d\n",i+1);
            i++;
            printf("%s\n", aux->name);
            printf("Os seus dias de trabalho são:\n");
            for (int i = 0; i < 5; i++){
                if(aux->diasDeOficio[i] == 1){
                    printf("%s\n", osDiasDaSemana[i]);
                }
            }
        
        }
        printf("\nQual instrutor quer escolher?[1 até %d]\n",i);
            scanf("%d",&i);

        if(i>tamIns||i<0){
            printf("\nERRO O INDICE DESEJADO NÃO É VALIDO\n");
            break;
        }
        
        // Relaciona o instrutor escolhido com seu respectivo Cliente
        for (INSTRUTOR *aux = inicioIns; aux != NULL; aux = aux->prox){
            if(i==1){
                instructorDesejado = aux;
                break;
            }
            else{
                i--;
            }
        }
        clrscr();
        cadastrarCliente(nomeR, peso, altura, plano, cpfR, senhaR, instructorDesejado);
        if(tamIns == 0){printf("Cadastro Não Realizado. Cadastro de Instrutor Necessário.\n");}
        else{printf("Cadastro Realizado com Sucesso!\n");}
        
        break;
    
    case 2:
        printf("Digite o nome do Instrutor: ");
        fflush(stdin);
        scanf("%[^\n]s", nome);
        
        sizeNome = strlen(nome);
        nomeR = (char*)malloc(sizeof(char)*(sizeNome+1));
        for(int a = 0; a <= sizeNome; a++)  nomeR[a]= '\0';
        strcpy(nomeR,nome);
     
        printf("\n");

        printf("Pressione [1] para os dias da semana que o Instrutor irá comparecer e [0] para os que ele não irá:\n");
        for (int i = 0; i < 5; i++){
            printf("%s: ", osDiasDaSemana[i]);
            fflush(stdin);
            scanf("%d", &diasDaSemana[i]);
            if(diasDaSemana[i]==1){
                salario += (float)(105 * 4);
            }
        }
        printf("\n");

        printf("Digite o CPF do instrutor: ");
        fflush(stdin);
        scanf("%[^\n]", cpf);
        cpflen = strlen(cpf);
        if(cpflen!=11){
            printf("ERRO! cpf invalido\n");
             break;
             }
        else{
            for(int l = 0; l < 11; l++){
                if (cpf[l] >= '0' && cpf[l] <='9') continue;
                else{printf("ERRO! cpf possui caracters invalidos\n"); break;
                }
            }
        }
        sizeCpf = strlen(cpf);
        cpfR = (char*)malloc(sizeof(char)*(sizeCpf+1));
        for(int a = 0; a <= sizeCpf; a++)  cpfR[a]= '\0';
        strcpy(cpfR,cpf);

        printf("\n");

        printf("Digite a senha do instrutor (até 14 digitos): ");
        fflush(stdin);
        scanf("%[^\n]s", senha);

        sizeSenha = strlen(senha);
        senhaR = (char*)malloc(sizeof(char)*(sizeSenha+1));
        for(int a = 0; a <= sizeSenha; a++)  senhaR[a]= '\0';
        strcpy(senhaR,senha);

        clrscr();

        cadastrarInstrutor(nomeR, diasDaSemana, salario, cpfR, senhaR);

        printf("Cadastro Realizado com Sucesso!\n");
        break;

    default:
        printf("Houve uma Falha no Cadastro, Tente Novamente Mais Tarde\n");
        break;
    }
}
/////////////////////////////////////////////////PERFIL////////////////////////////////////////////////////////////


void buscarPerfilCl(char cpf[]){
    float imc;
    if(tamCl > 0){
        for (CLIENTE *busca = inicioCl; busca != NULL; busca = busca->prox){
            if(strcmp(busca->cpf, cpf) == 0){
                printf("Nome do Cliente: %s\n", busca->nome);
                printf("Peso do Cliente: %.2f kg\n", busca->peso);
                printf("Altura do Cliente: %d cm\n", busca->altura);
                imc = (float)busca->altura/100;
                imc *= imc;
                imc = busca->peso / imc;
                printf("IMC do Cliente: %.2f\n", imc);
                printf("Plano %s: %.2f\n", nomesPlanos[busca->plano], planos[busca->plano]);
                if(busca->instrutor == NULL){
                    printf("Nenhum instrutor está responsável por %s, por favor, atribuir um novo instrutor.\n", busca->nome);
                    break;
                }
                else{
                    printf("O instrutor a cargo é: %s\n", busca->instrutor->name);
                    for (int i = 0; i < 5; i++){
                        if(busca->instrutor->diasDeOficio[i] == 1){
                            printf("Os dias em que o instrutor comparece são: %s\n", osDiasDaSemana[i]);
                        }
                    }
                }
            }
            else{
                printf("Cliente Não Encontrado no Banco de Dados.\n");
            }
        }
    }
    else{
        printf("Nenhum Cliente Cadastrado.\n");
    }
}

void buscarPerfilIns(char cpf[]){
    if(tamIns > 0){
        for (INSTRUTOR *busca = inicioIns; busca != NULL; busca = busca->prox){
            if(strcmp(busca->cpf, cpf) == 0){
                printf("CPF Instrutor: %s\n", busca->cpf);
                printf("Nome do Instrutor: %s\n", busca->name);
                printf("Os dias em que ele trabalha são:\n");
                for (int i = 0; i < 5; i++){
                    if(busca->diasDeOficio[i] == 1){
                        printf("%s\n", osDiasDaSemana[i]);
                    }
                }
                printf("Seu salário é: %.2f\n", busca->salario);
                printf("Seu CPF é: %s\n", busca->cpf);
            }
            else{
                printf("Instrutor Não Encontrado no Banco de Dados.\n");
            }
        }
    }
    else{
        printf("Nenhum Instrutor Cadastrado.\n");
    }
}

void menuPerfil(){
    int opcoes;
    printf("[1] Ver Perfil de um Cliente\n");
    printf("[2] Ver Perfil de um Instrutor\n");

    printf("N: ");
    scanf("%d", &opcoes);

    char cpf[11];

    clrscr();
    switch (opcoes){
    case 1:
        printf("Digite o CPF do cliente (apenas os números): ");
        fflush(stdin);
        scanf("%s", cpf);
        buscarPerfilCl(cpf);
        break;
    
    case 2:
        printf("Digite o CPF do instrutor (apenas os números): ");
        fflush(stdin);
        scanf("%s", cpf);
        buscarPerfilIns(cpf);
        break;

    default:
        printf("Houve uma Falha na Escolha de Perfil, Tente Novamente Mais Tarde\n");
        break;
    }
}
void perfil_CL(CLIENTE *cliente){
    printf("Olá %s\n", cliente->nome);
    printf("Seu CPF é: %s\n", cliente->cpf);
    printf("Seu peso é: %.2f\n", cliente->peso);
    printf("Seu altura é: %d\n", cliente->altura);
    printf("Seu plano é: %s\n - R$%.2f", nomesPlanos[cliente->plano], planos[cliente->plano]);
    if(cliente->instrutor==NULL) 
        printf("Instrutor cancelou contrato, selecione outro instrutor na edição de dados\n");
    else 
        printf("Seu instrutor responsável é: %s\n", cliente->instrutor->name);
    
    int escolha;
    int escolinha;
    int sizeSenha;
    char senha[15];
    int i = 0;
    
    printf("Quer editar algum dado ou cancelar sua matricula?\n[0]não\n[1]sim\n");
    scanf("%d", &escolha);

    printf("\n");
    
    switch (escolha){
        case 1:
            printf("Quer cancelar sua matrícula?\n[1] para sim e [0] para não\n");
            scanf("%d",&escolinha);
            if(escolinha == 1){
                free(cliente -> nome);
                free(cliente -> cpf);
                free(cliente -> senha);
                cliente->instrutor = NULL;

                for(CLIENTE* aux = inicioCl; aux != NULL; aux = aux -> prox){
                    if(aux == cliente){
                        inicioCl = aux->prox;
                        free(cliente);
                        break;
                    }
                    
                    else if(aux -> prox == cliente){
                        aux -> prox = cliente -> prox;
                        free(cliente);
                        break;
                    }
                }tamCl--;
                break;
            }
            printf("\n");

            printf("Quer trocar a senha?\n[1] para sim e [0] para não\n");
            scanf("%d",&escolinha);

            if(escolinha == 1){
                free(cliente->senha);
                printf("Digite a nova senha do cliente (até 14 digitos): ");
                fflush(stdin);
                scanf("%[^\n]s", senha);

                sizeSenha = strlen(senha);
                cliente->senha = (char*)malloc(sizeof(char)*(sizeSenha+1));
                for(int a = 0; a <= sizeSenha; a++)  cliente -> senha[a]= '\0';
                strcpy(cliente -> senha,senha);
            }

            printf("\n");
            
            printf("Quer trocar/atualizar de instrutor?\n[1] para sim e [0] para não\n");
            scanf("%d",&escolinha);
            if(escolinha == 1 && tamIns > 0){
                printf("Os instrutores disponíveis são:\n");

                for (INSTRUTOR *aux = inicioIns; aux != NULL; aux = aux->prox){
                    printf("Instrutor: %d\n",i+1);
                    i++;
                    printf("%s\n", aux->name);
                    printf("Os seus dias de trabalho são:\n");
                    for (int i = 0; i < 5; i++){
                        if(aux->diasDeOficio[i] == 1){
                            printf("%s\n", osDiasDaSemana[i]);
                        }
                    }
                }
                printf("\nQual instrutor quer escolher?[1 até %d]\n",i);
                fflush(stdin);
                scanf("%d",&i);


                if(i>tamIns||i<0){
                    printf("\nERRO O INDICE DESEJADO NÃO É VALIDO\n");
                    break;
                }
            
                for (INSTRUTOR *aux = inicioIns; aux != NULL; aux = aux->prox){
                    if(i==1){
                        cliente->instrutor = aux;
                        break;
                    }
                    else{
                        i--;
                    }
                }
            }
            else if(tamIns == 0){
                printf("Sinto muito, mas não temos instrutores o bastante.\nPor favor, espere um novo instrutor ser cadastrado.\n");
            }
            break;
        
        default:
            break;
        }
}

void perfil_INS(INSTRUTOR *instrutor){
    printf("Olá %s\n", instrutor->name);
    printf("Seus dias de trabalho são:\n");
    for (int i = 0; i < 5; i++){
        if(instrutor->diasDeOficio[i] == 1){
            printf("%s\n", osDiasDaSemana[i]);
        }
    }
    printf("Seu salário é: %.2f\n", instrutor->salario);
    printf("Seu CPF é: %s\n", instrutor->cpf);
    printf("Seus alunos são:\n");

    for(CLIENTE* ESC = inicioCl; ESC != NULL; ESC = ESC -> prox ){

        if(ESC -> instrutor == instrutor){
            printf("%s\n",ESC -> nome);
        }    
    }
    
    int escolha;
    int escolinha;
    int sizeSenha;
    char senha[15];
    int  dias[5];
    float salario = 0;
    
    printf("Quer editar algum dado/ Cancelar contrato(pagamentos dos dias trabalhados são a parte)?\n[0]não\n[1]sim\n");
    scanf("%d", &escolha);
    int diasDaSemana[5]; 
    
    switch (escolha){
        case 1:
            printf("Quer cancelar o contrato com a academia?\n[1] para sim e [0] para não\n");
            scanf("%d",&escolinha);
            if(escolinha == 1){
                free(instrutor -> name);
                free(instrutor -> cpf);
                free(instrutor -> senha);

                for(INSTRUTOR* aux = inicioIns; aux != NULL; aux = aux -> prox){

                    if(aux == instrutor){
                        for(CLIENTE* ESC = inicioCl; ESC != NULL; ESC = ESC -> prox ){
                            if(ESC ->instrutor == instrutor){
                                ESC -> instrutor = NULL;
                            }
                         }
                        inicioIns = aux->prox;
                        free(instrutor);
                        break;
                    }
                    
                    else if(aux -> prox == instrutor){
                        for(CLIENTE* ESC = inicioCl; ESC != NULL; ESC = ESC -> prox ){
                            if(ESC -> instrutor == instrutor){
                                ESC -> instrutor = NULL;
                            }    
                         }
                        aux -> prox = instrutor -> prox;
                        free(instrutor);
                        break;
                    }
                }tamIns--;
                break;
            }
            printf("Quer trocar a senha?\n[1] para sim e [0] para não\n");
            scanf("%d",&escolinha);

            if(escolinha == 1){
                free(instrutor->senha);
                printf("Digite a nova senha do instrutor (até 14 digitos): ");
                fflush(stdin);
                scanf("%[^\n]s", senha);

                sizeSenha = strlen(senha);
                instrutor->senha = (char*)malloc(sizeof(char)*(sizeSenha+1));
                for(int a = 0; a <= sizeSenha; a++)  instrutor -> senha[a]= '\0';
                strcpy(instrutor -> senha,senha);
            }
            
            printf("Quer trocar os dias trabalhados?\n[1] para sim e [0] para não\n");
            scanf("%d",&escolinha);
            if(escolinha == 1){
                
                printf("Pressione [1] para os dias da semana que o Instrutor irá comparecer e [0] para os que ele não irá:\n");
                for (int i = 0; i < 5; i++){
                    printf("%s: ", osDiasDaSemana[i]);
                    fflush(stdin);
                    scanf("%d", dias[i]);
                    if(dias[i]==1){
                        salario += (float)(105 * 4);
                    }
                } instrutor->salario = salario;
                for (int i = 0; i < 5; i++){
                  instrutor->diasDeOficio[i] = dias[i];   
                }
            }
            break;

        default:
            break;
    }
}
/////////////////////////////////////////////////LOGIN///////////////////////////////////////////////////////////////
void login(char cpf[], char senha[]){
    int achoou = 0;
    
    for (CLIENTE *busca = inicioCl; busca != NULL; busca = busca->prox){
        if(strcmp(busca->cpf, cpf) == 0){
            perfil_CL(busca);
            achoou = 1;
        }
    }
    for (INSTRUTOR *busca = inicioIns; busca != NULL; busca = busca->prox){
        if(strcmp(busca->cpf, cpf) == 0){
            perfil_INS(busca);
            achoou = 1;
        }
    }
    if(achoou == 0){
        printf("ERRO: Usuário Inexistente!!\n Cadastro Necessário.\n");
    }
}

void preLogin(){
    char cpf[12];
    char senha[15];
    
    printf("Digite o seu CPF: ");
    fflush(stdin);
    scanf("%s", cpf);
    printf("\nDigite a sua Senha: ");
    fflush(stdin);
    scanf("%s", &senha);

    login(cpf, senha);
}
/////////////////////////////////////////////////////////////////////////////////////////////
// O MAIN DE FATO É ESSE
int main(){
    int opcoes;
    int menuOn = 1;
    clrscr();
    printf("Bem vindo ao Cjafit da Academia do Pai Tom\n");

    while (menuOn != 0){
        printf("--- Menu Inicial ---\n");
        printf("[1] Ver Perfis\n");
        printf("[2] Cadastro\n");
        printf("[3] Login\n");
        printf("[4] Gravar Instrutores\n");
        printf("[5] Ler Instrutores\n");
        printf("[6] Gravar Cliente\n");
        printf("[7] Ler Cliente\n");
        printf("[0] Sair\n");

        printf("N: ");
        scanf("%d", &opcoes);

        switch (opcoes){
        case 1:
            clrscr();
            menuPerfil();
            break;
        
        case 2:
            clrscr();
            menuCadastro();
            break;

        case 3:
            clrscr();
            preLogin();
            break;

        case 4:
            clrscr();
            gravacao_arquivo_instrutor();
            break;
        
        case 5:
            clrscr();
            leitura_arquivo_instrutor();
            break;
        
        case 6:
            clrscr();
            gravacao_arquivo_cliente();
            break;

        case 7:
            clrscr();
            leitura_arquivo_cliente();
            break;
        
        case 0:
            menuOn = 0;
            clrscr();
            break;

        default:
            printf("Opção indisponível, tente novamente.\n");
            break;
        }
    }
    clrscr();
    return 0;
}