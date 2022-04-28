#ifndef READ_CSV_HH
#define READ_CSV_HH

#include <fstream>
#include "DLL.hh"



void read_csv(std::string filename, DList<Packet<std::string>>& lista)
{
    using namespace std;
    // DList<Packet<string>> lista;
    ifstream fin(filename);
    string row; //an entire, raw row of the csv
    
    /*course of action:
        1. get an entire line using getline()
        2. scan this row char by char, every char you scan you put into an array/string/etc.
        3. you scan those chars and put them into the buffer until you see ',' or newline, then you package this string made of those scanned chars.
        4. if at any point you scan a '"', you toggle into reading every character including ',' (except newline). you toggle off once you read another '"'*/


    getline(fin, row);
    row.clear();
    while(!fin.eof())
    {
        bool quote_toggle = false;  //switch for checking if we read a quotation mark
        char c; //a single character read from the row.
        string buffer;  //a single column of this row, a rating number, a title, etc.
        string columns[3]; //three fields, one for lp, second for title, third for rating.
        int col_index = 0; //variale for indexing the above array.

        getline(fin, row); //get an entire line/row
        for (int i=0; i<row.length(); i++)
        {
            c = row[i];
            if (c == '"') {quote_toggle = !quote_toggle; continue;} //toggle switch
            if (!quote_toggle && c == ',')
            {
                columns[col_index] = buffer;
                col_index++;
                buffer.clear();
            }
            else if (quote_toggle || (!quote_toggle && c != ','))
            {
                buffer += c;
            }
            if (i == row.length()-1) // of we just read the last char
            {
                columns[col_index] = buffer;
                buffer.clear();
            }
        }
        // cout << columns[0] << " -- " << columns[1] << " -- " << stof(columns[2]) << " -- " << endl; 
        if (columns[2] == "") {columns[2]="-1.0";}
        lista.append(Packet<string>(columns[1], stof(columns[2])));

    }
    fin.close();
}

#endif