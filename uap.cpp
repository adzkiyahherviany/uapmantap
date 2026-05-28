#include <iostream>

using namespace std;

// Struct node untuk menyimpan data rumah user
struct Node {
    int idUser;
    string namaPelanggan;

    float temperature;
    float humidity;
    int airQuality;
    int smoke;
    float noise;

    int monitoringScore;
    string statusRumah;

    Node *next;
};

class MonitoringIoT {
private:
    Node *pHead;

public:
    // Constructor default
    MonitoringIoT() {
        pHead = NULL;
    }

    // =========================
    // Menghitung monitoring score
    // =========================
    int hitungScore(Node *node) {
        int jumlahIdeal = 0;

        // cek temperature ideal
        if (node->temperature >= 20 && node->temperature <= 27)
            jumlahIdeal++;

        // cek humidity ideal
        if (node->humidity >= 40 && node->humidity <= 60)
            jumlahIdeal++;

        // cek air quality ideal
        if (node->airQuality >= 0 && node->airQuality <= 50)
            jumlahIdeal++;

        // cek smoke ideal
        if (node->smoke == 0)
            jumlahIdeal++;

        // cek noise ideal
        if (node->noise >= 30 && node->noise <= 55)
            jumlahIdeal++;

        // rumus monitoring score
        return (jumlahIdeal * 100) / 5;
    }

    // =========================
    // Fitur tambahan
    // menentukan status rumah
    // =========================
    string cekStatusRumah(int score) {

        // kondisi rumah aman
        if (score >= 81)
            return "AMAN";

        // kondisi rumah cukup
        else if (score >= 61)
            return "CUKUP";

        // kondisi rumah waspada
        else if (score >= 41)
            return "WASPADA";

        // kondisi rumah berbahaya
        else
            return "BERBAHAYA";
    }

    // =========================
    // Validasi range sensor
    // =========================
    bool validasiSensor(float temp, float hum, int air,
                        int smoke, float noise) {

        if (temp < -10 || temp > 50)
            return false;

        if (hum < 0 || hum > 100)
            return false;

        if (air < 0 || air > 500)
            return false;

        if (!(smoke == 0 || smoke == 1))
            return false;

        if (noise < 0 || noise > 120)
            return false;

        return true;
    }

    // =========================
    // Mengecek ID duplicate
    // =========================
    bool cekId(int idCari) {
        Node *temp = pHead;

        while (temp != NULL) {

            if (temp->idUser == idCari)
                return true;

            temp = temp->next;
        }

        return false;
    }

    // =========================
    // Menambahkan user baru
    // =========================
    void tambahUser() {

        Node *pNodeBaru = new Node;

        cout << "\nMasukkan ID User : ";
        cin >> pNodeBaru->idUser;

        // validasi duplicate ID
        if (cekId(pNodeBaru->idUser)) {
            cout << "\n## ID User sudah digunakan";
            return;
        }

        cin.ignore();

        cout << "Masukkan Nama Pelanggan : ";
        getline(cin, pNodeBaru->namaPelanggan);

        cout << "Masukkan Temperature : ";
        cin >> pNodeBaru->temperature;

        cout << "Masukkan Humidity : ";
        cin >> pNodeBaru->humidity;

        cout << "Masukkan Air Quality : ";
        cin >> pNodeBaru->airQuality;

        cout << "Masukkan Smoke (0/1) : ";
        cin >> pNodeBaru->smoke;

        cout << "Masukkan Noise : ";
        cin >> pNodeBaru->noise;

        // validasi range sensor
        if (!validasiSensor(
            pNodeBaru->temperature,
            pNodeBaru->humidity,
            pNodeBaru->airQuality,
            pNodeBaru->smoke,
            pNodeBaru->noise)) {

            cout << "\n## Data sensor tidak valid";
            return;
        }

        // hitung monitoring score
        pNodeBaru->monitoringScore = hitungScore(pNodeBaru);

        // menentukan status rumah
        pNodeBaru->statusRumah =
            cekStatusRumah(pNodeBaru->monitoringScore);

        pNodeBaru->next = NULL;

        // insert node
        if (pHead == NULL) {
            pHead = pNodeBaru;
        }
        else {

            Node *temp = pHead;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = pNodeBaru;
        }

        cout << "\n## Berhasil menambahkan pelanggan baru";
        cout << "\nUser ID          : " << pNodeBaru->idUser;
        cout << "\nNama Pelanggan   : "
             << pNodeBaru->namaPelanggan;
        cout << "\nMonitoring Score : "
             << pNodeBaru->monitoringScore << "%";
        cout << "\nStatus Rumah     : "
             << pNodeBaru->statusRumah << endl;
    }

    // =========================
    // Mencari user berdasarkan ID
    // =========================
    void cariUser() {

        int idCari;

        cout << "\nMasukkan ID User yang dicari : ";
        cin >> idCari;

        Node *temp = pHead;

        // traversal mencari user
        while (temp != NULL) {

            if (temp->idUser == idCari) {

                cout << "\n## User ditemukan";
                cout << "\nUser ID          : "
                     << temp->idUser;

                cout << "\nNama Pelanggan   : "
                     << temp->namaPelanggan;

                cout << "\nMonitoring Score : "
                     << temp->monitoringScore << "%";

                cout << "\nStatus Rumah     : "
                     << temp->statusRumah;

                cout << "\nTemperature      : "
                     << temp->temperature;

                cout << "\nHumidity         : "
                     << temp->humidity;

                cout << "\nAir Quality      : "
                     << temp->airQuality;

                cout << "\nSmoke            : "
                     << temp->smoke;

                cout << "\nNoise            : "
                     << temp->noise << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "\n## User tidak ditemukan";
    }

    // =========================
    // Update data user
    // =========================
    void updateUser() {

        int idCari;

        cout << "\nMasukkan ID User yang diupdate : ";
        cin >> idCari;

        Node *temp = pHead;

        while (temp != NULL) {

            if (temp->idUser == idCari) {

                cin.ignore();

                cout << "Masukkan Nama Baru : ";
                getline(cin, temp->namaPelanggan);

                cout << "Masukkan Temperature Baru : ";
                cin >> temp->temperature;

                cout << "Masukkan Humidity Baru : ";
                cin >> temp->humidity;

                cout << "Masukkan Air Quality Baru : ";
                cin >> temp->airQuality;

                cout << "Masukkan Smoke Baru : ";
                cin >> temp->smoke;

                cout << "Masukkan Noise Baru : ";
                cin >> temp->noise;

                // validasi sensor
                if (!validasiSensor(
                    temp->temperature,
                    temp->humidity,
                    temp->airQuality,
                    temp->smoke,
                    temp->noise)) {

                    cout << "\n## Data sensor tidak valid";
                    return;
                }

                // hitung ulang score
                temp->monitoringScore = hitungScore(temp);

                // update status rumah
                temp->statusRumah =
                    cekStatusRumah(temp->monitoringScore);

                cout << "\n## User berhasil diupdate";
                cout << "\nMonitoring Score Baru : "
                     << temp->monitoringScore << "%";

                cout << "\nStatus Rumah Baru     : "
                     << temp->statusRumah << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "\n## User tidak ditemukan";
    }

    // =========================
    // Menghapus user
    // =========================
    void hapusUser() {

        int idCari;

        cout << "\nMasukkan ID User yang dihapus : ";
        cin >> idCari;

        // linked list kosong
        if (pHead == NULL) {
            cout << "\n## Data kosong";
            return;
        }

        Node *temp = pHead;
        Node *prev = NULL;

        while (temp != NULL &&
               temp->idUser != idCari) {

            prev = temp;
            temp = temp->next;
        }

        // user tidak ditemukan
        if (temp == NULL) {
            cout << "\n## User tidak ditemukan";
            return;
        }

        // hapus head
        if (prev == NULL) {
            pHead = temp->next;
        }

        // hapus tengah/belakang
        else {
            prev->next = temp->next;
        }

        delete temp;

        cout << "\n## User berhasil dihapus";
    }

    // =========================
    // Sorting ascending score
    // menggunakan bubble sort manual
    // =========================
// bagian sorting sebelumnya menggunakan swap()
// diganti manual supaya benar-benar tanpa STL
// dan lebih sesuai gaya praktikum ASD

void sortingScore() {

    if (pHead == NULL)
        return;

    bool swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {

        swapped = false;
        ptr1 = pHead;

        while (ptr1->next != lptr) {

            if (ptr1->monitoringScore >
                ptr1->next->monitoringScore) {

                // =========================
                // swap manual idUser
                // =========================
                int tempId =
                    ptr1->idUser;

                ptr1->idUser =
                    ptr1->next->idUser;

                ptr1->next->idUser =
                    tempId;

                // =========================
                // swap manual nama pelanggan
                // =========================
                string tempNama =
                    ptr1->namaPelanggan;

                ptr1->namaPelanggan =
                    ptr1->next->namaPelanggan;

                ptr1->next->namaPelanggan =
                    tempNama;

                // =========================
                // swap manual temperature
                // =========================
                float tempTemperature =
                    ptr1->temperature;

                ptr1->temperature =
                    ptr1->next->temperature;

                ptr1->next->temperature =
                    tempTemperature;

                // =========================
                // swap manual humidity
                // =========================
                float tempHumidity =
                    ptr1->humidity;

                ptr1->humidity =
                    ptr1->next->humidity;

                ptr1->next->humidity =
                    tempHumidity;

                // =========================
                // swap manual air quality
                // =========================
                int tempAir =
                    ptr1->airQuality;

                ptr1->airQuality =
                    ptr1->next->airQuality;

                ptr1->next->airQuality =
                    tempAir;

                // =========================
                // swap manual smoke
                // =========================
                int tempSmoke =
                    ptr1->smoke;

                ptr1->smoke =
                    ptr1->next->smoke;

                ptr1->next->smoke =
                    tempSmoke;

                // =========================
                // swap manual noise
                // =========================
                float tempNoise =
                    ptr1->noise;

                ptr1->noise =
                    ptr1->next->noise;

                ptr1->next->noise =
                    tempNoise;

                // =========================
                // swap monitoring score
                // =========================
                int tempScore =
                    ptr1->monitoringScore;

                ptr1->monitoringScore =
                    ptr1->next->monitoringScore;

                ptr1->next->monitoringScore =
                    tempScore;

                // =========================
                // swap status rumah
                // =========================
                string tempStatus =
                    ptr1->statusRumah;

                ptr1->statusRumah =
                    ptr1->next->statusRumah;

                ptr1->next->statusRumah =
                    tempStatus;

                swapped = true;
            }

            ptr1 = ptr1->next;
        }

        lptr = ptr1;

    } while (swapped);
}

    // =========================
    // Menampilkan laporan
    // =========================
    void showLaporan() {

        if (pHead == NULL) {
            cout << "\n## Data masih kosong";
            return;
        }

        // sorting ascending
        sortingScore();

        Node *temp = pHead;

        int totalUser = 0;
        int totalScore = 0;

        int tempIdeal = 0;
        int humIdeal = 0;
        int airIdeal = 0;
        int smokeIdeal = 0;
        int noiseIdeal = 0;

        // traversal statistik
        while (temp != NULL) {

            totalUser++;

            totalScore += temp->monitoringScore;

            if (temp->temperature >= 20 &&
                temp->temperature <= 27)
                tempIdeal++;

            if (temp->humidity >= 40 &&
                temp->humidity <= 60)
                humIdeal++;

            if (temp->airQuality >= 0 &&
                temp->airQuality <= 50)
                airIdeal++;

            if (temp->smoke == 0)
                smokeIdeal++;

            if (temp->noise >= 30 &&
                temp->noise <= 55)
                noiseIdeal++;

            temp = temp->next;
        }

        cout << "\n===================================";
        cout << "\nLAPORAN MONITORING IOT";
        cout << "\n===================================";

        cout << "\n\nTotal Pelanggan : "
             << totalUser;

        cout << "\nRata-rata Score : "
             << totalScore / totalUser << "%";

        cout << "\n\nRekap Sensor Ideal";
        cout << "\nTemperature : "
             << tempIdeal << " rumah";

        cout << "\nHumidity    : "
             << humIdeal << " rumah";

        cout << "\nAir Quality : "
             << airIdeal << " rumah";

        cout << "\nSmoke       : "
             << smokeIdeal << " rumah";

        cout << "\nNoise       : "
             << noiseIdeal << " rumah";

        temp = pHead;

        int ranking = 1;

        // menampilkan ranking rumah
        while (temp != NULL) {

            cout << "\n\n-----------------------------------";

            cout << "\nPeringkat "
                 << ranking;

            cout << "\nUser ID          : "
                 << temp->idUser;

            cout << "\nNama Pelanggan   : "
                 << temp->namaPelanggan;

            cout << "\nMonitoring Score : "
                 << temp->monitoringScore << "%";

            cout << "\nStatus Rumah     : "
                 << temp->statusRumah;

            cout << "\n\nData Sensor";

            cout << "\nTemperature : "
                 << temp->temperature;

            cout << "\nHumidity    : "
                 << temp->humidity;

            cout << "\nAir Quality : "
                 << temp->airQuality;

            cout << "\nSmoke       : "
                 << temp->smoke;

            cout << "\nNoise       : "
                 << temp->noise;

            ranking++;
            temp = temp->next;
        }

        cout << endl;
    }

    // =========================
    // Destructor
    // =========================
    ~MonitoringIoT() {

        Node *pKini = pHead;

        while (pKini != NULL) {

            Node *next = pKini->next;

            delete pKini;

            pKini = next;
        }

        pHead = NULL;
    }
};

int main() {

    MonitoringIoT sistem;

    int choice;
    int keluar = 0;

    do {

        cout << "\n===================================";
        cout << "\n SISTEM MONITORING RUMAH IoT";
        cout << "\n===================================";

        cout << "\n1. Tambah User";
        cout << "\n2. Cari User";
        cout << "\n3. Update User";
        cout << "\n4. Hapus User";
        cout << "\n5. Show Laporan";
        cout << "\n6. Keluar";

        cout << "\n\nMasukkan pilihan : ";
        cin >> choice;

        switch (choice) {

            case 1:
                sistem.tambahUser();
                break;

            case 2:
                sistem.cariUser();
                break;

            case 3:
                sistem.updateUser();
                break;

            case 4:
                sistem.hapusUser();
                break;

            case 5:
                sistem.showLaporan();
                break;

            case 6:
                keluar = 1;
                cout << "\n## Program selesai";
                break;

            default:
                cout << "\n## Pilihan tidak tersedia";
                break;
        }

    } while (keluar == 0);

    return 0;
}