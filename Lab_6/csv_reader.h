#ifndef CSV_READER_H
#define CSV_READER_H

#include <vector>
#include <fstream>
#include "abstractReader.h"

using namespace::std;

class CSV_Reader: public AbstractReader {
    ifstream file;
    vector<string> split(const string& str, char delim);
    vector<vector<string>> readCSV();
public:
    CSV_Reader();

    void openFile(const string fileName) override;
    vector<lesson> readAllFile() override;
    bool is_open() override {return file.is_open();};

    bool operator>>(lesson& lessonToWrite) override;

    ~CSV_Reader();
};

#endif // CSV_READER_H
