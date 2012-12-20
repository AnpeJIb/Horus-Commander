#include "general_config_test.h"
#include "config.h"

#include <QtTest/QtTest>

GeneralConfigTest::GeneralConfigTest(QObject *parent)
    : QObject(parent)
{
}

void GeneralConfigTest::initTestCase()
{
    CONFIG::INIT();
}

void GeneralConfigTest::testLangCode()
{
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::GENERAL.langCode() == DEFAULT_LANG_CODE);

    CONFIG::GENERAL.setLangCode(LANG_CODE_EN);
    QVERIFY(CONFIG::GENERAL.langCode() == LANG_CODE_EN);

    CONFIG::GENERAL.setLangCode(LANG_CODE_RU);
    QVERIFY(CONFIG::GENERAL.langCode() == LANG_CODE_RU);

    CONFIG::SAVE();
    CONFIG::GENERAL.setLangCode(LANG_CODE_EN);

    CONFIG::LOAD();
    QVERIFY(CONFIG::GENERAL.langCode() == LANG_CODE_RU);
}

void GeneralConfigTest::cleanupTestCase()
{
    CONFIG::CLEAN_UP();
}
