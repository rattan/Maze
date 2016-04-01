#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QPoint>
#include <QList>
#include <QPaintEvent>
#include <QPainter>

#include "map.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void paintEvent(QPaintEvent *event);

private slots:

    void on_calc_clicked();

    void on_check_dfs_clicked();

    void on_check_bfs_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_check_best_clicked();

private:
    Ui::Dialog *ui;
    QString input;
    Map Dfs,Bfs,BestFirst;

    int s_x,s_y,e_x,e_y;
    int box_size;


};

#endif // DIALOG_H
