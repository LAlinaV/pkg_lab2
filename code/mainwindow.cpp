
#include <iostream>
#include <string>
#include <algorithm>
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab->setColumnCount(6);
    ui->tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->tab->setHorizontalHeaderItem(1, new QTableWidgetItem("Format"));
    ui->tab->setHorizontalHeaderItem(2, new QTableWidgetItem("Size"));
    ui->tab->setHorizontalHeaderItem(3, new QTableWidgetItem("Extension"));
    ui->tab->setHorizontalHeaderItem(4, new QTableWidgetItem("Color depth"));
    ui->tab->setHorizontalHeaderItem(5, new QTableWidgetItem("Compression"));

    ui->tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    row = 0; // начинаем заполнение таблицы с нулевой строки
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_file_clicked()
{
    QString filter = "Images (*.jpg *.gif *.tif *.bmp *.png *.pcx *.BMP *JPG)";
    QString initialDirectory = QDir::homePath(); // Путь к начальной папке

    QFileDialog dialog(nullptr, "Выберите файл(ы)", initialDirectory, filter);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
    {
        QList<QUrl> urls = dialog.selectedUrls();
        std::set<QUrl> newFiles(urls.begin(), urls.end());
        files = newFiles;
        folderPath = dialog.directory().absolutePath();
        imageProcessing();
        ui->path->setText(folderPath);
    }


}



bool MainWindow::column1(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text() > item2->text();
}


bool MainWindow::column2(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    QStringList string1 = item1->text().split('x');
    QStringList string2 = item2->text().split('x');
    if (string1[0].toInt() > string2[0].toInt())
    {
        return true;
    }
    return false;
}

bool MainWindow::column3(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text() > item2 -> text();
}

bool MainWindow::column4(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text().toInt() > item2->text().toInt();
}

bool MainWindow::column5(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    return item1->text().toInt() > item2->text().toInt();
}
void MainWindow::on_radioButton_toggled(bool checked)
{

    if (checked)
    ui->tab->sortItems(0,Qt::AscendingOrder);
}


void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (checked)
        ui->tab->sortItems(1);
}


void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if (checked)
        ui->tab->sortItems(2);
}


void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if (checked)
        ui->tab->sortItems(3);
}


void MainWindow::on_radioButton_5_toggled(bool checked)
{
    if (checked)
        ui->tab->sortItems(4);
}


void MainWindow::on_pushButton_clicked()
{
    folderPath = QFileDialog::getExistingDirectory(nullptr, "Выберите папку", QDir::homePath());

        if (!folderPath.isEmpty())
        {
            QDir dir(folderPath);
            QStringList filters;
            filters << "*.jpg"
                    << "*.gif"
                    << "*.tif"
                    << "*.bmp"
                    << "*.png"
                    << "*.pcx"
                    << "*.JPG"
                    << "*.BMP";
            dir.setNameFilters(filters);

            QList<QUrl> f;
            for (const QFileInfo &fileInfo : dir.entryInfoList())
            {
                f.append(QUrl::fromLocalFile(fileInfo.filePath()));
            }
            std::set<QUrl> newFiles(f.begin(), f.end());

            files = newFiles;
            imageProcessing();
        }
        ui->path->setText(folderPath);
}

void MainWindow::imageProcessing()
{
        for (std::set<QUrl>::iterator it = files.begin(); it != files.end(); ++it)
        {
            int row = ui->tab->rowCount();
            ui->tab->insertRow(row);

            QString fileName = "", resolution = "", type = "";
            QFile temp((*it).toLocalFile());
            QImage im((*it).toLocalFile());
            QImageWriter a((*it).toLocalFile());
            int compression = a.compression();

            if (temp.fileName().lastIndexOf('.') == -1)
            {
                ui->tab->setRowCount(ui->tab->rowCount() - 1);
                continue;
            }

            for (int i = temp.fileName().lastIndexOf('.'); i < temp.fileName().size(); i++)
            {
                type.append(temp.fileName()[i]);
            }

            if (type == ".jpg" || type == "*.JPG")
            {
                compression = im.text("JPEGQuality").toInt();
            }
            else if (type == ".tif")
            {
                compression = im.text("Compression").toInt();
            }
            else if (type == ".png")
            {
                compression = im.text("CompressionLevel").toInt();
            }

            resolution = QString::number((int)(im.dotsPerMeterX() * 0.0254)) + "x" + QString::number((int)(im.dotsPerMeterY() * 0.0254));

            for (int i = temp.fileName().lastIndexOf('/') + 1; i < temp.fileName().lastIndexOf('.'); i++)
            {
                fileName.append(temp.fileName()[i]);
            }

            ui->tab->setItem(row, 0, new QTableWidgetItem(fileName));
            ui->tab->setItem(row, 1, new QTableWidgetItem(type));
            ui->tab->setItem(row, 2, new QTableWidgetItem(QString::number(im.size().width()) + "x" + QString::number(im.size().height())));
            ui->tab->setItem(row, 3, new QTableWidgetItem(resolution));
            ui->tab->setItem(row, 4, new QTableWidgetItem(QString::number(im.bitPlaneCount())));
            ui->tab->setItem(row, 5, new QTableWidgetItem(compression < 0 ? "None" : QString::number(compression)));
        }
}

void MainWindow::on_radioButton_6_toggled(bool checked)
{
        if (checked)
            ui->tab->sortItems(5);
}


void MainWindow::on_pushButton_2_clicked()
{
        ui->tab->clear();
        ui->tab->setColumnCount(6);
        ui->tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tab->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
        ui->tab->setHorizontalHeaderItem(1, new QTableWidgetItem("Format"));
        ui->tab->setHorizontalHeaderItem(2, new QTableWidgetItem("Size"));
        ui->tab->setHorizontalHeaderItem(3, new QTableWidgetItem("Extension"));
        ui->tab->setHorizontalHeaderItem(4, new QTableWidgetItem("Color depth"));
        ui->tab->setHorizontalHeaderItem(5, new QTableWidgetItem("Compression"));

        ui->tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        row = 0;
}

