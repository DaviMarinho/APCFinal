#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define NULO '\0'
#define MAX 999

FILE *arquivocurso;
FILE *arquivoestado;
FILE *arquivopessoa;
FILE *arquivotemporario;

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

//Mostrando todas as funções que vão ser usadas.
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
    system("clear");
    mostrarmenu(); //Ao iniciar o programa o menu será mostrado.
    scanf("%d", &opcoes);//Será pedido uma opção do menu.
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
        apagaLinha();
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

    arquivoestado = fopen("estado.txt", "a+b");//Comando usado para abrir o arquivo e usa-lo na variável "arquivoestado".

    if (arquivoestado == NULL){
    printf("Não foi possível abrir o arquivo!\n");
    exit(0);
    }else{

    printf("Escreva o nome do estado que deseja cadastrar com unidade de federação:\n");
    scanf("%[^\n]", estado);//O usuário irá digitar o estado que ele deseja cadastrar.
    getchar();

    for(i=0;i<strlen(estado);i++){
        estado[i] = toupper(estado[i]);//Essa função do ctype irá passar todos os caracteres para maiúsculo.    
    }    

    fprintf(arquivoestado, "%s\n", estado);//Salvando o estado no arquivo.

    printf("Estado cadastrado com sucesso.\n");

    getchar();

    fclose(arquivoestado);//Fechando o arquivo.
    }
}

//Cadastrando o curso.
void cadastrarcurso(){
    char curso[100];
    FILE *arquivocurso;
    int i;

    arquivocurso = fopen("curso.txt", "a+b");//Abrindo o segundo arquivo e salvando na variável.

    if (arquivocurso == NULL){
    printf("Não foi possível abrir o arquivo!\n");
    }else{

    printf("Escreva o nome do curso que deseja cadastrar:\n");
    scanf("%[^\n]", curso);//Salvando a variável do usuário.
    getchar();

    for(i=0;i<strlen(curso);i++){
        curso[i] = toupper(curso[i]);
    }

    fprintf(arquivocurso, "%s\n", curso);//Salvando o curso no arquivo.

    printf("Curso cadastrado com sucesso.\n");

    getchar();

    fclose(arquivocurso);//Fechando o arquivo.
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
    char *ponteiro = NULL;

    FILE *arquivopessoa;
    FILE *arquivocurso;
    FILE *arquivoestado;

    pulalinha=';';

    arquivopessoa = fopen("pessoa.csv", "a+b");//Abrindo com "a+b" pois eu preciso modificar o arquivo.
    arquivocurso = fopen("curso.txt", "r");
    arquivoestado = fopen("estado.txt", "r"); //Os outros dois eu abri com "r", porque eu preciso apenas ler eles.

    if (arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{

        printf("Digite o nome:\n");
        scanf("%[^\n]", pessoa.nome);
        getchar();

        for(i=0;i<strlen(pessoa.nome);i++){
        pessoa.nome[i] = toupper(pessoa.nome[i]);//Passando o nome para maiúsculo.
        }

        printf("Digite o sexo:\n");
        scanf("%[^\n]", pessoa.sexo);
        getchar();

        for(i=0;i<strlen(pessoa.sexo);i++){
        pessoa.sexo[i] = toupper(pessoa.sexo[i]);//Passando o sexo para maiúsculo.
        }

        printf("Digite a data de nascimento: (No formato XX/XX/XXXX)\n");
        scanf("%d/%d/%d", &pessoa.data.dia, &pessoa.data.mes, &pessoa.data.ano);
        getchar();

        if(validacao_data(pessoa.data.dia, pessoa.data.mes, pessoa.data.ano)==0){
            printf("Data inválida.\n");//Chamando a função de validação de data para ver se a data do usuário é válida.
            exit(0);
        }

        printf("Digite o curso desejado:\n");
        scanf("%[^\n]", pessoa.curso);
        getchar();

        for(i=0;i<strlen(pessoa.curso);i++){
        pessoa.curso[i] = toupper(pessoa.curso[i]);//Passando o curso para maiúsculo.
        }

        while(fgets(linhas1, MAX, arquivocurso)!=NULL){
        k++;//Vendo quantos cursos já estão cadastrados.
        }

        rewind(arquivocurso);//Voltando para o início do arquivo.

        while(fgets(linhas, MAX, arquivocurso)!=NULL){
            strcpy(Ctodos, linhas);

            compara = strncmp(Ctodos, pessoa.curso, strlen(pessoa.curso));

            if(compara!=0){//Comparando todos os cursos que estão cadastrados com o do usuário.
                cont++;
            }
        }
        if(cont==k){//Se o curso do usuário não estiver cadastrado o programa será finalizado.
            printf("\nCurso não cadastrado\n");
            exit(0);
        }

        compara=0;
        cont=0;
        k=0;

        printf("Digite a unidade de federacao:\n");//Irei fazer o mesmo procedimento que eu fiz em cima, mas agora com o estado.
        scanf("%[^\n]", pessoa.uf);
        getchar();

        for(i=0;i<strlen(pessoa.uf);i++){
        pessoa.uf[i] = toupper(pessoa.uf[i]);
        }

        while(fgets(linhas1, MAX, arquivoestado)!=NULL){
        k++;
        }

        rewind(arquivoestado);

        while(fgets(linhas, MAX, arquivoestado)!=NULL){
            strcpy(Etodos, linhas);

            ponteiro = strstr(Etodos, pessoa.uf);

            if( ponteiro ){
                continue;
            }else{
                cont++;
            }
        }
        if(cont==k){
            printf("\nEstado não cadastrado\n");
            exit(0);
        }

        printf("\n");
        printf("Aluno(a) cadastrado com sucesso.\n");
        getchar();

    //Se todos os cadastros estiverem corretos eles irão ser colocados dentro do arquivo.
    fprintf(arquivopessoa, "%s", pessoa.nome);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%s", pessoa.sexo);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%02d/%02d/%02d", pessoa.data.dia, pessoa.data.mes, pessoa.data.ano);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%s", pessoa.curso);
    fprintf(arquivopessoa, "%c", pulalinha);
    fprintf(arquivopessoa, "%s", pessoa.uf);
    fprintf(arquivopessoa, "\n");

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

    while(fgets(linhas, MAX, arquivopessoa)!=NULL){//Extraindo as informações do arquivo para a variável "linhas".
        char str1[999]={};
        int cont=0;
        int j=0;
        
        for(i=0;i<strlen(linhas);i++){//E fazendo um "tratamento" na informação.
            if(linhas[i]==',' || linhas[i]==';'){
                cont++;
            }//Todas as informações do arquivo são divididas por ";".
            if(cont==4 && linhas[i] != ';' && i<strlen(linhas)-1){
                str1[j]=linhas[i];//Quando o contador chegar em 4 será a opção que eu desejo pesquisar.
                j++;
            }
        }

        if(strstr(str1, estado)){//Se a informação do arquivo for igual a do usuário eu irei printar a linha.
            printf("%s", linhas);
            printf("\n");
        }
    }
    }
    
    getchar();

    fclose(arquivopessoa);//Fechando o arquivo.
  

}

void listarpessoacurso(){//Será feito o mesmo procedimento do mostrado acima, mas nesse caso com o curso.

    Aluno pessoa;
    char curso[100]={};
    char linhas[100]={};
    char str[100]={};
    int i;

    FILE *arquivopessoa;
    arquivopessoa = fopen("pessoa.csv", "r");

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

    while(fgets(linhas, MAX, arquivopessoa)!=NULL){
        char str1[999]={};
        int cont=0;
        int j=0;
        
        for(i=0;i<strlen(linhas);i++){
            if(linhas[i]==',' || linhas[i]==';'){
                cont++;
            }
            if(cont==3 && linhas[i] != ';' && i<strlen(linhas)-1){
                str1[j]=linhas[i];
                j++;
            }
        }

        if(strstr(str1,curso)){
            printf("%s", linhas);
            printf("\n");
        }
    }
    }
    
    getchar();

    fclose(arquivopessoa);
    }

void consultarpessoanome(){//Nesse será o mesmo procedimento, mas de uma maneira mais simplificada.
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
    

    while(fgets(linhas, MAX, arquivopessoa)!=NULL){
        strcpy(str, linhas);
        
        for(i=0;i<strlen(str);i++){//Nesse caso especifico não precisaremos do contador.
            if(str[i]!=';' || str[i]!=','){
                str1[i]=str[i];
            }//Pois o nome já é a primeira parte do arquivo, então só precisamos limitar até o ";".
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
    double faixa1520=0, faixa2126=0, faixa2630=0, faixa30=0;
    int idade, imes, iano;
    char linhas[100], linhas1[100], str[100], str1[100];
    char masc[] = "MASCULINO";
    char fem[] = "FEMININO";
    char mes[2] = {}; 
    char ano[4] = {};
    int i, cont, j, k=0; 
    double masculino=0, feminino=0, outros=0;
    FILE *arquivopessoa;

    arquivopessoa = fopen("pessoa.csv", "r");

    if(arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{

    while(fgets(linhas1, MAX, arquivopessoa)!=NULL){
        k++;//Contando o número de linhas do arquivo.
    }

    rewind(arquivopessoa);//Voltando o arquivo para o início.

    while(fgets(linhas, MAX, arquivopessoa)!=NULL){//Pegando as linhas do arquivo e passando para a variável "linhas".
        char str1[999]={};
        int cont=0;
        int j=0;
        
        for(i=0;i<strlen(linhas);i++){//Fazendo o tratamento de linhas, até o segundo ";" do arquivo.
            if(linhas[i]==',' ||  linhas[i]==';'){
                cont++;
            }
            if(cont==1 && linhas[i] != ';' && i<strlen(linhas)-1){
                str1[j]=linhas[i];
                j++;
            }
        }//Recebendo se é Masculino, Feminino ou outros.
        if(strcmp(str1, masc)==0){
            masculino++;
        }
        if(strcmp(str1, fem)==0){
            feminino++;
        }
        if(strcmp(str1, masc)!=0 && strcmp(str1, fem)!=0){
            outros++;
        }
    }
    //Fazendo o cálculo da porcentagem de homens, mulheres ou outros.
    masculino = (masculino/k)*100;
    feminino = (feminino/k)*100;
    outros = (outros/k)*100;

    printf("Estão cadastradas um total de %d pessoas.\n", k);

    printf("%.2lf%% são homens.\n", masculino);
    printf("%.2lf%% são mulheres.\n", feminino);
    printf("%.2lf%% são outros.\n", outros);
    
    rewind(arquivopessoa);//Voltando o arquivo pro início para fazer o mesmo com as datas.

    while(fgets(linhas, MAX, arquivopessoa)!=NULL){
        char str1[999]={};
        int cont=0;
        int j=0;
        
        for(i=0;i<strlen(linhas);i++){//Fazendo o tratamento para a data.
            if(linhas[i]==',' ||  linhas[i]==';'){
                cont++;
            }
            if(cont==2 && linhas[i] != ';' && i<strlen(linhas)-1){
                str1[j]=linhas[i];
                j++;
            }
        }//Como no arquivo a data vem como uma string, precisei modificar um pouco e usar a função "atoi".
        mes[0] = str1[3];
        mes[1] = str1[4];
        mes[2] = '\0';

        imes = atoi(mes);//A função "atoi" vai passar de uma string para um número inteiro.

        ano[0] = str1[6];
        ano[1] = str1[7];
        ano[2] = str1[8];
        ano[3] = str1[9];
        ano[4] = '\0';

        iano = atoi(ano);
        idade=(calculaidade(imes, iano));//Chamando a função calculaidade, que me dará um inteiro mostrando a idade do usuário.

        if(idade>=15 && idade<=20){
            faixa1520++;
        }
        if(idade>=21 && idade<=26){
            faixa2126++;
        }
        if(idade>=27 && idade<=30){
            faixa2630++;
        }
        if(idade>30){
            faixa30++;
        }
    }
        //Fazendo o cálculo para ver em qual faixa etária o usúario se encaixa.
        faixa1520 = (faixa1520/k)*100;
        faixa2126 = (faixa2126/k)*100;
        faixa2630 = (faixa2630/k)*100;
        faixa30 = (faixa30/k)*100;

        printf("\n");
        printf("%.2lf%% estão na faixa de 15 à 20 anos.\n", faixa1520);
        printf("%.2lf%% estão na faixa de 21 à 26 anos.\n", faixa2126);
        printf("%.2lf%% estão na faixa de 26 à 30 anos.\n", faixa2630);
        printf("%.2lf%% tem mais de 30 anos.\n", faixa30);

    getchar();

    fclose(arquivopessoa);

    }
}

//Função para validar as datas.
int validacao_data(int dia, int mes, int ano){
    if (ano>= 1900 && ano <= 2004){
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

    time(&segundos);//Essa função pega a data em segundos e precisamos usar outras funções para trazer pro modelo que necessitamos.
    data_hora_atual = localtime(&segundos);

    mesA = data_hora_atual->tm_mon+1;//Usamos um ponteiro com a struct "tm", para mostrar a parte do mês na variável.
    anoA = data_hora_atual->tm_year+1900;//Usamos esse mesmo ponteiro mas agora com anos.

    idade = anoA - ano;

    if(mesA < mes || mesA == mes)
        idade--;//Algumas observações somente para a idade do usuário ser um pouco mais precisa.

    return idade;
}

int apagaLinha(){
    FILE *arquivopessoa, *arquivotemporario;//Aqui precisamos criar um arquivo a mais, um arquivo temporario.
    char nome[MAX];
    char str[MAX], str1[MAX];
    int i, j=0, k=0;
    char textoArquivo[MAX];
    unsigned int linha_selecionada = 0;
    unsigned int linha_atual = 0;

    arquivopessoa = fopen("pessoa.csv", "r");
    arquivotemporario = fopen("temporario.csv", "w");//Abrimos os dois arquivos normalmente.

    rewind(arquivopessoa);//Apenas certificando que o arquivo está no início.

    if(arquivopessoa == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(0);
    }else{

    printf("Digite o nome da pessoa que deseja apagar:\n");
    scanf("%[^\n]", nome);//Lendo o nome que o usuário deseja apagar.
    getchar();

    for(i=0;i<strlen(nome);i++){
        nome[i] = toupper(nome[i]);
    }

    while(fgets(str, MAX, arquivopessoa)!=NULL){//Nessa parte iremos cálcular as linhas do código.
        if(strstr(str, nome)){//Quando for a linha que o usuário deseja o "j" vai ser igual à linha.
            j=k;
        }
        k++;
    }

    rewind(arquivopessoa);//Voltando o arquivo para o início.

    while(fgets(str, MAX, arquivopessoa) != NULL){
        if(linha_atual != j){//Enquanto a linha for diferente do "j" ele irá passar as informações do arquivo original para o arquivo temporário.
            fputs(str, arquivotemporario);
        }
        memset(str, 0, sizeof(char) * 1001);//Essa função irá preencher a linha com um caracter nulo.
        linha_atual += 1;//Somando "1" na linha.
    }

    fclose(arquivopessoa);
    fclose(arquivotemporario);//Fechando os dois arquivos usados.

    remove("pessoa.csv");//Apagando o arquivo que estavamos usando antes.
    rename("temporario.csv", "pessoa.csv");//E renomeamos o arquivo que recebeu as informações para o arquivo antigo.

    printf("\n");
    printf("Aluno excluído com sucesso!\n");

    getchar();
    }
}

//E assim foi finalizado o programa, espero que tenha gostado!!