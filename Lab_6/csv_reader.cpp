#include "csv_reader.h"

CSV_Reader::CSV_Reader() { }

void CSV_Reader::openFile(const string fileName){
    file.open(fileName);
}

vector<string> CSV_Reader::split(const string& str, char delim) {
    vector<string> tokens;
    if (!str.empty()) {
        size_t start = 0;
        size_t end = 0;
        do {
            end = str.find(delim, start);
            tokens.push_back(str.substr(start, (end - start)));
            start = end + 1;
        } while (end != string::npos);
    }

    return tokens;
}

vector<vector<string>> CSV_Reader::readCSV(){
    vector<vector<string>> records;

    string line;
    while(getline(file, line)) {
        if(!line.length()){
            continue;
        }
        records.push_back(split(line, ';'));
    }
    file.close();
    return records;
}

vector<lesson> CSV_Reader::readAllFile() {
    vector<lesson> returnLessonVec;

    vector<vector<string>> CSV_rows = readCSV();
    lesson::parseRowsIntoLessons(CSV_rows, returnLessonVec);

    return returnLessonVec;
}

bool CSV_Reader::operator>>(lesson& lessonToWrite) {
    if (file.eof()) {
        file.close();
        return false;
    }
    string line;
    getline(file, line);
    if(!line.length()){
        return false;
    }
    auto row = split(line, ';');

    if (!lesson::getLessonFromStr(row, lessonToWrite)) {
        return false;
    }
    return true;
}

CSV_Reader::~CSV_Reader(){}
