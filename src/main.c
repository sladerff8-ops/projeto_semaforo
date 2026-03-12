#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

// Tempos de ciclo
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
        setCor(cores[i]);
        printf(" %-18s | %-8s ", vias[i].nome, 
               (cores[i] == C_VERDE ? "VERDE" : (cores[i] == C_AMARELO ? "AMARELO" : "VERMELHO")));
        
        setCor(C_PADRAO);
        printf("| Carros: %-4d | ", vias[i].carros);
        
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
}

int main() {
    srand((unsigned)time(NULL));

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    while (1) {
        // Fase 1: Horizontal Verde
        executarCiclo(C_VERDE, C_VERDE, C_VERMELHO, C_VERMELHO, T_PRINCIPAL, false);
        
        // Fase 2: Amarelo
        executarCiclo(C_AMARELO, C_AMARELO, C_VERMELHO, C_VERMELHO, T_AMARELO, false);
        
        // Fase 3: Vertical Verde
        executarCiclo(C_VERMELHO, C_VERMELHO, C_VERDE, C_VERDE, T_SECUNDARIA, false);
        
        // Fase 4: Amarelo
        executarCiclo(C_VERMELHO, C_VERMELHO, C_AMARELO, C_AMARELO, T_AMARELO, false);
        
        // Fase 5: Travessia Pedestre (Tudo Vermelho)
        executarCiclo(C_VERMELHO, C_VERMELHO, C_VERMELHO, C_VERMELHO, T_PEDESTRE, true);
    }

    return 0;
}