#include <iostream>
#include "DLL.hh"


int main()
{
    using namespace std;

    DList<Packet<int>> lista;
    lista.append(Packet<int>(69,420));
    lista.append(Packet<int>(1,2));
    lista.append(Packet<int>(3,4));
    // lista.append(Packet<int>(5,6));

    cout << lista.get(1)->getNext()->readData()->getContent() << endl;
    cout << lista.get(1)->getPrev()->readData()->getContent() << endl;


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