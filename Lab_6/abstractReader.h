#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H

#include <vector>
#include <string>
#include "lesson.h"


class AbstractReader {
public:
    AbstractReader();

    virtual void openFile(const string fileName) = 0;
    virtual bool is_open() = 0;
    virtual vector<lesson> readAllFile() = 0;

    virtual bool operator>>(lesson& lessonToWrite) = 0;

    virtual ~AbstractReader();
};

#endif // ABSTRACTREADER_H
