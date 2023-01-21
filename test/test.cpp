#include <QObject>
#include <QTest>
#include <QTime>
#include <qtcsv/reader.h>
#include <qtcsv/stringdata.h>
#include <restaurant.hpp>
#include <QDebug>

class Tst : public QObject {
  Q_OBJECT

public:
  Tst();

private Q_SLOTS:
  void initTestCase();

private:
  QTime time;
  QStringList times;
  QList<QStringList> strList;
};

Tst::Tst() {
  strList = QtCSV::Reader::readToList(QStringLiteral(":/restaurant-hours.csv"));
}

void Tst::initTestCase() {
  // Verify Content
  QVERIFY(!strList.isEmpty());

  // Verify Time
  QVERIFY(time.isNull());

  // hours
  for (auto &&str : strList) {
    auto hours = str.at(1).split("-");
    times = QStringList() << hours.join("\n");
  }

  // remove "" (latest) element
  times.removeLast();
  
  for (auto &&t : times) {
    time.fromString(t);
    qDebug() << "Debug: " << time.toString();
    QVERIFY2(time.isValid(), "Valid time format.");
  }

}

QTEST_MAIN(Tst)
#include "test.moc"