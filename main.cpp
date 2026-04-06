#include <iostream>
#include <vector>
using namespace std;

// Movimentos possíveis do cavalo
int dx[8] = {2,1,-1,-2,-2,-1,1,2};
int dy[8] = {1,2,2,1,-1,-2,-2,-1};

// Verifica se a posição é válida
bool valido(int x, int y, int N, vector<vector<int>>& tab) {
    return (x >= 0 && y >= 0 && x < N && y < N && tab[x][y] == -1);
}

// Conta quantos movimentos futuros são possíveis (grau)
int grau(int x, int y, int N, vector<vector<int>>& tab) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (valido(nx, ny, N, tab)) count++;
    }
    return count;
}

// Função principal usando Warnsdorff
bool passeioCavalo(int N, int startX, int startY) {
    vector<vector<int>> tab(N, vector<int>(N, -1));

    int x = startX;
    int y = startY;

    tab[x][y] = 0; // posição inicial

    for (int passo = 1; passo < N * N; passo++) {

        int minGrau = 9;
        int proxX = -1, proxY = -1;

        // Testa todos os movimentos possíveis
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (valido(nx, ny, N, tab)) {
                int g = grau(nx, ny, N, tab);

                if (g < minGrau) {
                    minGrau = g;
                    proxX = nx;
                    proxY = ny;
                }
            }
        }

        // Se não encontrou próximo movimento → falhou
        if (proxX == -1 && proxY == -1) {
            cout << "Nao ha solucao para esse caso.\n";
            return false;
        }

        x = proxX;
        y = proxY;
        tab[x][y] = passo;
    }

    // Imprime o tabuleiro
    cout << "\nCaminho do cavalo:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tab[i][j] << "\t";
        }
        cout << endl;
    }

    return true;
}

int main() {
    int N, x, y;

    cout << "Digite o tamanho do tabuleiro (N): ";
    cin >> N;

    cout << "Digite a posicao inicial (linha e coluna): ";
    cin >> x >> y;

    passeioCavalo(N, x, y);

    return 0;
}