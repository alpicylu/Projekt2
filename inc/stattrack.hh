#pragma once

#include "DLL.hh"
#include "sortingAlgos.hh"
#include <iostream>
#include <chrono>

#define __FUNCTION__

template <class generic>
class Stats
{
public:
    class Value
    {
    private:
        float median;
        float mean;

    public:

        Value() {}

        float getMean() const {return mean;}
        float getMedian() const {return median;}

        /* try and think of a way that would allow for calculating the mean in this what as new records are appended */
        void calcMean(DList<Packet<generic>>& lista)
        {
            if (lista.len() < 1)
            {
                std::cerr << "calcMean - lenght of list cant be 0" << std::endl;
                exit(1);
            }

            double avg = lista[0].getRank();
            for (int i=1; i < lista.len(); i++)
            {
                avg = avg * (double(i)/double(i+1)) + lista[i].getRank()/double(i+1);
            }
            mean = avg;
        }

        void calcMedian(DList<Packet<generic>>& lista)
        {
            if (lista.len() < 1)
            {
                std::cerr << "calcMedian - lenght of list cant be 0" << std::endl;
                exit(1);
            }

            int size = lista.len();
            if (size%2 == 0)
            {
                int index = size/2 + 1;
                median = (lista[index].getRank() + lista[index+1].getRank())/2.0;
                return;
            }
            median = lista[size/2].getRank();
            return; 
        }


        void delete_empty(DList<Packet<generic>>& lista)
        {
            while (true)
            {
                if (lista[0].getRank() == -1) lista.del(0);
                else return; // kożystamy z faktu, że po posorotwaniu rosnąco "puste rankingi" oznaczane numerem -1
                //będą znajdowały się na samym początku.
            }
        }
    };

    class Time
    {
    private:
        //all timings are in miliseconds
        double mergeTime;
        double quickTime;
        double bucketTime;

    public:
        Time() {mergeTime = 0; quickTime = 0; bucketTime = 0;}

        double getTimeMS() {return mergeTime;}
        double getTimeQS() {return quickTime;}
        double getTimeBS() {return bucketTime;}

        void Time_MS(DList<Packet<generic>>& lista)
        {
            using namespace std;
            auto start = chrono::high_resolution_clock::now();
            MergeSort(lista);
            auto stop = chrono::high_resolution_clock::now();
            mergeTime = (chrono::duration<double>(stop - start).count())*1000;
        }

        void Time_QS(DList<Packet<generic>>& lista)
        {
            using namespace std;
            auto start = chrono::high_resolution_clock::now();
            QuickSort(lista);
            auto stop = chrono::high_resolution_clock::now();
            quickTime = (chrono::duration<double>(stop - start).count())*1000;
        }

        void Time_BS(DList<Packet<generic>>& lista)
        {
            using namespace std;
            auto start = chrono::high_resolution_clock::now();
            BucketSort(lista);
            auto stop = chrono::high_resolution_clock::now();
            bucketTime = (chrono::duration<double>(stop - start).count())*1000;
        }

    };

};




