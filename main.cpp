#include "sculptor.h"

int main() {
    // Aumentei um pouco o espaço em Y e Z para mais folga
    Sculptor parque(120, 85, 50);

    // ==============================
    // 1️⃣ Piso de areia (arena)
    // ==============================
    parque.setColor(0.94, 0.87, 0.73, 1.0); // areia
    parque.putBox(5, 115, 5, 60, 0, 1); // piso

   // ==============================
// 2️⃣ Cercas ao redor da arena (versão simplificada e mais densa)
// ==============================
parque.setColor(0.65, 0.50, 0.39, 1.0); // marrom madeira

int espacamento = 4; // postes mais próximos (antes era 10)
int alturaCerca = 4; // altura dos postes
int zArame = 3;      // altura da linha horizontal

// ---- Frente (lado Y = 5)
for (int x = 5; x <= 115; x += espacamento) {
    parque.putBox(x, x, 5, 5, 1, alturaCerca); // poste
    // linha horizontal ligando os postes
    if (x + espacamento <= 115) {
        for (int x2 = x; x2 < x + espacamento; x2++) {
            parque.putVoxel(x2, 5, zArame);
        }
    }
}

// ---- Fundo (lado Y = 60)
for (int x = 5; x <= 115; x += espacamento) {
    parque.putBox(x, x, 60, 60, 1, alturaCerca); // poste
    if (x + espacamento <= 115) {
        for (int x2 = x; x2 < x + espacamento; x2++) {
            parque.putVoxel(x2, 60, zArame);
        }
    }
}

// ---- Lateral direita (lado X = 115)
for (int y = 5; y <= 60; y += espacamento) {
    parque.putBox(115, 115, y, y, 1, alturaCerca); // poste
    if (y + espacamento <= 60) {
        for (int y2 = y; y2 < y + espacamento; y2++) {
            parque.putVoxel(115, y2, zArame);
        }
    }
}


/// ==============================
// 3️⃣ Muro com portão (saída do boi)
// ==============================

// Cor cinza-claro (alvenaria visível no visualizador OFF)
parque.setColor(0.8, 0.8, 0.8, 1.0);

// Cria o muro inteiro
parque.putBox(5, 5, 5, 60, 1, 10);

// Portão central (estreito e aberto só embaixo)
int yCentro = (5 + 60) / 2;  // centro da parede
int larguraPortao = 2;       // largura total do portão
int y0Portao = yCentro - larguraPortao / 2;
int y1Portao = yCentro + larguraPortao / 2;

// Abertura inferior (tipo portal)
parque.cutBox(5, 5, y0Portao, y1Portao, 1, 6);



    // ==============================
    // 4️⃣ Arquibancada (fora da arena)
    // ==============================
    parque.setColor(0.8, 0.8, 0.8, 1.0); // cimento

    int degraus = 6;
    int alturaDegrau = 2;
    int larguraDegrau = 3;

    // Início logo após a cerca do fundo (Y=60)
    for (int i = 0; i < degraus; i++) {
        int z0 = 1 + i * alturaDegrau;
        int z1 = z0 + alturaDegrau - 1;
        int y0 = 61 + i * larguraDegrau;
        int y1 = y0 + larguraDegrau - 1;

        // segurança: se passar do limite, para
        if (y1 >= 84) break;

        parque.putBox(10, 110, y0, y1, 0, z1);
    }

   // ==============================
// 5️⃣ Cobertura da arquibancada (corrigida)
// ==============================
parque.setColor(0.45, 0.45, 0.45, 1.0); // telhado

int yInicioTeto = 61; // começa no início da arquibancada
int yFimTeto = 61 + degraus * larguraDegrau; // termina no fim do último degrau
int zAlturaTeto = degraus * alturaDegrau + 4; // altura do teto acima dos degraus

// Cria o retângulo que cobre toda a arquibancada
if (yFimTeto + 2 < 85) {
    parque.putBox(10, 110, yInicioTeto, yFimTeto + 2, zAlturaTeto, zAlturaTeto + 1);
}

// ==============================
// Linhas da faixa do boi pintadas no piso
// ==============================
parque.setColor(0.8, 0.8, 0.8, 1.0); // cinza claro
int xLinha1 = 30;
int xLinha2 = 50; // separadas por 20 blocos
int yInicio = 33;
int yFim = 60;
int zTopoPiso = 1; // topo do piso

for (int y = yInicio; y <= yFim; y++) {
    parque.putVoxel(xLinha1, y, zTopoPiso);
    parque.putVoxel(xLinha2, y, zTopoPiso);
}



// ==============================
// Abertura na lateral direita para o boi
// ==============================
int yCentroSaida = (5 + 60) / 2;  // centro da lateral direita
int larguraSaida = 12;            // 3 estacas * 4 blocos espaçamento
int y0Saida = yCentroSaida - larguraSaida/2;
int y1Saida = yCentroSaida + larguraSaida/2;

// remove apenas postes
parque.cutBox(115, 115, y0Saida, y1Saida, 1, alturaCerca);

// remove linha de arame correspondente
for (int y = y0Saida; y <= y1Saida; y++) {
    parque.cutVoxel(115, y, zArame);
}


    // ==============================
    // 6️⃣ Exportar modelo 3D
    // ==============================
    parque.writeOFF("parque_vaquejada.off");

    return 0;
}
