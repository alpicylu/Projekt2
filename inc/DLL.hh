#ifndef DLL_HH
#define DLL_HH

#include <memory>
#include "packet.hh"


/* the following implementation of list nodes will be able to point to any data type (because its generic).
    This will provide easier portability in future project as well as more flexibility - Nodes are no longer constrained to point to Packets, but rather any
    data type including packets.  */
template <class generic>
class Node
{
private:
    std::shared_ptr<Node<generic>> prevNode;
    std::shared_ptr<generic> data;
    std::shared_ptr<Node<generic>> nextNode;

public:

    Node(){ data = NULL; prevNode = NULL; nextNode = NULL;}

    //simmilar functionality to setData()
    Node(const generic& element)
    {
        prevNode = NULL;
        nextNode = NULL;
        data = std::make_shared<generic>(element);
    }


    Node(const Node &wezel)
    {
        /*Making the CopyConstructor copy the previous and next node will be useless and extremally chaotic.
        If this node is a part of LinkedList A, and we copy all attributes of a node from LinkedList B to this one, this node
        will point to nodes that are outside of the linked list it belongs to.*/
        data = wezel.data;
    }

    inline std::shared_ptr<const generic> readData() const
    {
        return data;
    }

    inline void setData(const generic& pakiet)
    {
        data = std::make_shared<generic>(pakiet);
    }

    inline std::shared_ptr<Node<generic>> getPrev() const
    {
        return prevNode;
    }

    inline std::shared_ptr<Node<generic>> getNext() const
    {
        return nextNode;
    }

    inline void setPrev(std::shared_ptr<Node<generic>> wezel)  //!!! do i need any consts here?
    {
        prevNode = wezel;
    }

    inline void setNext(std::shared_ptr<Node<generic>> wezel)  //!!! do i need any consts here?
    {
        nextNode = wezel;
    }

};


template <class generic>
class DList
{
private:
    std::shared_ptr<Node<generic>> headNode;
    std::shared_ptr<Node<generic>> tailNode;
    int n_nodes;

public:

    DList()
    {
        headNode = NULL;
        tailNode = NULL;
        n_nodes = 0;
    }

    inline int len() const
    {
        return n_nodes;
    }

    void append(const generic& element)
    {
        n_nodes++;
        std::shared_ptr<Node<generic>> nowa(new Node<generic>(element));
        if (headNode == NULL) //jezeli lista jest pusta
        {
            headNode = nowa;
            tailNode = headNode;
            return;
        }

        tailNode->setNext(nowa);
        nowa->setPrev(tailNode);
        tailNode = tailNode->getNext();
    }

    //Takes in the same argument type as get() returns, so that you can l.append(lista.get(i))
    //it should make a copy of the passed node. 
    void append(std::shared_ptr<Node<generic>> wezel)
    {
        n_nodes++;
        std::shared_ptr<Node<generic>>nowa = std::make_shared<Node<generic>>(*wezel);
        if (headNode == NULL) //jezeli lista jest pusta
        {
            headNode = nowa;
            tailNode = headNode;
            return;
        }
        tailNode->setNext(nowa);
        nowa->setPrev(tailNode);
        nowa->setNext(NULL);
        tailNode = tailNode->getNext();
    }

    void push(const generic& element)
    {
        n_nodes++;
        std::shared_ptr<Node<generic>> nowa(new Node<generic>(element));
        if (headNode == NULL) //jezeli lista jest pusta
        {
            headNode = nowa;
            tailNode = headNode;
            return;
        }

        headNode->setPrev(nowa);
        nowa->setNext(headNode);
        headNode = headNode->getPrev();
    }

    void insert(int index, const generic& element)
    {
        if (index > n_nodes-1 || index < 0)
        {
            std::cerr << "insert() - List index out of range" << std::endl;
            exit(1);
        }

        std::shared_ptr<Node<generic>> finger(headNode);
        for (int i=0; i<index; i++)
        {
            finger = finger->getNext();
        }

        std::shared_ptr<Node<generic>> nowa(new Node<generic>(element));
        nowa->setPrev(finger->getPrev());
        nowa->setNext(finger);
        finger->getPrev()->setNext(nowa);
        finger->setPrev(nowa);

        n_nodes++;
    }

    void swp(int id1, int id2)
    {
        /*Jest to sposob na rozwiazanie problemu, gdy pierwszy index jest wiekszy od drugiego.
        Jezeli tego podstawienia by nie bylo, nie nie mozna by bylo zastosowac funkcji swap() na tych dwoch wartosciach
        gdyz swap() potrzebuje l-wartości, a do funkcji swp() moga zastac wprowadzone r-wartosci.
        Alternatywą tego rozwiazania, ktore wykozystuje malo eleganckie i marnujace zasoby ponizsze przypisanie,
        bylo by dostosowanie wskaznikow 'finger1' i 'finger2' oraz operacji z nimi zwiazanymi w taki sposob, aby
        wykonywaly swoje operacje niezaleznie od tego, ktory z indeksow jest wiekszy a ktory mniejszy. Jest to
        jednakże o wiele bardziej skomplikowane i błędo-skłonne rozwiązanie. */
        int idx1 = id1;
        int idx2 = id2;

        if (idx1 > n_nodes-1 || idx2 > n_nodes-1 || idx1<0 || idx2<0)
        {
            std::cerr << "swp() - List index out of range" << std::endl;
            exit(1);
        }
        if (idx1 == idx2) {return;}
        if (idx1 > idx2) {std::swap(idx1, idx2);}

        std::shared_ptr<Node<generic>> temp;

        std::shared_ptr<Node<generic>> finger1(headNode);
        for (int i=0; i<idx1; i++)
        {
            finger1 = finger1->getNext();
        }

        std::shared_ptr<Node<generic>> finger2(finger1);
        for (int i=0; i<idx2-idx1; i++)
        {
            finger2 = finger2->getNext();
        }

        /* Poniższy ciąg operacji jest stosunkowo skomplikowany, dlatego też
        zdecydowano się przedstawić go w formie graficznej (zdj/Zdj_swp) */

        if (idx2-idx1 == 1) //jezeli elementy są tuż obok siebie
        {
            /*SWAP b*/
            if (finger1 == headNode){headNode = finger2;} 
            else {finger1->getPrev()->setNext(finger2);}
            if (finger2 == tailNode) {tailNode = finger1;}
            else {finger2->getNext()->setPrev(finger1);}

            /*SWAP c*/
            finger1->setNext(finger2->getNext());
            finger2->setNext(finger1);
            
            /*SWAP d*/
            finger2->setPrev(finger1->getPrev());
            finger1->setPrev(finger2);
        }
        else
        {
            /*SWAP a*/
            finger1->getNext()->setPrev(finger2);
            finger2->getPrev()->setNext(finger1);  
            
            /*SWAP b*/
            if (finger1 == headNode){headNode = finger2;} 
            else {finger1->getPrev()->setNext(finger2);}
            if (finger2 == tailNode) {tailNode = finger1;}
            else {finger2->getNext()->setPrev(finger1);}

            /*SWAP c*/
            temp = finger1->getNext();
            finger1->setNext(finger2->getNext());
            finger2->setNext(temp);

            /*SWAP d*/
            temp = finger1->getPrev();
            finger1->setPrev(finger2->getPrev());
            finger2->setPrev(temp);
        }
    }

    std::shared_ptr<Node<generic>> get(int index) const
    {
        if (index > n_nodes-1 || index < 0)
        {
            std::cerr << "get() - List index out of range" << std::endl;
            exit(1);
        }
        std::shared_ptr<Node<generic>> finger(headNode);
        for (int i=0; i<index; i++)
        {
            finger = finger->getNext();
        }
        return finger;
    }

    void del(int index)
    {

        if (index > n_nodes-1 || index < 0)
        {
            std::cerr << "del() - List index out of range" << std::endl;
            exit(1);
        }
        if (index == 0)
        {
            headNode = headNode->getNext();
            headNode->setPrev(NULL);
            n_nodes--;
            return;
        }
        else if (index == n_nodes-1)
        {
            tailNode = tailNode->getPrev();
            tailNode->setNext(NULL);
            n_nodes--;
            return;
        }

        std::shared_ptr<Node<generic>> finger(headNode);
        for (int i=0; i<index; i++)
        {
            finger = finger->getNext();
        }
        //finger->getPrev()->getNext() = finger->getNext();
        /*the above didnt work because (theories):
            1. finger->getPrev()->getNext() is a rigth-value, and assigning a value to right-val does not make any perma chenges
            2. something with the fact that prev and nextNode are private fields
            3. getNext() and getPrev() are const methods, but i dont think it would matter in this case.*/

        finger->getPrev()->setNext(finger->getNext());
        finger->getNext()->setPrev(finger->getPrev());

        finger->getNext() = NULL;
        finger->getPrev() = NULL;

        
    }


};

/* SNIPPETS

    // cout << finger1->getPrev()->readData()->getContent() << endl;
    // cout << finger1->readData()->getContent() << endl;
    // cout << finger1->getNext()->readData()->getContent() << endl << endl;

    // cout << finger2->getPrev()->readData()->getContent() << endl;
    // cout << finger2->readData()->getContent() << endl;
    // cout << finger2->getNext()->readData()->getContent() << endl;
    // cout << "-------\n";

    // cout << finger2->getPrev()->readData()->getContent() << endl;
    // cout << finger2->readData()->getContent() << endl;
    // cout << finger2->getNext()->readData()->getContent() << endl << endl;

    // cout << finger1->getPrev()->readData()->getContent() << endl;
    // cout << finger1->readData()->getContent() << endl;
    // cout << finger1->getNext()->readData()->getContent() << endl;


 */

#endif