#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    box_size(0),
    Dfs(Map::method_DFS),
    Bfs(Map::method_BFS),
    BestFirst(Map::method_BestFirst),
    A(Map::method_A),
    A_Star(Map::method_A_Star)
{
    ui->setupUi(this);
    box_size = ui->verticalSlider->value();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    int top = 110;
    int left = 10;
    int radius = box_size/5;

    painter.drawRect(left,top,box_size*Dfs.getWidth(),box_size*Dfs.getHeight());

    if(Dfs.getValid()|| Bfs.getValid() ||BestFirst.getValid() || A.getValid() || A_Star.getValid())
    {
        painter.setBrush(QBrush(QColor(0,0,0,200)));
        for(int i=0;i<Dfs.getHeight();++i)
        {
            for(int j=0;j<Dfs.getWidth();++j)
            {
                if(Dfs.get_value(j,i) == Map::value_wall) painter.drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
            }
        }
    }

    if(ui->check_bfs->isChecked() && Bfs.getValid()) _draw_map(Bfs,&painter);
    if(ui->check_dfs->isChecked() && Dfs.getValid()) _draw_map(Dfs,&painter);
    if(ui->check_best->isChecked() && BestFirst.getValid()) _draw_map(BestFirst,&painter);
    if(ui->check_a->isChecked() && A.getValid()) _draw_map(A,&painter);
    if(ui->check_a_star->isChecked() && A.getValid()) _draw_map(A_Star,&painter);



    if(Dfs.getValid()|| Bfs.getValid() || BestFirst.getValid() || A.getValid() || A_Star.getValid())
    {
        painter.setPen(Qt::black);
        if(ui->check_bfs->isChecked() || ui->check_dfs->isChecked()) painter.setPen(Qt::white);
        painter.drawText(QRect(left+s_x*box_size,top+s_y*box_size,box_size,box_size),Qt::AlignCenter,"s");
        painter.drawText(QRect(left+e_x*box_size,top+e_y*box_size,box_size,box_size),Qt::AlignCenter,"e");
    }
}

void Dialog::on_calc_clicked()
{
    bool dfs,bfs,bestfirst,a,a_star;
    if(ui->textEdit_map_input->toPlainText() == "" || ui->start_x->text() == "" || ui->start_y->text() == "" || ui->end_x->text() == "" || ui->end_y->text() == "") return;
    s_x = ui->start_x->text().toInt();
    s_y = ui->start_y->text().toInt();
    e_x = ui->end_x->text().toInt();
    e_y = ui->end_y->text().toInt();

    // set a map information
    Bfs.set(ui->textEdit_map_input->toPlainText());
    Dfs.set(ui->textEdit_map_input->toPlainText());
    BestFirst.set(ui->textEdit_map_input->toPlainText());
    A.set(ui->textEdit_map_input->toPlainText());
    A_Star.set(ui->textEdit_map_input->toPlainText());

    // find result road.
    dfs = Dfs.find_road(s_x,s_y,e_x,e_y);
    bfs = Bfs.find_road(s_x,s_y,e_x,e_y);
    bestfirst = BestFirst.find_road(s_x,s_y,e_x,e_y);
    a = A.find_road(s_x,s_y,e_x,e_y);
    a_star = A_Star.find_road(s_x,s_y,e_x,e_y);

    if(bfs == false || dfs == false || bestfirst == false || a == false || a_star == false) return;        // can not calculate
    ui->label_bfs_step->setText(QString("%1 Step").arg(Bfs.getResult_step()));
    ui->label_dfs_step->setText(QString("%1 Step").arg(Dfs.getResult_step()));
    ui->label_best_step->setText(QString("%1 Step").arg(BestFirst.getResult_step()));
    ui->label_a_step->setText(QString("%1 step").arg(A.getResult_step()));
    ui->label_a_star_step->setText(QString("%1 step").arg(A_Star.getResult_step()));

    ui->label_dfs_visit_step->setText(QString("%1 Visit").arg(Dfs.getVisit_step()));
    ui->label_bfs_visit_step->setText(QString("%1 Visit").arg(Bfs.getVisit_step()));
    ui->label_best_visit_step->setText(QString("%1 Visit").arg(BestFirst.getVisit_step()));
    ui->label_a_visit_step->setText(QString("%1 Visit").arg(A.getVisit_step()));
    ui->label_a_star_visit_step->setText(QString("%1 Visit").arg(A_Star.getVisit_step()));

    // clear all input information
    ui->textEdit_map_input->clear();
    ui->start_x->clear();
    ui->start_y->clear();
    ui->end_x->clear();
    ui->end_y->clear();
    repaint();
}


void Dialog::on_check_dfs_clicked()
{
    repaint();
}

void Dialog::on_check_bfs_clicked()
{
    repaint();
}

void Dialog::on_verticalSlider_valueChanged(int value)
{
    box_size = value;
    repaint();
}

void Dialog::on_check_best_clicked()
{
    repaint();
}

void Dialog::on_check_a_clicked()
{
    repaint();
}

void Dialog::on_check_a_star_clicked()
{
    repaint();
}

void Dialog::_draw_map(const Map&map,QPainter* painter)
{
//    QPainter painter(this);
    QColor visit;
    QColor step;
    int top = 110;
    int left = 10;
    int radius = box_size/5;

    switch(map.getMethod())
    {
    case Map::method_BFS:
        visit = QColor(100,0,0,100);
        step = QColor(255,0,0,200);
        break;
    case Map::method_DFS:
        visit = QColor(0,0,100,100);
        step = QColor(0,0,255,200);
        break;
    case Map::method_BestFirst:
        visit = QColor(0,100,0,100);
        step = QColor(0,255,0,200);
        break;
    case Map::method_A:
        visit = QColor(0,100,100,100);
        step = QColor(0,255,255,200);
        break;
    case Map::method_A_Star:
        visit = QColor(100,100,0,100);
        step = QColor(255,255,0,200);
        break;
    }

    for(int i=0;i<map.getHeight();++i)
    {
        for(int j=0;j<map.getWidth();++j)
        {
            if(map.get_state(j,i) == Map::state_visit)
            {
                painter->setBrush(QBrush(visit));
                painter->setPen(QPen(visit));
                painter->drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
            }
            if(map.get_state(j,i) == Map::state_solution)
            {
                painter->setBrush(QBrush(step));
                painter->setPen(QPen(step));
                painter->drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
            }
        }
    }
}
