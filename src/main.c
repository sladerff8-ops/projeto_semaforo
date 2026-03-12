#include <stdio.h>
#include <windows.h>
<<<<<<< HEAD
#include <time.h>
#include <stdbool.h>

// Tempos originais preservados
#define T_PRINCIPAL 30
#define T_SECUNDARIA 30
#define T_AMARELO 5
#define T_PEDESTRE 30

// Cores do sistema Windows
#define C_VERDE 10
#define C_VERMELHO 12
#define C_AMARELO 14
#define C_PADRAO 7

typedef struct {
    char nome[30];
    int carros, pedestres;
} Via;

Via vias[4] = {
    {"Principal", 0, 0},
    {"Saida Principal", 0, 0},
    {"Entrada Dupla Sul", 0, 0},
    {"Entrada-O/Saida-S", 0, 0}
};

void setCor(int cor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void atualizarEstatisticas(int idx, int cor) {
    if (cor == C_VERDE) {
        vias[idx].carros += rand() % 4;
    } else if (cor == C_VERMELHO) {
        vias[idx].pedestres += rand() % 2;
    }
}

void desenharInterface(int cores[], int tempoRestante, bool fasePedestreExclusiva) {
    system("cls");
    printf("==========================================================\n");
    printf("   SIMULADOR DE TRAFEGO - LOOP CONTINUO (Ctrl+C p/ Sair)  \n");
    printf("==========================================================\n");
    
    for (int i = 0; i < 4; i++) {
        // 1. Nome da Via e Status do Carro
        setCor(cores[i]);
        printf(" %-18s | %-8s ", vias[i].nome, 
               (cores[i] == C_VERDE ? "VERDE" : (cores[i] == C_AMARELO ? "AMARELO" : "VERMELHO")));
        
        // 2. Contador de Carros (Sempre cor padrão)
        setCor(C_PADRAO);
        printf("| Carros: %-4d | ", vias[i].carros);
        
        // 3. LÓGICA PEDESTRE: Se o sinal da via é VERMELHO, os pedestres estão passando (Verde)
        // Se o sinal da via é VERDE ou AMARELO, os pedestres estão parados (Vermelho)
        if (cores[i] == C_VERMELHO) {
            setCor(C_VERDE);
        } else {
            setCor(C_VERMELHO);
        }
        printf("Pedestres: %-4d\n", vias[i].pedestres);
    }
    
    setCor(C_PADRAO);
    printf("----------------------------------------------------------\n");
    
    if(fasePedestreExclusiva) {
        setCor(C_VERDE);
        printf(" STATUS: FASE EXCLUSIVA PARA TRAVESSIA (TODOS LIBERADOS)\n");
    } else {
        printf(" STATUS: Aguardando ciclo de pedestres...\n");
    }
    
    setCor(C_PADRAO);
    printf(" Tempo restante na fase atual: %d segundos\n", tempoRestante);
    printf("==========================================================\n");
}

void executarCiclo(int c0, int c1, int c2, int c3, int duracao, bool isPedestreExclusivo) {
    int cores[] = {c0, c1, c2, c3};
    for (int i = duracao; i > 0; i--) {
        for (int j = 0; j < 4; j++) {
            atualizarEstatisticas(j, cores[j]);
        }
        desenharInterface(cores, i, isPedestreExclusivo);
        Sleep(1000);
    }
=======
#include <time.h>  // for srand/time
#include <stdbool.h>

#define TEMPO_PRINCIPAL_VERDE 60   // segundos
#define TEMPO_SECUNDARIA_VERDE 30  // segundos
#define TEMPO_AMARELO 5           // segundos

// códigos de cor do console
#define COR_VERDE (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COR_VERMELHO (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define COR_AMARELO (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COR_PADRAO (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// Contadores de carros que já passaram em cada direção
static int carrosWE = 0; // oeste para leste
static int carrosEW = 0; // leste para oeste
static int carrosNS = 0; // norte para sul
static int carrosSN = 0; // sul para norte

// exibe o estado dos quatro semáforos com cores, contador regressivo e simulação
void estadoQuatro(const char* we, int corWE,
                  const char* ew, int corEW,
                  const char* ns, int corNS,
                  const char* sn, int corSN,
                  int tempoSegundos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int restante = tempoSegundos; restante > 0; --restante) {
        // atualiza contadores de acordo com as luzes verdes
        if (corWE == COR_VERDE) carrosWE += rand() % 4;
        if (corEW == COR_VERDE) carrosEW += rand() % 4;
        if (corNS == COR_VERDE) carrosNS += rand() % 4;
        if (corSN == COR_VERDE) carrosSN += rand() % 4;

        system("cls");
        printf("=================================\n");
        SetConsoleTextAttribute(hConsole, corWE);
        printf("Oeste->Leste: %s\n", we);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        SetConsoleTextAttribute(hConsole, corEW);
        printf("Oeste->Leste: %s\n", ew);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        SetConsoleTextAttribute(hConsole, corNS);
        printf("Norte->Sul: %s\n", ns);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        SetConsoleTextAttribute(hConsole, corSN);
        printf("Sul->Norte: %s\n", sn);
        SetConsoleTextAttribute(hConsole, COR_PADRAO);
        printf("---------------------------------\n");
        printf("Tempo restante: %d segundos\n", restante);
        printf("Carros que ja passaram:\n");
        printf("  Oeste-Leste: %d\n", carrosWE);
        printf("  Oeste-Leste: %d\n", carrosEW);
        printf("  Norte-Sul: %d\n", carrosNS);
        printf("  Sul-Norte: %d\n", carrosSN);
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
>>>>>>> e2611280d8686b88f2ea5cd95661d3411cec2e65
}

int main() {
    srand((unsigned)time(NULL));
<<<<<<< HEAD

    // Ocultar cursor do terminal
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    while (1) {
        // Fase 1: Principal Verde | Pedestres das vias Vermelhas ficam VERDE (contando)
        executarCiclo(C_VERDE, C_VERDE, C_VERMELHO, C_VERMELHO, T_PRINCIPAL, false);
        
        // Fase 2: Amarelo
        executarCiclo(C_AMARELO, C_AMARELO, C_VERMELHO, C_VERMELHO, T_AMARELO, false);
        
        // Fase 3: Secundária Verde | Pedestres das vias Vermelhas ficam VERDE (contando)
        executarCiclo(C_VERMELHO, C_VERMELHO, C_VERDE, C_VERDE, T_SECUNDARIA, false);
        
        // Fase 4: Amarelo
        executarCiclo(C_VERMELHO, C_VERMELHO, C_AMARELO, C_AMARELO, T_AMARELO, false);
        
        // Fase 5: TUDO VERMELHO (Todos os pedestres ficam VERDE no terminal)
        executarCiclo(C_VERMELHO, C_VERMELHO, C_VERMELHO, C_VERMELHO, T_PEDESTRE, true);
=======
    // variáveis ajustáveis pelo usuário
    int tPrincipal = TEMPO_PRINCIPAL_VERDE;
    int tSecundaria = TEMPO_SECUNDARIA_VERDE;
    int tAmarelo = TEMPO_AMARELO;

    while (1) {
        system("cls");
        printf("=== Simulador Interativo de Semaforo ===\n");
        printf("Tempos atuais (s): principal=%d, secundaria=%d, amarelo=%d\n", tPrincipal, tSecundaria, tAmarelo);
        printf("Carros passados: W->E=%d, E->W=%d, N->S=%d, S->N=%d\n", carrosWE, carrosEW, carrosNS, carrosSN);
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
                break;
            case 2:
                tPrincipal = lerInteiro("Tempo verde rua principal (s)", 1, 3600);
                tSecundaria = lerInteiro("Tempo verde rua secundária (s)", 1, 3600);
                tAmarelo = lerInteiro("Tempo amarelo (s)", 1, 3600);
                break;
            case 3:
                carrosWE = carrosEW = carrosNS = carrosSN = 0;
                printf("Contadores zerados.\n");
                Sleep(1000);
                break;
            case 4:
                printf("Encerrando...\n");
                return 0;
            default:
                printf("Opção inválida\n");
                break;
        }
        // consome o resto da linha antes de repetir
        while (getchar() != '\n');
>>>>>>> e2611280d8686b88f2ea5cd95661d3411cec2e65
    }

    return 0;
}