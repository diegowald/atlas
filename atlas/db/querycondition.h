#ifndef QUERYCONDITION_H
#define QUERYCONDITION_H

#include <QObject>

class queryCondition : public QObject
{
    Q_OBJECT
public:
    enum class conditionOperator {
        isNull,
        isNotNull,
        equals,
        notEquals,
        like,
        in,
        notIn,
        between,
        greaterThan,
        greaterOrEqual,
        lessThan,
        lessOrEqual
    };
    explicit queryCondition(const QString &fieldName, const conditionOperator condition, const QStringList &values, QObject *parent = nullptr);
    virtual ~queryCondition();

    QString fieldName() const;
    conditionOperator condition() const;
    QStringList values() const;

private:
    QString _fieldName;
    conditionOperator _condition;
    QStringList _values;
};

#endif // QUERYCONDITION_H
