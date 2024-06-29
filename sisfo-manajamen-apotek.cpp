#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
#include <list>
#include <ctime>

using namespace std;

struct Obat {
    int id;
    string nama;
    string jenis;
    int stok;
    double harga;
};

struct Transaksi {
    int id;
    Obat obat;
    int jumlah;
    string nama;
    double total;
    time_t waktu;
};

struct Supplier {
    int id;
    string nama;
    string kontak;
};

stack<Obat> riwayatTransaksi;
queue<string> antrianPelanggan;
unordered_map<int, Obat> daftarObat;
vector<Transaksi> daftarTransaksi;

void tampilkanRiwayatTransaksi() {
    for (const Transaksi& transaksi : daftarTransaksi) {
        cout << "\nID Transaksi: " << transaksi.id << endl;
        cout << "Obat: " << transaksi.obat.nama << endl;
        cout << "Jumlah: " << transaksi.jumlah << endl;
        cout << "Total Harga: " << transaksi.total << endl;
        cout << "Waktu: " << ctime(&transaksi.waktu) << endl;
    }
}

void tambahAntrianPelanggan(string nama) {
    antrianPelanggan.push(nama);
}

void layaniPelanggan() {
    if (!antrianPelanggan.empty()) {
        cout << "\nMelayani: " << antrianPelanggan.front() << endl;
        antrianPelanggan.pop();
    } else {
        cout << "\nTidak ada pelanggan dalam antrian." << endl;
    }
}

struct Node {
    Obat data;
    Node* next;
};

Node* head = nullptr;

void tambahObat(Obat obat) {
    Node* newNode = new Node{obat, nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    daftarObat[obat.id] = obat;
}

void tampilkanObat() {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "\nID: " << temp->data.id << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Jenis: " << temp->data.jenis << endl;
        cout << "Stok: " << temp->data.stok << endl;
        cout << "Harga: " << temp->data.harga << endl;
        temp = temp->next;
    }
}

struct DoubleNode {
    Supplier data;
    DoubleNode* next;
    DoubleNode* prev;
};

DoubleNode* headSupplier = nullptr;

void tambahSupplier(Supplier supplier) {
    DoubleNode* newNode = new DoubleNode{supplier, nullptr, nullptr};
    if (headSupplier == nullptr) {
        headSupplier = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        DoubleNode* tail = headSupplier->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = headSupplier;
        headSupplier->prev = newNode;
    }
}

void tampilkanSupplier() {
    if (headSupplier != nullptr) {
        DoubleNode* temp = headSupplier;
        do {
            cout << "\nID: " << temp->data.id << endl;
            cout << "Nama: " << temp->data.nama << endl;
            cout << "Kontak: " << temp->data.kontak << endl;
            temp = temp->next;
        } while (temp != headSupplier);
    }
}

struct TreeNode {
    string kategori;
    vector<TreeNode*> children;
};

TreeNode* rootKategori = new TreeNode{"Obat", {}};

void tambahKategori(TreeNode* parent, string kategori) {
    TreeNode* newNode = new TreeNode{kategori, {}};
    parent->children.push_back(newNode);
}

void tampilkanKategori(TreeNode* node, int depth = 0) {
    for (int i = 0; i < depth; ++i) cout << "-";
    cout << node->kategori << endl;
    for (TreeNode* child : node->children) {
        tampilkanKategori(child, depth + 1);
    }
}

class Graph {
    unordered_map<string, list<string>> adjList;
public:
    void tambahRute(string kota1, string kota2) {
        adjList[kota1].push_back(kota2);
        adjList[kota2].push_back(kota1);
    }

    void tampilkanRute() {
        for (auto& pair : adjList) {
            cout << pair.first << " -> ";
            for (string& kota : pair.second) {
                cout << kota << " ";
            }
            cout << endl;
        }
    }
};

Graph rutePengiriman;

int getNextId() {
    static int id = 0;
    return ++id;
}

void tambahTransaksi(Obat obat, int jumlah) {
    Transaksi transaksi;
    transaksi.id = getNextId();
    transaksi.obat = obat;
    transaksi.jumlah = jumlah;
    transaksi.total = obat.harga * jumlah;
    transaksi.waktu = time(0);
    daftarTransaksi.push_back(transaksi);

    daftarObat[obat.id].stok -= jumlah;
}

void menu() {
    cout << "\nMenu:" << endl;
    cout << "1. Tambah Antrian Pelanggan" << endl;
    cout << "2. Layani Pelanggan" << endl;
    cout << "3. Tambah Transaksi" << endl;
    cout << "4. Tampilkan Riwayat Transaksi" << endl;
    cout << "5. Tambah Obat" << endl;
    cout << "6. Tampilkan Obat" << endl;
    cout << "7. Tambah Supplier" << endl;
    cout << "8. Tampilkan Supplier" << endl;
}

int main() {
    int pilihan;
    do {
        menu();
        cout << "Pilihan Menu: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1: {
                string nama;
                cout << "Nama Pelanggan: ";
                getline(cin, nama);
                tambahAntrianPelanggan(nama);
                break;
            }
            case 2: {
                layaniPelanggan();
                break;
            }
            case 3: {
                int idObat, jumlah;
                cout << "Masukkan ID Obat: ";
                cin >> idObat;
                cout << "Masukkan Jumlah: ";
                cin >> jumlah;

                if (daftarObat.find(idObat) != daftarObat.end() && daftarObat[idObat].stok >= jumlah) {
                    tambahTransaksi(daftarObat[idObat], jumlah);
                } else {
                    cout << "Obat tidak ditemukan atau stok tidak cukup." << endl;
                }
                break;
            }
            case 4: {
                tampilkanRiwayatTransaksi();
                break;
            }
            case 5: {
                Obat obat;
                obat.id = getNextId();
                cout << "Nama Obat: ";
                getline(cin, obat.nama);
                cout << "Jenis Obat: ";
                getline(cin, obat.jenis);
                cout << "Stok: ";
                cin >> obat.stok;
                cout << "Harga: ";
                cin >> obat.harga;
                tambahObat(obat);
                break;
            }
            case 6: {
                tampilkanObat();
                break;
            }
            case 7: {
                Supplier supplier;
                supplier.id = getNextId();
                cout << "Nama Supplier: ";
                getline(cin, supplier.nama);
                cout << "Kontak Supplier: ";
                getline(cin, supplier.kontak);
                tambahSupplier(supplier);
                break;
            }
            case 8: {
                tampilkanSupplier();
                break;
            }
            default: {
                cout << "Pilihan tidak valid." << endl;
            }
        }
    } while (pilihan != 0);
    cout << "Program selesai." << endl;

    return 0;
}
