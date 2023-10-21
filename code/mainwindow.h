
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTableWidget>
#include <QImageWriter>
#include <QtGui/private/qzipwriter_p.h>
#include <QtGui/private/qzipreader_p.h>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomTableWidgetItem : public QTableWidgetItem {
public:
    bool operator <(const QTableWidgetItem &other) const override {
        return text().toInt() < other.text().toInt();
    }
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int row;

private slots:
    void on_file_clicked();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_5_toggled(bool checked);

    void on_pushButton_clicked();

    void on_radioButton_6_toggled(bool checked);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QString folderPath;
    std::set<QUrl> files;
    void imageProcessing();
    bool column1(QTableWidgetItem* item1, QTableWidgetItem* item2);
    bool column2(QTableWidgetItem* item1, QTableWidgetItem* item2);
    bool column3(QTableWidgetItem* item1, QTableWidgetItem* item2);
    bool column4(QTableWidgetItem* item1, QTableWidgetItem* item2);
    bool column5(QTableWidgetItem* item1, QTableWidgetItem* item2);


};

#endif // MAINWINDOW_H
