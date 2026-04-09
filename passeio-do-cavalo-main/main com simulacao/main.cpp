#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

long long tentativas = 0;
long long avaliacoes = 0;
long long decisoes = 0;

int dx[8] = { 2,1,-1,-2,-2,-1,1,2 };
int dy[8] = { 1,2,2,1,-1,-2,-2,-1 };

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool valido(int x, int y, int N, vector<vector<int>>& tab) {
    tentativas++;
    return (x >= 0 && y >= 0 && x < N&& y < N&& tab[x][y] == -1);
}

int grau(int x, int y, int N, vector<vector<int>>& tab) {
    avaliacoes++;
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (valido(nx, ny, N, tab))
            count++;
    }
    return count;
}

void simularPasseio(int N, const vector<pair<int, int>>& caminho) {
    vector<vector<string>> tela(N, vector<string>(N, "[ ]"));

    for (size_t passo = 0; passo < caminho.size(); passo++) {
        limparTela();

        int cx = caminho[passo].first;
        int cy = caminho[passo].second;

        tela[cx][cy] = "[♞]";

        cout << "--- SIMULACAO DO PASSEIO (Passo " << passo + 1 << "/" << N * N << ") ---\n\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << tela[i][j];
            }
            cout << "\n";
        }

        tela[cx][cy] = "[X]";

        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << "\nSimulacao concluida!\n";
}

bool passeioCavalo(int N, int startX, int startY) {
    vector<vector<int>> tab(N, vector<int>(N, -1));
    vector<pair<int, int>> caminho;

    int x = startX;
    int y = startY;
    tab[x][y] = 0;
    caminho.push_back({ x, y });

    for (int passo = 1; passo < N * N; passo++) {
        int minGrau = 9;
        int proxX = -1, proxY = -1;

        int start_idx = rand() % 8;

        for (int count = 0; count < 8; count++) {
            int i = (start_idx + count) % 8;
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

        if (proxX == -1 && proxY == -1) {
            cout << "Nao ha solucao para esse caso.\n";
            return false;
        }

        decisoes++;
        x = proxX;
        y = proxY;
        tab[x][y] = passo;
        caminho.push_back({ x, y });
    }

    cout << "\nCaminho do cavalo:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tab[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\n===== ESTATISTICAS =====\n";
    cout << "Tentativas (verificacoes): " << tentativas << endl;
    cout << "Avaliacoes (grau): " << avaliacoes << endl;
    cout << "Decisoes tomadas: " << decisoes << endl;

    char resp;
    cout << "\nDeseja visualizar a simulacao em ASCII? (S/N): ";
    cin >> resp;

    if (resp == 'S' || resp == 's') {
#ifdef _WIN32
        system("chcp 65001 > nul");
#endif
        simularPasseio(N, caminho);
    }

    return true;
}

int main() {
    srand(time(NULL));
    int N, x, y;
    char continuar = 'S';

    while (continuar == 'S' || continuar == 's') {
        tentativas = 0;
        avaliacoes = 0;
        decisoes = 0;

        cout << "\nDigite o tamanho do tabuleiro (N): ";
        cin >> N;
        cout << "Digite a posicao inicial (linha e coluna): ";
        cin >> x >> y;

        passeioCavalo(N, x, y);

        cout << "\nDeseja testar outro tabuleiro? (S/N): ";
        cin >> continuar;
    }

    return 0;
}