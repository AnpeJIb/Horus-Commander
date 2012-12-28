#ifndef LISTED_STACK_H
#define LISTED_STACK_H

#include <QFrame>

namespace Ui {
class ListedStack;
}

class ListedStack : public QFrame
{
    Q_OBJECT
    
public:
    explicit ListedStack(int percentPos, int minPos, QWidget *parent = 0);
    ~ListedStack();
    
    void addPage(const QString& name, const QIcon& icon, QWidget* page);
    void setCurrentIndex(int value);

private slots:
    void on_list_currentRowChanged(int currentRow);

private:
    void setSplitterPosition(int percent, int min);

    Ui::ListedStack *ui;
};

#endif // LISTED_STACK_H
