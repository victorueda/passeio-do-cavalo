/*
Autor: Victor Hugo kenji e Daniel Cardoso
Descrição: Implementação do Problema do Passeio do Cavalo utilizando:
- Heurística de Warnsdorff

Entrada:
- Tamanho do tabuleiro (N)
- Posição inicial (x, y)

Saída:
- Matriz com ordem dos movimentos
- Estatísticas de execução
*/

INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO

Requisitos:
- Compilador C++ (g++ recomendado)

Compilação:
No terminal, execute:

g++ main.cpp -o cavalo

Execução:

./cavalo

ou no Windows:

cavalo.exe

Uso:
- Digite o tamanho do tabuleiro (N)
- Digite a posição inicial (x y)

Observações:
- O algoritmo com heurística é eficiente para N maiores
- O backtracking pode ser muito lento para N >= 7