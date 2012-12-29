#ifndef SCHEME_EDITOR_H
#define SCHEME_EDITOR_H

#include <QDialog>
#include <QAbstractButton>

#include "scheme.h"
#include "scheme_judge.h"

using namespace Domain::Parameters;

namespace Ui {
class SchemeEditor;
}

class SchemeEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit SchemeEditor(Scheme* scheme, SchemeJudge *judge, QWidget *parent = 0);
    ~SchemeEditor();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    void load();
    bool isValid();
    void apply();

    Ui::SchemeEditor *ui;
    Scheme* m_scheme;
    SchemeJudge* m_judge;
};

#endif // SCHEME_EDITOR_H
