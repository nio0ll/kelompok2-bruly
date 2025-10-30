#include <iostream>
#include <fstream>
#include <string>
using namespace std;


//tipe nilai
struct nilais{
    float mtk;
    float bin;
    float bing;
    float ipa;
    float akhir;
};

//tipe data siswa
struct siswa{
    string nama;
    string nisn;
    string jurusan;
    nilais nilai;
};

//rumus nilaiakhir = mtk*0.4 + ipa*0.3 + bin*0.2 + bing*0.2
float nilaiakhir(nilais i){
    return (i.mtk*0.4 + i.ipa*0.3 + i.bin*0.2 + i.bing*0.2);
}

//tambah data pada file
void adddata(siswa data[], int n){
    ofstream fileOutput("zaraseva.txt",ios::app);
    cout << "jumlah siswa? ";
            cin >> n;
            cin.ignore();
    for (int i=0;i<n;i++){
        // nama
        cout << "Data ke- " << i+1 << "\n";
        cout << "Nisn\t: ";
        cin >> data[i].nisn;
        cin.ignore();
        cout << "Nama\t: ";
        getline(cin, data[i].nama);
        cout << "Jurusan\t: ";
        getline(cin, data[i].jurusan);
        // nilai
        cout << "Nilai MTK\t: ";
        cin >> data[i].nilai.mtk;
        cin.ignore();
        cout << "Nilai B.IND\t: ";
        cin >> data[i].nilai.bin;
        cin.ignore();
        cout << "Nilai B.ING\t: ";
        cin >> data[i].nilai.bing;
        cin.ignore();
        cout << "Nilai IPA\t: ";
        cin >> data[i].nilai.ipa;
        cin.ignore();
        cout << endl;
        //menyimpan nilai akhir
        data[i].nilai.akhir = nilaiakhir(data[i].nilai);
    }
    if (fileOutput.is_open()){
        for (int i=0;i<n;i++){
            fileOutput << endl << data[i].nisn << " | " << data[i].nama << " | " << data[i].jurusan << endl;
            fileOutput << "Nilai MTK\t: " << data[i].nilai.mtk << "\nNilai B.IND\t: " << data[i].nilai.bin 
                       << "\nNilai B.ING\t: " << data[i].nilai.bing << "\nNilai IPA\t: " << data[i].nilai.ipa
                       << "\nNilai Akhir\t: " << data[i].nilai.akhir << endl;
    }
        fileOutput.close();
        cout<<"data berhasil dikirim!\n";
    }
    else{
        cout<<"data gagal dikirim!\n";
    }
        
}

//membaca data dari file dan di tampilkann
void outputdata(){
    ifstream fileInput("zaraseva.txt");
    if (fileInput.is_open()) {
        string line;
        cout << "\n DAFTAR DATA SISWA \n";
        while (getline(fileInput, line)) {
            cout << line << endl;
        }
        cout << "\n file berhasil dibaca \n";
        fileInput.close();
    }
    else {
        cout << "file gagal dibuka" << endl;
    }
}

//searching data berdasarkan nisn
void searchdata(){
    ifstream fileInput("zaraseva.txt");
    if(fileInput.is_open()){
        siswa cari;
        string carinisn, teks;
        bool ketemu = false;
        cout << "input NISN yang dicari: ";
        cin >> carinisn;
        while (fileInput >> cari.nisn) {
            //getline(fileInput, cari.nisn, '|');
            fileInput.ignore(1000, '|');
            fileInput.ignore();
            getline(fileInput, cari.nama, '|'); 
            fileInput.ignore();
            getline(fileInput, cari.jurusan); 
            
            fileInput >> teks >> teks >> teks >> cari.nilai.mtk 
                      >> teks >> teks >> teks >> cari.nilai.bin
                      >> teks >> teks >> teks >> cari.nilai.bing 
                      >> teks >> teks >> teks >> cari.nilai.ipa
                      >> teks >> teks >> teks >> cari.nilai.akhir;
            fileInput.ignore(); 

            if(cari.nisn == carinisn) {
                cout << "\nData Ditemukan!";
                cout << "\nNISN\t: " << cari.nisn
                     << "\nNama\t: " << cari.nama
                     << "\nJurusan\t: " << cari.jurusan
                     << "\nNilai MTK\t: " << cari.nilai.mtk
                     << "\nNilai B.IND\t: " << cari.nilai.bin
                     << "\nNilai B.ING\t: " << cari.nilai.bing
                     << "\nNilai IPA\t: " << cari.nilai.ipa
                     << "\nNilai Akhir\t: " << cari.nilai.akhir << endl;
                ketemu = true;
                break;
            }
        }
        if(!ketemu) cout << "data " << carinisn << " tidak ditemukan.\n";
        cout << "file berhasil dibuka!\n";
        fileInput.close();
    }
    else{
        cout<<"file gagal dibuka!\n";
    }
}

//menampilkan data berdasarkan rankingnya
void ranking() {
    ifstream fileInput ("zaraseva.txt");
    if (!fileInput.is_open()) {
        cout << "file gagal dibuka" << endl;
        return;
    }

    siswa data [100];
    int n=0;
    string line;
    
    //baca data
    while (getline(fileInput, line)) {
        if (line.empty()) continue;

        //ambil data
        size_t pos1 = line.find ("|");
        size_t pos2 = line.find ("|", pos1 + 3);
        if (pos1 == string ::npos || pos2 == string::npos) continue;

        data[n].nisn =line.substr(0, pos1);
        data[n].nama = line.substr (pos1 + 3, pos2 - (pos1 + 3));
        data[n].jurusan = line.substr(pos2 + 3);

        //baca 5 nilai
        getline(fileInput, line);
        data[n].nilai.mtk = stof(line.substr(line.find(":") + 1));
        getline(fileInput, line);
        data[n].nilai.bin = stof(line.substr(line.find(":") + 1));
        getline(fileInput, line);
        data[n].nilai.bing = stof(line.substr(line.find(":") + 1));
        getline(fileInput, line);
        data[n].nilai.ipa = stof(line.substr(line.find(":") + 1));
        getline(fileInput, line);
        data[n].nilai.akhir = stof(line.substr(line.find(":") + 1));
        n++;
    }

    fileInput.close();

    if (n == 0) {
        cout << "tidak ada";
        return;
    }

    //urutan data (bubble sort descending)
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (data[j].nilai.akhir < data[j+1].nilai.akhir) {
                siswa T = data[j];
                data[j] = data[j + 1];
                data [j + 1] = T;
            }
        }
    }

    //tampil rank
    cout << "\n DATA BERDASARKAN RANKING \n";
    for (int i=0; i<n; i++) {
        cout << "Ranking ke-" << i+1 << endl;
        cout << "NISN\t : " << data[i].nisn << endl;
        cout << "Nama\t : " << data[i].nama << endl;
        cout << "Jurusan\t : " << data[i].jurusan << endl;
        cout << "Nilai akhir\t : " << data[i].nilai.akhir << endl;
    }
}

int main (){
    int n, menu;
    siswa data[100];
    do{
        cout << "\nPROGRAM DATA SISWA\n1. tambah data siswa \n2. daftar data siswa\n3. ranking \n4. cari nisn \n5. keluar"
             << "\ninput MENU: ";
        cin >> menu; 

        cin.ignore();

        if (menu==1){
            cout << "\ntambah data siswa\n";
            adddata(data, n);
        }
        if (menu==2){
            cout << "\ndaftar data siswa\n";
            outputdata();
        }
        if (menu==3){
            cout << "\ncari data siswa\n";
            ranking();
        }
        if (menu==4){
            cout << "\ncari data siswa\n";
            searchdata();
        }
    } while (menu!=5);

    return 0;
}
