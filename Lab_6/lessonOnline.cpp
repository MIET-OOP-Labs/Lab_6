#include "lessonOnline.h"

lessonOnline::lessonOnline() {
}

onlineLessonStruct lessonOnline::getLessonParams() const {
    return lessonParams;
}

void lessonOnline::setLessonParams(onlineLessonStruct newRecord) {
    lessonParams = newRecord;
}

int lessonOnline::getParamNum() {
    return param_num;
}

string lessonOnline::repr() {
    char buff[128] = "";
    sprintf(buff, "ID: %d; Subject: %s; Type: %s; Platform: %s; Link: %s\n",
            lessonParams.id, lessonParams.subjectName.c_str(),
            getLessonStr(lessonParams.lessonType).c_str(), getPlatformStr(lessonParams.platform).c_str(), lessonParams.link.c_str());
    return string(buff);
}

