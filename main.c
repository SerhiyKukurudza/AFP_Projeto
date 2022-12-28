#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#include"conio2.h"

#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


#define FALSE 0
#define TRUE 1
#define BOX_X 80
#define BOX_Y 30+6
#define TIME 2000

typedef struct
{
    long int nif;
    char nome [50];
} TipoPassageiro;

typedef struct
{
    int id;
    int capacidade;
    int numVoos;
    char estado[20];
    char local[20];
    char destino[20];
    char historico[3][20];
    TipoPassageiro manifesto[4];
} TipoAeronave;

typedef struct
{
    int totalPassageiros;
    int idContador;
    TipoAeronave aeronaves[10];
} TipoFrota;




void gotoxy(int x, int y);
void desenharBox();
void aprecentacaoInicial();

int menu(int opcao);
void seta(int realPosition, int arrowPosition);
void aprecentacaoInicial();
void adicionarAeronave(TipoFrota aeronave[]);
int verificaIgualdadeID (TipoFrota aeronave[], int idTemp);

int main()
{
    //Predefinicao do tamanho da janela do terminal
    SMALL_RECT windowSize = {0, 0, 150, 50};    //{L, T, R(X), B(Y)}
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    //Predefinicao da funcao para esconder o cursor
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);

    //Main do projeto a partir de aqui

    int opcao = 0;

    //setlocale(LC_CTYPE, "Portuguese");
    //system("color 0A");

    TipoFrota aeronave[10];

    aprecentacaoInicial();

    while(1)
    {
        opcao = menu(opcao);


        switch (opcao)
        {
        case 1:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 1\n");
            break;
        case 2:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 2\n");
            break;
        case 3:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 3\n");
            break;
        case 4:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 4\n");
            break;
        case 5:
            system("cls");
            adicionarAeronave(aeronave);
            break;
        case 6:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 6\n");
            break;
        case 7:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 7\n");
            break;
        case 8:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 8\n");
            break;
        case 9:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 9\n");
            break;
        case 10:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 10\n");
            break;
        default:
            return 0;
            break;
        }
    }
}


void gotoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void desenharBox()
{
    gotoxy(35,5);
    //box borda superior
    for(int i = 0; i <= BOX_X; i++)
    {
        if(i == 0)
        {
            printf("%c", 201);
        }
        else if(i == BOX_X)
        {
            printf("%c", 187);
        }
        else
        {
            printf("%c", 205);
        }
    }

    //box lados
    for(int i = 6; i < BOX_Y; i++)
    {
        printf("\n");
        gotoxy(35,i);
        printf("%c",186);
        gotoxy(BOX_X+35,i);
        printf("%c",186);
    }

    //box borda inferior
    gotoxy(35,BOX_Y);
    for(int i = 0; i <= BOX_X; i++)
    {
        if(i == 0)
        {
            printf("%c", 200);
        }
        else if(i == BOX_X)
        {
            printf("%c", 188);
        }
        else
        {
            printf("%c", 205);
        }
    }
}

void aprecentacaoInicial()
{
    desenharBox();
    gotoxy(53,10);
    puts("Bem vindo ao TAIPS - Transportadora Aerea IPS");
    gotoxy(50,30);
    puts("Projeto realizado por: Serhiy Kukurudza e Bruno Rosa");
    Sleep(1000);
    system("cls");
}

int menu(int opcao)
{
    int position = 1;
    int keyPressed = 0;

    while (keyPressed != 13)
    {
        system("cls");
        desenharBox();
        gotoxy(70,7);
        printf("Menu principal");
        gotoxy(40,10);
        seta(1,position);
        printf("1. Listar aeronaves e detalhes");
        gotoxy(40,11);
        seta(2,position);
        printf("2. Listar aeronaves no estado pronto e detalhes");
        gotoxy(40,12);
        seta(3,position);
        printf("3. Listar aeronaves a aguardar autorizacao e detalhes");
        gotoxy(40,13);
        seta(4,position);
        printf("4. Consultar aeronave especifica mostrando respetivos detalhes");
        gotoxy(40,14);
        seta(5,position);
        printf("5. Adicionar aeronave a frota");
        gotoxy(40,15);
        seta(6,position);
        printf("6. Eliminar aeronave da frota");
        gotoxy(40,16);
        seta(7,position);
        printf("7. Editar aeronave");
        gotoxy(40,17);
        seta(8,position);
        printf("8. Autorizar voo");
        gotoxy(40,18);
        seta(9,position);
        printf("9. Cancelar voo");
        gotoxy(40,19);
        seta(10,position);
        printf("10. Gravar listagem de aeronaves para ficheiro de texto");

        gotoxy(50,23);
        printf("Precione tecla \"ESC\" duas vezes para sair do sistema");

        keyPressed = getch();

        if(keyPressed == 80 && position != 10)
        {
            position++;
        }
        else if(keyPressed == 72 && position != 1)
        {
            position--;
        }
        else if(keyPressed == 27)
        {
            gotoxy(55,24);
            printf("Voce escolheu opcao sair do sistema");
            position = 0;
            break;
        }
        else
        {
            position = position;
        }
    }

    opcao = position;

    return opcao;

}

void seta(int realPosition, int arrowPosition)
{
    if(realPosition == arrowPosition)
    {
        for(int i = 0; i <= 2; i++)
        {
            printf("%c",61);
        }
        printf("%c ",62);
    }
    else
    {
        printf("       ");
    }
}


void adicionarAeronave(TipoFrota aeronave[])
{
    int idTemp;
    int quantidadaAeronaves;
    int position = 1;
    int keyPressed = 0;
    int opcaoEstado, opcaoLocalizacao, opcaoDestino;
    char estadoTemp[2][20] = {"Pronto","Autorizado"};
    char strOrdenarNomes[50];
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};

    quantidadaAeronaves = aeronave[0].idContador;

    if(aeronave[0].idContador < 2)
    {
        aeronave[0].idContador += 1;
    }
    else
    {
        gotoxy(50,23);
        printf("Limite maximo de aeronaves foi atingido, elimine aeronave para poder adicionar outra aeronave");
        gotoxy(50,25);
        printf("A voltar para menu principal em:");
        for(int i = 5; i > 0; i--)
        {
            printf(" %d",i);
            Sleep(1000);
        }
        printf("\a");
        return;
    }

    printf("\n\nIntroduza os dados da %d aeronave\n", aeronave[0].idContador);

    //recolher do ID da aeronave
    do
    {
        printf("Introduza o numero de ID da aeronave:\n--->");
        scanf("%d",&idTemp);
        fflush(stdin);
        if(verificaIgualdadeID(aeronave, idTemp) != 0)
        {
            printf("ERRO: O ID ja existe, reintroduza o ID da aeronave.\n");
        }
    }
    while (verificaIgualdadeID(aeronave, idTemp) != 0);
    aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].id = idTemp;
    fflush(stdin);

    //recolher do valor da capacidade
    do
    {
        printf("Introduza a capacidade maxima de passageirosos (No minimo 2 e no maximo 4):\n--->");
        scanf("%d",&aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade);
        //fflush(stdin);
        if ((aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade < 2) || (aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade > 4))
        {
            printf("ERRO: Voce intoduziu a quantidade incorreta, reintroduza a quantidade.\n");
        }
    }
    while (( aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade < 2) || (aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade > 4));

    //atribuicao do estado
    while (keyPressed != 13)
    {
        system("cls");
        printf("Selecione o estado atual da aeronave:\n");
        seta(1,position);
        printf("Pronto\n");
        seta(2,position);
        printf("Autorizado\n");

        keyPressed = getch();

        if(keyPressed == 80 && position != 2)
        {
            position++;
        }
        else if(keyPressed == 72 && position != 1)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }

    opcaoEstado = position;

    position = 1;
    keyPressed = 0;

    switch(opcaoEstado)
    {
    case 1:
        strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].estado, estadoTemp[0]);
        break;
    case 2:
        strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].estado, estadoTemp[1]);
        break;
    default:
        break;
    }

    //recolher dados dos passageiros
    printf("Introduza os dados dos passageiros:\n");
    for(int i = 0; i < aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade; i++)
    {
        printf("\nIntroduza o NIF do %d passageiro:\n--->", i+1);
        scanf("%ld",&aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[i].nif);
        fflush(stdin);
        printf("\nIntroduza o nome do %d passageiro:\n--->", i+1);
        gets(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[i].nome);
        fflush(stdin);
    }

    //ordenar nomes por ordem alfabetica
    for(int i = 0; i < aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade; i++)
    {
        for(int j = i+1; j < aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade; j++)
        {
            if(strcmp(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[i].nome,aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[j].nome)>0)
            {
                strcpy(strOrdenarNomes,aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[i].nome);
                strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[i].nome,aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[j].nome);
                strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].manifesto[j].nome,strOrdenarNomes);
            }
        }
    }

    //atribuicao da localizacao atual da aeronave
    while (keyPressed != 13)
    {
        system("cls");
        printf("Selecione a localizacao atual da aeronave:\n");
        seta(1,position);
        printf("Vila Real\n");
        seta(2,position);
        printf("Tires\n");
        seta(3,position);
        printf("Portimao\n");

        keyPressed = getch();

        if(keyPressed == 80 && position != 3)
        {
            position++;
        }
        else if(keyPressed == 72 && position != 1)
        {
            position--;
        }
        else
        {
            position = position;
        }
    }

    opcaoLocalizacao = position;

    position = 1;
    keyPressed = 0;

    switch(opcaoLocalizacao)
    {
    case 1:
        strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[0]);
        break;
    case 2:
        strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[1]);
        break;
    case 3:
        strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[2]);
        break;
    default:
        break;
    }

    //atribuicao do destino da aeronave
    if(opcaoLocalizacao == 1)
    {
        while (keyPressed != 13)
        {
            system("cls");
            printf("Selecione o destino da aeronave:\n");
            seta(1,position);
            printf("Tires\n");
            seta(2,position);
            printf("Portimao\n");

            keyPressed = getch();

            if(keyPressed == 80 && position != 3)
            {
                position++;
            }
            else if(keyPressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }

        opcaoDestino = position;

        position = 1;
        keyPressed = 0;

        switch(opcaoDestino)
        {
        case 1:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[1]);
            break;
        case 2:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[2]);
            break;
        default:
            break;
        }
    }

    else if(opcaoLocalizacao == 2)
    {
        while (keyPressed != 13)
        {
            system("cls");
            printf("Selecione o destino da aeronave:\n");
            seta(1,position);
            printf("Vila Real\n");
            seta(2,position);
            printf("Portimao\n");

            keyPressed = getch();

            if(keyPressed == 80 && position != 3)
            {
                position++;
            }
            else if(keyPressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }

        opcaoDestino = position;

        position = 1;
        keyPressed = 0;

        switch(opcaoDestino)
        {
        case 1:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[0]);
            break;
        case 2:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[2]);
            break;
        default:
            break;
        }
    }

    else
    {
        while (keyPressed != 13)
        {
            system("cls");
            printf("Selecione o destino da aeronave:\n");
            seta(1,position);
            printf("Vila Real\n");
            seta(2,position);
            printf("Tires\n");

            keyPressed = getch();

            if(keyPressed == 80 && position != 3)
            {
                position++;
            }
            else if(keyPressed == 72 && position != 1)
            {
                position--;
            }
            else
            {
                position = position;
            }
        }

        opcaoDestino = position;

        position = 1;
        keyPressed = 0;

        switch(opcaoDestino)
        {
        case 1:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[0]);
            break;
        case 2:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].local, localizacaoTemp[1]);
            break;
        default:
            break;
        }
    }

    gotoxy(50,23);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal");

    getch();


    //registo de ultimos 3 voos --- fazer na parte de autorizar aeronave



    //

    /*
    scanf("%d",&a->numeroUtente);
    fflush(stdin);


    printf("Introduza o nome do passageiro: \n");
    gets(a->nomeUtente);
    fflush(stdin);


    printf("Introduza a localização atual:\n");
    gets(a->moradaUtente);
    fflush(stdin);

    printf("Introduza o destino da aeronave:\n");
    scanf("%d",&a->dataInscricao.dia);
    fflush(stdin);

    printf("Introduza o mes:\n");
    gets(a->dataInscricao.mes);
    fflush(stdin);
    printf("Introduza o ano:\n");
    scanf("%d",&a->dataInscricao.ano);
    fflush(stdin);
    printf("Introduza o número de obras requisitadas (Máximo 5 unidades):\n");
    scanf("%d", &a->numeroObras);
    fflush(stdin);


    }*/
}

int verificaIgualdadeID (TipoFrota aeronave[], int idTemp)
{
    for(int i = 0; i < 10; i++)
    {
        if (aeronave[i].aeronaves[i].id == idTemp)
        {
            return 1;
        }
    }
    return 0;
}
