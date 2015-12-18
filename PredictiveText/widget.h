#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

// non-Qt includes //
#include "main.h"
#include "CharTree.h"
#include "functs.h"
#include "TreeEdit.h"
/////////////////////

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    CharTree* tree;

    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_useWordButton_clicked();

    void on_wordEntry_textEdited(const QString &arg1);

    void on_saveTreeButton_clicked();

    void on_reloadTreeButton_clicked();

    void on_clearTextButton_clicked();

    void on_saveTextButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
