#ifndef ICLICKABLE_H
#define ICLICKABLE_H

#include <QPainter>

class IClickable
{
public:
    virtual bool CheckClicked() = 0;
    virtual bool CheckMouseOver(QPainter*) = 0;
    bool clicked;
};

#endif // ICLICKABLE_H
