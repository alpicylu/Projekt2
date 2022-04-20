#ifndef PACKET_HH
#define PACKET_HH

#include <iostream>


/* Header przeniesiony z poprzedniego projektu i zmodyfikowany na potrzeby aktualnego. */

template <class generic>
class Packet
{
private:

    generic content; //generic will usually be a string
    float ranking; //MNIEJSZY pryjorytet == element szybciej pojawi się pierwszy w kolejce

    /* Metoda odpowiedzialna za ustalanie pryjorytetu pakietu po jego zainicjowaniu. W tej implementacji rzadko używana.
        IN:
            int p - pryjorytet, który ma zostać przypisany pakietowi */
    inline void setRank(float r) {ranking = r;}

    /* Metoda odpowiedzialna za ustalanie zawartości pakietu po jego zainicjowaniu. W tej implementacji rzadko używana.
        IN:
            generic c - zawartość typu generycznego, która ma zostać przypisana pakietowi */
    inline void setContent(generic c) {content = c;}

public:

    //Pusty kostruktor domyślny
    Packet() {}

    /* Konstruktor.
        IN:
            cntnt - wartość, która ma zostać przypisana pakietowi podczas inicjalizacji
            rnkg - ranging, który ma zostać przypisany pakietowi podczas inicjalizacji */
    Packet(generic cntnt, float rnkg)
    {
        content = cntnt;
        ranking = rnkg;
    }

    /* Konstruktor kopiujący. W tej implementacji nie używany.
        IN:
            pckt - referencja na stały obiekt typu Packet */
    Packet(const Packet<generic>& pckt)
    {
        content = pckt.getContent();
        ranking = pckt.getRank();
    }

    /* Metoda ta zwraca wartość pakietu */
    inline generic getContent() const { return content; }

    /* Metoda ta zwraca pryjorytet pakietu */
    inline float getRank() const { return ranking; }
};

/* Przeciążenie operatora "<<" służace wypisywaniu wartości i pryjorytetu pakietu */
template <class generic>
std::ostream& operator<<(std::ostream& os, const Packet<generic>& pckt)
{
    os << "(" << pckt.getContent() << ", " << pckt.getRank() << ")";
    return os; 
}

#endif