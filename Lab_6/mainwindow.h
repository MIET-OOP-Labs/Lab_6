#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lesson.h"
#include "lessonOnline.h"
#include "lessonOpen.h"
#include "lessonsHandler.h"
#include "myTextBrowser.h"
#include <QDebug>
#include <sstream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void findLesson();
    void addLesson();
    void reprLesson();

private slots:
    void on_chooseFile_clicked();
private:
    Ui::MainWindow *ui;

    const int maxLessonsNum = 100;

    vector<lesson> myLessons;
    vector<lessonOnline> myLessonsOnline;
    vector<lessonOpen> myLessonsOpen;

    lessonsHandler *mylessonsHandler;

    void printLessonsRecords(vector<lesson> lessonRecords);
    void printLessonsRecords(vector<lessonOpen> lessonRecords);
    void printLessonsRecords(vector<lessonOnline> lessonRecords);

    string repr(lesson lessonToRepr);
    string repr(lessonOnline lessonToRepr);
    string repr(lessonOpen lessonToRepr);

    void readFile(AbstractReader & pReader, string myFile);
};
#endif // MAINWINDOW_H
