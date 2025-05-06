#ifndef T_TABLEVIEW_DELEGATE_H
#define T_TABLEVIEW_DELEGATE_H

#include "T_BasePage.h"

class ElaTableView;
class T_TableView_Delegate : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit T_TableView_Delegate(QWidget* parent = nullptr);
    ~T_TableView_Delegate();
private:
    ElaTableView* _tableView{nullptr};
};

#endif // T_TABLEVIEW_DELEGATE_H
