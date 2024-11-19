#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("qt-web.db");
    if(!db.open()) {
        qDebug() << "Failed to open Database!!..";
    } else {
        qDebug() << "Connected to Database Successfully..";
    }
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Items("
               "id INTEGER PRIMARY KEY"
               "name TEXT)");
}

void DatabaseManager::addItem(const QString& name) {
    QSqlQuery query;
    query.prepare("INSERT INTO Items (name) VALUES (:name)");
    query.bindValue(":name", name);
    if(!query.exec()) {
        qDebug() << "Failed to insert item!! " ;
    }
}
QStringList DatabaseManager::fetchItems() {
    QStringList Items;
    QSqlQuery query("SELECT name FROM Items");
    while(query.next()) {
        Items << query.value(0).toString();
    }
    return Items;
}
