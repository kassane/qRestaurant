#include <qdebug.h>
#include <qnamespace.h>
#include <restaurant.hpp>
#include <QStringList>
#include <qtcsv/stringdata.h>
#include <qtcsv/reader.h>
#include <QDebug>
#include <QTime>

Restaurant::Restaurant(QObject* parent): QObject(parent) {}

QString Restaurant::availableHours() const{
    return m_availableHours;
}

void Restaurant::setavailableHours(const QString& availableHours) {
    auto time = QTime::fromString(availableHours);
    qDebug() << time.toString();
    QString file = ":/restaurant-hours.csv";
    QList<QStringList> strList = QtCSV::Reader::readToList(file);
    if(!establishment.isEmpty()) establishment.clear();

    for (auto&& str : strList) {
        if (!time.isValid()){
            m_availableHours = "";
            continue;
        };
        auto employeer = str.join(",");
        if (employeer.contains(availableHours))
            establishment << str.at(0);
    }
    m_availableHours = !establishment.isEmpty() ? establishment.join("\n") : "No vacancies!";
    // qDebug() << this->availableHours();
    emit availableHoursChanged();
}

void Restaurant::print() {
    if (establishment.isEmpty()) qDebug() << "No vacancies!";
    for (auto&& values : establishment) qDebug() << values;
}