#include <iostream>
#include <fstream>
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

//membaca data dari file dan di tampilkan
void outputdata(){}

//searching data berdasarkan nisn
void searchdata(){}

//menampilkan data berdasarkan rankingnya
void rank(){}

int main (){
    int n=0, i;
    siswa data[100];
    adddata(data, n);

    return 0;
}
