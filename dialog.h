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

    void on_check_a_clicked();

    void on_check_a_star_clicked();

private:
    Ui::Dialog *ui;
    QString input;
    Map Dfs,Bfs,BestFirst,A,A_Star;

    int s_x,s_y,e_x,e_y;
    int box_size;

    void _draw_map(const Map&map,QPainter* painter);


};

#endif // DIALOG_H
