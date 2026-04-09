#include <iostream>
#include <vector>
using namespace std;

// Contadores globais
long long tentativas = 0;   // verificações de movimentos
long long avaliacoes = 0;   // chamadas da heurística (grau)
long long decisoes = 0;     // decisões tomadas

// Movimentos do cavalo
int dx[8] = {2,1,-1,-2,-2,-1,1,2};
int dy[8] = {1,2,2,1,-1,-2,-2,-1};

// Verifica se a posição é válida
bool valido(int x, int y, int N, vector<vector<int>>& tab) {
    tentativas++; // contou uma verificação
    return (x >= 0 && y >= 0 && x < N && y < N && tab[x][y] == -1);
}

// Conta o grau (Warnsdorff) 
int grau(int x, int y, int N, vector<vector<int>>& tab) {
    avaliacoes++; // chamou heurística

    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (valido(nx, ny, N, tab))
            count++;
    }
    return count;
}

// Passeio do cavalo
bool passeioCavalo(int N, int startX, int startY) {
    vector<vector<int>> tab(N, vector<int>(N, -1));

    int x = startX;
    int y = startY;

    tab[x][y] = 0;

    for (int passo = 1; passo < N * N; passo++) {

        int minGrau = 9;
        int proxX = -1, proxY = -1;

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

        // Falha
        if (proxX == -1 && proxY == -1) {
            cout << "Nao ha solucao para esse caso.\n";
            return false;
        }

        // Decisão tomada
        decisoes++;

        x = proxX;
        y = proxY;
        tab[x][y] = passo;
    }

    // Imprime tabuleiro
    cout << "\nCaminho do cavalo:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tab[i][j] << "\t";
        }
        cout << endl;
    }

    // Estatísticas
    cout << "\n===== ESTATISTICAS =====\n";
    cout << "Tentativas (verificacoes): " << tentativas << endl;
    cout << "Avaliacoes (grau): " << avaliacoes << endl;
    cout << "Decisoes tomadas: " << decisoes << endl;

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