#include "buttom_widget.h"

Buttom_Widget::Buttom_Widget(QWidget *parent) :
    QWidget(parent)
{
    QFont ft;
//    ft.setBold(true);
    bottom_layout = new QHBoxLayout();
    contract_label = new QLabel("欢迎使用主站性能测试工具");
    contract_label->setStyleSheet("color:#27408B");
    contract_label->setFont(ft);
    bottom_layout->addWidget(contract_label,0,Qt::AlignCenter);
    bottom_layout->setContentsMargins(5,0,0,0);
    setLayout(bottom_layout);
   // this->setLayout(main_Layout);
}
