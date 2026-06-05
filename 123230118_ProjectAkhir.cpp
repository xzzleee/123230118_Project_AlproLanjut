#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>

using namespace std;

struct Mahasiswa {
    char nim[12];
    char nama[50];
    float uts, uas, tugas;
    float akhir;
    char grade;
};

const int MAX = 100;
Mahasiswa mhs[MAX];
int n = 0;

// ================= HITUNG NILAI =================
float hitungAkhir(float uts, float uas, float tugas) {
    return (0.3 * uts) + (0.4 * uas) + (0.3 * tugas);
}

char hitungGrade(float nilai) {
    if (nilai >= 85) return 'A';
    if (nilai >= 70) return 'B';
    if (nilai >= 55) return 'C';
    if (nilai >= 40) return 'D';
    return 'E';
}

// ================= INPUT =================
void inputData() {
    if (n >= MAX) {
        cout << "Data penuh!\n";
        return;
    }

    cout << "\nNIM   : ";
    cin >> mhs[n].nim;

    cin.ignore();
    cout << "Nama  : ";
    cin.getline(mhs[n].nama, 50);

    cout << "UTS   : ";
    cin >> mhs[n].uts;

    cout << "UAS   : ";
    cin >> mhs[n].uas;

    cout << "Tugas : ";
    cin >> mhs[n].tugas;

    mhs[n].akhir = hitungAkhir(mhs[n].uts, mhs[n].uas, mhs[n].tugas);
    mhs[n].grade = hitungGrade(mhs[n].akhir);

    n++;

    cout << "Data masuk!\n";
}

// ================= TAMPIL =================
void tampilData() {
    if (n == 0) {
        cout << "Kosong!\n";
        return;
    }

    cout << "\nDATA MAHASISWA\n";
    cout << "-------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". "
             << mhs[i].nim << " | "
             << mhs[i].nama << " | "
             << mhs[i].akhir << " | "
             << mhs[i].grade << endl;
    }
}

// ================= SEARCH =================
void cariData() {
    char key[50];
    cout << "Cari NIM/Nama: ";
    cin >> key;

    for (int i = 0; i < n; i++) {
        if (strcmp(mhs[i].nim, key) == 0 || strstr(mhs[i].nama, key)) {
            cout << "Ditemukan: " << mhs[i].nama << " | " << mhs[i].akhir << endl;
            return;
        }
    }

    cout << "Tidak ditemukan!\n";
}

// ================= SORT (BUBBLE) =================
void bubbleSort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (mhs[j].akhir < mhs[j + 1].akhir) {
                Mahasiswa t = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = t;
            }
        }
    }
    cout << "Sudah diurutkan!\n";
}

// ================= POINTER =================
void demoPointer() {
    Mahasiswa *p = mhs;

    for (int i = 0; i < n; i++) {
        cout << (p + i)->nim << " - "
             << (p + i)->nama << " - "
             << (p + i)->akhir << endl;
    }
}

// ================= REKURSIF =================
float cariMax(int i) {
    if (i == n - 1) return mhs[i].akhir;

    float maxSisa = cariMax(i + 1);

    return (mhs[i].akhir > maxSisa) ? mhs[i].akhir : maxSisa;
}

// ================= FIXED SAVE FILE =================
void simpanFile() {
    FILE *f = fopen("data.dat", "wb");

    if (f == NULL) {
        cout << "Gagal buka file!\n";
        return;
    }

    fwrite(&n, sizeof(int), 1, f);
    fwrite(mhs, sizeof(Mahasiswa), n, f);

    fclose(f);

    cout << "Data tersimpan!\n";
}

// ================= FIXED LOAD FILE =================
void bacaFile() {
    FILE *f = fopen("data.dat", "rb");

    if (f == NULL) {
        cout << "File belum ada!\n";
        return;
    }

    fread(&n, sizeof(int), 1, f);

    if (n < 0 || n > MAX) {
        cout << "File rusak / tidak valid!\n";
        n = 0;
        fclose(f);
        return;
    }

    fread(mhs, sizeof(Mahasiswa), n, f);

    fclose(f);

    cout << "Data berhasil dibaca!\n";
}

// ================= MENU =================
int main() {
    int pilih;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Input\n2. Tampil\n3. Cari\n4. Sort\n5. Pointer\n6. Rekursif Max\n7. Save\n8. Load\n0. Exit\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: inputData(); break;
            case 2: tampilData(); break;
            case 3: cariData(); break;
            case 4: bubbleSort(); break;
            case 5: demoPointer(); break;
            case 6:
                if (n > 0)
                    cout << "Max nilai: " << cariMax(0) << endl;
                else
                    cout << "Kosong!\n";
                break;
            case 7: simpanFile(); break;
            case 8: bacaFile(); break;
        }

    } while (pilih != 0);

    return 0;
}