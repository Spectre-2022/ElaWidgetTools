#include "T_UpdateWidget.h"

#include <QVBoxLayout>

#include "ElaText.h"
T_UpdateWidget::T_UpdateWidget(QWidget* parent)
    : QWidget{parent}
{
    setMinimumSize(200, 260);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    mainLayout->setContentsMargins(5, 10, 5, 5);
    mainLayout->setSpacing(4);
    ElaText* updateTitle = new ElaText("2024-9-21更新", 15, this);
    ElaText* update1 = new ElaText("1、ElaTheme主题模块重新设计", 13, this);
    ElaText* update2 = new ElaText("2、新增ElaCalendar日历视图、ElaCalendarPicker日历选择器", 13, this);
    ElaText* update3 = new ElaText("3、ElaScrollPage新增自定义窗口模块", 13, this);
    ElaText* update4 = new ElaText("4、新增Setting设置界面", 13, this);
    ElaText* update5 = new ElaText("5、全数风格和细节优化，以及一系列问题修正", 13, this);
    update1->setIsWrapAnywhere(true);
    update2->setIsWrapAnywhere(true);
    update3->setIsWrapAnywhere(true);
    update4->setIsWrapAnywhere(true);
    update5->setIsWrapAnywhere(true);

    mainLayout->addWidget(updateTitle);
    mainLayout->addWidget(update1);
    mainLayout->addWidget(update2);
    mainLayout->addWidget(update3);
    mainLayout->addWidget(update4);
    mainLayout->addWidget(update5);
    mainLayout->addStretch();
}

T_UpdateWidget::~T_UpdateWidget()
{
}
