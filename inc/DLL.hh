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

    std::shared_ptr<const generic> readData() const
    {
        return data;
    }

    void setData(const generic& pakiet)
    {
        data = std::make_shared<generic>(pakiet);
    }

    std::shared_ptr<Node<generic>> getPrev() const
    {
        return prevNode;
    }

    std::shared_ptr<Node<generic>> getNext() const
    {
        return nextNode;
    }

    void setPrev(std::shared_ptr<Node<generic>> wezel)  //!!! do i need any consts here?
    {
        prevNode = wezel;
    }

    void setNext(std::shared_ptr<Node<generic>> wezel)  //!!! do i need any consts here?
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
        if (index > n_nodes-1)
        {
            std::cerr << "List index out of range" << std::endl;
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

    std::shared_ptr<Node<generic>> get(int index) const
    {
        if (index > n_nodes-1)
        {
            std::cerr << "List index out of range" << std::endl;
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
        if (index > n_nodes-1)
        {
            std::cerr << "List index out of range" << std::endl;
            exit(1);
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

        n_nodes--;
    }


};