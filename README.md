# 🚦 Simulador de Semáforo Inteligente

Projeto desenvolvido para a disciplina de Algoritmos e Programação, focado no controle de um cruzamento viário complexo com gestão de fluxo de carros e segurança de pedestres.

## 📋 Sobre o Projeto
O simulador gerencia 4 vias distintas utilizando uma lógica de estados para alternar entre as fases de Verde, Amarelo e Vermelho, garantindo que não haja colisões e permitindo a travessia segura de pedestres.

## 🛠️ Funcionalidades
- **Ciclo Completo:** Alternância automática entre vias principais e secundárias.
- **Fase de Pedestres:** Fase exclusiva onde todos os veículos param para a travessia.
- **Interface Visual:** Uso de cores no terminal para representar os estados do semáforo.
- **Contadores:** Exibição em tempo real da quantidade de carros e pedestres processados.

## 🚦 Lógica de Cores no Terminal
- **Verde:** Sinal aberto para veículos.
- **Amarelo:** Atenção, transição de sinal.
- **Vermelho:** Sinal fechado para veículos.
- **Texto Verde em "Pedestres":** Indica que a travessia está liberada naquela via.

## 🚀 Como Executar
1. Certifique-se de estar em um ambiente Windows.
2. Compile o arquivo `src/main.c` usando um compilador C (GCC, Dev-C++, etc).
3. Execute o arquivo gerado.

---
**Desenvolvido por:** Fernando Gomes Silva Sousa  
**Curso:** Engenharia de Software | UC26101490