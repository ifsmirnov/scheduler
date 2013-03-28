#include "daywidget.hpp"
#include "weekwidget.hpp"

WeekWidget::WeekWidget(std::vector<DayWidget*> dayWidgets, QWidget *parent) :
    dayWidgets(dayWidgets), QWidget(parent)
{
    //for (auto dayWidget : dayWidgets)
    {
        dayWidget.setParent(this);
    }
}

void WeekWidget::paintEvent(QPaintEvent *)
{

}
