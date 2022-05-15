#ifndef JSON_READER_H
#define JSON_READER_H

#include "abstractReader.h"
#include <fstream>
#include <json.hpp>

class JSON_Reader: public AbstractReader {
    ifstream file;
    int readRowNum;
    nlohmann::json json;
public:
    JSON_Reader();

    void openFile(const string fileName)override;
    bool is_open()override {return file.is_open();};
    vector<lesson> readAllFile()override;

    bool operator>>(lesson& lessonToWrite) override;

    ~JSON_Reader();
};

#endif // JSON_READER_H
