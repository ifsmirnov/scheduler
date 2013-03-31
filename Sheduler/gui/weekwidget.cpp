#include "weekwidget.hpp"

#include "daywidget.hpp"

WeekWidget::WeekWidget(std::vector<DayWidget*> dayWidgets, QWidget *parent) :
    QWidget(parent), dayWidgets(dayWidgets)
{
    //for (auto dayWidget : dayWidgets)
    /*{
        dayWidget.setParent(this);
    }*/
}

void WeekWidget::paintEvent(QPaintEvent *)
{

}
