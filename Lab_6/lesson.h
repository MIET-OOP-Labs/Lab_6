#ifndef LESSON_H
#define LESSON_H

#include <iostream>
#include "lessonTypedefs.h"
#include <vector>

inline lessonTypesEnum getLessonEnum(string lessonStr) {
    lessonTypesEnum lesson = noneType;
    if (!lessonStr.compare("Lection")) {
        lesson = Lection;
    } else if (!lessonStr.compare("Practice")) {
        lesson = Practice;
    } else if (!lessonStr.compare("Lab")) {
        lesson = Lab;
    } else if (!lessonStr.compare("Exam")) {
        lesson = Exam;
    }
    return lesson;
}


inline string getLessonStr(lessonTypesEnum lesson){       //functions to convert enum type of lessons to string and vice-versa
    switch (lesson) {
    case Lection:   return "Lection";
    case Practice:   return "Practice";
    case Lab:   return "Lab";
    case Exam:   return "Exam";
    default: return "None";
    }
}

class lesson {
    lessonStruct lessonParams;
    const int param_num = 5;
public:
    lesson();
    lesson(const lesson &src) {lessonParams = src.lessonParams; }
    lesson(lesson && src) {lessonParams = src.lessonParams; }

    lessonStruct getLessonParams() const;
    void setLessonParams(lessonStruct newRecord);
    int getParamNum();

    friend bool operator< (const lesson& l1, const lesson& l2){
        return l1.lessonParams.num < l2.lessonParams.num;
    }

    friend ostream& operator<< (ostream& out, const lesson& l){
        out << "ID: " << l.lessonParams.id << " Num: " << l.lessonParams.num << " Subject: " << l.lessonParams.subjectName <<
            " Type: " << getLessonStr(l.lessonParams.lessonType) << " Classroom: " << l.lessonParams.classroom << endl;
        return out;
    }

    string repr();

    static bool getLessonFromStr(vector<string> str, lesson &newLesson);
    static bool parseRowsIntoLessons(vector<vector<string>> rows, vector<lesson>& returnLessons);
};

#endif // LESSON_H
