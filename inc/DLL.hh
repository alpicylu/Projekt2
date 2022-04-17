#include <memory>
#include "packet.hh"

template <class generic>
class Node
{
private:
    std::shared_ptr<Node> prevNode;
    std::shared_ptr<Packet<generic>> data;
    std::shared_ptr<Node> nextNode;

public:

    Node(){}

    Node(const Node &wezel)
    {
        /*Making the CopyConstructor copy the previous and next node will be useless and extremally chaotic.
        If this node is a part of LinkedList A, and we copy all attributes of a node from LinkedList B to this one, this node
        will point to nodes that are outside of the linked list it belongs to.*/
        data = wezel.data;
    }

    std::shared_ptr<const Packet<generic>> readData() const //Do i need so many consts?
    {
        return data;
    }

    void setData(const Packet<generic>& pakiet)
    {
        data = std::make_shared<Packet<generic>>(pakiet);
    }

    std::shared_ptr<Node> getPrev() const
    {
        return prevNode;
    }

    std::shared_ptr<Node> getNext() const
    {
        return nextNode;
    }

    void setPrev(const Node& wezel)
    {
        prevNode = std::make_shared<Node>(wezel);
    }

    void setNext(const Node& wezel)
    {
        nextNode = std::make_shared<Node>(wezel);
    }

};


template <class generic>
class DList
{
private:



public:


};