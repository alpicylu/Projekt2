#ifndef DLL_HH
#define DLL_HH

#include <memory>
#include <math.h>
#include <algorithm>
#include "packet.hh"

//class declaration
template <class generic>
class DList;

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
    template <class type>
    friend class DList; //DList has access to Node's private parts



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

    ~Node()
    {
        prevNode = NULL;
        nextNode = NULL;
        data = NULL;
    }

    inline std::shared_ptr<generic> getData() const
    {
        return data;
    }

    inline void setData(const generic& pakiet)
    {
        data = std::make_shared<generic>(pakiet);
    }

    // inline void setData(std::shared_ptr<Node<generic>> wezel)
    // {
    //     data = std::make_shared<generic>(wezel->get)
    // }

    inline std::shared_ptr<Node<generic>> getPrev() const
    {
        return prevNode;
    }

    inline std::shared_ptr<Node<generic>> getNext() const
    {
        return nextNode;
    }

    inline void setPrev(const std::shared_ptr<Node<generic>>& wezel)  //!!! do i need any consts here?
    {
        prevNode = wezel;
    }

    inline void setNext(const std::shared_ptr<Node<generic>>& wezel)  //!!! do i need any consts here?
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

    //make this outside of the class
    std::shared_ptr<Node<generic>> closest_to(int idx, int fing1_idx, std::shared_ptr<Node<generic>> fing1_ptr)
    {
        int to_tail = idx - n_nodes-1;
        int to_head = idx;
        int to_finger = idx - fing1_idx;
        
        if (abs(to_tail) <= abs(to_head) && abs(to_tail) <= abs(to_finger)) //if distance to tail is smallest
        {
            //iterate backwards from tail and return
            std::shared_ptr<Node<generic>> finger2(tailNode);
            for (int i=0; i<n_nodes-1-idx; i++)
            {
                finger2 = finger2->getPrev();
            }
            return finger2;
        }
        else if (abs(to_head) <= abs(to_tail) && abs(to_head) <= abs(to_finger)) //if distance to head is smallest
        {
            //iterate from head upwards and return
            std::shared_ptr<Node<generic>> finger2(headNode);
            for (int i=0; i<idx; i++)
            {
                finger2 = finger2->getNext();
            }
            return finger2;
        }
        else //if finger is the closest
        {
            //somehow get finger's pointer and iterate from there in the right direction.
            if (idx-fing1_idx < 0)
            {
                std::shared_ptr<Node<generic>> finger2(fing1_ptr);
                for (int i=0; i<fing1_idx-idx; i++)
                {
                    finger2 = finger2->getPrev();
                }
                return finger2;
            }
            std::shared_ptr<Node<generic>> finger2(fing1_ptr);
            for (int i=0; i< idx-fing1_idx; i++)
            {
                finger2 = finger2->getNext();
            }
            return finger2;

        }
        return NULL;
    }

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
        using namespace std;
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

        // std::shared_ptr<Node<generic>> temp;

        std::shared_ptr<Node<generic>> finger1;
        if (idx1 < n_nodes/2)
        {
            finger1 = headNode;
            for (int i=0; i<idx1; i++)
            {
                finger1 = finger1->getNext();
            }
        }
        else
        {
            finger1 = tailNode;
            for (int i=0; i<n_nodes-1-idx1; i++)
            {
                finger1 = finger1->getPrev();
            }
        }

        //consider deleting this after some performance tests, 
        std::shared_ptr<Node<generic>> finger2 = closest_to(idx2, idx1, finger1);
        // std::shared_ptr<Node<generic>> finger2(finger1);
        // for (int i=0; i<idx2-idx1; i++)
        // {
        //     finger2 = finger2->getNext();
        // }

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
            // finger1->setNext(finger2->getNext());
            // finger2->setNext(finger1);
            finger1->nextNode = finger2->nextNode;
            finger2->nextNode = finger1;
            
            /*SWAP d*/
            // finger2->setPrev(finger1->getPrev());
            // finger1->setPrev(finger2);
            finger2->prevNode = finger1->prevNode;
            finger1->prevNode = finger2;
            return;
        }
        /*SWAP a*/
        // finger1->getNext()->setPrev(finger2);
        // finger2->getPrev()->setNext(finger1);
        swap(finger1->getNext()->prevNode, finger2->getPrev()->nextNode);
        
        /*SWAP b*/
        if (finger1 == headNode){headNode = finger2;} 
        else {finger1->getPrev()->setNext(finger2);}
        if (finger2 == tailNode) {tailNode = finger1;}
        else {finger2->getNext()->setPrev(finger1);}

        /*SWAP c*/
        // temp = finger1->getNext();
        // finger1->setNext(finger2->getNext());
        // finger2->setNext(temp);
        swap(finger1->nextNode, finger2->nextNode);

        /*SWAP d*/
        // temp = finger1->getPrev();
        // finger1->setPrev(finger2->getPrev());
        // finger2->setPrev(temp);
        swap(finger1->prevNode, finger2->prevNode);
        
    }

    std::shared_ptr<Node<generic>> get(int index) const
    {
        if (index > n_nodes-1 || index < 0)
        {
            std::cerr << "get() - List index out of range" << std::endl;
            exit(1);
        }

        if (index < n_nodes/2)
        {
            std::shared_ptr<Node<generic>> finger(headNode);
            for (int i=0; i<index; i++)
            {
                finger = finger->getNext();
            }
            return finger;
        }
        std::shared_ptr<Node<generic>> finger(tailNode);
        for (int i=0; i<n_nodes-1-index; i++)
        {
            finger = finger->getPrev();
        }
        return finger;
        /*you could additionally store the location of the last node retrieved to make the process even faster*/
    }

    void del(int index)
    {

        if (index > n_nodes-1 || index < 0)
        {
            std::cerr << "del() - List index out of range" << std::endl;
            exit(1);
        }
        if (n_nodes==1)
        {
            headNode = NULL;
            tailNode = NULL;
            n_nodes--;
            return;
        }
        else if (index == 0)
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


        //optimise
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

        finger->nextNode = NULL;
        finger->prevNode = NULL;
        n_nodes--;

        
    }

    void clear()
    {
        for (int i=0; i < this->len(); i++)
        {
            this->del(0);
        }
        headNode = NULL;
        tailNode = NULL;
        n_nodes = 0;
    }

    generic& operator[] (int index)
    {
        return *(this->get(index)->getData());
    }

};



#endif