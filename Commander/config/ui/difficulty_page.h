#ifndef DIFFICULTY_PAGE_H
#define DIFFICULTY_PAGE_H

#include <QWidget>
#include <QList>
#include <QListWidgetItem>
#include "uiconfig_module.h"
#include "named_page.h"
#include "difficulty_subpage.h"

namespace Ui {
class DifficultyPage;
}

class DifficultyPage : public QWidget, public UIConfigModule, public NamedPage
{
    Q_OBJECT
    
public:
    explicit DifficultyPage(QWidget *parent = 0);
    ~DifficultyPage();

    bool save();
    void load();
    void loadDefaults();

    QString pageName();
    
private slots:
    void on_easyButton_clicked();
    void on_normalButton_clicked();
    void on_realButton_clicked();
    void on_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void setSplitterPos();
    void addPages();

    Ui::DifficultyPage *ui;
    QList<DifficultySubpage*> subpages;
};

#endif // DIFFICULTY_PAGE_H
