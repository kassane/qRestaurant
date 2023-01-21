#pragma once
#include <QObject>
#include <QStringList>
#include <qqml.h>

class Restaurant : public QObject {

  Q_OBJECT
  Q_PROPERTY(QString availableHours READ availableHours WRITE setavailableHours
                 NOTIFY availableHoursChanged)
  QML_ELEMENT

public:
  explicit Restaurant(QObject *parent = nullptr);
  void setavailableHours(const QString &availableHours);
  QString availableHours() const;

private:
  QStringList establishment;
  QString m_availableHours;

signals:
  void availableHoursChanged();
};
