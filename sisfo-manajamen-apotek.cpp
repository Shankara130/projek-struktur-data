#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
#include <list>

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
}

void tampilkanObat() {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->data.id << ", Nama: " << temp->data.nama << "\n";
        temp = temp->next;
    }
}

struct DoubleNode {
    Obat data;
    DoubleNode* next;
    DoubleNode* prev;
};

DoubleNode* headSupplier = nullptr;

void tambahSupplier(Obat obat) {
    DoubleNode* newNode = new DoubleNode{obat, nullptr, nullptr};
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
            cout << "ID: " << temp->data.id << ", Nama: " << temp->data.nama << "\n";
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
    cout << node->kategori << "\n";
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
            cout << "\n";
        }
    }
};

Graph rutePengiriman;

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

    // Contoh penggunaan single linked list non circular
    tambahObat(paracetamol);
    tambahObat(ibuprofen);
    tampilkanObat();

    // Contoh penggunaan double linked list circular
    tambahSupplier(paracetamol);
    tambahSupplier(ibuprofen);
    tampilkanSupplier();

    // Contoh penggunaan tree
    TreeNode* obatKeras = new TreeNode{"Obat Keras", {}};
    tambahKategori(rootKategori, "Obat Keras");
    tambahKategori(obatKeras, "Antibiotik");
    tambahKategori(obatKeras, "Analgesik");
    tampilkanKategori(rootKategori);

    // Contoh penggunaan graph
    rutePengiriman.tambahRute("Jakarta", "Bandung");
    rutePengiriman.tambahRute("Bandung", "Surabaya");
    rutePengiriman.tambahRute("Jakarta", "Surabaya");
    rutePengiriman.tampilkanRute();

    return 0;
}
