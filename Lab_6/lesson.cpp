#include "lesson.h"

bool lesson::getLessonFromStr(vector<string> str, lesson &newLesson) {
    lessonStruct currRecord;
    if (str.size() != newLesson.getParamNum()) {
        return false;
    }
    currRecord.id = stoi(str[0]);
    currRecord.num = stoi(str[1]);
    currRecord.subjectName = str[2];
    currRecord.lessonType = getLessonEnum(str[3]);                 //function for filling record struct from string-line, taken from .csv file
    currRecord.classroom = stoi(str[4]);

    newLesson.setLessonParams(currRecord);
    return true;
}

bool lesson::parseRowsIntoLessons(vector<vector<string>> rows, vector<lesson>& returnLessons) {

    if (!rows.size()) {
        return false;
    }

    for (int it = 0; it < rows.size(); it++) {
        lesson currLesson;
        if (!getLessonFromStr(rows[it], currLesson)) {
            return false;
        }
        returnLessons.push_back(currLesson);
    }
    return true;
}

lesson::lesson() {
}

lessonStruct lesson::getLessonParams() const {
    return lessonParams;
}

void lesson::setLessonParams(lessonStruct newRecord) {
    lessonParams = newRecord;
}

int lesson::getParamNum() {
    return this->param_num;
}

string lesson::repr() {
    char buff[128] = "";
    sprintf(buff, "ID: %d; Subject: %s; Type: %s; Classroom: %d\n",
            lessonParams.id, lessonParams.subjectName.c_str(),
            getLessonStr(lessonParams.lessonType).c_str(), lessonParams.classroom);
    return string(buff);
}

