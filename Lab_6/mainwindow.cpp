#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mylessonsHandler = new lessonsHandler(myLessons, myLessonsOnline, myLessonsOpen);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::printLessonsRecords(vector<lesson> lessonRecords) {
    for (lesson currLesson : lessonRecords) {            //function for printing all records in recordStruct vector
        ui->textOut->append(QString::fromStdString(currLesson.repr()));
    }
}

void MainWindow::printLessonsRecords(vector<lessonOpen> lessonRecords) {
    for (lessonOpen currLesson : lessonRecords) {            //function for printing all records in recordStruct vector
        ui->textOut->append(QString::fromStdString(currLesson.repr()));
    }
}


void MainWindow::printLessonsRecords(vector<lessonOnline> lessonRecords) {
    for (lessonOnline currLesson : lessonRecords) {            //function for printing all records in recordStruct vector
        ui->textOut->append(QString::fromStdString(currLesson.repr()));
    }
}

void MainWindow::findLesson() {
    QString logStr = "You entered: ";
    QString userRequest = ui->editSearch->text();
    ui->textOut->append(logStr.append(userRequest) + "\n");
    lessonStruct filter;
    char subjectName_c[16];
    char lessonType_c[16];
    char *userRequest_c = new char[userRequest.length() + 1];
    strcpy(userRequest_c, userRequest.toStdString().c_str());
    sscanf(userRequest_c, "%[^;];%[^;];%d", subjectName_c, lessonType_c, &filter.classroom);
    delete[] userRequest_c;
    filter.lessonType = getLessonEnum(lessonType_c);
    filter.subjectName = subjectName_c;

    printLessonsRecords(mylessonsHandler->getFilteredCmnRecords(filter));
}

void MainWindow::readFile(AbstractReader &pReader, string myFile){
    pReader.openFile(myFile);

    if(!pReader.is_open()){
        QMessageBox::information(this,"Failed to open file ",QString::fromStdString(myFile));
        return;
    }
    myLessons.clear();
    lesson newLesson;
    while( pReader >> newLesson){
        cout << newLesson << endl;
        myLessons.push_back(newLesson);
    }
    //delete pReader;
}

void MainWindow::on_chooseFile_clicked() {
    string myFile = QFileDialog::getOpenFileName(this, "Open a file", QDir::currentPath()).toStdString();
    string format = myFile.substr(myFile.find_last_of('.'), myFile.length() - myFile.find_last_of('.'));
    if(!format.compare(".csv")) {
        CSV_Reader pReader;
        readFile(pReader, myFile);

    } else if(!format.compare(".json")){
        JSON_Reader pReader;
        readFile(pReader, myFile);
    }
    QMessageBox::information(this,"Opened file ", QString::fromStdString(myFile));

    printLessonsRecords(myLessons);
}

void MainWindow::addLesson() {
    lessonCategoryEnum lessonCat = static_cast<lessonCategoryEnum>(ui->comboCat->currentIndex() + 1);


    if (((myLessons.size() == maxLessonsNum) && (lessonCat == Lesson)) ||
        ((myLessonsOnline.size() == maxLessonsNum) && (lessonCat == Online)) ||
        ((myLessonsOpen.size() == maxLessonsNum) && (lessonCat == Open))) {
        QMessageBox::information(this,"Failed to add more subjects ", "Sorry, but students can't cope with so many subjects, take pity on them");
        return;
    }

    switch (lessonCat) {
    case Lesson: {
            lessonStruct newCmnLessonData;
            newCmnLessonData.subjectName = ui->lineSubject->text().toStdString();
            newCmnLessonData.lessonType = static_cast<lessonTypesEnum>(ui->comboType->currentIndex() + 1);
            newCmnLessonData.classroom = ui->lineClassroom->text().toInt();
            newCmnLessonData.num = myLessons[myLessons.size() - 1].getLessonParams().num + 1;
            newCmnLessonData.id = mylessonsHandler->getUniqRandID(Lesson);


            lesson newCmnLesson;
            newCmnLesson.setLessonParams(newCmnLessonData);
            myLessons.push_back(newCmnLesson);

            QString outStr1;
            outStr1.sprintf("Added new record: Category - %s; ID - %d; Num - %d; Subject - %s; Type - %s; Classroom - %d\n",
                           getLessonCatEnum(lessonCat).c_str(), newCmnLessonData.id, newCmnLessonData.num,
                           newCmnLessonData.subjectName.c_str(), getLessonStr(newCmnLessonData.lessonType).c_str(),
                           newCmnLessonData.classroom);
            ui->textOut->append(outStr1);

            break;
    }
    case Online: {
            onlineLessonStruct newOnlineLessonData;
            newOnlineLessonData.subjectName = ui->lineSubject->text().toStdString();
            newOnlineLessonData.lessonType = static_cast<lessonTypesEnum>(ui->comboType->currentIndex() + 1);
            newOnlineLessonData.platform = static_cast<onlinePlatformEnum>(ui->comboPlatformOnline->currentIndex() + 1);
            newOnlineLessonData.link = ui->lineLink->text().toStdString();
            newOnlineLessonData.id = mylessonsHandler->getUniqRandID(Online);

            if (myLessonsOnline.size()) {
                newOnlineLessonData.num = myLessonsOnline[myLessonsOnline.size() - 1].getLessonParams().num + 1;
            } else {
                newOnlineLessonData.num = 1;
            }

            lessonOnline newLessonOnline;
            newLessonOnline.setLessonParams(newOnlineLessonData);
            myLessonsOnline.push_back(newLessonOnline);

            QString outStr2;
            outStr2.sprintf("Added new record: Category - %s; ID - %d; Num - %d; Subject - %s; Type - %s; Platform - %s; Link - %s\n",
                            getLessonCatEnum(lessonCat).c_str(), newOnlineLessonData.id, newOnlineLessonData.num,
                            newOnlineLessonData.subjectName.c_str(), getLessonStr(newOnlineLessonData.lessonType).c_str(),
                            getPlatformStr(newOnlineLessonData.platform).c_str(), newOnlineLessonData.link.c_str());
            ui->textOut->append(outStr2);

            break;
    }
    case Open: {
            openLessonStruct newOpenLessonData;
            newOpenLessonData.subjectName = ui->lineSubject->text().toStdString();
            newOpenLessonData.lessonType = static_cast<lessonTypesEnum>(ui->comboType->currentIndex() + 1);
            newOpenLessonData.link = ui->lineLink->text().toStdString();
            newOpenLessonData.studentsNum = ui->lineStudentsNum->text().toInt();
            newOpenLessonData.teacherName = ui->lineTeacher->text().toStdString();
            newOpenLessonData.id = mylessonsHandler->getUniqRandID(Open);

            if (myLessonsOpen.size()) {
                newOpenLessonData.num = myLessonsOpen[myLessonsOpen.size() - 1].getLessonParams().num + 1;
            } else {
                newOpenLessonData.num = 1;
            }

            lessonOpen newLessonOpen;
            newLessonOpen.setLessonParams(newOpenLessonData);
            myLessonsOpen.push_back(newLessonOpen);

            QString outStr3;
            outStr3.sprintf("Added new record: Category - %s; ID - %d; Num - %d; Subject - %s; Type - %s; Students - %d; Teacher - %s; Link - %s\n",
                           getLessonCatEnum(lessonCat).c_str(), newOpenLessonData.id, newOpenLessonData.num,
                           newOpenLessonData.subjectName.c_str(), getLessonStr(newOpenLessonData.lessonType).c_str(),
                           newOpenLessonData.studentsNum, newOpenLessonData.teacherName.c_str(),
                           newOpenLessonData.link.c_str());
            ui->textOut->append(outStr3);

            break;
    }
        default:
            break;
    }
}

void MainWindow::reprLesson() {
    lessonCategoryEnum category = static_cast<lessonCategoryEnum>(ui->comboCatRepr->currentIndex() + 1);
    int id = ui->lineID->text().toInt();

    if(category == Lesson){
        if (!myLessons.size()) {
            ui->textOut->RedText("Lessons are empty");
            return;
        }
        vector<lesson>::iterator it = begin(myLessons);
        while ((it != (end(myLessons) - 1)) && ((*it).getLessonParams().id != id)) {
            ++it;
        }
        if ((*it).getLessonParams().id != id) {
            ui->textOut->RedText("Can't find this ID");
            return;
        }

        ui->textOut->append(QString::fromStdString(it->repr()));

    } else if(category == Online) {
        if (!myLessonsOnline.size()) {
            ui->textOut->RedText("Online lessons are empty");
            return;
        }

        vector<lessonOnline>::iterator it = begin(myLessonsOnline);
        while ((it != (end(myLessonsOnline) - 1)) && ((*it).getLessonParams().id != id)) {
            ++it;
        }
        if ((*it).getLessonParams().id != id) {
            ui->textOut->RedText("Can't find this ID");
            return;
        }

        ui->textOut->append(QString::fromStdString(it->repr()));

    } else if(category == Open) {
        if (!myLessonsOpen.size()) {
            ui->textOut->RedText("Open lessons are empty");
            return;
        }

        vector<lessonOpen>::iterator it = begin(myLessonsOpen);
        while ((it != (end(myLessonsOpen) - 1)) && ((*it).getLessonParams().id != id)) {
            ++it;
        }
        if ((*it).getLessonParams().id != id) {
            ui->textOut->RedText("Can't find this ID");
            return;
        }

        ui->textOut->append(QString::fromStdString(it->repr()));
    }
}
