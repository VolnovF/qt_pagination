#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    //Ui::Widget *ui;
    QVBoxLayout *background;
    QHBoxLayout *search_box;
    QLineEdit *search_line;
    QPushButton *search_button;
    QListView *view;
    QHBoxLayout *pagination_bar;
    QSpacerItem *pagination_bar_l_spacer;
    QPushButton *prev_button;
    QPushButton *next_button;
    QSpacerItem *pagination_bar_r_spacer;
public slots:
    void beginSearch();
signals:
    void search(QString request);
    void setCurrentPage(int page);
};
#endif // WIDGET_H
