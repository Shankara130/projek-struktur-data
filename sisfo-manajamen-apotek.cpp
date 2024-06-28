#include <iostream>
#include <stack>

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
