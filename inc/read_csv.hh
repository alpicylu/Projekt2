#ifndef READ_CSV_HH
#define READ_CSV_HH

#include <fstream>
#include "DLL.hh"

std::shared_ptr<DList<Packet<std::string>>> read_csv(std::string filename);


#endif