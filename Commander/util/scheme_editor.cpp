#include "scheme_editor.h"
#include "ui_scheme_editor.h"

#include <QMessageBox>

SchemeEditor::SchemeEditor(Domain::Parameters::Scheme *scheme, SchemeJudge *judge, QWidget *parent)
    :   QDialog(parent),
        ui(new Ui::SchemeEditor),
        m_scheme(scheme),
        m_judge(judge)
{
    ui->setupUi(this);
    load();
}

SchemeEditor::~SchemeEditor()
{
    delete ui;
}

void SchemeEditor::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->buttonRole(button))
    {
        case QDialogButtonBox::RejectRole:
            close();
            break;
        case QDialogButtonBox::AcceptRole:
            if (isValid())
            {
                apply();
                accept();
            }
            break;
        default:;
    }
}

void SchemeEditor::load()
{
    ui->schemeTitle->setText(m_scheme->title);
    ui->schemeDescr->setText(m_scheme->description);
}

bool SchemeEditor::isValid()
{
    if (ui->schemeTitle->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Undefined value"),
                              tr("Scheme's title is undefined!"),
                              QMessageBox::Close);
        return false;
    }

    if (m_judge->isTitleAcceptable(m_scheme, ui->schemeTitle->text())==false)
    {
        QMessageBox::critical(this,
                              tr("Invalid value"),
                              tr("Scheme's title is invalid!"),
                              QMessageBox::Close);
        return false;
    }

    return true;
}

void SchemeEditor::apply()
{
    QString descr = ui->schemeDescr->text();

    m_scheme->title = ui->schemeTitle->text();
    m_scheme->description = (descr.isEmpty())?tr("No scheme description"):descr;
}
