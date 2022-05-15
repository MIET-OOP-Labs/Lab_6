#include "csv_writer.h"

CSV_Writer::CSV_Writer(const string filePath) {
    string writerFileName = filePath.substr(0,filePath.find_last_of('/')+1).append(CMN_LESSON_FILE_NAME);
    file.open(writerFileName);
    clearFile();
}

void CSV_Writer::clearFile(){
    file << "";
    file.close();
}

bool CSV_Writer::writeCSV(string newRecord){
    file  << newRecord;       // Write to the file
    file.close();
    return true;
}

bool CSV_Writer::write(lesson lesson) {
    lessonStruct lessonParams = lesson.getLessonParams();
    char buff[64] = "";
    sprintf(buff, "%d;%d;%s;%s;%d\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.classroom);
    return writeCSV(buff);
}

bool CSV_Writer::write(lessonOnline lesson) {
    onlineLessonStruct lessonParams = lesson.getLessonParams();
    char buff[64] = "";
    sprintf(buff, "%d;%d;%s;%s;%s;%s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.platform, lessonParams.link.c_str());
    return writeCSV(buff);
}

bool CSV_Writer::write(lessonOpen lesson) {
    openLessonStruct lessonParams = lesson.getLessonParams();
    char buff[64] = "";
    sprintf(buff, "%d;%d;%s;%s;%s;%d;%s\n", lessonParams.id, lessonParams.num, lessonParams.subjectName.c_str(), getLessonStr(lessonParams.lessonType).c_str(), lessonParams.link.c_str(), lessonParams.studentsNum, lessonParams.teacherName.c_str());
    return writeCSV(buff);
}

CSV_Writer::~CSV_Writer() {}
