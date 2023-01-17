#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
//-------------------------------------------------------------------------------------------------------------------------------------------------------
#define TRUE 1
#define FALSE 0
//-------------------------------------------------------------------------------------------------------------------------------------------------------
#define RED   "\x1B[31m"                                                        // Definicao das cores para mudar a cor das letras
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
//-------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct                                                                  // Definicao da estrutura do projeto
{
    long int nif;
    char nome [50];
} TipoPassageiro;

typedef struct
{
    int id;
    int capacidade;
    int numVoos;
    char estado[30];
    char localAtual[20];
    char destino[20];
    char historico[3][30];
    TipoPassageiro manifesto[4];
} TipoAeronave;

typedef struct
{
    int totalPassageiros;
    int idContador;
    int totalAeronaves;
    int totalFrota;
    TipoAeronave aeronaves[10];
} TipoFrota;
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y);                                                      // Subprograma para movimentar o cursos
int desenharBox(int x, int y);                                                  // Subprograma para desenhar box
void aprecentacaoInicial();                                                     // Subprograma que apresenta capa do projeto
void seta(int realPosition, int arrowPosition);                                 // Subprograma que implementa a seta da escolha
//-------------------------------------------------------------------------------------------------------------------------------------------------------
int implementacaoMenu(int opcao);                                                                                        // Menu principal
void adicionarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20]);                            // 1 - Adicionar aeronave a frota
void eliminarAeronaveFrota(TipoFrota *frota);                               // 2 - Eliminar aeronave da frota
void editarAeronaveFrota(TipoFrota *frota);                       //Parte2  // 3 - Editar aeronave
void iniciarPedidoVoo(TipoFrota *frota);                                    // 4 - Iniciar pedido de voo
void autorizarVoo(TipoFrota *frota);                                        // 5 - Autorizar voo
void cancelarVoo(TipoFrota *frota);                                         // 6 - Cancelar voo
void listarAeronavesOrdemDescendenteVoos(TipoFrota *frota);                 // 7 - Listar todas as aeronaves por ordem descendente de numero de voos
void listarAeronavesEstadoPronto(TipoFrota *frota,int *verificarAirCraft, int *opcaoAirCraft, int *localAirCraft);                         // 8 - Listar aeronaves prontas (Todas ou por Local)
void listarAeronavesEstadoAutorizacao(TipoFrota *frota, int *verificarAirCraft);                    // 9 - Listar aeronaves a aguardar autorizacao (Todas ou por Local)
void consultarAeronavePorId(TipoFrota *frota);                              // 10 - Consultar aeronave inserindo o ID disponivel
void gravarListagemAeronaves(TipoFrota *frota);                   //Parte 2 // 11 - Gravar listagem de aeronaves para ficheiro de texto
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void listaAutomaticaAeronaves(TipoFrota *frota, int *aeronave, int opcao, int local, int estado);
void desenharLinhaSeparacao(int y);

int main()                                                                      // Main do projeto
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
//--------------------------------------------
    int opcao = 0;
    char estadosAeronave[3][30] = {"Pronto","A aguardar autorizacao","Fora de servico"};
    char locaisAeronave[3][20] = {"Vila Real","Tires","Portimao"};
    int verificarAirCraft;
    int niu;

    //setlocale(LC_CTYPE, "Portuguese");
    //system("color 0A");
    TipoFrota frota = {};

    aprecentacaoInicial();

    while(1)
    {
        opcao = implementacaoMenu(opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            adicionarAeronaveFrota(&frota, estadosAeronave, locaisAeronave);
            break;
        case 2:
            system("cls");
            eliminarAeronaveFrota(&frota);
            break;
        case 3:
            system("cls");
            editarAeronaveFrota(&frota);
            break;
        case 4:
            system("cls");
            iniciarPedidoVoo(&frota);
            break;
        case 5:
            system("cls");
            autorizarVoo(&frota);
            break;
        case 6:
            system("cls");
            cancelarVoo(&frota);
            break;
        case 7:
            system("cls");
            //listarAeronavesOrdemDescendenteVoos(&frota);
            break;
        case 8:
            system("cls");
            listarAeronavesEstadoPronto(&frota, &verificarAirCraft, &niu, &niu);

            if(verificarAirCraft != 1)
            {
                gotoxy(43,52);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
            }

            break;
        case 9:
            system("cls");
            listarAeronavesEstadoAutorizacao(&frota, &verificarAirCraft);

            if(verificarAirCraft != 1)
            {
                gotoxy(43,52);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
            }

            break;
        case 10:
            system("cls");
            consultarAeronavePorId(&frota);
            break;
        case 11:
            system("cls");
            //gravarListagemAeronaves(&frota);
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
        gotoxy(38,10);
        seta(1,position);
        printf(GRN"1. Adicionar aeronave a frota - 100%%"RESET);
        gotoxy(38,11);
        seta(2,position);
        printf(GRN"2. Eliminar aeronave da frota - 100%%"RESET);
        gotoxy(38,12);
        seta(3,position);
        printf(RED"3. Editar aeronave (Parte 2)"RESET);
        gotoxy(38,13);
        seta(4,position);
        printf(GRN"4. Iniciar pedido de voo - 100%%"RESET);
        gotoxy(38,14);
        seta(5,position);
        printf("5. Autorizar voo");
        gotoxy(38,15);
        seta(6,position);
        printf(GRN"6. Cancelar voo"RESET);
        gotoxy(38,16);
        seta(7,position);
        printf("7. Listar aeronaves e detalhes (Ordem descendente de N%c de voos)"RED " " "(NF)"RESET,167);
        gotoxy(38,17);
        seta(8,position);
        printf(GRN"8. Listar aeronaves no estado pronto e detalhes - 100%%"RESET);
        gotoxy(38,18);
        seta(9,position);
        printf(GRN"9. Listar aeronaves a aguardar autorizacao e detalhes - 100%%"RESET);
        gotoxy(38,19);
        seta(10,position);
        printf(GRN"10. Consultar aeronave especifica mostrando respetivos detalhes"RESET" "RED"Falta historico"RESET);
        gotoxy(38,20);
        seta(11,position);
        printf(RED"11. Gravar listagem de aeronaves para ficheiro de texto (Parte 2)"RESET);

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
void adicionarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20])                               // 1 - Adicionar aeronave a frota
{
    int posicaoAeronave = 0, opcaoLocalizacao = 0;
    int position = 1;
    int keyPressed = 0;

    if(frota->totalAeronaves < 10)
    {
        frota->totalAeronaves += 1;
        frota->idContador += 1;
    }
    else
    {
        desenharBox(80,36);
        gotoxy(63,7);
        printf("Adicionar Aeronave a Frota:");
        gotoxy(55,12);
        printf("Limite maximo das aeronaves foi atingido,");
        gotoxy(45,14);
        printf("Elimine alguma aeronave para poder adicionar outra aeronave.");
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
    for(int i = 0; i < frota->totalAeronaves; i++)
    {
        if(frota->aeronaves[i].id == 0)
        {
            frota->aeronaves[i].id = frota->idContador;
            posicaoAeronave = i;
            break;
        }
    }

    //recolher do valor da capacidade
    do
    {
        desenharBox(80,36);
        gotoxy(63,7);
        printf("Adicionar Aeronave a Frota");
        gotoxy(59,10);
        printf("Introduza os dados da %d aeronave", (posicaoAeronave+1));
        gotoxy(38,12);
        printf("Introduza a capacidade maxima de passageiros (No minimo 2 e no maximo 4):");
        gotoxy(38,13);
        printf("---> ");
        scanf("%d",&frota->aeronaves[posicaoAeronave].capacidade);
        fflush(stdin);

        if ((frota->aeronaves[posicaoAeronave].capacidade < 2) || (frota->aeronaves[posicaoAeronave].capacidade > 4))
        {
            gotoxy(40,18);
            printf(RED"ERRO: Voce introduziu a quantidade incorreta, reintroduza a quantidade."RESET);
            Sleep(2000);
            system("cls");

        }
    }
    while ((frota->aeronaves[posicaoAeronave].capacidade < 2) || (frota->aeronaves[posicaoAeronave].capacidade > 4));

//    gotoxy(62,18);
//    printf(GRN"Capacidade de %d passageiros,",frota->aeronaves[posicaoAeronave].capacidade);
//    gotoxy(52,20);
//    printf("foi atribuido com sucesso a aeronave com ID N%c%d"RESET,167,frota->aeronaves[posicaoAeronave].id);
//    Sleep(500);

    //atribuicao da localizacao atual da aeronave
    while (keyPressed != 13)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(63,7);
        printf("Adicionar Aeronave a Frota");
        gotoxy(59,10);
        printf("Introduza os dados da %d aeronave", posicaoAeronave + 1);
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
        strcpy(frota->aeronaves[posicaoAeronave].localAtual, locaisAeronave[0]);
        break;
    case 2:
        strcpy(frota->aeronaves[posicaoAeronave].localAtual, locaisAeronave[1]);
        break;
    case 3:
        strcpy(frota->aeronaves[posicaoAeronave].localAtual, locaisAeronave[2]);
        break;
    default:
        break;
    }

    //atribuicao estado pronto
    strcpy(frota->aeronaves[posicaoAeronave].estado, estadosAeronave[0]);

    gotoxy(57,20);
    printf("Foi atribuido estado pronto a aeronave");

    gotoxy(43,23);
    printf("Pressione qual quer tecla do teclado para voltar ao menu principal");

    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void listaAutomaticaAeronaves(TipoFrota *frota, int *aeronave, int opcao, int local, int estado)
{
    int j = 12, l = 12;
    char estadosAeronave[3][30] = {"Pronto","A aguardar autorizacao","Fora de servico"};
    char locaisAeronave[3][20] = {"Vila Real","Tires","Portimao"};
    *aeronave = 1;

    if(opcao == 0)
    {
        for(int i = 0; i < 10; i++)
        {
            if((frota->aeronaves[i].id != 0) && (j <= 46) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[estado]) == 0))
            {
                gotoxy(40,j);
                printf("---------Aeronave N%c%d---------",167, *aeronave);
                j++;
                gotoxy(40,j);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                j++;
                gotoxy(40,j);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                j++;
                gotoxy(40,j);
                printf("Numero de voos realizados: %d",frota->aeronaves[i].numVoos);
                j++;
                gotoxy(40,j);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                j++;
                gotoxy(40,j);
                printf("Local atual: %s",frota->aeronaves[i].localAtual);
                j += 2;
                *aeronave += 1;
            }
            else if((frota->aeronaves[i].id != 0) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[estado]) == 0))
            {
                gotoxy(80,l);
                printf("---------Aeronave N%c%d---------",167, *aeronave);
                l++;
                gotoxy(80,l);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                l++;
                gotoxy(80,l);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                l++;
                gotoxy(80,l);
                printf("Numero de voos realizados: %d",frota->aeronaves[i].numVoos);
                l++;
                gotoxy(80,l);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                l++;
                gotoxy(80,l);
                printf("Local atual: %s",frota->aeronaves[i].localAtual);
                l += 2;
                *aeronave += 1;
            }
        }
    }
    else if(opcao == 1)
    {
        for(int i = 0; i < 10; i++)
        {
            if((frota->aeronaves[i].id != 0) && (j <= 46) && (strcmp(frota->aeronaves[i].localAtual,locaisAeronave[local]) == 0) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[estado]) == 0))
            {
                gotoxy(40,j);
                printf("---------Aeronave N%c%d---------",167, *aeronave);
                j++;
                gotoxy(40,j);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                j++;
                gotoxy(40,j);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                j++;
                gotoxy(40,j);
                printf("Numero de voos realizados: %d",frota->aeronaves[i].numVoos);
                j++;
                gotoxy(40,j);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                j++;
                gotoxy(40,j);
                printf("Local atual: %s",frota->aeronaves[i].localAtual);
                j += 2;
                *aeronave += 1;
            }
            else if((frota->aeronaves[i].id != 0) && (strcmp(frota->aeronaves[i].localAtual,locaisAeronave[local]) == 0) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[estado]) == 0))
            {
                gotoxy(80,l);
                printf("---------Aeronave N%c%d---------",167, *aeronave);
                l++;
                gotoxy(80,l);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                l++;
                gotoxy(80,l);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                l++;
                gotoxy(80,l);
                printf("Numero de voos realizados: %d",frota->aeronaves[i].numVoos);
                l++;
                gotoxy(80,l);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                l++;
                gotoxy(80,l);
                printf("Local atual: %s",frota->aeronaves[i].localAtual);
                l += 2;
                *aeronave += 1;
            }
        }
    }
    desenharLinhaSeparacao(47);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void eliminarAeronaveFrota(TipoFrota *frota)                                // 2 - Eliminar aeronave da frota // falta fazer
{
    int aeronaveEscolhida = 0, aeronaveEncontrada = 0, posicaoAeronave = 0, numeroAeronave;
    int position = 1;
    int keyPressed = 0;
    int opcao;
    char estadosAeronave[2][30] = {"Pronto","Fora de servico"};

    while (keyPressed != 13)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(64,7);
        printf("Eliminar aeronave da frota");
        gotoxy(40,10);
        printf("Escolhe a opcao pretendida:");
        gotoxy(40,12);
        seta(1,position);
        printf("Listar todas as aeronaves em estado \"Pronto\"");
        gotoxy(40,13);
        seta(2,position);
        printf("Listar todas as aeronaves em estado \"Fora de servico\"");

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
        do
        {
            listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 0);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(64,7);
                printf("Eliminar aeronave da frota");
                gotoxy(50,14);
                printf("De momento nao ha aeronaves \"Prontas\" para eliminar,");
                gotoxy(45,16);
                printf("pode adicionar aeronave atravez da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(64,7);
            printf("Eliminar aeronave da frota");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado \"Pronto\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 0);

            gotoxy(40,49);
            printf("Introduza o ID da aeronave que pretende eliminar");
            gotoxy(40,50);
            printf("(Se nao tiver aeronaves disponiveis, introduza 0 para voltar ao menu)");
            gotoxy(40,51);
            printf("---> ");
            scanf("%d",&aeronaveEscolhida);

            for(int i = 0; i < 10; i++)
            {
                if(aeronaveEscolhida == 0)
                {
                    return;
                }
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[0]) == 0))
                {
                    posicaoAeronave = i;
                    aeronaveEncontrada = TRUE;
                }
            }
            if(aeronaveEncontrada == FALSE)
            {
                gotoxy(57,54);
                printf(RED"ERRO: Voce introduziu o ID invalido,");
                gotoxy(54,55);
                printf("reintroduza o valor dentro dos apresentados."RESET);
                Sleep(2000);
                system("cls");
            }
        }
        while (aeronaveEncontrada == FALSE);

        gotoxy(58,54);
        printf(GRN"Foi escolhida a aeronave N%c%d com ID: %d"RESET,167, posicaoAeronave+1,frota->aeronaves[posicaoAeronave].id);
        Sleep(2000);
        break;

    case 2:
        do
        {
            listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 2);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(64,7);
                printf("Eliminar aeronave da frota");
                gotoxy(46,14);
                printf("De momento nao ha aeronaves \"Fora de servico\" para eliminar,");
                gotoxy(45,16);
                printf("pode adicionar aeronave atravez da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(64,7);
            printf("Eliminar aeronave da frota");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado \"Fora de servico\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 2);

            gotoxy(40,49);
            printf("Introduza o ID da aeronave que pretende eliminar");
            gotoxy(40,50);
            printf("(Se nao tiver aeronaves disponiveis, introduza 0 para voltar ao menu)");
            gotoxy(40,51);
            printf("---> ");
            scanf("%d",&aeronaveEscolhida);

            for(int i = 0; i < 10; i++)
            {
                if(aeronaveEscolhida == 0)
                {
                    return;
                }
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[1]) == 0))
                {
                    posicaoAeronave = i;
                    aeronaveEncontrada = TRUE;
                }
            }
            if(aeronaveEncontrada == FALSE)
            {
                gotoxy(57,54);
                printf(RED"ERRO: Voce introduziu o ID invalido,");
                gotoxy(54,55);
                printf("reintroduza o valor dentro dos apresentados."RESET);
                Sleep(2000);
                system("cls");
            }
        }
        while (aeronaveEncontrada == FALSE);

        gotoxy(58,54);
        printf(GRN"Foi escolhida a aeronave N%c%d com ID: %d"RESET,167, posicaoAeronave+1,frota->aeronaves[posicaoAeronave].id);
        Sleep(2000);
        break;

    default:
        break;
    }

    frota->totalAeronaves -= 1;

    frota->aeronaves[posicaoAeronave].id = 0;
    frota->aeronaves[posicaoAeronave].capacidade = 0;
    frota->aeronaves[posicaoAeronave].numVoos = 0;
    strcpy(frota->aeronaves[posicaoAeronave].estado,"");
    strcpy(frota->aeronaves[posicaoAeronave].localAtual,"");
    strcpy(frota->aeronaves[posicaoAeronave].destino,"");

    for(int i = 0; i < 3; i++)
    {
        strcpy(frota->aeronaves[posicaoAeronave].historico[i],"");
    }

    for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
    {
        frota->aeronaves[posicaoAeronave].manifesto[i].nif = 0;
        strcpy(frota->aeronaves[posicaoAeronave].manifesto[i].nome,"");
    }

    system("cls");
    desenharBox(80,36);
    gotoxy(64,7);
    printf("Eliminar aeronave da frota");
    gotoxy(54,14);
    printf("A aeronave escolhida foi eliminada com sucesso");
    gotoxy(43,21);
    printf("Pressione qual quer tecla do teclado para voltar ao menu principal");

    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void editarAeronaveFrota(TipoFrota *frota)                        //Parte2  // 3 - Editar aeronave
{
    char estadosAeronave[3][30] = {"Pronto","A aguardar autorizacao","Fora de servico"};

    strcpy(frota->aeronaves[2].estado,estadosAeronave[1]);
    strcpy(frota->aeronaves[3].estado,estadosAeronave[1]);
    strcpy(frota->aeronaves[4].estado,estadosAeronave[1]);
    strcpy(frota->aeronaves[5].estado,estadosAeronave[1]);
    strcpy(frota->aeronaves[6].estado,estadosAeronave[1]);

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void iniciarPedidoVoo(TipoFrota *frota)                                     // 4 - Iniciar pedido de voo
{
    int position = 1;
    int keyPressed = 0;
    int posicaoAeronave, aeronaveEncontrada;
    int opcaoDestino, y1, y2, aeronaveEscolhida;
    char strOrdenarNomes[50];
    long int ordenarNifs;
    char estadosAeronave[2][30] = {"Pronto","A aguardar autorizacao"};
    char localizacaoTemp[3][20] = {"Vila Real","Tires","Portimao"};
    int existenciaAeronaves = 0;
    int opcaoAirCraft, localAirCraft;

    do
    {
        listarAeronavesEstadoPronto(frota, &existenciaAeronaves, &opcaoAirCraft, &localAirCraft);

        if(existenciaAeronaves == 1)
        {
            return;
        }

        gotoxy(40,49);
        printf("Introduza o ID da aeronave para iniciar o pedido de voo");
        gotoxy(40,50);
        printf("(Se nao tiver aeronaves disponiveis, introduza 0 para voltar ao menu)");
        gotoxy(40,51);
        printf("---> ");
        scanf("%d",&aeronaveEscolhida);

        if(opcaoAirCraft == 0)
        {
            for(int i = 0; i < 10; i++)
            {
                if(aeronaveEscolhida == 0)
                {
                    return;
                }
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[0]) == 0))
                {
                    posicaoAeronave = i;
                    aeronaveEncontrada = TRUE;
                }
            }
            if(aeronaveEncontrada == FALSE)
            {
                gotoxy(57,54);
                printf(RED"ERRO: Voce introduziu o ID invalido,");
                gotoxy(54,55);
                printf("reintroduza o valor dentro dos apresentados."RESET);
                Sleep(2000);
                system("cls");
            }
        }
        else if(opcaoAirCraft == 1)
        {
            for(int i = 0; i < 10; i++)
            {
                if(aeronaveEscolhida == 0)
                {
                    return;
                }
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[0]) == 0) && (strcmp(frota->aeronaves[i].localAtual,localizacaoTemp[localAirCraft]) == 0))
                {
                    posicaoAeronave = i;
                    aeronaveEncontrada = TRUE;
                }
            }
            if(aeronaveEncontrada == FALSE)
            {
                gotoxy(57,54);
                printf(RED"ERRO: Voce introduziu o ID invalido,");
                gotoxy(54,55);
                printf("reintroduza o valor dentro dos apresentados."RESET);
                Sleep(2000);
                system("cls");
            }
        }
    }
    while (aeronaveEncontrada == FALSE);


    gotoxy(58,54);
    printf(GRN"Foi escolhida a aeronave N%c%d com ID: %d"RESET,167, posicaoAeronave+1,frota->aeronaves[posicaoAeronave].id);
    Sleep(2000);

    //recolher dados dos passageiros
    system("cls");
    desenharBox(80,36);
    gotoxy(67,7);
    printf("Iniciar pedido de voo");
    gotoxy(59,10);
    printf("Introduza os dados dos passageiros:");
    y1 = 12;
    y2 = 12;
    for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
    {
        if(i < 2)
        {
            gotoxy(40,y1);
            printf("Introduza o NIF do %d passageiro:", i+1);
            y1++;
            gotoxy(40,y1);
            printf("---> ");
            scanf("%ld",&frota->aeronaves[posicaoAeronave].manifesto[i].nif);
            fflush(stdin);
            y1 += 2;
            gotoxy(40,y1);
            printf("Introduza o nome do %d passageiro:", i+1);
            y1++;
            gotoxy(40,y1);
            printf("---> ");
            gets(frota->aeronaves[posicaoAeronave].manifesto[i].nome);
            fflush(stdin);
            y1 += 2;
        }

        else
        {
            gotoxy(80,y2);
            printf("Introduza o NIF do %d passageiro:", i+1);
            y2++;
            gotoxy(80,y2);
            printf("---> ");
            scanf("%ld",&frota->aeronaves[posicaoAeronave].manifesto[i].nif);
            fflush(stdin);
            y2 += 2;
            gotoxy(80,y2);
            printf("Introduza o nome do %d passageiro:", i+1);
            y2++;
            gotoxy(80,y2);
            printf("---> ");
            gets(frota->aeronaves[posicaoAeronave].manifesto[i].nome);
            fflush(stdin);
            y2 += 2;
        }
    }

    //ordenar nomes por ordem alfabetica
    for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
    {
        for(int j = i+1; j < frota->aeronaves[posicaoAeronave].capacidade; j++)
        {
            if(strcmp(frota->aeronaves[posicaoAeronave].manifesto[i].nome,frota->aeronaves[posicaoAeronave].manifesto[j].nome)>0)
            {
                strcpy(strOrdenarNomes,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                strcpy(frota->aeronaves[posicaoAeronave].manifesto[i].nome,frota->aeronaves[posicaoAeronave].manifesto[j].nome);
                strcpy(frota->aeronaves[posicaoAeronave].manifesto[j].nome,strOrdenarNomes);

                ordenarNifs = frota->aeronaves[posicaoAeronave].manifesto[i].nif;
                frota->aeronaves[posicaoAeronave].manifesto[i].nif = frota->aeronaves[posicaoAeronave].manifesto[j].nif;
                frota->aeronaves[posicaoAeronave].manifesto[j].nif = ordenarNifs;

            }
        }
    }

    //atribuicao do destino da aeronave
    if(strcmp(frota->aeronaves[posicaoAeronave].localAtual, localizacaoTemp[0]) == 0)
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
            strcpy(frota->aeronaves[posicaoAeronave].destino, localizacaoTemp[1]);
            break;
        case 2:
            strcpy(frota->aeronaves[posicaoAeronave].destino, localizacaoTemp[2]);
            break;
        default:
            break;
        }
    }

    else if(strcmp(frota->aeronaves[posicaoAeronave].localAtual, localizacaoTemp[1]) == 0)
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
            strcpy(frota->aeronaves[posicaoAeronave].destino, localizacaoTemp[0]);
            break;
        case 2:
            strcpy(frota->aeronaves[posicaoAeronave].destino, localizacaoTemp[2]);
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
            printf("Selecione o destino da aeronave:");
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
            strcpy(frota->aeronaves[posicaoAeronave].destino, localizacaoTemp[0]);
            break;
        case 2:
            strcpy(frota->aeronaves[posicaoAeronave].destino, localizacaoTemp[1]);
            break;
        default:
            break;
        }
    }

    strcpy(frota->aeronaves[posicaoAeronave].estado, estadosAeronave[1]);

    gotoxy(60,19);
    printf("Aeronave a aguardar autorizacao");
    gotoxy(43,24);
    printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void autorizarVoo(TipoFrota *frota)                                         // 5 - Autorizar voo // falta fazer
{

    int y1, existenciaAeronaves = 0, aeronaveEscolhida = 0, posicaoAeronave = 0, aeronaveEncontrada = 0;
    int opcao, position = 1, keyPressed;
    char estadosAeronave[3][30] = {"Pronto","A aguardar autorizacao","Fora de servico"};

    do
    {
        do
        {
            listarAeronavesEstadoAutorizacao(frota, &existenciaAeronaves);

            if(existenciaAeronaves == 1)
            {
                return;
            }

            gotoxy(40,49);
            printf("Introduza o ID da aeronave para a autorizacao");
            gotoxy(40,50);
            printf("(Se nao tiver aeronaves disponiveis, introduza 0 para voltar ao menu)");
            gotoxy(40,51);
            printf("---> ");
            scanf("%d",&aeronaveEscolhida);

            for(int i = 0; i < 10; i++)
            {
                if(aeronaveEscolhida == 0)
                {
                    return;
                }
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[1]) == 0))
                {
                    posicaoAeronave = i;
                    aeronaveEncontrada = TRUE;
                }
            }
            if(aeronaveEncontrada == FALSE)
            {
                gotoxy(57,54);
                printf(RED"ERRO: Voce introduziu o ID invalido,");
                gotoxy(54,55);
                printf("reintroduza o valor dentro dos apresentados."RESET);
                Sleep(2000);
                system("cls");
            }
        }
        while (aeronaveEncontrada == FALSE);


        gotoxy(58,54);
        printf(GRN"Foi escolhida a aeronave N%c%d com ID: %d"RESET,167, posicaoAeronave+1,frota->aeronaves[posicaoAeronave].id);
        Sleep(2000);

        while (keyPressed != 13)
        {
            system("cls");
            desenharBox(80,50);
            gotoxy(71,7);
            printf("Autorizar voo");
            gotoxy(40,9);
            printf("A listar detalhes da aeronave com ID N%c%d:",167,posicaoAeronave+1);
            y1 = 12;
            gotoxy(40,y1);
            printf("---------Aeronave N%c%d---------",167,posicaoAeronave+1);
            y1 += 2;
            gotoxy(40,y1);
            printf("ID da aeronave: %d",frota->aeronaves[posicaoAeronave].id);
            y1 += 2;
            gotoxy(40,y1);
            printf("Capacidade da aeronave: %d",frota->aeronaves[posicaoAeronave].capacidade);
            y1 += 2;
            gotoxy(40,y1);
            printf("Numero de voos realizados: %d",frota->aeronaves[posicaoAeronave].numVoos);
            y1 += 2;
            gotoxy(40,y1);
            printf("Estado atual: %s",frota->aeronaves[posicaoAeronave].estado);
            y1 += 2;
            gotoxy(40,y1);
            printf("Local atual: %s",frota->aeronaves[posicaoAeronave].localAtual);
            y1 += 2;
            gotoxy(40,y1);
            printf("Local do destino: %s",frota->aeronaves[posicaoAeronave].destino);
            y1 += 2;

            for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
            {
                gotoxy(40, y1);
                printf("Nome completo do N%c%d passageiro: %s",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                y1 += 2;
                gotoxy(40, y1);
                printf("NIF do N%c%d passageiro: %ld",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                y1 += 2;
            }

            desenharLinhaSeparacao(42);

            gotoxy(40,44);
            printf("Pretende autorizar o voo(Escolha a opcao pretendida):");
            gotoxy(40,46);
            seta(1,position);
            printf("Sim");
            gotoxy(40,47);
            seta(2,position);
            printf("Nao");
            gotoxy(40,48);
            seta(3,position);
            printf("Nao - Voltar para menu principal");

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

        opcao = position;

        position = 1;
        keyPressed = 0;

        switch(opcao)
        {
        case 1:

            system("cls");
            desenharBox(80,36);
            gotoxy(71,7);
            printf("Autorizar voo");



            if(frota->aeronaves[posicaoAeronave].numVoos < 99)
            {
                frota->aeronaves[posicaoAeronave].numVoos += 1;
                strcpy(frota->aeronaves[posicaoAeronave].estado, estadosAeronave[0]);
            }
            else
            {
                frota->aeronaves[posicaoAeronave].numVoos += 1;
                strcpy(frota->aeronaves[posicaoAeronave].estado, estadosAeronave[2]);
            }

            strcpy(frota->aeronaves[posicaoAeronave].localAtual, frota->aeronaves[posicaoAeronave].destino);


            strcpy(frota->aeronaves[posicaoAeronave].destino, "");



            for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
            {
                frota->aeronaves[posicaoAeronave].manifesto[i].nif = 0;
                strcpy(frota->aeronaves[posicaoAeronave].manifesto[i].nome,"");
            }

            //memoria dos ultimos tres voos

            char seta[] = "--->";
            for(int i = 2; i >= 0; i--)
            {
                if(frota->aeronaves[posicaoAeronave].historico[i][0] == '\0')
                {
                    strcpy(frota->aeronaves[posicaoAeronave].historico[i], frota->aeronaves[posicaoAeronave].localAtual);
                    strcat(frota->aeronaves[posicaoAeronave].historico[i], seta);
                    strcat(frota->aeronaves[posicaoAeronave].historico[i], frota->aeronaves[posicaoAeronave].destino);


                    strcpy(frota->aeronaves[posicaoAeronave].historico[i], frota->aeronaves[posicaoAeronave].localAtual, traco[0],frota->aeronaves[posicaoAeronave].destino);
                    break;
                }
            }








            gotoxy(55,15);
            printf("O voo foi autorizado com sucesso");

            gotoxy(43,20);
            printf("Pressione qual quer tecla do teclado para voltar ao menu principal");

            getch();
            break;
        case 2:

            break;
        case 3:
            return;
            break;
        default:
            break;
        }
    }
    while(1);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void cancelarVoo(TipoFrota *frota)                                // 6 - Cancelar voo // falta fazer
{
    int y1, existenciaAeronaves = 0, aeronaveEscolhida = 0, posicaoAeronave = 0, aeronaveEncontrada = 0;
    int opcao, position = 1, keyPressed;
    char estadosAeronave[2][30] = {"Pronto","A aguardar autorizacao"};
    do
    {
        do
        {
            listarAeronavesEstadoAutorizacao(frota, &existenciaAeronaves);

            if(existenciaAeronaves == 1)
            {
                return;
            }

            gotoxy(40,49);
            printf("Introduza o ID da aeronave que pretende eliminar");
            gotoxy(40,50);
            printf("(Se nao tiver aeronaves disponiveis, introduza 0 para voltar ao menu)");
            gotoxy(40,51);
            printf("---> ");
            scanf("%d",&aeronaveEscolhida);

            for(int i = 0; i < 10; i++)
            {
                if(aeronaveEscolhida == 0)
                {
                    return;
                }
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[1]) == 0))
                {
                    posicaoAeronave = i;
                    aeronaveEncontrada = TRUE;
                }
            }
            if(aeronaveEncontrada == FALSE)
            {
                gotoxy(57,54);
                printf(RED"ERRO: Voce introduziu o ID invalido,");
                gotoxy(54,55);
                printf("reintroduza o valor dentro dos apresentados."RESET);
                Sleep(2000);
                system("cls");
            }
        }
        while (aeronaveEncontrada == FALSE);


        gotoxy(58,54);
        printf(GRN"Foi escolhida a aeronave N%c%d com ID: %d"RESET,167, posicaoAeronave+1,frota->aeronaves[posicaoAeronave].id);
        Sleep(2000);

        while (keyPressed != 13)
        {
            system("cls");
            desenharBox(80,50);
            gotoxy(71,7);
            printf("Cancelar voo");
            gotoxy(40,9);
            printf("A listar detalhes da aeronave com ID N%c%d:",167,posicaoAeronave+1);
            y1 = 12;
            gotoxy(40,y1);
            printf("---------Aeronave N%c%d---------",167,posicaoAeronave+1);
            y1 += 2;
            gotoxy(40,y1);
            printf("ID da aeronave: %d",frota->aeronaves[posicaoAeronave].id);
            y1 += 2;
            gotoxy(40,y1);
            printf("Capacidade da aeronave: %d",frota->aeronaves[posicaoAeronave].capacidade);
            y1 += 2;
            gotoxy(40,y1);
            printf("Numero de voos realizados: %d",frota->aeronaves[posicaoAeronave].numVoos);
            y1 += 2;
            gotoxy(40,y1);
            printf("Estado atual: %s",frota->aeronaves[posicaoAeronave].estado);
            y1 += 2;
            gotoxy(40,y1);
            printf("Local atual: %s",frota->aeronaves[posicaoAeronave].localAtual);
            y1 += 2;
            gotoxy(40,y1);
            printf("Local do destino: %s",frota->aeronaves[posicaoAeronave].destino);
            y1 += 2;

            for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
            {
                gotoxy(40, y1);
                printf("Nome completo do N%c%d passageiro: %s",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                y1 += 2;
                gotoxy(40, y1);
                printf("NIF do N%c%d passageiro: %ld",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                y1 += 2;
            }

            desenharLinhaSeparacao(42);

            gotoxy(40,44);
            printf("Pretende mesmo cancelar o voo(Escolha a opcao pretendida):");
            gotoxy(40,46);
            seta(1,position);
            printf("Sim");
            gotoxy(40,47);
            seta(2,position);
            printf("Nao");
            gotoxy(40,48);
            seta(3,position);
            printf("Nao - Voltar para menu principal");

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

        opcao = position;

        position = 1;
        keyPressed = 0;

        switch(opcao)
        {
        case 1:

            system("cls");
            desenharBox(80,36);
            gotoxy(71,7);
            printf("Cancelar voo");

            strcpy(frota->aeronaves[posicaoAeronave].estado, estadosAeronave[0]);
            strcpy(frota->aeronaves[posicaoAeronave].destino, "");

            for(int i = 0; i < 3; i++)
            {
                strcpy(frota->aeronaves[posicaoAeronave].historico[i],"");
            }

            for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
            {
                frota->aeronaves[posicaoAeronave].manifesto[i].nif = 0;
                strcpy(frota->aeronaves[posicaoAeronave].manifesto[i].nome,"");
                strcpy(frota->aeronaves[posicaoAeronave].destino,"");
            }

            gotoxy(55,15);
            printf("O voo foi cancelado com sucesso");

            gotoxy(43,20);
            printf("Pressione qual quer tecla do teclado para voltar ao menu principal");

            getch();
            break;
        case 2:

            break;
        case 3:
            return;
            break;
        default:
            break;
        }
    }
    while(1);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
/*
void listarAeronavesOrdemDescendenteVoos(TipoFrota *f)                  // 7 - Listar todas as aeronaves por ordem descendente de numero de voos // falta fazer
{
    desenharBox(80,36);
    gotoxy(47,7);
    printf("Listar aeronaves e detalhes (Ordem descendente de N%c de voos)",167);
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel"RESET);
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal");
    getch();
}
*/
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void listarAeronavesEstadoPronto(TipoFrota *frota, int *verificarAirCraft, int *opcaoAirCraft, int *localAirCraft)                          // 8 - Listar aeronaves prontas (Todas ou por Local)
{
    int position = 1;
    int keyPressed = 0;
    int opcao, numeroAeronave;

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

        listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 0);

        if(numeroAeronave == 1)
        {
            system("cls");
            desenharBox(80,36);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(50,14);
            printf("De momento nao ha aeronaves \"Prontas\" para listar,");
            gotoxy(45,16);
            printf("pode adicionar aeronave atravez da opcao \"1\" no menu principal");
            gotoxy(43,25);
            printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
            getch();
            *verificarAirCraft = numeroAeronave;
            return;
        }

        system("cls");
        desenharBox(80,58);
        gotoxy(56,7);
        printf("Listar aeronaves no estado pronto e detalhes");
        gotoxy(40,10);
        printf("A listar todas as aeronaves em estado \"Pronto\":");

        listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 0);
        *verificarAirCraft = numeroAeronave;
        *opcaoAirCraft = 0;
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

        opcao = position;

        position = 1;
        keyPressed = 0;

        switch(opcao)
        {
        case 1:
            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 0, 0);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(56,7);
                printf("Listar aeronaves no estado pronto e detalhes");
                gotoxy(44,14);
                printf("De momento nao ha aeronaves \"Prontas\" em \"Vila Real\" para listar,");
                gotoxy(45,16);
                printf("pode adicionar aeronave atravez da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                *verificarAirCraft = numeroAeronave;
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado \"Pronto\" em \"Vila Real\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 0, 0);
            *verificarAirCraft = numeroAeronave;
            *opcaoAirCraft = 1;
            *localAirCraft = 0;
            break;

        case 2:
            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 1, 0);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(56,7);
                printf("Listar aeronaves no estado pronto e detalhes");
                gotoxy(46,14);
                printf("De momento nao ha aeronaves \"Prontas\" em \"Tires\" para listar,");
                gotoxy(45,16);
                printf("pode adicionar aeronave atravez da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                *verificarAirCraft = numeroAeronave;
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado \"Pronto\" em \"Tires\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 1, 0);
            *verificarAirCraft = numeroAeronave;
            *opcaoAirCraft = 1;
            *localAirCraft = 1;
            break;

        case 3:
            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 2, 0);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(56,7);
                printf("Listar aeronaves no estado pronto e detalhes");
                gotoxy(44,14);
                printf("De momento nao ha aeronaves \"Prontas\" em \"Portimao\" para listar,");
                gotoxy(45,16);
                printf("pode adicionar aeronave atravez da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                *verificarAirCraft = numeroAeronave;
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(56,7);
            printf("Listar aeronaves no estado pronto e detalhes");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado \"Pronto\" em \"Portimao\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 2, 0);
            *verificarAirCraft = numeroAeronave;
            *opcaoAirCraft = 1;
            *localAirCraft = 2;
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
void listarAeronavesEstadoAutorizacao(TipoFrota *frota, int *verificarAirCraft)                     // 9 - Listar aeronaves a aguardar autorizacao (Todas ou por Local)
{
    int position = 1;
    int keyPressed = 0;
    int opcao, numeroAeronave;

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

        listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 1);

        if(numeroAeronave == 1)
        {
            system("cls");
            desenharBox(80,36);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(44,14);
            printf("De momento nao ha aeronaves \"A Aguardar Autorizacao\" para listar,");
            gotoxy(49,16);
            printf("pode iniciar voo atravez da opcao \"4\" no menu principal");
            gotoxy(43,25);
            printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
            getch();
            *verificarAirCraft = numeroAeronave;
            return;
        }

        system("cls");
        desenharBox(80,58);
        gotoxy(52,7);
        printf("Listar aeronaves a aguardar autorizacao e detalhes");
        gotoxy(40,10);
        printf("A listar todas as aeronaves em estado \"A Aguardar Autorizacao\":");

        listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 1);

        *verificarAirCraft = numeroAeronave;
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

        opcao = position;

        position = 1;
        keyPressed = 0;

        switch(opcao)
        {
        case 1:
            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 0, 1);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(52,7);
                printf("Listar aeronaves a aguardar autorizacao e detalhes");
                gotoxy(42,14);
                printf("De momento nao ha aeronaves \"A Aguardar Autorizacao\" em \"Vila Real\"");
                gotoxy(47,16);
                printf("pode iniciar voo atravez da opcao \"4\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                *verificarAirCraft = numeroAeronave;
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(40,9);
            printf("A listar todas as aeronaves em estado \"A Aguardar Autorizacao\"");
            gotoxy(40,10);
            printf("em \"Vila Real\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 0, 1);

            *verificarAirCraft = numeroAeronave;
            break;

        case 2:
            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 1, 1);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(52,7);
                printf("Listar aeronaves a aguardar autorizacao e detalhes");
                gotoxy(44,14);
                printf("De momento nao ha aeronaves \"A Aguardar Autorizacao\" em \"Tires\"");
                gotoxy(48,16);
                printf("pode iniciar voo atravez da opcao \"4\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                *verificarAirCraft = numeroAeronave;
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(40,9);
            printf("A listar todas as aeronaves em estado \"A Aguardar Autorizacao\"");
            gotoxy(40,10);
            printf("em \"Tires\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 1, 1);

            *verificarAirCraft = numeroAeronave;
            break;
        case 3:
            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 2, 1);

            if(numeroAeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(52,7);
                printf("Listar aeronaves a aguardar autorizacao e detalhes");
                gotoxy(43,14);
                printf("De momento nao ha aeronaves \"A Aguardar Autorizacao\" em \"Portimao\"");
                gotoxy(48,16);
                printf("pode iniciar voo atravez da opcao \"4\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qual quer tecla do teclado para voltar ao menu principal");
                getch();
                *verificarAirCraft = numeroAeronave;
                return;
            }

            system("cls");
            desenharBox(80,58);
            gotoxy(52,7);
            printf("Listar aeronaves a aguardar autorizacao e detalhes");
            gotoxy(40,9);
            printf("A listar todas as aeronaves em estado \"A Aguardar Autorizacao\"");
            gotoxy(40,10);
            printf("em \"Portimao\":");

            listaAutomaticaAeronaves(frota, &numeroAeronave, 1, 2, 1);

            *verificarAirCraft = numeroAeronave;
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
void consultarAeronavePorId(TipoFrota *frota)                               // 10 - Consultar aeronave inserindo o ID disponivel
{
    int y1, y2, aeronaveEscolhida, posicaoAeronave, aeronaveEncontrada;
    char estadoAutorizacao[30] = {"A aguardar autorizacao"};

    //listaAutomaticaAeronaves(frota, &numeroAeronave, 0, 0, 2);


    do
    {
        y1 = 11;
        y2 = 11;

        system("cls");
        desenharBox(80,47);
        gotoxy(43,7);
        printf("Consultar aeronave especifica mostrando respetivos detalhes por ID");
        gotoxy(40,9);
        printf("A listar todas as aeronaves disponiveis:");

        for(int i = 0; i < frota->totalAeronaves; i++)
        {
            if(i <= 4)
            {
                gotoxy(40,y1);
                printf("---------Aeronave N%c%d---------",167,i+1);
                y1++;
                gotoxy(40,y1);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                y1++;
                gotoxy(40,y1);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                y1++;
                gotoxy(40,y1);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                y1 += 2;
            }
            else
            {
                gotoxy(80,y2);
                printf("---------Aeronave N%c%d---------",167,i+1);
                y2++;
                gotoxy(80,y2);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                y2++;
                gotoxy(40,y2);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                y2++;
                gotoxy(80,y2);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                y2 += 2;
            }
        }

        desenharLinhaSeparacao(36);

        gotoxy(40,38);
        printf("Introduza o numero da aeronave disponivel");
        gotoxy(40,39);
        printf("(Se nao tiver aeronaves disponiveis, introduza 0 para voltar ao menu)");
        gotoxy(40,40);
        printf("---> ");
        scanf("%d",&aeronaveEscolhida);

        for(int i = 0; i < 10; i++)
        {
            if(aeronaveEscolhida == 0)
            {
                return;
            }
            else if((aeronaveEscolhida == frota->aeronaves[i].id))
            {
                posicaoAeronave = i;
                aeronaveEncontrada = TRUE;
            }
        }
        if(aeronaveEncontrada == FALSE)
        {
            gotoxy(57,43);
            printf(RED"ERRO: Voce introduziu o ID invalido,");
            gotoxy(54,44);
            printf("reintroduza o valor dentro dos apresentados."RESET);
            Sleep(2000);
            system("cls");
        }
    }
    while (aeronaveEncontrada == FALSE);

    system("cls");
    desenharBox(80,50);
    gotoxy(43,7);
    printf("Consultar aeronave especifica mostrando respetivos detalhes por ID");
    gotoxy(40,9);
    printf("A listar detalhes da aeronave N%c%d:",167,posicaoAeronave+1);
    y1 = 12;
    for(int i = 0; i < 1; i++)
    {
        gotoxy(40,y1);
        printf("---------Aeronave N%c%d---------",167,posicaoAeronave+1);
        y1 += 2;
        gotoxy(40,y1);
        printf("ID da aeronave: %d",frota->aeronaves[posicaoAeronave].id);
        y1 += 2;
        gotoxy(40,y1);
        printf("Capacidade da aeronave: %d",frota->aeronaves[posicaoAeronave].capacidade);
        y1 += 2;
        gotoxy(40,y1);
        printf("Numero de voos realizados: %d",frota->aeronaves[posicaoAeronave].numVoos);
        y1 += 2;
        gotoxy(40,y1);
        printf("Estado atual: %s",frota->aeronaves[posicaoAeronave].estado);
        y1 += 2;
        gotoxy(40,y1);
        printf("Local atual: %s",frota->aeronaves[posicaoAeronave].localAtual);
        y1 += 2;

        if(strcmp(frota->aeronaves[posicaoAeronave].estado, estadoAutorizacao) == 0)
        {
            gotoxy(40,y1);
            printf("Local do destino: %s",frota->aeronaves[posicaoAeronave].destino);
            y1 += 2;

            for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
            {
                gotoxy(40, y1);
                printf("Nome completo do N%c%d passageiro: %s",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                y1 += 2;
                gotoxy(40, y1);
                printf("NIF do N%c%d passageiro: %ld",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                y1 += 2;
            }
        }
    }

    desenharLinhaSeparacao(42);

    gotoxy(43,46);
    printf("Pressione qual quer tecla do teclado para voltar ao menu principal");

    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
/*
void gravarListagemAeronaves(TipoFrota *f)                    //Parte 2 // 11 - Gravar listagem de aeronaves para ficheiro de texto
{
    desenharBox(80,36);
    gotoxy(52,7);
    printf("Gravar listagem de aeronaves para ficheiro de texto");
    gotoxy(45,13);
    printf(RED"De momento esta funcionalidade encontrasse em desenvolvimento,");
    gotoxy(67,15);
    printf("nao esta disponivel"RESET);
    gotoxy(43,20);
    printf("Precione qual quer tecla do teclado para voltar ao menu principal");
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------
*/

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
void desenharLinhaSeparacao(int y)
{
    gotoxy(35,y);
    for(int i = 0; i <= 80; i++)
    {
        if(i == 0)
        {
            printf("%c", 204);
        }
        else if(i == 80)
        {
            printf("%c", 185);
        }
        else
        {
            printf("%c", 205);
        }
    }
}
