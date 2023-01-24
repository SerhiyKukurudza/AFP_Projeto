#include <stdio.h>                                                                                                      // Bibliotecas usadas no projeto
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define TRUE 1                                                                                                          // Definicao das condicoes
#define FALSE 0
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define RED   "\x1B[31m"                                                                                                // Definicao das cores para mudar a cor das letras
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct                                                                                                          // Definicao da estrutura do projeto
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
    TipoAeronave aeronaves[10];
} TipoFrota;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y);                                                                                              // Subprograma para movimentar o cursos
int desenharBox(int x, int y);                                                                                          // Subprograma para desenhar box
void aprecentacaoInicial();                                                                                             // Subprograma que apresenta capa do projeto
void seta(int realPosition, int arrowPosition);                                                                         // Subprograma que implementa a seta da escolha
void listaAutomaticaAeronaves(TipoFrota *frota, int *aeronave, int opcao, int local, int estado);                       // Subprograma que implementa a lista das aeronaves consuante dados recebidos
void desenharLinhaSeparacao(int y);                                                                                     // Subprograma que implementa uma linha para separar dados
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int implementacaoMenu(int opcao);                                                                                       // Menu principal
void adicionarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20]);                   // 1 - Adicionar aeronave a frota
void eliminarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30]);                                               // 2 - Eliminar aeronave da frota
void editarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20]);                      // 3 - Editar aeronave
void iniciarPedidoVoo(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20]);                         // 4 - Iniciar pedido de voo
void autorizarVoo(TipoFrota *frota, char estadosAeronave[][30]);                                                        // 5 - Autorizar voo
void cancelarVoo(TipoFrota *frota, char estadosAeronave[][30]);                                                         // 6 - Cancelar voo
void listarAeronavesOrdemDescendenteVoos(TipoFrota *frota);                                                             // 7 - Listar todas as aeronaves por ordem descendente de numero de voos
void listarAeronavesEstadoPronto(TipoFrota *frota,int *verificarAirCraft, int *opcaoAirCraft, int *localAirCraft);      // 8 - Listar aeronaves prontas (Todas ou por Local)
void listarAeronavesEstadoAutorizacao(TipoFrota *frota, int *verificarAirCraft);                                        // 9 - Listar aeronaves a aguardar autorizacao (Todas ou por Local)
void consultarAeronavePorId(TipoFrota *frota, char estadosAeronave[][30]);                                              // 10 - Consultar aeronave inserindo o ID disponivel
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()                                                                                                              // Main do projeto
{
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    SMALL_RECT windowSize = {0, 0, 150, 50};    //{L, T, R(X), B(Y)}                                                    // Predefinicao do tamanho da janela do terminal
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    HANDLE hStdOut = NULL;                                                                                              // Predefinicao da funcao para esconder o cursor
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

    //    setlocale(LC_CTYPE, "Portuguese");
    //    system("color 0A");

    FILE *file;
    TipoFrota frota = {};

    file = fopen("Aeronaves.bin", "rb");
    fread(&frota, sizeof(TipoFrota), 1, file);
    fclose(file);

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
            eliminarAeronaveFrota(&frota, estadosAeronave);
            break;
        case 3:
            system("cls");
            editarAeronaveFrota(&frota, estadosAeronave, locaisAeronave);
            break;
        case 4:
            system("cls");
            iniciarPedidoVoo(&frota, estadosAeronave, locaisAeronave);
            break;
        case 5:
            system("cls");
            autorizarVoo(&frota, estadosAeronave);
            break;
        case 6:
            system("cls");
            cancelarVoo(&frota, estadosAeronave);
            break;
        case 7:
            system("cls");
            listarAeronavesOrdemDescendenteVoos(&frota);
            break;
        case 8:
            system("cls");
            listarAeronavesEstadoPronto(&frota, &verificarAirCraft, &niu, &niu);

            if(verificarAirCraft != 1)
            {
                gotoxy(43,52);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
                getch();
            }
            break;
        case 9:
            system("cls");
            listarAeronavesEstadoAutorizacao(&frota, &verificarAirCraft);

            if(verificarAirCraft != 1)
            {
                gotoxy(43,52);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
                getch();
            }
            break;
        case 10:
            system("cls");
            consultarAeronavePorId(&frota, estadosAeronave);
            break;
        case 11:
            system("cls");
            desenharBox(80,36);
            gotoxy(52,7);
            printf("Gravar listagem de aeronaves para ficheiro de texto");
            gotoxy(53,13);
            printf("Dados das aeronaves foram guardadas com sucesso");
            gotoxy(43,20);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
            getch();

            file = fopen("Aeronaves.bin", "wb");
            fwrite(&frota, sizeof(TipoFrota), 1, file);
            fclose(file);
            break;
        case 12:
            file = fopen("Aeronaves.bin", "wb");
            fwrite(&frota, sizeof(TipoFrota), 1, file);
            fclose(file);
            return 0;
            break;
        default:
            return 0;
            break;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int implementacaoMenu(int opcao)                                                                                        // Menu principal
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
        printf("1. Adicionar aeronave a frota"RESET);
        gotoxy(38,11);
        seta(2,position);
        printf("2. Eliminar aeronave da frota"RESET);
        gotoxy(38,12);
        seta(3,position);
        printf("3. Editar aeronave"RESET);
        gotoxy(38,13);
        seta(4,position);
        printf("4. Iniciar pedido de voo"RESET);
        gotoxy(38,14);
        seta(5,position);
        printf("5. Autorizar voo"RESET);
        gotoxy(38,15);
        seta(6,position);
        printf("6. Cancelar voo"RESET);
        gotoxy(38,16);
        seta(7,position);
        printf("7. Listar aeronaves e detalhes (Ordem descendente de N%c de voos)"RESET,167);
        gotoxy(38,17);
        seta(8,position);
        printf("8. Listar aeronaves no estado pronto e detalhes"RESET);
        gotoxy(38,18);
        seta(9,position);
        printf("9. Listar aeronaves a aguardar autorizacao e detalhes"RESET);
        gotoxy(38,19);
        seta(10,position);
        printf("10. Consultar aeronave especifica mostrando respetivos detalhes"RESET);
        gotoxy(38,20);
        seta(11,position);
        printf("11. Gravar listagem de aeronaves para ficheiro de texto"RESET);

        gotoxy(50,25);
        printf("Pressione tecla \"ESC\" duas vezes para sair do sistema");
        gotoxy(57,28);
        printf("Nota: Ao pressionar tecla \"ESC\" uma vez");
        gotoxy(52,29);
        printf("tambem grava listagem de aeronaves para ficheiro");

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
            gotoxy(58,32);
            printf(RED"Voce escolheu opcao sair do sistema"RESET);
            position = 0;
            gotoxy(0,40);
            opcao = 12;
            return opcao;
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void adicionarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20])                    // 1 - Adicionar aeronave a frota
{
    int posicaoAeronave = 0, opcaoLocal = 0, keyPressed = 0, position = 1;

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

    opcaoLocal = position;

    position = 1;
    keyPressed = 0;

    switch(opcaoLocal)
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
    printf("Pressione qualquer tecla do teclado para voltar ao menu principal");

    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void listaAutomaticaAeronaves(TipoFrota *frota, int *aeronave, int opcao, int local, int estado)                        // Subprograma que implementa a lista das aeronaves consuante dados recebidos
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
                gotoxy(38,j);
                printf("---------Aeronave N%c%d---------",167, *aeronave);
                j++;
                gotoxy(38,j);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                j++;
                gotoxy(38,j);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                j++;
                gotoxy(38,j);
                printf("Numero de voos realizados: %d",frota->aeronaves[i].numVoos);
                j++;
                gotoxy(38,j);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                j++;
                gotoxy(38,j);
                printf("Local atual: %s",frota->aeronaves[i].localAtual);
                j += 2;
                *aeronave += 1;
            }
            else if((frota->aeronaves[i].id != 0) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[estado]) == 0))
            {
                gotoxy(78,l);
                printf("---------Aeronave N%c%d---------",167, *aeronave);
                l++;
                gotoxy(78,l);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                l++;
                gotoxy(78,l);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                l++;
                gotoxy(78,l);
                printf("Numero de voos realizados: %d",frota->aeronaves[i].numVoos);
                l++;
                gotoxy(78,l);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                l++;
                gotoxy(78,l);
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void eliminarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30])                                                // 2 - Eliminar aeronave da frota
{
    int opcao = 0, aeronaveEscolhida = 0, aeronaveEncontrada = 0, posicaoAeronave = 0, numeroAeronave = 0, keyPressed = 0, position = 1;

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
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
            printf("(Se nao pretende voltar para menu, introduza 0 para voltar ao menu)");
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
                printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
            printf("(Se nao pretende voltar para menu, introduza 0 para voltar ao menu)");
            gotoxy(40,51);
            printf("---> ");
            scanf("%d",&aeronaveEscolhida);

            for(int i = 0; i < 10; i++)
            {
                if(aeronaveEscolhida == 0)
                {
                    return;
                }
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[2]) == 0))
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
    printf("Pressione qualquer tecla do teclado para voltar ao menu principal");

    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void editarAeronaveFrota(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20])                       // 3 - Editar aeronave
{
    int y1 = 0, numeroPassageiro = 1, passageiroPosicao = 0, passageiroEncontrado = 0, aeronave = 0, opcao = 0, aeronaveEscolhida = 0, posicaoAeronave = 0, aeronaveEncontrada = 0, keyPressed = 0, position = 1;
    long int numPassageiro = 0, nifVerificacao = 0, ordenarNifs = 0;;
    char strOrdenarNomes[50], auxNome[50];

    while (keyPressed != 13)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(69,7);
        printf("Editar aeronave");
        gotoxy(41,10);
        printf("Atraves do seguinte separador apenas e possivel editar a capacidade da");
        gotoxy(39,12);
        printf("aeronave, respeitando os limites e modificar o numero de voos efetuados se");
        gotoxy(58,14);
        printf("aeronave estiver em estado \"Pronto\"");
        gotoxy(43,18);
        printf("Caso aeronave esteja \"A Aguardar Autorizacao\" sera apenas possivel");
        gotoxy(47,20);
        printf("editar/adicionar/remover os passageiros e editar o destino");

        desenharLinhaSeparacao(25);

        gotoxy(40,29);
        printf("Selecione a opcao pretendida:");
        gotoxy(40,31);
        seta(1,position);
        printf("Listar aeronaves em estado \"Pronto\"");
        gotoxy(40,32);
        seta(2,position);
        printf("Listar aeronaves em estado \"A Aguardar Autorizacao\"");

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
            system("cls");
            desenharBox(80,58);
            gotoxy(69,7);
            printf("Editar aeronave");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado \"Pronto\":");

            listaAutomaticaAeronaves(frota, &aeronave, 0, 0, 0);

            if(aeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(50,14);
                printf("De momento nao ha aeronaves \"Prontas\" para listar,");
                gotoxy(45,16);
                printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
                getch();
                return;
            }

            gotoxy(40,49);
            printf("Introduza o ID da aeronave para editar");
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

        while (keyPressed != 13)
        {
            system("cls");
            desenharBox(80,36);
            gotoxy(69,7);
            printf("Editar aeronave");
            gotoxy(40,12);
            printf("Selecione a opcao pretendida:");
            gotoxy(40,14);
            seta(1,position);
            printf("Editar a capacidade da aeronave");
            gotoxy(40,15);
            seta(2,position);
            printf("Modificar o numero de voos efetuados");
            gotoxy(40,16);
            seta(3,position);
            printf("Voltar para menu principal");

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
            do
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(40,10);
                printf("Editar a capacidade da aeronave com ID N%c%d:",167, frota->aeronaves[posicaoAeronave].id);
                gotoxy(40,12);
                printf("Introduza a capacidade maxima de passageiros (No minimo 2 e no maximo 4):");
                gotoxy(40,13);
                printf("---> ");
                scanf("%d",&frota->aeronaves[posicaoAeronave].capacidade);
                fflush(stdin);

                if ((frota->aeronaves[posicaoAeronave].capacidade < 2) || (frota->aeronaves[posicaoAeronave].capacidade > 4))
                {
                    gotoxy(40,20);
                    printf(RED"ERRO: Voce introduziu a quantidade incorreta, reintroduza a quantidade."RESET);
                    Sleep(2000);
                }
            }
            while ((frota->aeronaves[posicaoAeronave].capacidade < 2) || (frota->aeronaves[posicaoAeronave].capacidade > 4));


            gotoxy(59,18);
            printf("Capacidade foi editada com sucesso");

            gotoxy(43,23);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
            getch();
            return;
            break;

        case 2:
            do
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(40,10);
                printf("Modifica o numero de voos efetuados da aeronave com ID N%c%d:",167, frota->aeronaves[posicaoAeronave].id);
                gotoxy(40,12);
                printf("Introduza numero de voos (No minimo 0 e no maximo 100):");
                gotoxy(40,13);
                printf("---> ");
                scanf("%d",&frota->aeronaves[posicaoAeronave].numVoos);
                fflush(stdin);

                if ((frota->aeronaves[posicaoAeronave].numVoos < 0) || (frota->aeronaves[posicaoAeronave].numVoos > 100))
                {
                    gotoxy(40,20);
                    printf(RED"ERRO: Voce introduziu a quantidade incorreta, reintroduza a quantidade."RESET);
                    Sleep(2000);
                }
            }
            while ((frota->aeronaves[posicaoAeronave].numVoos < 0) || (frota->aeronaves[posicaoAeronave].numVoos > 100));

            if(frota->aeronaves[posicaoAeronave].numVoos == 100)
            {
                strcpy(frota->aeronaves[posicaoAeronave].estado,estadosAeronave[2]);
            }

            gotoxy(55,18);
            printf("Numero de voos foi modificado com sucesso");

            gotoxy(43,23);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
            getch();
            return;
            break;
        case 3:
            return;
            break;
        default:
            break;
        }
        break;

    case 2:
        do
        {
            system("cls");
            desenharBox(80,58);
            gotoxy(69,7);
            printf("Editar aeronave");
            gotoxy(40,10);
            printf("A listar todas as aeronaves em estado \"A Aguardar Autorizacao\":");

            listaAutomaticaAeronaves(frota, &aeronave, 0, 0, 1);

            if(aeronave == 1)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(44,14);
                printf("De momento nao ha aeronaves \"A Aguardar Autorizacao\" para listar,");
                gotoxy(49,16);
                printf("pode iniciar voo atraves da opcao \"4\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
                getch();
                return;
            }

            gotoxy(40,49);
            printf("Introduza o ID da aeronave para editar");
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
            desenharBox(80,36);
            gotoxy(69,7);
            printf("Editar aeronave");
            gotoxy(40,12);
            printf("Selecione a opcao pretendida:");
            gotoxy(40,14);
            seta(1,position);
            printf("Editar passageiros");
            gotoxy(40,15);
            seta(2,position);
            printf("Adicionar passageiros");
            gotoxy(40,16);
            seta(3,position);
            printf("Remover passageiros");
            gotoxy(40,17);
            seta(4,position);
            printf("Editar o destino");
            gotoxy(40,18);
            seta(5,position);
            printf("Voltar para menu principal");

            keyPressed = getch();

            if(keyPressed == 80 && position != 5)
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
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(55,10);
                printf("Editar passageiros da aeronave com ID N%c%d",167, frota->aeronaves[posicaoAeronave].id);
                gotoxy(40,12);
                printf("A listar todos os passageiros da aeronave:");

                y1 = 14;

                for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
                {
                    gotoxy(40, y1);
                    printf("Nome completo do N%c%d passageiro: %s",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                    y1++;
                    gotoxy(40, y1);
                    printf("NIF do N%c%d passageiro: %ld",167,i+1,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                    y1 += 2;
                }

                desenharLinhaSeparacao(27);

                gotoxy(40,28);
                printf("Introduza o NIF do passageiro que pretende editar:");
                gotoxy(40,29);
                printf("(Se pretende voltar para menu principal introduza 0)");
                gotoxy(40,30);
                printf("---> ");
                scanf("%ld",&numPassageiro);

                for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
                {
                    if(numPassageiro == 0)
                    {
                        return;
                    }

                    else if(numPassageiro == frota->aeronaves[posicaoAeronave].manifesto[i].nif)
                    {
                        passageiroPosicao = i;
                        passageiroEncontrado = TRUE;
                    }
                }

                if(passageiroEncontrado == FALSE)
                {
                    gotoxy(40,32);
                    printf(RED"ERRO: Voce introduziu NIF invalido, reintroduza dentro dos apresetados."RESET);
                    Sleep(2000);
                }
            }
            while (passageiroEncontrado == FALSE);

            gotoxy(54,32);
            printf(GRN"Foi escolhido o passageiro N%c%d com NIF: %d"RESET,167, passageiroPosicao+1,frota->aeronaves[posicaoAeronave].manifesto[passageiroPosicao].nif);
            Sleep(2000);


            do
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(55,10);
                printf("Editar passageiros da aeronave com ID N%c%d",167, frota->aeronaves[posicaoAeronave].id);
                gotoxy(40,12);
                printf("Reintroduza os dados do passageiro:");
                gotoxy(40,14);
                printf("Introduza o NIF do passageiro:");
                gotoxy(40,15);
                printf("---> ");
                scanf("%ld",&numPassageiro);
                fflush(stdin);

                for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
                {
                    if(numPassageiro == frota->aeronaves[posicaoAeronave].manifesto[i].nif)
                    {
                        gotoxy(48,20);
                        printf(RED"ERRO: Voce introduziu NIF ja existente, reintroduza o NIF"RESET);
                        Sleep(2000);
                        nifVerificacao = TRUE;
                        break;
                    }
                    else
                    {
                        nifVerificacao = FALSE;
                    }
                }
                if(nifVerificacao == FALSE)
                {
                    frota->aeronaves[posicaoAeronave].manifesto[passageiroPosicao].nif = numPassageiro;
                }
            }
            while(nifVerificacao == TRUE);

            fflush(stdin);

            gotoxy(40,17);
            printf("Introduza o Nome do passageiro:");
            gotoxy(40,18);
            printf("--->");
            gets(frota->aeronaves[posicaoAeronave].manifesto[passageiroPosicao].nome);
            fflush(stdin);

            gotoxy(52,23);
            printf("Dados do passageiro foram alterados com sucesso");

            gotoxy(43,26);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
            getch();
            return;
            break;
        case 2:
            if(frota->aeronaves[posicaoAeronave].capacidade == 4)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(48,14);
                printf("Nao e possivel acrescentar mais passageiros a aeronave,");
                gotoxy(47,16);
                printf("porque a aeronave ja chegou ao seu limite maximo inicial,");
                gotoxy(39,18);
                printf("pode editar ou remover passageiros atravez da opcao \"3\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
                getch();
                return;
            }

            while (keyPressed != 13)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(55,10);
                printf("Editar passageiros da aeronave com ID N%c%d",167, frota->aeronaves[posicaoAeronave].id);
                gotoxy(52,12);
                printf("A aeronave que escolheu possui %d passageiros", frota->aeronaves[posicaoAeronave].capacidade);
                gotoxy(40,15);
                printf("Selecione a opcao pretendida:");
                gotoxy(40,17);
                seta(1,position);
                printf("Adicionar 1 passageiro");
                gotoxy(40,18);
                seta(2,position);
                printf("Voltar para menu principal");

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

                frota->aeronaves[posicaoAeronave].capacidade += 1;

                do
                {
                    system("cls");
                    desenharBox(80,36);
                    gotoxy(69,7);
                    printf("Editar aeronave");
                    gotoxy(55,10);
                    printf("Editar passageiros da aeronave com ID N%c%d",167, frota->aeronaves[posicaoAeronave].id);
                    gotoxy(40,12);
                    printf("Introduza os dados do passageiro adicionado:");
                    gotoxy(40,14);
                    printf("Introduza o NIF do passageiro:");
                    gotoxy(40,15);
                    printf("---> ");
                    scanf("%ld",&numPassageiro);
                    fflush(stdin);

                    for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
                    {
                        if(numPassageiro == frota->aeronaves[posicaoAeronave].manifesto[i].nif)
                        {
                            gotoxy(48,20);
                            printf(RED"ERRO: Voce introduziu NIF ja existente, reintroduza o NIF"RESET);
                            Sleep(2000);
                            nifVerificacao = TRUE;
                            break;
                        }
                        else
                        {
                            nifVerificacao = FALSE;
                        }
                    }
                    if(nifVerificacao == FALSE)
                    {
                        for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
                        {
                            if(frota->aeronaves[posicaoAeronave].manifesto[i].nif == 0)
                            {
                                frota->aeronaves[posicaoAeronave].manifesto[i].nif = numPassageiro;
                            }
                        }
                    }
                }
                while(nifVerificacao == TRUE);

                fflush(stdin);

                gotoxy(40,17);
                printf("Introduza o Nome do passageiro:");
                gotoxy(40,18);
                printf("--->");
                gets(auxNome);
                fflush(stdin);

                for(int i = 0; i < 4; i++)
                {
                    if(frota->aeronaves[posicaoAeronave].manifesto[i].nome[0] != '\0')
                    {
                        gotoxy(40, y1);
                        printf("Nome completo do N%c%d passageiro: %s",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                        y1++;
                        gotoxy(40, y1);
                        printf("NIF do N%c%d passageiro: %ld",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                        y1 += 2;
                        numeroPassageiro++;
                    }
                }

                gotoxy(58,23);
                printf("Passageiro foi adicionado com sucesso");
                gotoxy(43,30);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");

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

                getch();
                return;
                break;
            case 2:
                return;
                break;
            default:
                break;
            }

            gotoxy(43,23);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
            getch();
            return;
            break;
        case 3:
            if(frota->aeronaves[posicaoAeronave].capacidade == 2)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(48,14);
                printf("Nao e possivel remover mais passageiros da aeronave,");
                gotoxy(47,16);
                printf("porque a aeronave ja chegou ao seu limite minimo inicial,");
                gotoxy(39,18);
                printf("pode editar ou adicionar passageiros atraves da opcao \"3\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
                getch();
                return;
            }

            while (keyPressed != 13)
            {
                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(55,10);
                printf("Editar passageiros da aeronave com ID N%c%d",167, frota->aeronaves[posicaoAeronave].id);
                gotoxy(52,12);
                printf("A aeronave que escolheu possui %d passageiros", frota->aeronaves[posicaoAeronave].capacidade);
                gotoxy(40,15);
                printf("Selecione a opcao pretendida:");
                gotoxy(40,17);
                seta(1,position);
                printf("Remover 1 passageiro");
                gotoxy(40,18);
                seta(2,position);
                printf("Voltar para menu principal");

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
                    system("cls");
                    desenharBox(80,36);
                    gotoxy(69,7);
                    printf("Editar aeronave");
                    gotoxy(55,10);
                    printf("Editar passageiros da aeronave com ID N%c%d",167, frota->aeronaves[posicaoAeronave].id);
                    gotoxy(40,12);
                    printf("A listar todos os passageiros da aeronave:");

                    y1 = 14;

                    for(int i = 0; i < 4; i++)
                    {
                        if(frota->aeronaves[posicaoAeronave].manifesto[i].nome[0] != '\0')
                        {
                            gotoxy(40, y1);
                            printf("Nome completo do N%c%d passageiro: %s",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                            y1++;
                            gotoxy(40, y1);
                            printf("NIF do N%c%d passageiro: %ld",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                            y1 += 2;
                            numeroPassageiro++;
                        }
                    }

                    desenharLinhaSeparacao(27);

                    gotoxy(40,28);
                    printf("Introduza o NIF do passageiro que pretende editar:");
                    gotoxy(40,29);
                    printf("(Se pretende voltar para menu principal introduza 0)");
                    gotoxy(40,30);
                    printf("---> ");
                    scanf("%ld",&numPassageiro);

                    for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
                    {
                        if(numPassageiro == 0)
                        {
                            return;
                        }

                        else if(numPassageiro == frota->aeronaves[posicaoAeronave].manifesto[i].nif)
                        {
                            passageiroPosicao = i;
                            passageiroEncontrado = TRUE;
                        }
                    }

                    if(passageiroEncontrado == FALSE)
                    {
                        gotoxy(40,32);
                        printf(RED"ERRO: Voce introduziu NIF invalido, reintroduza dentro dos apresetados."RESET);
                        Sleep(2000);
                    }
                }
                while (passageiroEncontrado == FALSE);

                gotoxy(54,32);
                printf(GRN"Foi escolhido o passageiro N%c%d com NIF: %d"RESET,167, passageiroPosicao+1,frota->aeronaves[posicaoAeronave].manifesto[passageiroPosicao].nif);
                Sleep(2000);

                system("cls");
                desenharBox(80,36);
                gotoxy(69,7);
                printf("Editar aeronave");
                gotoxy(51,19);
                printf("Passageiro com NIF %ld foi eliminado com sucesso", frota->aeronaves[posicaoAeronave].manifesto[passageiroPosicao].nif);

                frota->aeronaves[posicaoAeronave].manifesto[passageiroPosicao].nif = 0;
                strcpy(frota->aeronaves[posicaoAeronave].manifesto[passageiroPosicao].nome,"");
                frota->aeronaves[posicaoAeronave].capacidade -= 1;

                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");

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

                getch();
                return;
                break;
            case 2:
                return;
                break;
            default:
                break;
            }
            break;

        case 4:
            if(strcmp(frota->aeronaves[posicaoAeronave].localAtual, locaisAeronave[0]) == 0)
            {
                while (keyPressed != 13)
                {
                    system("cls");
                    desenharBox(80,36);
                    gotoxy(69,7);
                    printf("Editar aeronave");
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

                opcao = position;

                position = 1;
                keyPressed = 0;

                switch(opcao)
                {
                case 1:
                    strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[1]);
                    break;
                case 2:
                    strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[2]);
                    break;
                default:
                    break;
                }
            }

            else if(strcmp(frota->aeronaves[posicaoAeronave].localAtual, locaisAeronave[1]) == 0)
            {
                while (keyPressed != 13)
                {
                    system("cls");
                    desenharBox(80,36);
                    gotoxy(69,7);
                    printf("Editar aeronave");
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

                opcao = position;

                position = 1;
                keyPressed = 0;

                switch(opcao)
                {
                case 1:
                    strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[0]);
                    break;
                case 2:
                    strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[2]);
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
                    gotoxy(69,7);
                    printf("Editar aeronave");
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

                opcao = position;

                position = 1;
                keyPressed = 0;

                switch(opcao)
                {
                case 1:
                    strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[0]);
                    break;
                case 2:
                    strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[1]);
                    break;
                default:
                    break;
                }
            }

            gotoxy(61,19);
            printf("Destino foi alterado com sucesso");
            gotoxy(43,24);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
            getch();
            return;
            break;
        case 5:
            return;
            break;
        default:
            break;
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
        break;
    default:
        break;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void iniciarPedidoVoo(TipoFrota *frota, char estadosAeronave[][30], char locaisAeronave[][20])                          // 4 - Iniciar pedido de voo
{
    int opcaoDestino = 0, y1 = 0, y2 = 0, aeronaveEscolhida = 0, existenciaAeronaves = 0, opcaoAirCraft = 0, localAirCraft = 0, posicaoAeronave = 0, aeronaveEncontrada = 0, keyPressed = 0, position = 1;
    char strOrdenarNomes[50];
    long int ordenarNifs = 0;

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
                else if((aeronaveEscolhida == frota->aeronaves[i].id) && (strcmp(frota->aeronaves[i].estado,estadosAeronave[0]) == 0) && (strcmp(frota->aeronaves[i].localAtual,locaisAeronave[localAirCraft]) == 0))
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
    if(strcmp(frota->aeronaves[posicaoAeronave].localAtual, locaisAeronave[0]) == 0)
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
            strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[1]);
            break;
        case 2:
            strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[2]);
            break;
        default:
            break;
        }
    }

    else if(strcmp(frota->aeronaves[posicaoAeronave].localAtual, locaisAeronave[1]) == 0)
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
            strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[0]);
            break;
        case 2:
            strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[2]);
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
            strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[0]);
            break;
        case 2:
            strcpy(frota->aeronaves[posicaoAeronave].destino, locaisAeronave[1]);
            break;
        default:
            break;
        }
    }

    strcpy(frota->aeronaves[posicaoAeronave].estado, estadosAeronave[1]);

    gotoxy(60,19);
    printf("Aeronave a aguardar autorizacao");
    gotoxy(43,24);
    printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void autorizarVoo(TipoFrota *frota, char estadosAeronave[][30])                                                         // 5 - Autorizar voo
{
    char setaHistorico[] = "--->";
    int y1 = 0, existenciaAeronaves = 0, aeronaveEscolhida = 0, posicaoAeronave = 0, aeronaveEncontrada = 0, opcao = 0, keyPressed = 0, historicoCheio = 0, position = 1, numeroPassageiro = 1;

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
            printf("Introduza o ID da aeronave para autorizacao");
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

            for(int i = 0; i < 4; i++)
            {
                if(frota->aeronaves[posicaoAeronave].manifesto[i].nome[0] != '\0')
                {
                    gotoxy(40, y1);
                    printf("Nome completo do N%c%d passageiro: %s",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                    y1++;
                    gotoxy(40, y1);
                    printf("NIF do N%c%d passageiro: %ld",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                    y1 += 2;
                    numeroPassageiro++;
                }
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

            //memoria dos ultimos tres voos
            for(int i = 2; i >= 0; i--)
            {
                if(frota->aeronaves[posicaoAeronave].historico[i][0] == '\0')
                {
                    strcpy(frota->aeronaves[posicaoAeronave].historico[i], frota->aeronaves[posicaoAeronave].localAtual);
                    strcat(frota->aeronaves[posicaoAeronave].historico[i], setaHistorico);
                    strcat(frota->aeronaves[posicaoAeronave].historico[i], frota->aeronaves[posicaoAeronave].destino);
                    historicoCheio += 1;
                    break;
                }
            }

            if(historicoCheio == 0)
            {
                strcpy(frota->aeronaves[posicaoAeronave].historico[2], frota->aeronaves[posicaoAeronave].historico[1]);
                strcpy(frota->aeronaves[posicaoAeronave].historico[1], frota->aeronaves[posicaoAeronave].historico[0]);

                strcpy(frota->aeronaves[posicaoAeronave].historico[0], frota->aeronaves[posicaoAeronave].localAtual);
                strcat(frota->aeronaves[posicaoAeronave].historico[0], setaHistorico);
                strcat(frota->aeronaves[posicaoAeronave].historico[0], frota->aeronaves[posicaoAeronave].destino);
            }

            strcpy(frota->aeronaves[posicaoAeronave].localAtual, frota->aeronaves[posicaoAeronave].destino);
            strcpy(frota->aeronaves[posicaoAeronave].destino, "");

            for(int i = 0; i < frota->aeronaves[posicaoAeronave].capacidade; i++)
            {
                frota->aeronaves[posicaoAeronave].manifesto[i].nif = 0;
                strcpy(frota->aeronaves[posicaoAeronave].manifesto[i].nome,"");
            }

            gotoxy(60,15);
            printf("O voo foi autorizado com sucesso");

            gotoxy(43,20);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");

            getch();
            return;
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void cancelarVoo(TipoFrota *frota, char estadosAeronave[][30])                                                          // 6 - Cancelar voo
{
    int y1 = 0, existenciaAeronaves = 0, aeronaveEscolhida = 0, posicaoAeronave = 0, aeronaveEncontrada = 0, opcao = 0, keyPressed = 0, position = 1;

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
            gotoxy(70,7);
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
            gotoxy(70,7);
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

            gotoxy(60,15);
            printf("O voo foi cancelado com sucesso");

            gotoxy(43,20);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");

            getch();
            return;
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void listarAeronavesOrdemDescendenteVoos(TipoFrota *frota)                                                              // 7 - Listar todas as aeronaves por ordem descendente de numero de voos
{
    int i = 0, j = 0, indiceMaximo = 0;
    int auxId = 0, auxCapacidade = 0, auxNumVoos = 0, auxNif = 0;
    char auxEstado[30], auxLocalAtual[20], auxDestino[20], auxHistorico[30], auxNome[50];
    int y1 = 12, y2 = 12, numeroAeronave = 1;

    if(frota->totalAeronaves == 0)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(47,7);
        printf("Listar aeronaves e detalhes (Ordem descendente de N%c de voos)",167);
        gotoxy(53,14);
        printf("De momento nao ha nenhuma aeronave para listar,");
        gotoxy(45,16);
        printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
        gotoxy(43,25);
        printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
        getch();
        return;
    }

    system("cls");
    desenharBox(80,58);
    gotoxy(47,7);
    printf("Listar aeronaves e detalhes (Ordem descendente de N%c de voos)",167);
    gotoxy(40,10);
    printf("A listar todas as aeronaves da frota:");


    for (i = 0; i < frota->totalAeronaves-1; i++)
    {
        indiceMaximo = i;

        for (j = i + 1; j < frota->totalAeronaves; j++)
        {
            if (frota->aeronaves[j].numVoos > frota->aeronaves[indiceMaximo].numVoos)
            {
                indiceMaximo = j;
            }
        }

        if(i != indiceMaximo)
        {
            // troca id's consuante numero de voos por ordem descrescente
            auxId = frota->aeronaves[i].id;
            frota->aeronaves[i].id = frota->aeronaves[indiceMaximo].id;
            frota->aeronaves[indiceMaximo].id = auxId;

            // troca capacidade consuante numero de voos por ordem descrescente
            auxCapacidade = frota->aeronaves[i].capacidade;
            frota->aeronaves[i].capacidade = frota->aeronaves[indiceMaximo].capacidade;
            frota->aeronaves[indiceMaximo].capacidade = auxCapacidade;

            // troca numero de voos por ordem descrescente
            auxNumVoos = frota->aeronaves[i].numVoos;
            frota->aeronaves[i].numVoos = frota->aeronaves[indiceMaximo].numVoos;
            frota->aeronaves[indiceMaximo].numVoos = auxNumVoos;

            // troca estado consuante numero de voos por ordem descrescente
            strcpy(auxEstado,frota->aeronaves[i].estado);
            strcpy(frota->aeronaves[i].estado,frota->aeronaves[indiceMaximo].estado);
            strcpy(frota->aeronaves[indiceMaximo].estado,auxEstado);

            // troca localAtual consuante numero de voos por ordem descrescente
            strcpy(auxLocalAtual,frota->aeronaves[i].localAtual);
            strcpy(frota->aeronaves[i].localAtual,frota->aeronaves[indiceMaximo].localAtual);
            strcpy(frota->aeronaves[indiceMaximo].localAtual,auxLocalAtual);

            // troca destino consuante numero de voos por ordem descrescente
            strcpy(auxDestino,frota->aeronaves[i].destino);
            strcpy(frota->aeronaves[i].destino,frota->aeronaves[indiceMaximo].destino);
            strcpy(frota->aeronaves[indiceMaximo].destino,auxDestino);

            // troca historico consuante numero de voos por ordem descrescente
            for(int h = 0; h < 3; h++)
            {
                strcpy(auxHistorico,frota->aeronaves[i].historico[h]);
                strcpy(frota->aeronaves[i].historico[h],frota->aeronaves[indiceMaximo].historico[h]);
                strcpy(frota->aeronaves[indiceMaximo].historico[h],auxHistorico);
            }

            // troca passageiros consuante numero de voos por ordem descrescente
            for(int p = 0; p < 4; p++)
            {
                strcpy(auxNome,frota->aeronaves[i].manifesto[p].nome);
                strcpy(frota->aeronaves[i].manifesto[p].nome,frota->aeronaves[indiceMaximo].manifesto[p].nome);
                strcpy(frota->aeronaves[indiceMaximo].manifesto[p].nome,auxNome);

                auxNif = frota->aeronaves[i].manifesto[p].nif;
                frota->aeronaves[i].manifesto[p].nif = frota->aeronaves[indiceMaximo].manifesto[p].nif;
                frota->aeronaves[indiceMaximo].manifesto[p].nif = auxNif;
            }
        }
    }

    for(int l = 0; l < 10; l++)
    {
        if((frota->aeronaves[l].id != 0) && (y1 <= 46))
        {
            gotoxy(38,y1);
            printf("---------Aeronave N%c%d---------",167, numeroAeronave);
            y1++;
            gotoxy(38,y1);
            printf("ID da aeronave: %d",frota->aeronaves[l].id);
            y1++;
            gotoxy(38,y1);
            printf("Capacidade da aeronave: %d",frota->aeronaves[l].capacidade);
            y1++;
            gotoxy(38,y1);
            printf("Numero de voos realizados: %d",frota->aeronaves[l].numVoos);
            y1++;
            gotoxy(38,y1);
            printf("Estado atual: %s",frota->aeronaves[l].estado);
            y1++;
            gotoxy(38,y1);
            printf("Local atual: %s",frota->aeronaves[l].localAtual);
            y1 += 2;
            numeroAeronave++;
        }
        else if(frota->aeronaves[l].id != 0)
        {
            gotoxy(78,y2);
            printf("---------Aeronave N%c%d---------",167, numeroAeronave);
            y2++;
            gotoxy(78,y2);
            printf("ID da aeronave: %d",frota->aeronaves[l].id);
            y2++;
            gotoxy(78,y2);
            printf("Capacidade da aeronave: %d",frota->aeronaves[l].capacidade);
            y2++;
            gotoxy(78,y2);
            printf("Numero de voos realizados: %d",frota->aeronaves[l].numVoos);
            y2++;
            gotoxy(78,y2);
            printf("Estado atual: %s",frota->aeronaves[l].estado);
            y2++;
            gotoxy(78,y2);
            printf("Local atual: %s",frota->aeronaves[l].localAtual);
            y2 += 2;
            numeroAeronave++;
        }
    }

    desenharLinhaSeparacao(47);
    gotoxy(43,52);
    printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
    getch();
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void listarAeronavesEstadoPronto(TipoFrota *frota, int *verificarAirCraft, int *opcaoAirCraft, int *localAirCraft)      // 8 - Listar aeronaves prontas (Todas ou por Local)
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
            printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
            gotoxy(43,25);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
                printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
                printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
                printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void listarAeronavesEstadoAutorizacao(TipoFrota *frota, int *verificarAirCraft)                                         // 9 - Listar aeronaves a aguardar autorizacao (Todas ou por Local)
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
            printf("pode iniciar voo atraves da opcao \"4\" no menu principal");
            gotoxy(43,25);
            printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
            printf("Selecione a localizacao pretendida da lista abaixo:");
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
                printf("pode iniciar voo atraves da opcao \"4\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
                printf("pode iniciar voo atraves da opcao \"4\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
                printf("pode iniciar voo atraves da opcao \"4\" no menu principal");
                gotoxy(43,25);
                printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void consultarAeronavePorId(TipoFrota *frota, char estadosAeronave[][30])                                               // 10 - Consultar aeronave inserindo o ID disponivel
{
    int y1 = 0, y2 = 0, aeronaveEscolhida = 0, posicaoAeronave = 0, aeronaveEncontrada = 0, keyPressed = 0, opcao = 0, position = 1, numAeronave = 1, numeroPassageiro = 1;

    if(frota->totalAeronaves == 0)
    {
        system("cls");
        desenharBox(80,36);
        gotoxy(43,7);
        printf("Consultar aeronave especifica mostrando respetivos detalhes por ID");
        gotoxy(53,14);
        printf("De momento nao ha nenhuma aeronave para listar,");
        gotoxy(45,16);
        printf("pode adicionar aeronave atraves da opcao \"1\" no menu principal");
        gotoxy(43,25);
        printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
        getch();
        return;
    }

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

        for(int i = 0; i < 10; i++)
        {
            if((frota->aeronaves[i].id != 0) && (y1 <= 35))
            {
                gotoxy(38,y1);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                y1++;
                gotoxy(38,y1);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                y1++;
                gotoxy(38,y1);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                y1++;
                gotoxy(38,y1);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                y1 += 2;
                numAeronave++;
            }
            else if(frota->aeronaves[i].id != 0)
            {
                gotoxy(78,y2);
                printf("---------Aeronave N%c%d---------",167,numAeronave);
                y2++;
                gotoxy(78,y2);
                printf("ID da aeronave: %d",frota->aeronaves[i].id);
                y2++;
                gotoxy(78,y2);
                printf("Capacidade da aeronave: %d",frota->aeronaves[i].capacidade);
                y2++;
                gotoxy(78,y2);
                printf("Estado atual: %s",frota->aeronaves[i].estado);
                y2 += 2;
                numAeronave++;
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

    while (keyPressed != 13)
    {
        system("cls");
        desenharBox(80,50);
        gotoxy(40,44);
        printf("Pretende visualizar o historico da aeronave escolhida");
        gotoxy(40,45);
        printf("(Escolha a opcao pretendida):");
        gotoxy(40,47);
        seta(1,position);
        printf("Sim");
        gotoxy(40,48);
        seta(2,position);
        printf("Nao");

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

            if(strcmp(frota->aeronaves[posicaoAeronave].estado, estadosAeronave[1]) == 0)
            {
                gotoxy(40,y1);
                printf("Local do destino: %s",frota->aeronaves[posicaoAeronave].destino);
                y1 += 2;


                for(int i = 0; i < 4; i++)
                {
                    if(frota->aeronaves[posicaoAeronave].manifesto[i].nome[0] != '\0')
                    {
                        gotoxy(40, y1);
                        printf("Nome completo do N%c%d passageiro: %s",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nome);
                        y1++;
                        gotoxy(40, y1);
                        printf("NIF do N%c%d passageiro: %ld",167,numeroPassageiro,frota->aeronaves[posicaoAeronave].manifesto[i].nif);
                        y1 += 2;
                        numeroPassageiro++;
                    }
                }
            }
        }

        desenharLinhaSeparacao(42);

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
        desenharBox(80,36);
        gotoxy(43,7);
        printf("Consultar aeronave especifica mostrando respetivos detalhes por ID");
        gotoxy(40,11);
        printf("A listar historico (Ultimos 3 voos) da aeronave N%c%d:",167,posicaoAeronave+1);

        y1 = 14;
        numAeronave = 1;

        for(int i = 0; i <= 2; i++)
        {
            if(frota->aeronaves[posicaoAeronave].historico[i][0] != '\0')
            {
                gotoxy(40,y1);
                printf("Destino N%c%d da aeronave: %s",167, numAeronave, frota->aeronaves[posicaoAeronave].historico[i]);
                y1 += 2;
                numAeronave++;
            }
        }

        if(frota->aeronaves[posicaoAeronave].numVoos == 0)
        {
            system("cls");
            desenharBox(80,36);
            gotoxy(43,7);
            printf("Consultar aeronave especifica mostrando respetivos detalhes por ID");
            gotoxy(39,15);
            printf("De momento a aeronave que escolheu nao tem registado nenhum voo realizado,");
            gotoxy(58,17);
            printf("ou seja, historico esta indisponivel");

        }

        gotoxy(43,28);
        printf("Pressione qualquer tecla do teclado para voltar ao menu principal");
        getch();
        break;
    case 2:
        return;
        break;
    default:
        break;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y)                                                                                               // Subprograma para movimentar o cursos
{
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int desenharBox(int x, int y)                                                                                           // Subprograma para desenhar box
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void aprecentacaoInicial()                                                                                              // Subprograma que apresenta capa do projeto
{
    gotoxy(70,6);
    printf(R"EOF(
                                                                       ___
                                                                       \\ \
                                                                        \\ `\
                                                     ___                 \\  \
                                                    |    \                \\  `\
                                                    |_____\                \    \
                                                    |______\                \    `\
                                                    |       \                \     \
                                                    |      __\__---------------------------------._.
                                                  __|---~~~__o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_[][\__
                                                 |___                         /~      )                \__
                                                     ~~~---..._______________/      ,/_________________/
                                                                            /      /
                                                                           /     ,/
                                                                          /     /
                                                                         /    ,/
                                                                        /    /
                                                                       //  ,/
                                                                      //  /
                                                                     // ,/
                                                                    //_/
)EOF");


    desenharBox(80,36);
    gotoxy(53,30);
    puts("Bem vindo ao TAIPS - Transportadora Aerea IPS");
    gotoxy(50,33);
    puts("Projeto realizado por: Serhiy Kukurudza e Bruno Rosa");
    Sleep(1000);
    system("cls");
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void seta(int realPosition, int arrowPosition)                                                                          // Subprograma que implementa a seta da escolha
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void desenharLinhaSeparacao(int y)                                                                                      // Subprograma que implementa uma linha para separar dados
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
