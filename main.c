#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
//-------------------------------------------------------------------------------------------------------------------------------------------------------
#define RED   "\x1B[31m"                                                        //
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
//-------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct                                                                  //
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y);                                                      // Subprograma para movimentar o cursos
int desenharBox(int x, int y);                                                  // Subprograma para desenhar box
void aprecentacaoInicial();                                                     // Subprograma que apresenta capa do projeto
void seta(int realPosition, int arrowPosition);                                 // Subprograma que implementa a seta da escolha
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int implementacaoMenu(int opcao);                                               // Menu principal
void adicionarAeronaveFrota(TipoFrota aeronave[]);                              // 1 - Adicionar aeronave a frota
void eliminarAeronaveFrota(TipoFrota aeronave[]);                               // 2 - Eliminar aeronave da frota
void editarAeronaveFrota(TipoFrota aeronave[]);                       //Parte2  // 3 - Editar aeronave
void iniciarPedidoVoo(TipoFrota aeronave[]);                                    // 4 - Iniciar pedido de voo
void autorizarVoo(TipoFrota aeronave[]);                                        // 5 - Autorizar voo
void cancelarVoo(TipoFrota aeronave[]);                                         // 6 - Cancelar voo
void listarAeronavesOrdemDescendenteVoos(TipoFrota aeronave[]);                 // 7 - Listar todas as aeronaves por ordem descendente de numero de voos
void listarAeronavesEstadoPronto(TipoFrota aeronave[]);                         // 8 - Listar aeronaves prontas (Todas ou por Local)
void listarAeronavesEstadoAutorizacao(TipoFrota aeronave[]);                    // 9 - Listar aeronaves a aguardar autorizacao (Todas ou por Local)
void consultarAeronavePorId(TipoFrota aeronave[]);                              // 10 - Consultar aeronave inserindo o ID disponivel
void gravarListagemAeronaves(TipoFrota aeronave[]);                   //Parte 2 // 11 - Gravar listagem de aeronaves para ficheiro de texto
//-------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
//-------------------------------------------------------------------------------------------------------------------------------------------------------
    SMALL_RECT windowSize = {0, 0, 150, 50};    //{L, T, R(X), B(Y)}            // Predefinicao do tamanho da janela do terminal
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
//-------------------------------------------------------------------------------------------------------------------------------------------------------
    HANDLE hStdOut = NULL;                                                      // Predefinicao da funcao para esconder o cursor
    CONSOLE_CURSOR_INFO curInfo;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
//-------------------------------------------------------------------------------------------------------------------------------------------------------

    int opcao = 0;
    //setlocale(LC_CTYPE, "Portuguese");
    //system("color 0A");
    TipoFrota aeronave[10];
    aprecentacaoInicial();

    while(1)
    {
        opcao = implementacaoMenu(opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            adicionarAeronaveFrota(aeronave);
            break;
        case 2:
            system("cls");
            eliminarAeronaveFrota(aeronave);
            break;
        case 3:
            system("cls");
            editarAeronaveFrota(aeronave);
            break;
        case 4:
            system("cls");
            iniciarPedidoVoo(aeronave);
            break;
        case 5:
            system("cls");
            autorizarVoo(aeronave);
            break;
        case 6:
            system("cls");
            cancelarVoo(aeronave);
            break;
        case 7:
            system("cls");
            listarAeronavesOrdemDescendenteVoos(aeronave);
            break;
        case 8:
            system("cls");
            listarAeronavesEstadoPronto(aeronave);
            break;
        case 9:
            system("cls");
            listarAeronavesEstadoAutorizacao(aeronave);
            break;
        case 10:
            system("cls");
            consultarAeronavePorId(aeronave);
            break;
        case 11:
            system("cls");
            gravarListagemAeronaves(aeronave);
            break;
        default:
            return 0;
            break;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int implementacaoMenu(int opcao)                                                // Menu principal
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
        printf("1. Adicionar aeronave a frota");
        gotoxy(40,11);
        seta(2,position);
        printf("2. Eliminar aeronave da frota");
        gotoxy(40,12);
        seta(3,position);
        printf("3. Editar aeronave");
        gotoxy(40,13);
        seta(4,position);
        printf("4. Iniciar pedido de voo");
        gotoxy(40,14);
        seta(5,position);
        printf("5. Autorizar voo");
        gotoxy(40,15);
        seta(6,position);
        printf("6. Cancelar voo");
        gotoxy(40,16);
        seta(7,position);
        printf("7. Listar aeronaves e detalhes (Ordem descendente de N%c de voos)",167);
        gotoxy(40,17);
        seta(8,position);
        printf("8. Listar aeronaves no estado pronto e detalhes");
        gotoxy(40,18);
        seta(9,position);
        printf("9. Listar aeronaves a aguardar autorizacao e detalhes");
        gotoxy(40,19);
        seta(10,position);
        printf("10. Consultar aeronave especifica mostrando respetivos detalhes");
        gotoxy(40,20);
        seta(11,position);
        printf("11. Gravar listagem de aeronaves para ficheiro de texto");

        gotoxy(50,27);
        printf("Pressione tecla \"ESC\" duas vezes para sair do sistema");

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
            gotoxy(58,29);
            printf(RED"Voce escolheu opcao sair do sistema"RESET);
            position = 0;
            gotoxy(0,40);
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void adicionarAeronaveFrota(TipoFrota aeronave[])                               // 1 - Adicionar aeronave a frota
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void eliminarAeronaveFrota(TipoFrota aeronave[])                                // 2 - Eliminar aeronave da frota // falta fazer
{
    desenharBox(80,36);
    gotoxy(65,7);
    printf("Eliminar aeronave da frota");
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel");
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal"RESET);
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void editarAeronaveFrota(TipoFrota aeronave[])                        //Parte2  // 3 - Editar aeronave
{
    desenharBox(80,36);
    gotoxy(69,7);
    printf("Editar aeronave");
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel");
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal"RESET);
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void iniciarPedidoVoo(TipoFrota aeronave[])                                     // 4 - Iniciar pedido de voo
{
    int position = 1;
    int keyPressed = 0;
    int opcaoDestino, j = 12, l = 12, numAeronave = 1, aeronaveEscolhida;
    char estadoTemp[2][30] = {"Pronto","A aguardar autorizacao"};
    char strOrdenarNomes[50];
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};

        do
        {
            j = 12;
            l = 12;
            numAeronave = 1;

            system("cls");
            desenharBox(80,50);
            gotoxy(67,7);
            printf("Iniciar pedido de voo");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado pronto:");

            for(int i = 0; i < aeronave[0].totalAeronaves; i++)
            {
                if((strcmp(aeronave[i].aeronaves[i].estado, estadoTemp[0]) == 0) && (i <= 4))
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
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    j++;
                    gotoxy(40,j);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    j += 2;
                    numAeronave++;
                }
                else if((strcmp(aeronave[i].aeronaves[i].estado, estadoTemp[0]) == 0) && (i >= 5))
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
                    printf("Estado atual: %s",aeronave[i].aeronaves[i].estado);
                    l++;
                    gotoxy(80,l);
                    printf("Local atual: %s",aeronave[i].aeronaves[i].local);
                    l += 2;
                    numAeronave++;
                }
            }
            gotoxy(40,43);
            printf("Introduza o numero da aeronave disponivel");
            gotoxy(40,44);
            printf("(Se nao tiver aeronaves disponiveis, introduza 20)");
            gotoxy(40,45);
            printf("---> ");
            scanf("%d",&aeronaveEscolhida);

            if (aeronaveEscolhida == 20)
            {
                return;
            }
            else if ((aeronaveEscolhida < 1) || (aeronaveEscolhida > aeronave[0].totalAeronaves))
            {
                gotoxy(57,47);
                printf("ERRO: Voce intoduziu o valor invalido,");
                gotoxy(54,48);
                printf("reintroduze o valor dentro dos apresentados.");
                Sleep(2000);
                system("cls");
            }
        }
        while ((aeronaveEscolhida < 1) || (aeronaveEscolhida > aeronave[0].totalAeronaves));

        aeronaveEscolhida -= 1;

        gotoxy(58,48);
        printf("Foi escolhida a aeronave N%c%d com ID: %d",167,aeronaveEscolhida + 1,aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].id);
        Sleep(2000);

        //recolher dados dos passageiros
        system("cls");
        desenharBox(80,36);
        gotoxy(67,7);
        printf("Iniciar pedido de voo");
        gotoxy(59,10);
        printf("Introduza os dados dos passageiros:");
        j = 12;
        l = 12;
        for(int i = 0; i < aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].capacidade; i++)
        {
            if(i < 2)
            {
                gotoxy(40,j);
                printf("Introduza o NIF do %d passageiro:", i+1);
                j++;
                gotoxy(40,j);
                printf("---> ");
                scanf("%ld",&aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[i].nif);
                fflush(stdin);
                j += 2;
                gotoxy(40,j);
                printf("Introduza o nome do %d passageiro:", i+1);
                j++;
                gotoxy(40,j);
                printf("---> ");
                gets(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[i].nome);
                fflush(stdin);
                j += 2;
            }
            else
            {
                gotoxy(80,l);
                printf("Introduza o NIF do %d passageiro:", i+1);
                l++;
                gotoxy(80,l);
                printf("---> ");
                scanf("%ld",&aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[i].nif);
                fflush(stdin);
                l += 2;
                gotoxy(80,l);
                printf("Introduza o nome do %d passageiro:", i+1);
                l++;
                gotoxy(80,l);
                printf("---> ");
                gets(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[i].nome);
                fflush(stdin);
                l += 2;
            }
        }

        //ordenar nomes por ordem alfabetica
        for(int i = 0; i < aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].capacidade; i++)
        {
            for(int j = i+1; j < aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].capacidade; j++)
            {
                if(strcmp(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[i].nome,aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[j].nome)>0)
                {
                    strcpy(strOrdenarNomes,aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[i].nome);
                    strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[i].nome,aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[j].nome);
                    strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].manifesto[j].nome,strOrdenarNomes);
                }
            }
        }

        //atribuicao do destino da aeronave
        if(strcmp(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].local, localizacaoTemp[0]) == 0)
        {
            while (keyPressed != 13)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(67,7);
                printf("Iniciar pedido de voo");
                gotoxy(40,10);
                printf("Selecione o destino da aeronave:");
                gotoxy(40,12);
                seta(1,position);
                printf("Tires");
                gotoxy(40,13);
                seta(2,position);
                printf("Portimao");

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

            opcaoDestino = position;

            position = 1;
            keyPressed = 0;

            switch(opcaoDestino)
            {
            case 1:
                strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].destino, localizacaoTemp[1]);
                break;
            case 2:
                strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].destino, localizacaoTemp[2]);
                break;
            default:
                break;
            }
        }

        else if(strcmp(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].local, localizacaoTemp[1]) == 0)
        {
            while (keyPressed != 13)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(67,7);
                printf("Iniciar pedido de voo");
                gotoxy(40,10);
                printf("Selecione o destino da aeronave:\n");
                gotoxy(40,12);
                seta(1,position);
                printf("Vila Real");
                gotoxy(40,13);
                seta(2,position);
                printf("Portimao");

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

            opcaoDestino = position;

            position = 1;
            keyPressed = 0;

            switch(opcaoDestino)
            {
            case 1:
                strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].destino, localizacaoTemp[0]);
                break;
            case 2:
                strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].destino, localizacaoTemp[2]);
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
                desenharBox(80,36);
                gotoxy(67,7);
                printf("Iniciar pedido de voo");
                gotoxy(40,10);
                printf("Selecione o destino da aeronave:\n");
                gotoxy(40,12);
                seta(1,position);
                printf("Vila Real");
                gotoxy(40,13);
                seta(2,position);
                printf("Tires");

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

            opcaoDestino = position;

            position = 1;
            keyPressed = 0;

            switch(opcaoDestino)
            {
            case 1:
                strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].destino, localizacaoTemp[0]);
                break;
            case 2:
                strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].destino, localizacaoTemp[1]);
                break;
            default:
                break;
            }
        }

        strcpy(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].estado, estadoTemp[1]);

        gotoxy(60,19);
        printf("Aeronave a aguardar autorizacao");
        gotoxy(43,24);
        printf("Precione qual quer tecla do teclado para voltar ao menu principal");
        getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void autorizarVoo(TipoFrota aeronave[])                                         // 5 - Autorizar voo // falta fazer
{
    desenharBox(80,36);
    gotoxy(69,7);
    printf("Autorizar voo");
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel");
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal"RESET);
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void cancelarVoo(TipoFrota aeronave[])                                          // 6 - Cancelar voo // falta fazer
{
    desenharBox(80,36);
    gotoxy(70,7);
    printf("Cancelar voo");
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel");
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal"RESET);
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void listarAeronavesOrdemDescendenteVoos(TipoFrota aeronave[])                  // 7 - Listar todas as aeronaves por ordem descendente de numero de voos // falta fazer
{
    desenharBox(80,36);
    gotoxy(47,7);
    printf("Listar aeronaves e detalhes (Ordem descendente de N%c de voos)",167);
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel");
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal"RESET);
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void listarAeronavesEstadoPronto(TipoFrota aeronave[])                          // 8 - Listar aeronaves prontas (Todas ou por Local)
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

        gotoxy(43,50);
        printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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

            gotoxy(43,50);
            printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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

            gotoxy(43,50);
            printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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

            gotoxy(43,50);
            printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void listarAeronavesEstadoAutorizacao(TipoFrota aeronave[])                     // 9 - Listar aeronaves a aguardar autorizacao (Todas ou por Local)
{
    int position = 1;
    int keyPressed = 0;
    int j = 12, l = 12, numAeronave = 1, opcao, opcaoLocalizacao;
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};
    char estadoAutorizacao[30] = {"A aguardar autorizacao"};

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
                j++;
                gotoxy(40,j);
                printf("Destino atual: %s",aeronave[i].aeronaves[i].destino);
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
                l++;
                gotoxy(80,l);
                printf("Local atual: %s",aeronave[i].aeronaves[i].destino);
                l += 2;
                numAeronave++;
            }
        }

        gotoxy(43,50);
        printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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

            gotoxy(43,50);
            printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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

            gotoxy(43,50);
            printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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

            gotoxy(43,50);
            printf("Precione qual quer tecla do teclado para voltar ao menu principal");

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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void consultarAeronavePorId(TipoFrota aeronave[])                               // 10 - Consultar aeronave inserindo o ID disponivel
{
    int j = 11, l = 11, numAeronave = 1, aeronaveEscolhida;
    char estadoAutorizacao[30] = {"A aguardar Autorizacao"};

    do
    {
        j = 11;
        l = 11;
        numAeronave = 1;

        system("cls");
        desenharBox(80,50);
        gotoxy(43,7);
        printf("Consultar aeronave especifica mostrando respetivos detalhes por ID");
        gotoxy(40,9);
        printf("A listar todas as aeronaves disponiveis:");

        for(int i = 0; i < aeronave[0].totalAeronaves; i++)
        {
            if(i <= 4)
            {
                gotoxy(40,j);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                j++;
                gotoxy(40,j);
                printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                j += 2;
                numAeronave++;
            }
            else if (i >= 5)
            {
                gotoxy(80,l);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                l++;
                gotoxy(80,l);
                printf("ID da aeronave: %d",aeronave[i].aeronaves[i].id);
                l += 2;
                numAeronave++;

            }
        }
        gotoxy(40,28);
        printf("Introduza o numero da aeronave disponivel");
        gotoxy(40,29);
        printf("---> ");
        scanf("%d",&aeronaveEscolhida);

        if ((aeronaveEscolhida < 1) || (aeronaveEscolhida > aeronave[0].totalAeronaves))
        {
            gotoxy(57,31);
            printf("ERRO: Voce intoduziu o valor invalido,");
            gotoxy(54,32);
            printf("reintroduze o valor dentro dos apresentados.");
            Sleep(2000);
            system("cls");
        }
    }
    while ((aeronaveEscolhida < 1) || (aeronaveEscolhida > aeronave[0].totalAeronaves));

    j = 31;
    aeronaveEscolhida -= 1;

    for(int i = 0; i < 1; i++)
    {
        gotoxy(40,j);
        printf("---------Aeronave N%c%d---------",167,aeronaveEscolhida + 1);
        j++;
        gotoxy(40,j);
        printf("ID da aeronave: %d",aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].id);
        j++;
        gotoxy(40,j);
        printf("Capacidade da aeronave: %d",aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].capacidade);
        j++;
        gotoxy(40,j);
        printf("Numero de voos realizados: %d",aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].numVoos);
        j++;
        gotoxy(40,j);
        printf("Estado atual: %s",aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].estado);
        j++;
        gotoxy(40,j);
        printf("Local atual: %s",aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].local);
        j++;

        if(strcmp(aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].estado, estadoAutorizacao) == 0)
        {
            gotoxy(40,j);
            printf("Local do destino: %s",aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].destino);
            j++;

            for(int i = 0; i < aeronave[aeronaveEscolhida].aeronaves[aeronaveEscolhida].capacidade; i++)
            {
                gotoxy(40, j);
                printf("NIF do N%c%d passageiro: %ld",167,i+1,aeronave[i].aeronaves[i].manifesto[i].nif);
                j++;
                gotoxy(40, j);
                printf("Nome completo do N%c%d passageiro: %s",167,i+1,aeronave[i].aeronaves[i].manifesto[i].nome);
                j++;
            }
        }
    }

    gotoxy(43,48);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal");

    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void gravarListagemAeronaves(TipoFrota aeronave[])                    //Parte 2 // 11 - Gravar listagem de aeronaves para ficheiro de texto
{
    desenharBox(80,36);
    gotoxy(52,7);
    printf("Gravar listagem de aeronaves para ficheiro de texto");
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel");
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal"RESET);
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y)                                                       // Subprograma para movimentar o cursos
{
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int desenharBox(int x, int y)                                                   // Subprograma para desenhar box
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void aprecentacaoInicial()                                                      // Subprograma que apresenta capa do projeto
{
    desenharBox(80,36);
    gotoxy(53,10);
    puts("Bem vindo ao TAIPS - Transportadora Aerea IPS");
    gotoxy(50,30);
    puts("Projeto realizado por: Serhiy Kukurudza e Bruno Rosa");
    Sleep(1000);
    system("cls");
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void seta(int realPosition, int arrowPosition)                                  // Subprograma que implementa a seta da escolha
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
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
