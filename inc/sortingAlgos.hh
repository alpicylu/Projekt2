#ifndef SORTING_ALGOS_HH
#define SORTING_ALGOS_HH

#include "DLL.hh"


// void QuickSort(DList<Packet<std::string>>& lista, int start, int stop)
// {
//     if (start >= stop) {return;}

//     int pivot = stop;
//     int pIdx = start;

//     for (int i=start; i<=stop; i++)
//     {
//         if ( lista.get(i)->readData()->getRank() < lista.get(pivot)->readData()->getRank() )
//         {
//             lista.swp(i, pIdx);
//             pIdx++;
//             continue;
//         }
//         // else {continue;}  //redundant
//     }
//     lista.swp(pivot, pIdx);
//     QuickSort(lista, start, pIdx-1);
//     QuickSort(lista, pIdx+1, stop);
// }



template <class generic>
void qs_step(DList<Packet<generic>>& lista, int start, int stop)
{
    if (start >= stop) return;

    int pivot = lista.get(stop)->readData()->getRank();
    int left = start;
    int right = stop-1;

    while (left <= right)
    {
        while (left <= right && pivot >= lista.get(left)->readData()->getRank()) left++;
        while (right >= left && lista.get(right)->readData()->getRank() >= pivot) right--;
        if (left < right) {lista.swp(left, right);}
    }
    lista.swp(left, stop);
    qs_step(lista, start, left-1);
    qs_step(lista, left+1, stop);
}

template <class generic>
void QuickSort(DList<Packet<generic>>& lista)
{
    if (lista.len() <= 1) return;
    qs_step(lista, 0, lista.len()-1);
}


// void MergeSort(DList<Packet<std::string>>& lista)
// {
//     if (lista.len() < 2) {return;}

//     int mid_index = lista.len()/2;  //[0....len()/2 - 1] [len()/2 .......len()-1]
//     DList<Packet<std::string>> lewa;
//     DList<Packet<std::string>> prawa;

//     for (int i=0; i<mid_index; i++)
//     {
//         lewa.append(lista.get(i));
//     }
//     for (int i=mid_index; i<lista.len(); i++)
//     {
//         prawa.append(lista.get(i));
//     }

//     MergeSort(lewa);
//     MergeSort(prawa);

//     /* Merging the sorted lists: */
//     int l = 0; //indexes that track positions of elements in the left, right and merge(middle) lists
//     int p = 0;
//     int m = 0;
//     while (l < lewa.len() && p < prawa.len())
//     {
//         if (lewa.get(l)->readData()->getRank() <= prawa.get(p)->readData()->getRank())
//         {
//             lista.get(m)->setData(Packet<std::string>( *(lewa.get(l)->readData()) ));
//             l++;
//             m++;
//         }
//         else
//         {
//             lista.get(m)->setData(Packet<std::string>( *(prawa.get(p)->readData()) ));
//             p++;
//             m++;
//         }
//     }
//     while (l < lewa.len())
//     {
//         lista.get(m)->setData(Packet<std::string>( *(lewa.get(l)->readData()) ));
//         l++;
//         m++;      
//     }
//     while (p < prawa.len())
//     {
//         lista.get(m)->setData(Packet<std::string>( *(prawa.get(p)->readData()) ));
//         p++;
//         m++;        
//     }

// }

template <class generic>
void merge(DList<Packet<generic>>& l1, DList<Packet<generic>>& l2, DList<Packet<generic>>& lista)
{
    int p1 = 0;
    int p2 = 0;
    while(p1 < l1.len() && p2 < l2.len())
    {
        if (l1.get(p1)->readData()->getRank() < l2.get(p2)->readData()->getRank())
        {
            lista.append(l1.get(p1++));
        }
        else
        {
            lista.append(l2.get(p2++));
        }
    }
    while (p1 < l1.len())
    {
        lista.append(l1.get(p1++));
    }
    while (p2 < l2.len())
    {
        lista.append(l2.get(p2++));
    }
}

template <class generic>
void MergeSort(DList<Packet<generic>>& lista)
{
    int size = lista.len();
    if (size <= 1) return;
    DList<Packet<generic>> l1, l2;

    for (int i=0; i<size/2; i++) l1.append(lista.get(i));
    for (int i=size/2; i<size; i++) l2.append(lista.get(i));
    lista.clear();
    MergeSort(l1);
    MergeSort(l2);
    merge(l1, l2, lista);
}

#endif