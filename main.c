#include <stdio.h>
#include <windows.h>
#include <time.h>  // for srand/time
#include <stdbool.h>

#define TEMPO_PRINCIPAL_VERDE 30   // segundos
#define TEMPO_SECUNDARIA_VERDE 30  // segundos
#define TEMPO_AMARELO 5           // segundos

// códigos de cor do console
#define COR_VERDE (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COR_VERMELHO (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define COR_AMARELO (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COR_PADRAO (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// Contadores de carros que já passaram em cada direção
static int carrosWE = 0; // principal
static int carrosEW = 0; // saida principal
static int carrosNS = 0; // entrada dupla Sul
static int carrosSN = 0; // entrada-O/saida-S

// Contadores de pedestres que já passaram em cada direção
static int pedestresWE = 0; // principal
static int pedestresEW = 0; // saida principal
static int pedestresNS = 0; // entrada dupla Sul
static int pedestresSN = 0; // entrada-O/saida-S

// Tempos totais de permanência em cada estado por direção
static int tempoVerdeWE = 0, tempoVermelhoWE = 0, tempoAmareloWE = 0;
static int tempoVerdeEW = 0, tempoVermelhoEW = 0, tempoAmareloEW = 0;
static int tempoVerdeNS = 0, tempoVermelhoNS = 0, tempoAmareloNS = 0;
static int tempoVerdeSN = 0, tempoVermelhoSN = 0, tempoAmareloSN = 0;

// exibe o estado dos quatro semáforos com cores, contador regressivo e simulação
void estadoQuatro(const char* we, int corWE,
                  const char* ew, int corEW,
                  const char* ns, int corNS,
                  const char* sn, int corSN,
                  int tempoSegundos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // somar tempos
    if (corWE == COR_VERDE) tempoVerdeWE += tempoSegundos;
    else if (corWE == COR_VERMELHO) tempoVermelhoWE += tempoSegundos;
    else if (corWE == COR_AMARELO) tempoAmareloWE += tempoSegundos;

    if (corEW == COR_VERDE) tempoVerdeEW += tempoSegundos;
    else if (corEW == COR_VERMELHO) tempoVermelhoEW += tempoSegundos;
    else if (corEW == COR_AMARELO) tempoAmareloEW += tempoSegundos;

    if (corNS == COR_VERDE) tempoVerdeNS += tempoSegundos;
    else if (corNS == COR_VERMELHO) tempoVermelhoNS += tempoSegundos;
    else if (corNS == COR_AMARELO) tempoAmareloNS += tempoSegundos;

    if (corSN == COR_VERDE) tempoVerdeSN += tempoSegundos;
    else if (corSN == COR_VERMELHO) tempoVermelhoSN += tempoSegundos;
    else if (corSN == COR_AMARELO) tempoAmareloSN += tempoSegundos;

    for(int restante = tempoSegundos; restante > 0; --restante) {
        // atualiza contadores de acordo com as luzes verdes para carros e vermelhas para pedestres
        if (corWE == COR_VERDE) carrosWE += rand() % 4;
        if (corWE == COR_VERMELHO) pedestresWE += rand() % 2; // pedestres passam quando vermelho para carros
        if (corEW == COR_VERDE) carrosEW += rand() % 4;
        if (corEW == COR_VERMELHO) pedestresEW += rand() % 2;
        if (corNS == COR_VERDE) carrosNS += rand() % 4;
        if (corNS == COR_VERMELHO) pedestresNS += rand() % 2;
        if (corSN == COR_VERDE) carrosSN += rand() % 4;
        if (corSN == COR_VERMELHO) pedestresSN += rand() % 2;

        system("cls");
        printf("=================================\n");
        SetConsoleTextAttribute(hConsole, corWE);
        printf("Principal: %s\n", we);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        SetConsoleTextAttribute(hConsole, corEW);
        printf("Saida Principal: %s\n", ew);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        SetConsoleTextAttribute(hConsole, corNS);
        printf("Entrada Dupla Sul: %s\n", ns);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        SetConsoleTextAttribute(hConsole, corSN);
        printf("Entrada-O/Saida-S: %s\n", sn);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        printf("---------------------------------\n");
        printf("Tempo restante: %d segundos\n", restante);
        printf("Carros que ja passaram:\n");
        if (corWE == COR_VERDE) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corWE == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Principal: %d\n", carrosWE);
        if (corEW == COR_VERDE) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corEW == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Saida Principal: %d\n", carrosEW);
        if (corNS == COR_VERDE) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corNS == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Entrada Dupla Sul: %d\n", carrosNS);
        if (corSN == COR_VERDE) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corSN == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Entrada-O/Saida-S: %d\n", carrosSN);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        printf("Pedestres que ja passaram:\n");
        if (corWE == COR_VERMELHO) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corWE == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Principal: %d\n", pedestresWE);
        if (corEW == COR_VERMELHO) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corEW == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Saida Principal: %d\n", pedestresEW);
        if (corNS == COR_VERMELHO) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corNS == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Entrada Dupla Sul: %d\n", pedestresNS);
        if (corSN == COR_VERMELHO) SetConsoleTextAttribute(hConsole, COR_VERDE);
        else if (corSN == COR_AMARELO) SetConsoleTextAttribute(hConsole, COR_AMARELO);
        else SetConsoleTextAttribute(hConsole, COR_VERMELHO);
        printf("  Entrada-O/Saida-S: %d\n", pedestresSN);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        fflush(stdout);
        Sleep(1000);
    }
    SetConsoleTextAttribute(hConsole, COR_PADRAO);
}

// lê um inteiro do usuário, repetindo até obter um valor válido
int lerInteiro(const char *msg, int minimo, int maximo) {
    int valor;
    while (1) {
        printf("%s (entre %d e %d): ", msg, minimo, maximo);
        if (scanf("%d", &valor) == 1 && valor >= minimo && valor <= maximo) {
            break;
        }
        // limpa buffer
        while (getchar() != '\n');
        printf("Entrada invalida, tente novamente.\n");
    }
    return valor;
}

int main() {
    srand((unsigned)time(NULL));
    // variáveis ajustáveis pelo usuário
    int tPrincipal = TEMPO_PRINCIPAL_VERDE;
    int tSecundaria = TEMPO_SECUNDARIA_VERDE;
    int tAmarelo = TEMPO_AMARELO;

    while (1) {
        system("cls");
        printf("=== Simulador Interativo de Semaforo ===\n");
        printf("Tempos atuais (s): principal=%d, secundaria=%d, amarelo=%d\n", tPrincipal, tSecundaria, tAmarelo);
        printf("Carros passados: Principal=%d, Saida Principal=%d, Entrada Dupla Sul=%d, Entrada-O/Saida-S=%d\n", carrosWE, carrosEW, carrosNS, carrosSN);
        printf("Pedestres passados: Principal=%d, Saida Principal=%d, Entrada Dupla Sul=%d, Entrada-O/Saida-S=%d\n", pedestresWE, pedestresEW, pedestresNS, pedestresSN);
        printf("1. Iniciar ciclo\n");
        printf("2. Configurar tempos\n");
        printf("3. Resetar contadores\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        int opcao;
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }
        switch (opcao) {
            case 1:
                // fase 1: W->E e E->W verde (ambos na via horizontal)
                estadoQuatro("VERDE", COR_VERDE,
                             "VERDE", COR_VERDE,
                             "VERMELHO", COR_VERMELHO,
                             "VERMELHO", COR_VERMELHO,
                             tPrincipal);
                // amarelo na via horizontal
                estadoQuatro("AMARELO", COR_AMARELO,
                             "AMARELO", COR_AMARELO,
                             "VERMELHO", COR_VERMELHO,
                             "VERMELHO", COR_VERMELHO,
                             tAmarelo);
                // fase 2: N->S e S->N verde (ambos na via vertical)
                estadoQuatro("VERMELHO", COR_VERMELHO,
                             "VERMELHO", COR_VERMELHO,
                             "VERDE", COR_VERDE,
                             "VERDE", COR_VERDE,
                             tSecundaria);
                // amarelo na via vertical
                estadoQuatro("VERMELHO", COR_VERMELHO,
                             "VERMELHO", COR_VERMELHO,
                             "AMARELO", COR_AMARELO,
                             "AMARELO", COR_AMARELO,
                             tAmarelo);
                // fase de pedestres: todos vermelhos, pedestres passando
                estadoQuatro("VERMELHO", COR_VERMELHO,
                             "VERMELHO", COR_VERMELHO,
                             "VERMELHO", COR_VERMELHO,
                             "VERMELHO", COR_VERMELHO,
                             30);
                break;
            case 2:
                tPrincipal = lerInteiro("Tempo verde rua principal (s)", 1, 3600);
                tSecundaria = lerInteiro("Tempo verde rua secundária (s)", 1, 3600);
                tAmarelo = lerInteiro("Tempo amarelo (s)", 1, 3600);
                break;
            case 3:
                carrosWE = carrosEW = carrosNS = carrosSN = 0;
                pedestresWE = pedestresEW = pedestresNS = pedestresSN = 0;
                tempoVerdeWE = tempoVermelhoWE = tempoAmareloWE = 0;
                tempoVerdeEW = tempoVermelhoEW = tempoAmareloEW = 0;
                tempoVerdeNS = tempoVermelhoNS = tempoAmareloNS = 0;
                tempoVerdeSN = tempoVermelhoSN = tempoAmareloSN = 0;
                printf("Contadores zerados.\n");
                Sleep(1000);
                break;
            case 4:
                system("cls");
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("=================================\n");
                printf("     RELATORIO FINAL\n");
                printf("=================================\n");
                printf("Tempos de permanencia (segundos):\n");
                printf("---------------------------------\n");
                
                printf("Principal:\n");
                SetConsoleTextAttribute(hConsole, COR_VERDE);
                printf("  Aberto (Verde): %d s\n", tempoVerdeWE);
                SetConsoleTextAttribute(hConsole, COR_VERMELHO);
                printf("  Fechado (Vermelho): %d s\n", tempoVermelhoWE);
                SetConsoleTextAttribute(hConsole, COR_AMARELO);
                printf("  Atencao (Amarelo): %d s\n", tempoAmareloWE);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("---------------------------------\n");
                
                printf("Saida Principal:\n");
                SetConsoleTextAttribute(hConsole, COR_VERDE);
                printf("  Aberto (Verde): %d s\n", tempoVerdeEW);
                SetConsoleTextAttribute(hConsole, COR_VERMELHO);
                printf("  Fechado (Vermelho): %d s\n", tempoVermelhoEW);
                SetConsoleTextAttribute(hConsole, COR_AMARELO);
                printf("  Atencao (Amarelo): %d s\n", tempoAmareloEW);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("---------------------------------\n");
                
                printf("Entrada Dupla Sul:\n");
                SetConsoleTextAttribute(hConsole, COR_VERDE);
                printf("  Aberto (Verde): %d s\n", tempoVerdeNS);
                SetConsoleTextAttribute(hConsole, COR_VERMELHO);
                printf("  Fechado (Vermelho): %d s\n", tempoVermelhoNS);
                SetConsoleTextAttribute(hConsole, COR_AMARELO);
                printf("  Atencao (Amarelo): %d s\n", tempoAmareloNS);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("---------------------------------\n");
                
                printf("Entrada-O/Saida-S:\n");
                SetConsoleTextAttribute(hConsole, COR_VERDE);
                printf("  Aberto (Verde): %d s\n", tempoVerdeSN);
                SetConsoleTextAttribute(hConsole, COR_VERMELHO);
                printf("  Fechado (Vermelho): %d s\n", tempoVermelhoSN);
                SetConsoleTextAttribute(hConsole, COR_AMARELO);
                printf("  Atencao (Amarelo): %d s\n", tempoAmareloSN);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("---------------------------------\n");
                
                printf("Carros que passaram:\n");
                SetConsoleTextAttribute(hConsole, COR_VERDE);
                printf("  Principal: %d\n", carrosWE);
                printf("  Saida Principal: %d\n", carrosEW);
                printf("  Entrada Dupla Sul: %d\n", carrosNS);
                printf("  Entrada-O/Saida-S: %d\n", carrosSN);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("---------------------------------\n");
                
                printf("Pedestres que passaram:\n");
                SetConsoleTextAttribute(hConsole, COR_VERDE);
                printf("  Principal: %d\n", pedestresWE);
                printf("  Saida Principal: %d\n", pedestresEW);
                printf("  Entrada Dupla Sul: %d\n", pedestresNS);
                printf("  Entrada-O/Saida-S: %d\n", pedestresSN);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("---------------------------------\n");
                
                printf("TOTAIS:\n");
                SetConsoleTextAttribute(hConsole, COR_VERDE);
                printf("  Total Carros: %d\n", carrosWE + carrosEW + carrosNS + carrosSN);
                printf("  Total Pedestres: %d\n", pedestresWE + pedestresEW + pedestresNS + pedestresSN);
                SetConsoleTextAttribute(hConsole, COR_PADRAO);
                printf("=================================\n");
                printf("Encerrando...\n");
                Sleep(3000);
                return 0;
            default:
                printf("Opção inválida\n");
                break;
        }
        // consome o resto da linha antes de repetir
        while (getchar() != '\n');
    }

    return 0;
}