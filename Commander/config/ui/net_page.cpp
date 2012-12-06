#include "net_page.h"
#include "ui_net_page.h"
#include "config.h"

#include <QMessageBox>

NetPage::NetPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetPage)
{
    ui->setupUi(this);
}

NetPage::~NetPage()
{
    delete ui;
}

QString NetPage::pageName()
{
    return ui->pageName->text();
}

bool NetPage::save()
{
    QString localIP = ui->LocalIP->text();

    if (localIP.isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Local IP"),
                              tr("Local IP is not set!"),
                              QMessageBox::Close);
        return false;
    }

    CONFIG::NET.setLocalIP(                 localIP);
    CONFIG::NET.setClientPort(              ui->ClientPort->value());
    CONFIG::NET.setLocalPort(               ui->LocalPort->value());
    CONFIG::NET.setChannelsCount(           ui->ChannelsCount->value());

    CONFIG::NET.setAllowCustomSkins(        ui->AllowCustomSkins->isChecked());

    CONFIG::NET.setCheckClientTimeSpeed(    ui->CheckClientTimeSpeed->isChecked());
    CONFIG::NET.setCheckClientTimeSpeed(    ui->CheckServerTimeSpeed->isChecked());

    CONFIG::NET.setCheckTimeSpeedDifferense(ui->CheckTimeSpeedDifferense->value());
    CONFIG::NET.setCheckTimeSpeedInterval(  ui->CheckTimeSpeedInterval->value());

    CONFIG::NET.setCheaterWarningDelay(     ui->CheaterWarningDelay->value());
    CONFIG::NET.setCheaterWarningNum(       ui->CheaterWarningNum->value());

    CONFIG::NET.setFarMaxLagTime(           ui->FarMaxLagTime->value());
    CONFIG::NET.setNearMaxLagTime(          ui->NearMaxLagTime->value());

    return true;
}

void NetPage::load()
{
    ui->AllowCustomSkins->setChecked(       CONFIG::NET.allowCustomSkins());

    ui->CheckClientTimeSpeed->setChecked(   CONFIG::NET.checkClientTimeSpeed());
    ui->CheckServerTimeSpeed->setChecked(   CONFIG::NET.checkServerTimeSpeed());

    ui->CheckTimeSpeedDifferense->setValue( CONFIG::NET.checkTimeSpeedDifferense());
    ui->CheckTimeSpeedInterval->setValue(   CONFIG::NET.checkTimeSpeedInterval());

    ui->ClientPort->setValue(               CONFIG::NET.clientPort());
    ui->LocalPort->setValue(                CONFIG::NET.localPort());
    ui->LocalIP->setText(                   CONFIG::NET.localIP());
    ui->ChannelsCount->setValue(            CONFIG::NET.channelsCount());

    ui->CheaterWarningDelay->setValue(      CONFIG::NET.cheaterWarningDelay());
    ui->CheaterWarningNum->setValue(        CONFIG::NET.cheaterWarningNum());

    ui->FarMaxLagTime->setValue(            CONFIG::NET.farMaxLagTime());
    ui->NearMaxLagTime->setValue(           CONFIG::NET.nearMaxLagTime());

    loadChildren();
}

void NetPage::loadDefaults()
{
    ui->AllowCustomSkins->setChecked(       DEFAULT_ALLOW_CUSTOM_SKINS);

    ui->CheckClientTimeSpeed->setChecked(   DEFAULT_CHECK_CLIENT_TIME_SPEED);
    ui->CheckServerTimeSpeed->setChecked(   DEFAULT_CHECK_SERVER_TIME_SPEED);

    ui->CheckTimeSpeedDifferense->setValue( DEFAULT_CHECK_TIME_SPEED_DIFFERENSE);
    ui->CheckTimeSpeedInterval->setValue(   DEFAULT_CHECK_TIME_SPEED_INTERVAL);

    ui->ClientPort->setValue(               DEFAULT_CLIENT_PORT);
    ui->LocalPort->setValue(                DEFAULT_LOCAL_PORT);
    ui->LocalIP->setText(                   DEFAULT_LOCAL_IP);
    ui->ChannelsCount->setValue(            DEFAULT_CHANNELS_COUNT);

    ui->CheaterWarningDelay->setValue(      DEFAULT_CHEATER_WARNING_DELAY);
    ui->CheaterWarningNum->setValue(        DEFAULT_CHEATER_WARNING_NUM);

    ui->FarMaxLagTime->setValue(            DEFAULT_FAR_MAX_LAG_TIME);
    ui->NearMaxLagTime->setValue(           DEFAULT_NEAR_MAX_LAG_TIME);

    loadChildrenDefaults();
}

void NetPage::on_ChannelsCount_valueChanged(int value)
{
    ui->ChannelsLb->setText(QString::number(value));
}
