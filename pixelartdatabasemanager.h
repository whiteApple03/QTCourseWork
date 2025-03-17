#ifndef PIXELARTDATABASEMANAGER_H
#define PIXELARTDATABASEMANAGER_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QSqlDatabase>

class PixelArtDatabaseManager : public QObject {
    Q_OBJECT

public:
    explicit PixelArtDatabaseManager(const QString &dbPath, QObject *parent = nullptr);
    ~PixelArtDatabaseManager();

    bool createTable(const QString &tableName);
    bool saveImage(const QImage &image, const QString &tableName);
    QImage loadImage(const QString &tableName, int imageId);

private:
    QSqlDatabase m_db;
    QString m_dbPath;

    bool openDatabase();
    void closeDatabase();
};

#endif // PIXELARTDATABASEMANAGER_H
