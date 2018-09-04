#include <QtTest/QtTest>
#include <ghgJson/QJsonObject>

#define PARSER_DEBUG


class QJsonObjectTest : public QObject
{
  Q_OBJECT
private slots:

  void testIteration()
  {
    ghg::QJsonObject object{
      {"string_key", "value1"},
      {"decimal_key", 1.12},
      {"boolean_key", true}
    };

    for (auto i = object.begin(); i != object.end(); ++i) {
      i.key();
      i.value();
    }
  }

};


QTEST_APPLESS_MAIN(QJsonObjectTest)
#include "QJsonObjectTest.moc"
