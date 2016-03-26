#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    box_size(0)
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
    QPainter painter(this);
    int top = 110;
    int left = 10;
    int radius = box_size/5;

    painter.drawRect(left,top,box_size*Dfs.getWidth(),box_size*Dfs.getHeight());

    if(Dfs.getValid()|| Bfs.getValid() ||BestFirst.getValid())
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

    if(ui->check_bfs->isChecked() && Bfs.getValid())
    {
        for(int i=0;i<Bfs.getHeight();++i)
        {
            for(int j=0;j<Bfs.getWidth();++j)
            {
                if(Bfs.get_state(j,i) == Map::state_visit)
                {
                    painter.setBrush(QBrush(QColor(100,0,0,100)));
                    painter.setPen(QPen(QColor(100,0,0,100)));
                    painter.drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
                }
                if(Bfs.get_state(j,i) == Map::state_solution)
                {
                    painter.setBrush(QBrush(QColor(255,0,0,200)));
                    painter.setPen(QPen(QColor(255,0,0,20)));
                    painter.drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
                }
            }
        }
    }

    if(ui->check_dfs->isChecked() && Dfs.getValid())
    {
        for(int i=0;i<Dfs.getHeight();++i)
        {
            for(int j=0;j<Dfs.getWidth();++j)
            {
                if(Dfs.get_state(j,i) == Map::state_visit)
                {
                    painter.setBrush(QBrush(QColor(0,0,100,100)));
                    painter.setPen(QPen(QColor(0,0,100,100)));
                    painter.drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
                }
                if(Dfs.get_state(j,i) == Map::state_solution)
                {
                    painter.setBrush(QBrush(QColor(0,0,255,200)));
                    painter.setPen(QPen(QColor(0,0,255,200)));
                    painter.drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
                }
            }
        }
    }

    if(ui->check_best->isChecked() && BestFirst.getValid())
    {
        for(int i=0;i<BestFirst.getHeight();++i)
        {
            for(int j=0;j<BestFirst.getWidth();++j)
            {
                if(BestFirst.get_state(j,i) == Map::state_visit)
                {
                    painter.setBrush(QBrush(QColor(0,100,0,100)));
                    painter.setPen(QPen(QColor(0,100,0,100)));
                    painter.drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
                }
                if(BestFirst.get_state(j,i) == Map::state_solution)
                {
                    painter.setBrush(QBrush(QColor(0,255,0,200)));
                    painter.setPen(QPen(QColor(0,255,0,200)));
                    painter.drawRoundedRect(QRect(left+j*box_size,top+i*box_size,box_size,box_size),radius,radius);
                }
            }
        }
    }

    if(Dfs.getValid()|| Bfs.getValid() || BestFirst.getValid())
    {
    painter.setPen(Qt::black);
    if(ui->check_bfs->isChecked() || ui->check_dfs->isChecked()) painter.setPen(Qt::white);
    painter.drawText(QRect(left+s_x*box_size,top+s_y*box_size,box_size,box_size),Qt::AlignCenter,"s");
    painter.drawText(QRect(left+e_x*box_size,top+e_y*box_size,box_size,box_size),Qt::AlignCenter,"e");
    }
}

void Dialog::on_calc_clicked()
{
    bool dfs,bfs,bestfirst;
    if(ui->textEdit_map_input->toPlainText() == "" || ui->start_x->text() == "" || ui->start_y->text() == "" || ui->end_x->text() == "" || ui->end_y->text() == "") return;
    s_x = ui->start_x->text().toInt();
    s_y = ui->start_y->text().toInt();
    e_x = ui->end_x->text().toInt();
    e_y = ui->end_y->text().toInt();

    Bfs.set(ui->textEdit_map_input->toPlainText());
    Dfs.set(ui->textEdit_map_input->toPlainText());
    BestFirst.set(ui->textEdit_map_input->toPlainText());
    dfs = Dfs.find_road(s_x,s_y,e_x,e_y,Map::method_DFS);
    bfs = Bfs.find_road(s_x,s_y,e_x,e_y,Map::method_BFS);
    bestfirst = BestFirst.find_road(s_x,s_y,e_x,e_y,Map::method_BestFirst);

    if(bfs == false || dfs == false || bestfirst == false) return;        // can not calculate
    ui->label_bfs_step->setText(QString("%1 Step").arg(Bfs.getResult_step()));
    ui->label_dfs_step->setText(QString("%1 Step").arg(Dfs.getResult_step()));
    ui->label_best_step->setText(QString("%1 Step").arg(BestFirst.getResult_step()));

    ui->label_dfs_visit_step->setText(QString("%1 Visit").arg(Dfs.getVisit_step()));
    ui->label_bfs_visit_step->setText(QString("%1 Visit").arg(Bfs.getVisit_step()));
    ui->label_best_visit_step->setText(QString("%1 Visit").arg(BestFirst.getVisit_step()));

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
