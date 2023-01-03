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
    int totalAeronaves;
    TipoAeronave aeronaves[10];
} TipoFrota;




void gotoxy(int x, int y);
int desenharBox(int x, int y);
void aprecentacaoInicial();
int menu(int opcao);
void seta(int realPosition, int arrowPosition);


                                                        //falta // 1 - Mostrar todas aeronaves por ordem descendente de numero de voos
void listarAeronavesProntas(TipoFrota aeronave[]);              // 2 - Mostar Aeronaves Prontas (Todas ou por Localizacao)
void listarAeronavesAutorizacao(TipoFrota aeronave[]);          // 3 - Mostar Aeronaves Aguardar Autorizacao (Todas ou por Localizacao)
                                                        //falta // 4 - Mostrar aeronave incerindo o ID disponivel
void adicionarAeronave(TipoFrota aeronave[]);                   // 5 - Adicionar aeronave a frota
                                                        //falta // 6 - Eliminar aeronave da frota
                                                        //falta // 7 - Editar aeronave
void iniciarPedidoVoo(TipoFrota aeronave[]);                    // 8 - Inciar pedido de voo
                                                        //falta // 9 - Autorizar voo
                                                        //falta // 10 - Cancelar voo
                                                        //falta // 11 - Gravar listagem de aeronaves para ficheiro de texto

//int verificaIgualdadeID (TipoFrota aeronave[], int idTemp);


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
            listarAeronavesProntas(aeronave);
            break;
        case 3:
            system("cls");
            listarAeronavesAutorizacao(aeronave);
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
            //iniciarPedidoVoo(aeronave);
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
        case 11:
            system("cls");
            gotoxy(70,6);
            printf("Voce escolheu opcao 11\n");
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

int desenharBox(int x, int y)
{
    gotoxy(35,5);
    //box borda superior
    for(int i = 0; i <= x; i++)
    {
        if(i == 0)
        {
            printf("%c", 201);
        }
        else if(i == x)
        {
            printf("%c", 187);
        }
        else
        {
            printf("%c", 205);
        }
    }

    //box lados
    for(int i = 6; i < y; i++)
    {
        printf("\n");
        gotoxy(35,i);
        printf("%c",186);
        gotoxy(x+35,i);
        printf("%c",186);
    }

    //box borda inferior
    gotoxy(35,y);
    for(int i = 0; i <= x; i++)
    {
        if(i == 0)
        {
            printf("%c", 200);
        }
        else if(i == x)
        {
            printf("%c", 188);
        }
        else
        {
            printf("%c", 205);
        }
    }
    return 1;
}

void aprecentacaoInicial()
{
    desenharBox(80,36);
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
        desenharBox(80,36);
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
        printf("8. Iniciar pedido de voo");
        gotoxy(40,18);
        seta(9,position);
        printf("9. Autorizar voo");
        gotoxy(40,19);
        seta(10,position);
        printf("10. Cancelar voo");
        gotoxy(40,20);
        seta(11,position);
        printf("11. Gravar listagem de aeronaves para ficheiro de texto");

        gotoxy(50,23);
        printf("Precione tecla \"ESC\" duas vezes para sair do sistema");

        keyPressed = getch();

        if(keyPressed == 80 && position != 11)
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


void listarAeronavesProntas(TipoFrota aeronave[]) // 2
{
    int position = 1;
    int keyPressed = 0;
    int j = 12, l = 12, numAeronave = 1, opcao, opcaoLocalizacao;
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};
    char estadoPronto[20] = {"Pronto"};

    while (keyPressed != 13)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(56,7);
        printf("Listar aeronaves no estado pronto e detalhes");
        gotoxy(40,10);
        printf("Pretende listar todas as aeronaves ou por localizacao especifica:");
        gotoxy(40,12);
        seta(1,position);
        printf("Listar todas as aeronaves");
        gotoxy(40,13);
        seta(2,position);
        printf("Localizacao Especifica");

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

    opcao = position;

    position = 1;
    keyPressed = 0;

    switch(opcao)
    {
    case 1:

        system("cls");
        desenharBox(80,53);
        gotoxy(56,7);
        printf("Listar aeronaves no estado pronto e detalhes");
        gotoxy(40,10);
        printf("A listar todas as aeronaves em estado pronto:");

        for(int i = 0; i < aeronave[0].totalAeronaves; i++)
        {
            if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (i <= 4))
            {
                gotoxy(40,j);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                j++;
                gotoxy(40,j);
                printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                j++;
                gotoxy(40,j);
                printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                j++;
                gotoxy(40,j);
                printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                j++;
                gotoxy(40,j);
                printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                j++;
                gotoxy(40,j);
                printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                j += 2;
                numAeronave++;
            }
            else if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (i >= 5))
            {
                gotoxy(80,l);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                l++;
                gotoxy(80,l);
                printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                l++;
                gotoxy(80,l);
                printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                l++;
                gotoxy(80,l);
                printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                l++;
                gotoxy(80,l);
                printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                l++;
                gotoxy(80,l);
                printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                l += 2;
                numAeronave++;
            }
        }
        getch();
        break;

    case 2:

        while (keyPressed != 13)
        {
            system("cls");
            desenharBox(80,36);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(40,10);
            printf("Selecione a localizacao pretendida da lista a baixo:");
            gotoxy(40,12);
            seta(1,position);
            printf("Vila Real");
            gotoxy(40,13);
            seta(2,position);
            printf("Tires");
            gotoxy(40,14);
            seta(3,position);
            printf("Portimao");

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
            system("cls");
            desenharBox(80,53);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado pronto em Vila Real:");
            for(int i = 0; i < aeronave[0].totalAeronaves; i++)
            {
                if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[0]) == 0) && (i <= 4))
                {
                    gotoxy(40,j);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    j++;
                    gotoxy(40,j);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    j++;
                    gotoxy(40,j);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    j++;
                    gotoxy(40,j);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    j++;
                    gotoxy(40,j);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    j++;
                    gotoxy(40,j);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    j += 2;
                    numAeronave++;
                }
                else if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[0]) == 0) && (i >= 5))
                {
                    gotoxy(80,l);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    l++;
                    gotoxy(80,l);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    l++;
                    gotoxy(80,l);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    l++;
                    gotoxy(80,l);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    l++;
                    gotoxy(80,l);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    l++;
                    gotoxy(80,l);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    l += 2;
                    numAeronave++;
                }
                else if((j == 12) && (l == 12))
                {
                    gotoxy(40,15);
                    printf("De momento nao ha aeronaves prontas em Vila Real");
                }
            }
            getch();
            break;
        case 2:
            system("cls");
            desenharBox(80,53);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado pronto em Tires:");
            for(int i = 0; i < aeronave[0].totalAeronaves; i++)
            {
                if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[1]) == 0) && (i <= 4))
                {
                    gotoxy(40,j);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    j++;
                    gotoxy(40,j);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    j++;
                    gotoxy(40,j);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    j++;
                    gotoxy(40,j);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    j++;
                    gotoxy(40,j);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    j++;
                    gotoxy(40,j);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    j += 2;
                    numAeronave++;
                }
                else if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[1]) == 0) && (i >= 5))
                {
                    gotoxy(80,l);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    l++;
                    gotoxy(80,l);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    l++;
                    gotoxy(80,l);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    l++;
                    gotoxy(80,l);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    l++;
                    gotoxy(80,l);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    l++;
                    gotoxy(80,l);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    l += 2;
                    numAeronave++;
                }
                else if((j == 12) && (l == 12))
                {
                    gotoxy(40,15);
                    printf("De momento nao ha aeronaves prontas em Tires");
                }
            }
            getch();
            break;
        case 3:
            system("cls");
            desenharBox(80,53);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado pronto em Portimao:");
            for(int i = 0; i < aeronave[0].totalAeronaves; i++)
            {
                if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[2]) == 0) && (i <= 4))
                {
                    gotoxy(40,j);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    j++;
                    gotoxy(40,j);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    j++;
                    gotoxy(40,j);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    j++;
                    gotoxy(40,j);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    j++;
                    gotoxy(40,j);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    j++;
                    gotoxy(40,j);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    j += 2;
                    numAeronave++;
                }
                else if((strcmp(aeronave[i].aeronaves[i].estado, estadoPronto) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[2]) == 0) && (i >= 5))
                {
                    gotoxy(80,l);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    l++;
                    gotoxy(80,l);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    l++;
                    gotoxy(80,l);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    l++;
                    gotoxy(80,l);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    l++;
                    gotoxy(80,l);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    l++;
                    gotoxy(80,l);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    l += 2;
                    numAeronave++;
                }
                else if((j == 12) && (l == 12))
                {
                    gotoxy(40,15);
                    printf("De momento nao ha aeronaves prontas em Portimao");
                }
            }
            getch();
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void listarAeronavesAutorizacao(TipoFrota aeronave[]) // 3
{
    int position = 1;
    int keyPressed = 0;
    int j = 12, l = 12, numAeronave = 1, opcao, opcaoLocalizacao;
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};
    char estadoAutorizacao[30] = {"A aguardar Autorizacao"};

    while (keyPressed != 13)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(52,7);
        printf("Listar aeronaves a aguardar autorizacao e detalhes");
        gotoxy(40,10);
        printf("Pretende listar todas as aeronaves ou por localizacao especifica:");
        gotoxy(40,12);
        seta(1,position);
        printf("Listar todas as aeronaves");
        gotoxy(40,13);
        seta(2,position);
        printf("Localizacao Especifica");

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

    opcao = position;

    position = 1;
    keyPressed = 0;

    switch(opcao)
    {
    case 1:

        system("cls");
        desenharBox(80,53);
        gotoxy(52,7);
        printf("Listar aeronaves a aguardar autorizacao e detalhes");
        gotoxy(40,10);
        printf("A listar todas as aeronaves a aguardar autorizacao:");

        for(int i = 0; i < aeronave[0].totalAeronaves; i++)
        {
            if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (i <= 4))
            {
                gotoxy(40,j);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                j++;
                gotoxy(40,j);
                printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                j++;
                gotoxy(40,j);
                printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                j++;
                gotoxy(40,j);
                printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                j++;
                gotoxy(40,j);
                printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                j++;
                gotoxy(40,j);
                printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                j += 2;
                numAeronave++;
            }
            else if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (i >= 5))
            {
                gotoxy(80,l);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                l++;
                gotoxy(80,l);
                printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                l++;
                gotoxy(80,l);
                printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                l++;
                gotoxy(80,l);
                printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                l++;
                gotoxy(80,l);
                printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                l++;
                gotoxy(80,l);
                printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                l += 2;
                numAeronave++;
            }
        }
        getch();
        break;

    case 2:

        while (keyPressed != 13)
        {
            system("cls");
            desenharBox(80,36);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(40,10);
            printf("Selecione a localizacao pretendida da lista a baixo:");
            gotoxy(40,12);
            seta(1,position);
            printf("Vila Real");
            gotoxy(40,13);
            seta(2,position);
            printf("Tires");
            gotoxy(40,14);
            seta(3,position);
            printf("Portimao");

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
            system("cls");
            desenharBox(80,53);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves a aguardar autorizacao em Vila Real:");
            for(int i = 0; i < aeronave[0].totalAeronaves; i++)
            {
                if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[0]) == 0) && (i <= 4))
                {
                    gotoxy(40,j);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    j++;
                    gotoxy(40,j);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    j++;
                    gotoxy(40,j);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    j++;
                    gotoxy(40,j);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    j++;
                    gotoxy(40,j);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    j++;
                    gotoxy(40,j);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    j += 2;
                    numAeronave++;
                }
                else if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[0]) == 0) && (i >= 5))
                {
                    gotoxy(80,l);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    l++;
                    gotoxy(80,l);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    l++;
                    gotoxy(80,l);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    l++;
                    gotoxy(80,l);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    l++;
                    gotoxy(80,l);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    l++;
                    gotoxy(80,l);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    l += 2;
                    numAeronave++;
                }
                else if((j == 12) && (l == 12))
                {
                    gotoxy(40,15);
                    printf("De momento nao ha aeronaves a aguardar autorizacao em Vila Real");
                }
            }
            getch();
            break;
        case 2:
            system("cls");
            desenharBox(80,53);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves a aguardar autorizacao em Tires:");
            for(int i = 0; i < aeronave[0].totalAeronaves; i++)
            {
                if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[1]) == 0) && (i <= 4))
                {
                    gotoxy(40,j);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    j++;
                    gotoxy(40,j);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    j++;
                    gotoxy(40,j);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    j++;
                    gotoxy(40,j);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    j++;
                    gotoxy(40,j);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    j++;
                    gotoxy(40,j);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    j += 2;
                    numAeronave++;
                }
                else if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[1]) == 0) && (i >= 5))
                {
                    gotoxy(80,l);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    l++;
                    gotoxy(80,l);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    l++;
                    gotoxy(80,l);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    l++;
                    gotoxy(80,l);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    l++;
                    gotoxy(80,l);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    l++;
                    gotoxy(80,l);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    l += 2;
                    numAeronave++;
                }
                else if((j == 12) && (l == 12))
                {
                    gotoxy(40,15);
                    printf("De momento nao ha aeronaves a aguardar autorizacao em Tires");
                }
            }
            getch();
            break;
        case 3:
            system("cls");
            desenharBox(80,53);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves a aguardar autorizacao em Portimao:");
            for(int i = 0; i < aeronave[0].totalAeronaves; i++)
            {
                if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[2]) == 0) && (i <= 4))
                {
                    gotoxy(40,j);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    j++;
                    gotoxy(40,j);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    j++;
                    gotoxy(40,j);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    j++;
                    gotoxy(40,j);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    j++;
                    gotoxy(40,j);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    j++;
                    gotoxy(40,j);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    j += 2;
                    numAeronave++;
                }
                else if((strcmp(aeronave[i].aeronaves[i].estado, estadoAutorizacao) == 0) && (strcmp(aeronave[i].aeronaves[i].local, localizacaoTemp[2]) == 0) && (i >= 5))
                {
                    gotoxy(80,l);
                    printf("---------Aeronave N%c%d---------",167,numAeronave);
                    l++;
                    gotoxy(80,l);
                    printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                    l++;
                    gotoxy(80,l);
                    printf("Capacidade da aeronave: %d",aeronave[i].aeronaves[i].capacidade);
                    l++;
                    gotoxy(80,l);
                    printf("Numero de voos realizados: %d",aeronave[i].aeronaves[i].numVoos);
                    l++;
                    gotoxy(80,l);
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    l++;
                    gotoxy(80,l);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    l += 2;
                    numAeronave++;
                }
                else if((j == 12) && (l == 12))
                {
                    gotoxy(40,15);
                    printf("De momento nao ha aeronaves a aguardar autorizacao em Portimao");
                }
            }
            getch();
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}


void adicionarAeronave(TipoFrota aeronave[]) // 5
{
    int quantidadaAeronaves;
    int position = 1;
    int keyPressed = 0;
    int opcaoLocalizacao;
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};
    char estadoPronto[20] = {"Pronto"};

    quantidadaAeronaves = aeronave[0].totalAeronaves;

    if(aeronave[0].totalAeronaves < 10)
    {
        aeronave[0].totalAeronaves += 1;
        aeronave[0].idContador += 1;
    }
    else
    {
        desenharBox(80,36);
        gotoxy(63,7);
        printf("Adicionar Aeronave a Frota:");
        gotoxy(55,12);
        printf("Limite maximo das aeronaves foi atingido,");
        gotoxy(45,14);
        printf("elimine alguma aeronave para poder adicionar outra aeronave.");
        gotoxy(53,20);
        printf("A voltar para menu principal em:");
        for(int i = 5; i > 0; i--)
        {
            printf(" %d",i);
            Sleep(1000);
        }
        printf("\a");
        return;
    }

    //atribuicao do ID da aeronave
    aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].id = aeronave[0].idContador;


//    do
//    {
//        printf("Introduza o numero de ID da aeronave:\n--->");
//        scanf("%d",&idTemp);
//        fflush(stdin);
//        if(verificaIgualdadeID(aeronave, idTemp) != 0)
//        {
//            printf("ERRO: O ID ja existe, reintroduza o ID da aeronave.\n");
//        }
//    }
//    while (verificaIgualdadeID(aeronave, idTemp) != 0);
//    aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].id = idTemp;
//    fflush(stdin);


    //recolher do valor da capacidade
    do
    {
        desenharBox(80,36);
        gotoxy(63,7);
        printf("Adicionar Aeronave a Frota:");
        gotoxy(60,10);
        printf("Introduza os dados da %d aeronave", aeronave[0].totalAeronaves);
        gotoxy(38,12);
        printf("Introduza a capacidade maxima de passageirosos (No minimo 2 e no maximo 4):");
        gotoxy(38,13);
        printf("---> ");
        scanf("%d",&aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade);
        fflush(stdin);

        if ((aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade < 2) || (aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade > 4))
        {
            gotoxy(40,15);
            printf("ERRO: Voce intoduziu a quantidade incorreta, reintroduza a quantidade.\n");
            Sleep(2000);
            system("cls");

        }
    }
    while (( aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade < 2) || (aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].capacidade > 4));

    //atribuicao da localizacao atual da aeronave
    while (keyPressed != 13)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(63,7);
        printf("Adicionar Aeronave a Frota:");
        gotoxy(60,10);
        printf("Introduza os dados da %d aeronave", aeronave[0].totalAeronaves);
        gotoxy(40,12);
        printf("Selecione a localizacao atual da aeronave:");
        gotoxy(40,14);
        seta(1,position);
        printf("Vila Real");
        gotoxy(40,15);
        seta(2,position);
        printf("Tires");
        gotoxy(40,16);
        seta(3,position);
        printf("Portimao");

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

    //atribuicao estado pronto
    strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].estado, estadoPronto);

    gotoxy(57,20);
    printf("Foi atribuido estado pronto a aeronave");

    gotoxy(43,23);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal");

    getch();


    //registo de ultimos 3 voos --- fazer na parte de autorizar aeronave
}


//int verificaIgualdadeID (TipoFrota aeronave[], int idTemp)
//{
//    for(int i = 0; i < 10; i++)
//    {
//        if (aeronave[i].aeronaves[i].id == idTemp)
//        {
//            return 1;
//        }
//    }
//    return 0;
//}


/*

void iniciarPedidoVoo(TipoFrota aeronave[]) // 8
{
    int position = 1;
    int keyPressed = 0;
    int opcaoEstado, opcaoDestino;
    char estadoTemp[2][20] = {"Pronto","Autorizado"};
    char strOrdenarNomes[50];
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};


    for(int i = 0; i < ; i)
    {





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
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].destino, localizacaoTemp[1]);
            break;
        case 2:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].destino, localizacaoTemp[2]);
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
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].destino, localizacaoTemp[0]);
            break;
        case 2:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].destino, localizacaoTemp[2]);
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
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].destino, localizacaoTemp[0]);
            break;
        case 2:
            strcpy(aeronave[quantidadaAeronaves].aeronaves[quantidadaAeronaves].destino, localizacaoTemp[1]);
            break;
        default:
            break;
        }
    }
} */
