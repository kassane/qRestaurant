#pragma once
#include <QStringList>
#include <QObject>
#include <qqml.h>

class Restaurant : public QObject {
    
    Q_OBJECT
    Q_PROPERTY(QString availableHours READ availableHours WRITE setavailableHours NOTIFY availableHoursChanged)
    QML_ELEMENT

    public:
        explicit Restaurant(QObject* parent = nullptr);
        void setavailableHours(const QString& availableHours);
        QString availableHours() const;
        void print();
    private:
     QStringList establishment;
     QString m_availableHours;

    signals:
        void availableHoursChanged();
};
