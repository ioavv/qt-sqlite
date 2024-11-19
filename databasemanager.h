#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QObject>


class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject* parent = nullptr);

    Q_INVOKABLE void addItem(const QString& name);
    Q_INVOKABLE QStringList fetchItems();
};

#endif // DATABASEMANAGER_H
