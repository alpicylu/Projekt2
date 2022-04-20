#include <iostream>
#include <string>
#include "read_csv.hh"

int main()
{
    using namespace std;
    
    string path = "/run/media/aleksander/D/SharedWithManjaro/SEM4/PAMSI/Projekt2/dane/dane.csv";

    shared_ptr<DList<Packet<string>>> lista = read_csv(path);
    cout << lista->len() << endl;
    for (int i = 6000; i < 6010; i++)
    {
        cout << lista->get(i)->readData()->getContent() << ", " << lista->get(i)->readData()->getRank() << endl;
    }
    cout << "-------------\n";

}

/*    string row = "asd";
    cout << row << endl;
    ifstream fin;
    fin.open(path, ios::in);
    if (fin.is_open()) {cout << "klawaitura" << endl;}
    getline(fin, row);

    cout << row;
    fin.close();*/