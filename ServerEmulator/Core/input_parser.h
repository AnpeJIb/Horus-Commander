#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <QObject>

class InputParser : public QObject
{
    Q_OBJECT
public:
    explicit InputParser(QObject *parent = 0);
    
public slots:
    void parseString(const QString& str);
};

#endif // INPUT_PARSER_H
