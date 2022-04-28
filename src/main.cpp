#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <random>
#include "read_csv.hh"
#include "sortingAlgos.hh"

void Test_dll_methods()
{
    using namespace std;

    DList<Packet<string>> lista3;
    DList<Packet<string>> lista4;
    std::filesystem::path path = "/run/media/aleksander/D/SharedWithManjaro/SEM4/PAMSI/Projekt2/dane/test.csv";

    int n_ent = 10000; //17 is the equilibriom point

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> creation(1, 10000);
    uniform_int_distribution<int> swaping(0, n_ent-1);

    // read_csv(path, lista3);
    // read_csv(path, lista4);
    for (int i=0; i<n_ent; i++)
    {
        lista3.append(Packet<string>("chuj", creation(rng)));
        lista4.append(Packet<string>("chuj", creation(rng)));
    }

    auto startqs = chrono::high_resolution_clock::now();
    QuickSort(lista3);
    auto stopqs = chrono::high_resolution_clock::now();
    cout << (chrono::duration<double>(stopqs - startqs).count())*1000 << endl;

    // auto startms = chrono::high_resolution_clock::now();
    // MergeSort(lista4);
    // auto stopms = chrono::high_resolution_clock::now();
    // cout << (chrono::duration<double>(stopms - startms).count())*1000 << endl;

    // auto start1 = chrono::high_resolution_clock::now();
    // for (int i=0; i<n_ent; i++)
    // {
    //     lista3.swp(swaping(rng), swaping(rng));
        
    // }
    // auto stop1 = chrono::high_resolution_clock::now();
    // cout << (chrono::duration<float>(stop1 - start1).count())*1000 << endl;

    // auto start2 = chrono::high_resolution_clock::now();
    // for (int i=0; i<n_ent; i++)
    // {
    //     lista3.get(swaping(rng));
    // }
    // auto stop2 = chrono::high_resolution_clock::now();
    // cout << (chrono::duration<float>(stop2 - start2).count())*1000 << endl;
}

int main()
{
    using namespace std;
    
    std::filesystem::path path = "/run/media/aleksander/D/SharedWithManjaro/SEM4/PAMSI/Projekt2/dane/test.csv";
    DList<Packet<string>> lista1;
    DList<Packet<string>> lista2;


    // for (int i=0; i < lista1.len(); i++)
    // {
    //     cout << lista1.get(i)->readData()->getContent() << ", " << lista1.get(i)->readData()->getRank() << endl;
    // }
    // cout << "-------------\n";

    // Test_dll_methods();

    // read_csv(path, lista2);
    // auto start2 = chrono::high_resolution_clock::now();
    // MergeSort(lista2);
    // auto stop2 = chrono::high_resolution_clock::now();
    // cout << (chrono::duration<float>(stop2 - start2).count())*1000 << endl;





    DList<Packet<string>> l;
    l.append(Packet<string>("a", 1)); //0
    l.append(Packet<string>("b", 2));
    l.append(Packet<string>("c", 3));
    l.append(Packet<string>("b", 2)); //3
    l.append(Packet<string>("g", 5));
    l.append(Packet<string>("h", 7));
    l.append(Packet<string>("x", 8)); //6
    l.append(Packet<string>("z", 6));

    // l.swp(1,4);

    QuickSort(l);

    for (int i=0; i < l.len(); i++)
    {
        cout << l.get(i)->readData()->getRank() << endl;
    }


    return 0;
}
