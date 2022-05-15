#include "lessonOpen.h"

lessonOpen::lessonOpen() {
}

openLessonStruct lessonOpen::getLessonParams() const {
    return lessonParams;
}

void lessonOpen::setLessonParams(openLessonStruct newRecord) {
    lessonParams = newRecord;
}

int lessonOpen::getParamNum() {
    return param_num;
}

string lessonOpen::repr() {
    char buff[128] = "";
    sprintf(buff, "ID: %d; Subject: %s; Type: %s; Link: %s; Students num: %d; Teacher name: %s\n",
            lessonParams.id, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(),
            lessonParams.link.c_str(), lessonParams.studentsNum, lessonParams.teacherName.c_str());

    return string(buff);

}
