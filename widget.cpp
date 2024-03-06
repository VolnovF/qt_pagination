#include "widget.h"
//#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::Widget)
{
    //ui->setupUi(this);
    background = new QVBoxLayout;

    search_box = new QHBoxLayout;
    search_line = new QLineEdit;
    search_button = new QPushButton("Поиск");
    search_box->addWidget(search_line);
    search_box->addSpacing(20);
    search_box->addWidget(search_button);

    view = new QListView;

    pagination_bar = new QHBoxLayout;
    pagination_bar_l_spacer = new QSpacerItem{20, 2, QSizePolicy::Expanding, QSizePolicy::Fixed};
    pagination_bar_r_spacer = new QSpacerItem{20, 2, QSizePolicy::Expanding, QSizePolicy::Fixed};
    prev_button = new QPushButton("<");
    next_button = new QPushButton(">");
    pagination_bar->addSpacerItem(pagination_bar_l_spacer);
    pagination_bar->addWidget(prev_button);
    pagination_bar->addWidget(next_button);
    pagination_bar->addSpacerItem(pagination_bar_r_spacer);

    background->addLayout(search_box);
    background->addWidget(view);
    background->addLayout(pagination_bar);
    setLayout(background);

}

Widget::~Widget()
{
    //delete ui;
}

void Widget::beginSearch()
{
    emit setCurrentPage(0);
    emit search(search_line->text());
}

