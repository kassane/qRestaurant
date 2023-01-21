#include <QDebug>
#include <QStringList>
#include <QTime>
#include <qtcsv/reader.h>
#include <qtcsv/stringdata.h>
#include <restaurant.hpp>

Restaurant::Restaurant(QObject *parent) : QObject(parent) {}

QString Restaurant::availableHours() const { return m_availableHours; }

void Restaurant::setavailableHours(const QString &availableHours) {
  auto time = QTime::fromString(availableHours);
  qDebug() << time.toString();

  QString file = QStringLiteral(":/restaurant-hours.csv");
  QList<QStringList> strList = QtCSV::Reader::readToList(file);

  // No accumulate content (reload)
  if (!establishment.isEmpty())
    establishment.clear();

  for (auto &&str : strList) {

    // check time format
    if (!time.isValid())
      continue; // skip

    // List all content and search available hour
    auto employeer = str.join(",");
    if (employeer.contains(availableHours))
      establishment << str.at(0); // only restaurant name
  }
  m_availableHours =
      !establishment.isEmpty() ? establishment.join("\n") : "No vacancies!";
  emit availableHoursChanged();
}