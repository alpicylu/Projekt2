#include <iostream>
#include "DLL.hh"


int main()
{
    using namespace std;

    DList<Packet<int>> lista;
    lista.append(Packet<int>(0,1)); //0
    lista.append(Packet<int>(2,3)); //6
    lista.append(Packet<int>(4,5)); //4
    lista.append(Packet<int>(6,7)); //2
    lista.append(Packet<int>(8,9)); //8

    //can i edit data returned by readData()? NO, and thats good. (it returns a ptr to const after all


    //print out the whole list:
    for (int i = 0; i < lista.len(); i++)
    {
        cout << lista.get(i)->readData()->getContent() << endl;
    }
    cout << "-------------\n";

    // lista.del(1);
    // for (int i = 0; i < lista.len(); i++)
    // {
    //     cout << lista.get(i)->readData()->getContent() << endl;
    // }
    // cout << "-------------\n";

    // lista.insert(2, Packet<int>(5,5));
    // for (int i = 0; i < lista.len(); i++)
    // {
    //     cout << lista.get(i)->readData()->getContent() << endl;
    // }
    lista.swap(4, 0);
    for (int i = 0; i < lista.len(); i++)
    {
        cout << lista.get(i)->readData()->getContent() << endl;
    }
    cout << "-------------\n";



}

    // Node<Packet<int>> knot;
    // Node<Packet<int>> knot2;
    // knot.setData(Packet<int>(69,1));
    // knot2.setData(Packet<int>(420, 12));
    // knot.setNext(knot2);

    // cout << knot.readData()->getContent() << endl;

    // cout << knot.getNext()->readData()->getContent();

    // knot.getNext()->setData(Packet<int>(1,2));

    // cout << knot.getNext()->readData()->getContent();