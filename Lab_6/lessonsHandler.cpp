#include "lessonsHandler.h"

lessonsHandler::lessonsHandler(vector <lesson> & lessons, vector <lessonOnline> & lessonsOnline, vector <lessonOpen> & lessonsOpen):
    cmnLessonArr_ref{lessons},
    onlineLessonArr_ref {lessonsOnline},
    openLessonArr_ref {lessonsOpen} {}

vector <int> lessonsHandler::getID_arr(const vector <lesson> & lessons) {
    vector <int> ID_arr;
    for (int it = 0; it < lessons.size(); it++) {
        ID_arr.push_back(lessons[it].getLessonParams().id);
    }
    sort(ID_arr.begin(), ID_arr.end());
    ID_arr.erase(unique(ID_arr.begin(), ID_arr.end()), ID_arr.end());
    return ID_arr;
}

vector <int> lessonsHandler::getID_arr(const vector <lessonOnline> & lessonsOnline) {
    vector <int> ID_arr;
    for (int it = 0; it < lessonsOnline.size(); it++) {
        ID_arr.push_back(lessonsOnline[it].getLessonParams().id);
    }
    sort(ID_arr.begin(), ID_arr.end());
    ID_arr.erase(unique(ID_arr.begin(), ID_arr.end()), ID_arr.end());
    return ID_arr;
}


vector <int> lessonsHandler::getID_arr(const vector <lessonOpen> & lessonsOpen) {
    vector <int> ID_arr;
    for (int it = 0; it < lessonsOpen.size(); it++) {
        ID_arr.push_back(lessonsOpen[it].getLessonParams().id);
    }
    sort(ID_arr.begin(), ID_arr.end());
    ID_arr.erase(unique(ID_arr.begin(), ID_arr.end()), ID_arr.end());
    return ID_arr;
}


int lessonsHandler::getUniqRandID(lessonCategoryEnum cat) {
    srand (time(NULL));
    vector <int> ID_sortedArr;
    switch (cat) {
        case Lesson:{
            ID_sortedArr = getID_arr(cmnLessonArr_ref);
            break;
        }
        case Online:{
            ID_sortedArr = getID_arr(onlineLessonArr_ref);
            break;
        }
        case Open:{
            ID_sortedArr = getID_arr(openLessonArr_ref);
            break;
        }
        default:
            break;
    }
    int randNum = 0;
    do {
        randNum = rand() % 100 + 1;
    } while (find(ID_sortedArr.begin(), ID_sortedArr.end(), randNum) != ID_sortedArr.end());

    return randNum;
}


void lessonsHandler::fillLessonArrWithRand_ID() {

}



vector<lesson> lessonsHandler::getFilteredCmnRecords(lessonStruct filter) {   //filter all records by filter struct. It will be also checked, if some parametr in filter isn't used
    vector<lesson> returnVec;
    for (lesson it : cmnLessonArr_ref) {
        bool subjectEqual = (!it.getLessonParams().subjectName.compare(filter.subjectName)) || (!filter.subjectName.compare(" ")); //check if subjects are equal or subject name in filter is empty, which means this parametr isn't used
        bool lessonTypeEqual = (it.getLessonParams().lessonType == filter.lessonType) || (!filter.lessonType);                //check if lesson types are equal or lesson type in filter is none (none in lessonTypesEnum = 0)
        bool classroomEqual = (it.getLessonParams().classroom == filter.classroom) || (!filter.classroom);                    //check if classrooms are equal or classroom in filter is null
        if (subjectEqual && lessonTypeEqual && classroomEqual) {
            returnVec.push_back(it);
        }
    }
    return returnVec;
}


