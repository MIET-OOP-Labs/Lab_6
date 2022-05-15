#ifndef LESSONSHANDLER_H
#define LESSONSHANDLER_H

#include "lesson.h"
#include "lessonOnline.h"
#include "lessonOpen.h"
#include "csv_writer.h"
#include "csv_reader.h"
#include "json_reader.h"
#include <time.h>
#include <algorithm>

#include <fstream>

class lessonsHandler {

    vector <lesson> & cmnLessonArr_ref;
    vector <lessonOnline> & onlineLessonArr_ref;
    vector <lessonOpen> & openLessonArr_ref;

    vector <int> getID_arr(const vector <lesson> & lessons);
    vector <int> getID_arr(const vector <lessonOnline> & lessonsOnline);
    vector <int> getID_arr(const vector <lessonOpen> & lessonsOpen);

    const string onlineLessonFileName = "lessons_online.csv";
    const string openLessonFileName = "lessons_open.csv";

    bool saveLessonInFile(lessonStruct lessonParams, string filePath);
    bool saveLessonInFile(onlineLessonStruct lessonParams, string filePath);
    bool saveLessonInFile(openLessonStruct lessonParams, string filePath);



public:

    lessonsHandler(vector <lesson> & lessons, vector <lessonOnline> & lessonsOnline, vector <lessonOpen> & lessonsOpen);

    int getUniqRandID(lessonCategoryEnum cat);
    void fillLessonArrWithRand_ID();
    vector<lesson> getFilteredCmnRecords(lessonStruct filter);
};

#endif // LESSONSHANDLER_H
