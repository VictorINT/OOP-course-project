#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>

using namespace std;

class FileReader {
public:
    // Citeste fisier si returneaza liniile
    static vector<string> citesteFisier(const string&);
    
    // Separa o linie CSV
    static vector<string> parseazaLinieCSV(const string&);
    
    // Valideaza si afiseaza erori
    static void raporteazaEroare(int, const string&);
};

#endif

