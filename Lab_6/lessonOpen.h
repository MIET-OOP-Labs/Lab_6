#ifndef LESSONOPEN_H
#define LESSONOPEN_H

#include <iostream>
#include "lesson.h"
#include "lessonTypedefs.h"

class lessonOpen: protected lesson {
    openLessonStruct lessonParams;
    const int param_num = 9;
public:
    lessonOpen();

    lessonOpen(const lessonOpen &src) {lessonParams = src.lessonParams; }
    lessonOpen(lessonOpen && src) {lessonParams = src.lessonParams; }

    //bool saveLessonInFile(string filePath);
    openLessonStruct getLessonParams() const;
    void setLessonParams(openLessonStruct newRecord);
    int getParamNum();

    friend bool operator< (const lessonOpen& l1, const lessonOpen& l2){
        return l1.lessonParams.num < l2.lessonParams.num;
    }

    friend ostream& operator<< (ostream& out, const lessonOpen& l){
        out << "ID: " << l.lessonParams.id << " Num: " << l.lessonParams.num << " Subject: " << l.lessonParams.subjectName <<
            " Type: " << getLessonStr(l.lessonParams.lessonType) << " Link: " << l.lessonParams.link << " Students num: " <<
            l.lessonParams.studentsNum << " Teacher name: " << l.lessonParams.teacherName << endl;
        return out;
    }

    string repr();
};

#endif // LESSONOPEN_H
