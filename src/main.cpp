#include <iostream>
#include "DLL.hh"


int main()
{
    using namespace std;

    Node<int> knot;
    Node<int> knot2;
    knot.setData(Packet<int>(69,1));
    knot2.setData(Packet<int>(420, 12));
    knot.setNext(knot2);

    cout << knot.readData()->getContent() << endl;

    cout << knot.getNext()->readData()->getContent();

    knot.getNext()->setData(Packet<int>(1,2));

    cout << knot.getNext()->readData()->getContent();
}