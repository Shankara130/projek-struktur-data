#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct Obat {
    int id;
    string nama;
    string jenis;
    int stok;
    double harga;
};

stack<Obat> riwayatTransaksi;

void tambahRiwayatTransaksi(Obat obat) {
    riwayatTransaksi.push(obat);
}

void tampilkanRiwayatTransaksi() {
    while (!riwayatTransaksi.empty()) {
        Obat obat = riwayatTransaksi.top();
        cout << "ID: " << obat.id << ", Nama: " << obat.nama << "\n";
        riwayatTransaksi.pop();
    }
}

queue<string> antrianPelanggan;

void tambahAntrianPelanggan(string nama) {
    antrianPelanggan.push(nama);
}

void layaniPelanggan() {
    if (!antrianPelanggan.empty()) {
        cout << "Melayani: " << antrianPelanggan.front() << "\n";
        antrianPelanggan.pop();
    } else {
        cout << "Tidak ada pelanggan dalam antrian.\n";
    }
}

int main() {
    // Contoh penggunaan struct
    Obat paracetamol = {1, "Paracetamol", "Tablet", 100, 5000};
    Obat ibuprofen = {2, "Ibuprofen", "Capsule", 50, 7500};

    // Contoh penggunaan stack
    tambahRiwayatTransaksi(paracetamol);
    tambahRiwayatTransaksi(ibuprofen);
    tampilkanRiwayatTransaksi();

    // Contoh penggunaan queue
    tambahAntrianPelanggan("Galbi");
    tambahAntrianPelanggan("Anya");
    layaniPelanggan();
    layaniPelanggan();
}
