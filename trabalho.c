#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define NULO '\0'

FILE *arquivocurso;
FILE *arquivoestado;
FILE *arquivopessoa;

//Criando o tipo aluno para cadastrar no futuro.
typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct aluno{
    char nome[60];
    char sexo[30];
    Data data;
    char curso[30];
    char uf[30];
}Aluno;

typedef struct estado{
    char nomes[100];
}Estado;

typedef struct curso{
    char nomes[100];
}Curso;

void mostrarmenu();
void cadastrarcurso();
void cadastrarestado();
void cadastrarpessoa();
void listarpessoaestado();
void listarpessoacurso();
void consultarpessoanome();
void relatoriodemografico();
int validacao_data();
int calculaidade();
int apagaLinha();

int main(void){
    int opcoes;

while(1){
    ///system("clear");
    mostrarmenu();
    scanf("%d", &opcoes);
    getchar();


    switch (opcoes){

    case 1:
        cadastrarestado();
        break;
    
    case 2:
        cadastrarcurso();
        break;

    case 3:
        cadastrarpessoa();
        break;

    case 4:
        listarpessoaestado();
        break;

    case 5:
        listarpessoacurso();
        break;

    case 6:
        consultarpessoanome();
        break;

    case 7:
        relatoriodemografico();
        break;

    case 8:
        apagaLinha("pessoa.csv");
        break;

    case 9:
        return 0;
        break;
    }
    }
}

//Mostrando o menu para o usuário.
void mostrarmenu(){
    printf("----------------------------\n");
    printf("1 - Cadastrar Estado:\n");
    printf("2 - Cadastrar Curso:\n");
    printf("3 - Cadastrar Pessoa:\n");
    printf("4 - Listar pessoas por Estado.\n");
    printf("5 - Listar pessoas por Curso Desejado.\n");
    printf("6 - Consultar Pessoa por Nome.\n");
    printf("7 - Gerar relatório demográfico.\n");
    printf("8 - Apagar uma Pessoa.\n");
    printf("9 - Finalizar Programa.\n");
    printf("----------------------------\n");
}


//Criando o primeiro cadastramento, o de estado.
void cadastrarestado(){
    char estado[100];
    int i;
    FILE *arquivoestado;

    arquivoestado = fopen("estado.txt", "a+b");

    if (arquivoestado == NULL){
    printf("Não foi possível abrir o arquivo!\n");
}else{

    printf("Escreva o nome do estado que deseja cadastrar:\n");
    scanf("%[^\n]", estado);
    getchar();

    for(i=0;i<strlen(estado);i++){
        estado[i] = toupper(estado[i]);
    }

    printf("Estado cadastrado com sucesso.\n");    

    fprintf(arquivoestado, "%s\n", estado);

    fclose(arquivoestado);
    }
}

//Cadastrando o curso.
void cadastrarcurso(){
    char curso[100];
    FILE *arquivocurso;
    int i;

    arquivocurso = fopen("curso.txt", "a+b");

    if (arquivocurso == NULL){
    printf("Não foi possível abrir o arquivo!\n");
}else{

    printf("Escreva o nome do curso que deseja cadastrar:\n");
    scanf("%[^\n]", curso);    
    getchar();

    for(i=0;i<strlen(curso);i++){
        curso[i] = toupper(curso[i]);
    }

    printf("Curso cadastrado com sucesso.\n");

    fprintf(arquivocurso, "%s\n", curso);

    fclose(arquivocurso);
    }
}

//Cadastrando pessoas usando o tipo Aluno.
void cadastrarpessoa(){
    Aluno pessoa;
    char pulalinha;
    char Etodos[100];
    char Ctodos[100];
    int i, compara=0;
    char linhas[100], linhas1[100];
    int cont=0, k=0;

    FILE *arquivopessoa;
    FILE *arquivocurso;
    FILE *arquivoestado;

    pulalinha=';';

    arquivopessoa = fopen("pessoa.csv", "a+b");
    arquivocurso = fopen("curso.txt", "r");
    arquivoestado = fopen("estado.txt", "r");

    if (arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{

        printf("Digite o nome:\n");
        scanf("%[^\n]", pessoa.nome);
        getchar();

        for(i=0;i<strlen(pessoa.nome);i++){
        pessoa.nome[i] = toupper(pessoa.nome[i]);
        }

        printf("Digite o sexo:\n");
        scanf("%[^\n]", pessoa.sexo);
        getchar();

        for(i=0;i<strlen(pessoa.sexo);i++){
        pessoa.sexo[i] = toupper(pessoa.sexo[i]);
        }

        printf("Digite a data de nascimento: (No formato XX/XX/XXXX)\n");
        scanf("%d/%d/%d", &pessoa.data.dia, &pessoa.data.mes, &pessoa.data.ano);
        getchar();

        if(validacao_data(pessoa.data.dia, pessoa.data.mes, pessoa.data.ano)==0){
            printf("Data inválida.\n");
            exit(0);
        }

        printf("Digite o curso desejado:\n");
        scanf("%[^\n]", pessoa.curso);
        getchar();

        for(i=0;i<strlen(pessoa.curso);i++){
        pessoa.curso[i] = toupper(pessoa.curso[i]);
        }

        while(fgets(linhas1, 100, arquivocurso)!=NULL){
        k++;
        }

        rewind(arquivocurso);

        while(fgets(linhas, 100, arquivocurso)!=NULL){
            strcpy(Ctodos, linhas);

            compara = strncmp(Ctodos, pessoa.curso, strlen(pessoa.curso));

            if(compara!=0){
                cont++;
            }
        }
        if(cont==k){
            printf("\nCurso não cadastrado\n");
            exit(0);
        }

        compara=0;
        cont=0;
        k=0;

        printf("Digite a unidade de federacao:\n");
        scanf("%[^\n]", pessoa.uf);
        getchar();

        for(i=0;i<strlen(pessoa.uf);i++){
        pessoa.uf[i] = toupper(pessoa.uf[i]);
        }

        while(fgets(linhas1, 100, arquivoestado)!=NULL){
        k++;
        }

        rewind(arquivoestado);

        while(fgets(linhas, 100, arquivoestado)!=NULL){
            strcpy(Etodos, linhas);

            printf("linhas = %s\n", Etodos);
            printf("curso = %s\n", pessoa.uf);

            compara = strncmp(Etodos, pessoa.uf, strlen(pessoa.uf));

            printf("compara = %d\n", compara);

            if(compara!=0){
                cont++;
            }
            printf("cont = %d\n", cont);
        }
        if(cont==k){
            printf("\nEstado não cadastrado\n");
            exit(0);
        }

        printf("\n");
        printf("Aluno(a) cadastrado com sucesso.\n");
        getchar();


    fprintf(arquivopessoa, "%s", pessoa.nome);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%s", pessoa.sexo);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%02d/%02d/%02d", pessoa.data.dia, pessoa.data.mes, pessoa.data.ano);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%s", pessoa.curso);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%s", pessoa.uf);
    fprintf(arquivopessoa, "%c\n", pulalinha);

    fclose(arquivopessoa);
    }
}

void listarpessoaestado(){
    Aluno pessoa;
    char estado[100];
    char linhas[100], str[100], str1[100];
    int i, cont, j=0;

    FILE *arquivopessoa;
    arquivopessoa = fopen("pessoa.csv", "r+");

        if(arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{
        printf("Digite o estado que deseja pesquisar:\n");
        scanf("%s", estado);
        getchar();

        for(i=0;i<strlen(estado);i++){
        estado[i] = toupper(estado[i]);
        }

    }


    while(fgets(linhas, 100, arquivopessoa)!=NULL){
        strcpy(str, linhas);

        for(i=0;i<strlen(str);i++){
            if(str[i]=='\n'){
                cont=0;
            }
            if(str[i]==',' || str[i]==';'){
                cont++;
            }
            else if(cont==4){
                j=0; 
                int contador_de_virgulas = 0;

                if( !(str[i] == ',' || str[i] == ';') ){
                    while(i<strlen(str)){
                    str1[j] = str[i];
                    j++;
                    i++;
                    }
                }
            }
        }

        if(strstr(str1,estado)){
            printf("%s", linhas);
            printf("\n");
        }
    }
    
    getchar();

    fclose(arquivopessoa);
  

}

void listarpessoacurso(){

    Aluno pessoa;
    char curso[100];
    char linhas[100], str[100], str1[100];
    int i, cont=0, j=0;

    FILE *arquivopessoa;
    arquivopessoa = fopen("pessoa.csv", "r+");

    if(arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{
        printf("Digite o curso que deseja pesquisar:\n");
        scanf("%s", curso);
        getchar();

        for(i=0;i<strlen(curso);i++){
        curso[i] = toupper(curso[i]);
        }
    }
    

    while(fgets(linhas, 100, arquivopessoa)!=NULL){

        strcpy(str, linhas);
        
        for(i=0;i<strlen(str);i++){
            if(str[i]=='\n'){
                cont=0;
            }
            if(str[i]==',' || str[i]==';'){
                cont++;
            }
            else if(cont==3){
                j=0; 
                int contador_de_virgulas = 0;

                if( !(str[i] == ',' || str[i] == ';') ){
                    while(i<strlen(str)){
                    str1[j] = str[i];
                    j++;
                    i++;
                    }
                }
            }
        }

        if(strstr(str1,curso)){
            printf("%s", linhas);
            printf("\n");
        }
    }
    
    getchar();

    fclose(arquivopessoa);
  
}

void consultarpessoanome(){
    Aluno pessoa;
    char nome[100];
    char linhas[100], str[100], str1[100];
    int i;

    FILE *arquivopessoa;
    arquivopessoa = fopen("pessoa.csv", "r+");

    if(arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{
        printf("Digite o nome que deseja pesquisar:\n");
        scanf("%s", nome);
        getchar();

        for(i=0;i<strlen(nome);i++){
        nome[i] = toupper(nome[i]);
        }
    }
    

    while(fgets(linhas, 100, arquivopessoa)!=NULL){
        strcpy(str, linhas);
        
        for(i=0;i<strlen(str);i++){
            if(str[i]!=';' || str[i]!=','){
                str1[i]=str[i];
            }
            if(str[i]==';'|| str[i]==','){
                break;
            }
        }

        if(strstr(str1,nome)){
            printf("%s", linhas);
            printf("\n");
        }
    }
    
    getchar();

    fclose(arquivopessoa);
  
}

void relatoriodemografico(){
    Aluno pessoa;
    int faixa1520, faixa2126, faixa2630, faixa30;
    int idade;
    char linhas[100], str[100], str1[100];
    int i, cont, j, k=0;
    FILE *arquivopessoa;

    arquivopessoa = fopen("pessoa.csv", "r");

    while(fgets(linhas1, 100, arquivoestado)!=NULL){
        k++;
        }

    rewind(arquivoestado);

    while(fgets(linhas, 100, arquivopessoa)!=NULL){
        strcpy(str, linhas);

        for(i=0;i<strlen(str);i++){char linhas[100], str[100], str1[100];
            if(str[i]=='\n'){
                cont=0;
            }
            if(str[i]==';'){
                cont++;
            }
            if(cont==2){
                for(j=0;j<strlen(str1);j++){
                    str1[j]=str[i];
                }      
            }
        }
    }

    

    idade=(calculaidade(pessoa.data.mes, pessoa.data.ano));

    printf("\nidade = %s\n", str1);

    
//Percentual de pessoas em cada faixa etaria
//15 a 20 anos
//21 a 26 anos
//26 a 30 anos
//acima de 30 anos
  



//Percentual de pessoas por sexo
//Masculino 
//Feminino
}

//Função para validar as datas.
int validacao_data(int dia, int mes, int ano){
    if (ano>= 1900 && ano <= 2100){
        //Checando mês.
        if (mes >= 1 && mes <= 12){
            //Checando dia.
            if ((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12))
                return 1;

            else if ((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11))
                return 1;

            else if ((dia >= 1 && dia <= 28) && (mes == 2))
                return 1;

            else if (dia == 29 && mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)))
                return 1;

            else
                return 0;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }

    return 0;
}

int calculaidade(int mes, int ano){
    int mesA, anoA;
    struct tm *data_hora_atual;     
    time_t segundos;
    int idade=0;

    time(&segundos);  
    data_hora_atual = localtime(&segundos);

    mesA = data_hora_atual->tm_mon+1;
    anoA = data_hora_atual->tm_year+1900;

    idade = anoA - ano;

    if(mesA < mes || mesA == mes)
        idade--;

    return idade;
}

int apagaLinha(char arquivo[]){
    FILE *arquivopessoa;
    char nome[100];
    int linha = 1;
    int i;
    char textoArquivo[100];

    arquivopessoa = fopen("pessoa.csv", "r+");

    if(arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{

    printf("Digite o nome da pessoa que deseja apagar:\n"); //pede a linha
    scanf("%[^\n]", nome); //le a linha e armazena na variável 'line'

    rewind(arquivopessoa); //certifica de que o cursor esta no primeiro caractere do arquivo

    for(i = 0; !feof(arquivopessoa);i++){ //incrementa 'i' enquando não for fim de arquivo
        memset(textoArquivo, NULO, 100); //inicializa e/ou limpa string 'textoArquivo'
        fgets(textoArquivo, 101, arquivopessoa); //pega uma string de 100 caracteres
        if(textoArquivo == nome){ //se a linha for a escolhida
            fputc('\n', arquivopessoa); //troca a linha que o usuario quer por nova linha
            linha = linha + 1; //incrementa o contador de linhas
            continue; //volta ao inicio do loop sem executar o resto
    }

    linha = linha + 1; //incrementa o contador de linas

    printf("Linhas: %d\n", (linha-1)); //imprime quantas linhas tem o arquivo lido

    fclose(arquivopessoa); //fecha a stream 'arqEntrada'
        }
    }
}