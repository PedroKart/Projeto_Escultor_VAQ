#include "sculptor.h"
#include <iostream>
#include <fstream>
using namespace std;


void Sculptor::putVoxel(int x, int y, int z) {
    if (x < 0 || x >= nx || y < 0 || y >= ny || z < 0 || z >= nz) return; // evita acessar fora da matriz
    v[x][y][z].show = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}
void Sculptor::cutVoxel(int x, int y, int z) {
    if (x < 0 || x >= nx || y < 0 || y >= ny || z < 0 || z >= nz) return; // evita acessar fora da matriz
    v[x][y][z].show = false;
}

// ---- Esferas ----
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    int x0 = xcenter - radius;
    int x1 = xcenter + radius;
    int y0 = ycenter - radius;
    int y1 = ycenter + radius;
    int z0 = zcenter - radius;
    int z1 = zcenter + radius;

    for (int i = x0; i <= x1; ++i) {
        for (int j = y0; j <= y1; ++j) {
            for (int k = z0; k <= z1; ++k) {
                if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) continue;
                int dx = i - xcenter;
                int dy = j - ycenter;
                int dz = k - zcenter;
                if (dx*dx + dy*dy + dz*dz <= radius*radius) {
                    v[i][j][k].show = true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    int x0 = xcenter - radius;
    int x1 = xcenter + radius;
    int y0 = ycenter - radius;
    int y1 = ycenter + radius;
    int z0 = zcenter - radius;
    int z1 = zcenter + radius;

    for (int i = x0; i <= x1; ++i) {
        for (int j = y0; j <= y1; ++j) {
            for (int k = z0; k <= z1; ++k) {
                if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) continue;
                int dx = i - xcenter;
                int dy = j - ycenter;
                int dz = k - zcenter;
                if (dx*dx + dy*dy + dz*dz <= radius*radius) {
                    v[i][j][k].show = false;
                }
            }
        }
    }
}

/* ---- Elipsóides ----
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    if (rx == 0 || ry == 0 || rz == 0) return;
    int x0 = xcenter - rx;
    int x1 = xcenter + rx;
    int y0 = ycenter - ry;
    int y1 = ycenter + ry;
    int z0 = zcenter - rz;
    int z1 = zcenter + rz;

    for (int i = x0; i <= x1; ++i) {
        for (int j = y0; j <= y1; ++j) {
            for (int k = z0; k <= z1; ++k) {
                if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) continue;
                double dx = double(i - xcenter) / double(rx);
                double dy = double(j - ycenter) / double(ry);
                double dz = double(k - zcenter) / double(rz);
                if (dx*dx + dy*dy + dz*dz <= 1.0) {
                    v[i][j][k].show = true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}
*/
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    if (rx == 0 || ry == 0 || rz == 0) return;
    int x0 = xcenter - rx;
    int x1 = xcenter + rx;
    int y0 = ycenter - ry;
    int y1 = ycenter + ry;
    int z0 = zcenter - rz;
    int z1 = zcenter + rz;

    for (int i = x0; i <= x1; ++i) {
        for (int j = y0; j <= y1; ++j) {
            for (int k = z0; k <= z1; ++k) {
                if (i < 0 || i >= nx || j < 0 || j >= ny || k < 0 || k >= nz) continue;
                double dx = double(i - xcenter) / double(rx);
                double dy = double(j - ycenter) / double(ry);
                double dz = double(k - zcenter) / double(rz);
                if (dx*dx + dy*dy + dz*dz <= 1.0) {
                    v[i][j][k].show = false;
                }
            }
        }
    }
}



Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // Alocação dinâmica
    v = new Voxel**[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
        }
    }
}

Sculptor::~Sculptor() {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                v[i][j][k].show = true;
                v[i][j][k].r = r;
                v[i][j][k].g = g;
                v[i][j][k].b = b;
                v[i][j][k].a = a;
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                v[i][j][k].show = false;
            }
        }
    }
}
void Sculptor::setColor(float r_, float g_, float b_, float a_) {
    r = r_;
    g = g_;
    b = b_;
    a = a_;
}


void Sculptor::writeOFF(const char* filename) {
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        std::cout << "Erro ao abrir arquivo OFF!" << std::endl;
        return;
    }

    int total_voxels = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) total_voxels++;
            }
        }
    }

    fout << "OFF\n";
    fout << total_voxels * 8 << " " << total_voxels * 6 << " 0\n";

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n";
                    fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n";
                    fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                    fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                }
            }
        }
    }

    int voxel_index = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    int v0 = voxel_index * 8;
                    fout << "4 " << v0 + 0 << " " << v0 + 3 << " " << v0 + 2 << " " << v0 + 1 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << v0 + 4 << " " << v0 + 5 << " " << v0 + 6 << " " << v0 + 7 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << v0 + 0 << " " << v0 + 1 << " " << v0 + 5 << " " << v0 + 4 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << v0 + 0 << " " << v0 + 4 << " " << v0 + 7 << " " << v0 + 3 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << v0 + 3 << " " << v0 + 7 << " " << v0 + 6 << " " << v0 + 2 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << "4 " << v0 + 1 << " " << v0 + 2 << " " << v0 + 6 << " " << v0 + 5 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    voxel_index++;
                }
            }
        }
    }
    

    fout.close();
    std::cout << "Arquivo OFF salvo com sucesso em: " << filename << std::endl;
}

