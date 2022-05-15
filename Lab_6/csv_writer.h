#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <fstream>
#include "lesson.h"
#include "lessonOnline.h"
#include "lessonOpen.h"

using namespace::std;

#define CMN_LESSON_FILE_NAME "lessons_common.csv"

class CSV_Writer {
    ofstream file;
    bool writeCSV(string newRecord);
public:
    CSV_Writer(const string filePath);

    void clearFile();
    bool write(lesson newLesson);
    bool write(lessonOnline newLesson);
    bool write(lessonOpen newLesson);

    ~CSV_Writer();
};

#endif // CSV_WRITER_H
