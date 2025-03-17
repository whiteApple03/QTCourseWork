#include "PixelArtDatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QBuffer>
#include <QDebug>

PixelArtDatabaseManager::PixelArtDatabaseManager(const QString &dbPath, QObject *parent)
    : QObject(parent), m_dbPath(dbPath) {
}

PixelArtDatabaseManager::~PixelArtDatabaseManager() {
    closeDatabase();
}

bool PixelArtDatabaseManager::openDatabase() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_dbPath);

    if (!m_db.open()) {
        qDebug() << "Error opening database:" << m_db.lastError().text();
        return false;
    }
    return true;
}

void PixelArtDatabaseManager::closeDatabase() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool PixelArtDatabaseManager::createTable(const QString &tableName) {
    if (!openDatabase()) return false;

    QSqlQuery query(m_db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS " + tableName + " (id INTEGER PRIMARY KEY AUTOINCREMENT, image BLOB)")) {
        qDebug() << "Error creating table:" << query.lastError().text();
        closeDatabase();
        return false;
    }

    closeDatabase();
    return true;
}

bool PixelArtDatabaseManager::saveImage(const QImage& image, const QString &tableName) {
    if (!openDatabase()) return false;

    QSqlQuery query(m_db);

    // Read image from file
    if (image.isNull()) {
        closeDatabase();
        return false;
    }

    // Convert image to PNG format and store in QByteArray
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    if (!image.save(&buffer, "PNG")) {
        qDebug() << "Error saving image to buffer";
        closeDatabase();
        return false;
    }
    buffer.close();

    // Prepare SQL query
    query.prepare("INSERT INTO " + tableName + " (image) VALUES (?)");
    query.addBindValue(imageData);

    // Execute query
    if (!query.exec()) {
        qDebug() << "Error inserting image:" << query.lastError().text();
        closeDatabase();
        return false;
    }

    closeDatabase();
    return true;
}

QImage PixelArtDatabaseManager::loadImage(const QString &tableName, int imageId) {
    if (!openDatabase()) return QImage();

    QSqlQuery query(m_db);
    query.prepare("SELECT image FROM " + tableName + " WHERE id = ?");
    query.addBindValue(imageId);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        closeDatabase();
        return QImage(); // Return an invalid image
    }

    if (query.next()) {
        QByteArray imageData = query.value(0).toByteArray();
        QImage image;
        image.loadFromData(imageData, "PNG"); // Or other format as needed
        closeDatabase();
        return image;
    } else {
        qDebug() << "Image with id" << imageId << "not found";
        closeDatabase();
        return QImage(); // Return an invalid image
    }
}

