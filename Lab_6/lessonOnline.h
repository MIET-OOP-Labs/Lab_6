#ifndef LESSONONLINE_H
#define LESSONONLINE_H

#include <iostream>
#include "lesson.h"
#include "lessonTypedefs.h"

inline onlinePlatformEnum getPlatformEnum(string platformStr) {
    onlinePlatformEnum lesson = nonePlatform;
    if (!platformStr.compare("Zoom")) {
        lesson = Zoom;
    } else if (!platformStr.compare("Moodle")) {
        lesson = Moodle;
    } else if (!platformStr.compare("Discord")) {
        lesson = Discord;
    } else if (!platformStr.compare("Skype")) {
        lesson = Skype;
    }
    return lesson;
}

inline string getPlatformStr(onlinePlatformEnum platform){       //functions to convert enum type of lessons to string and vice-versa
    switch (platform) {
    case Zoom:   return "Zoom";
    case Moodle:   return "Moodle";
    case Discord:   return "Discord";
    case Skype:   return "Skype";
    default: return "None";
    }
}

class lessonOnline: protected lesson  {
    onlineLessonStruct lessonParams;
    const int param_num = 7;
public:
    lessonOnline();

    lessonOnline(const lessonOnline &src) {lessonParams = src.lessonParams; }
    lessonOnline(lessonOnline && src) {lessonParams = src.lessonParams; }

    onlineLessonStruct getLessonParams() const;
    void setLessonParams(onlineLessonStruct newRecord);
    int getParamNum();

    friend bool operator< (const lessonOnline& l1, const lessonOnline& l2){
        return l1.lessonParams.num < l2.lessonParams.num;
    }

    friend ostream& operator<< (ostream& out, const lessonOnline& l){
        out << "ID: " << l.lessonParams.id << " Num: " << l.lessonParams.num << " Subject: " << l.lessonParams.subjectName <<
            " Type: " << getLessonStr(l.lessonParams.lessonType) << " Platform: " << l.lessonParams.platform << " Link: " << l.lessonParams.link << endl;
        return out;
    }

    string repr();
};

#endif // LESSONONLINE_H
