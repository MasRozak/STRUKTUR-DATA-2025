#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int id;
    string namaInfrastruktur;
    int perkiraanPengguna;
    int persenKerusakan;
    string lokasi;
    Node* next;

    Node(int id, string nama, int pengguna, int kerusakan, string lokasi) {
        this->id = id;
        this->namaInfrastruktur = nama;
        this->perkiraanPengguna = pengguna;
        this->persenKerusakan = kerusakan;
        this->lokasi = lokasi;
        this->next = NULL;
    }
};

void swapNodes(Node* a, Node* b) {
    swap(a->id, b->id);
    swap(a->namaInfrastruktur, b->namaInfrastruktur);
    swap(a->perkiraanPengguna, b->perkiraanPengguna);
    swap(a->persenKerusakan, b->persenKerusakan);
    swap(a->lokasi, b->lokasi);
}

void bubbleSort(Node* head) {
    if (!head) return;

    int swapped;
    Node* ptr;
    Node* last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->perkiraanPengguna < ptr->next->perkiraanPengguna) {
                swapNodes(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);
}

Node* copyList(Node* head) {
    if (!head) return NULL;

    Node* newHead = new Node(head->id, head->namaInfrastruktur, head->perkiraanPengguna, head->persenKerusakan, head->lokasi);
    Node* temp = newHead;
    Node* curr = head->next;

    while (curr) {
        temp->next = new Node(curr->id, curr->namaInfrastruktur, curr->perkiraanPengguna, curr->persenKerusakan, curr->lokasi);
        temp = temp->next;
        curr = curr->next;
    }
    return newHead;
}

Node* partition(Node* originalHead, int batas = 50) {
    if (!originalHead) return NULL;

    Node* head = copyList(originalHead);

    Node *minorHead = new Node(0, "", 0, 0, ""),
        *moderateHead = new Node(0, "", 0, 0, ""),
        *severeHead = new Node(0, "", 0, 0, "");

    Node *minor = minorHead, *moderate = moderateHead, *severe = severeHead;
    Node* curr = head;

    while (curr != NULL) {
        if (curr->persenKerusakan < batas) {
            minor->next = curr;
            minor = minor->next;
        } else if (curr->persenKerusakan == batas) {
            moderate->next = curr;
            moderate = moderate->next;
        } else {
            severe->next = curr;
            severe = severe->next;
        }
        curr = curr->next;
    }

    minor->next = NULL;
    moderate->next = NULL;
    severe->next = NULL;

    bubbleSort(severeHead->next);

    if (moderateHead->next) {
        severe->next = moderateHead->next;
        moderate->next = minorHead->next;
    } else {
        severe->next = minorHead->next;
    }

    Node* newHead = (severeHead->next) ? severeHead->next :
                    (moderateHead->next) ? moderateHead->next : minorHead->next;

    delete minorHead;
    delete moderateHead;
    delete severeHead;

    return newHead;
}

void printList(Node* head) {
    if (!head) {
        cout << "\nBelum ada laporan yang terdaftar.\n";
        return;
    }

    cout << "\n=== Daftar Laporan Kerusakan ===\n";
    Node* curr = head;
    while (curr != NULL) {
        cout << "ID Laporan      : " << curr->id << "\n";
        cout << "Infrastruktur   : " << curr->namaInfrastruktur << "\n";
        cout << "Pengguna Harian : " << curr->perkiraanPengguna << "\n";
        cout << "Kerusakan       : " << curr->persenKerusakan << "%\n";
        cout << "Lokasi          : " << curr->lokasi << "\n";
        cout << "--------------------------\n";
        curr = curr->next;
    }
}

void append(Node*& head, int id, string nama, int pengguna, int kerusakan, string lokasi) {
    Node* newNode = new Node(id, nama, pengguna, kerusakan, lokasi);
    if (!head) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

int main() {
    Node* head = NULL;
    int laporanKe = 1;
    int pilihan;

    cout << "=========================================\n";
    cout << "  Sistem Laporan Kerusakan Infrastruktur \n";
    cout << "=========================================\n";

    do {
        cout << "\nMENU:\n";
        cout << "1. Tambahkan Laporan Kerusakan\n";
        cout << "2. Tampilkan Laporan Setelah Diprioritaskan\n";
        cout << "3. Tampilkan Laporan Berdasarkan Urutan Masuk\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string nama, lokasi;
            int pengguna, kerusakan;

            cout << "\n=== Laporan Kerusakan ke-" << laporanKe << " ===\n";
            cout << "Nama Infrastruktur   : "; getline(cin, nama);
            cout << "Perkiraan Pengguna   : "; cin >> pengguna;
            cin.ignore();
            cout << "Persentase Kerusakan : "; cin >> kerusakan;
            cin.ignore();
            cout << "Lokasi              : "; getline(cin, lokasi);

            append(head, laporanKe, nama, pengguna, kerusakan, lokasi);
            laporanKe++;

            cout << "\nLaporan berhasil ditambahkan!\n";

        } else if (pilihan == 2) {
            Node* sortedHead = partition(head, 50);
            printList(sortedHead);
        } else if (pilihan == 3) {
            printList(head);
        } else if (pilihan == 4) {
            cout << "\nTerima kasih telah menggunakan sistem laporan!\n";
        } else {
            cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 4);

    return 0;
}
