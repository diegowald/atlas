#include "querycondition.h"

queryCondition::queryCondition(const QString &fieldName, const conditionOperator condition, const QStringList &values, QObject *parent) : QObject(parent)
{
    _fieldName = fieldName;
    _condition = condition;
    _values = values;
}

queryCondition::~queryCondition()
{
}

QString queryCondition::fieldName() const
{
    return _fieldName;
}

queryCondition::conditionOperator queryCondition::condition() const
{
    return _condition;
}

QStringList queryCondition::values() const
{
    return _values;
}
