#include <QtTest/QtTest>
#include <ghgJson/QJsonDocument>
#include <ghgJson/QJsonObject>

#define PARSER_DEBUG


class QJsonDocumentTest : public QObject
{
  Q_OBJECT
private slots:

  void testToDecimal()
  {
    ghg::QJsonValue value(ghg::QDecimal("0.57"));
    auto decimal = value.toDecimal();
    QCOMPARE(decimal, ghg::QDecimal("0.57"));
    QCOMPARE(decimal.ToString(), std::string("0.57"));
  }

  void testAssignDecimalToObject()
  {
    ghg::QJsonObject object;
    object["value"] = ghg::QDecimal("0.57");
    QCOMPARE(object["value"].toDecimal(), ghg::QDecimal("0.57"));
  }

  void testParsedThenToDecimal()
  {
    auto document = ghg::QJsonDocument::fromJson("{\"value\": 0.57}");
    QCOMPARE(document.object()["value"].toDecimal(), ghg::QDecimal("0.57"));
    QCOMPARE(document.object()["value"].toDecimal().ToString(), std::string("0.57"));
  }

  void testCopyJsonValue()
  {
    ghg::QJsonValue value(ghg::QDecimal("0.57"));
    ghg::QJsonValue copy(value);
    QCOMPARE(value.toDecimal(), copy.toDecimal());
  }

  void testCopyJsonObject()
  {
    auto document = ghg::QJsonDocument::fromJson("{\"value\": 0.57}");
    ghg::QJsonDocument copy(document);
    QCOMPARE(document.object()["value"].toDecimal(), copy.object()["value"].toDecimal());
  }

  void testCopyTemporaryJsonObject()
  {
    auto object = getTemporary();
    QCOMPARE(object["value"].toDecimal(), ghg::QDecimal("0.57"));
  }

  void testParseNumber()
  {
    QString value("0.57");
    auto document = ghg::QJsonDocument::fromJson(QByteArray("{\"value\": ") + value.toUtf8() + "}");
    QVERIFY2(document.object()["value"].isDouble(), "'value' must be a double.");

    const auto& tmp = document.object()["value"].toDecimal().ToString();
    auto decimalRepresentation = QString(tmp.c_str());
    QCOMPARE(decimalRepresentation, value);

    auto doubleRepresentation = QString::number(document.object()["value"].toDouble(), 'f', 18);
    const auto& error  =(QString("double representation should not exactly equal ") + value).toStdString();
    QVERIFY2(doubleRepresentation != value, error.c_str());
  }

  void testParseNumberBelow()
  {
    QString value("0.569999999999999950");
    auto document = ghg::QJsonDocument::fromJson(QByteArray("{\"value\": ") + value.toUtf8() + "}");
    QVERIFY2(document.object()["value"].isDouble(), "'value' must be a double.");

    ttmath::Conv conv;
    conv.base = 10;
    conv.round = 18;
    conv.trim_zeroes = false;
    const auto& tmp = document.object()["value"].toDecimal().ToString(conv);
    auto decimalRepresentation = QString(tmp.c_str());
    QCOMPARE(decimalRepresentation, value);

    auto doubleRepresentation = QString::number(document.object()["value"].toDouble(), 'f', 18);
    const auto& error  =(QString("double representation should not exactly equal ") + value).toStdString();
    QVERIFY2(doubleRepresentation != value, error.c_str());
  }

  void testParseNumberExact()
  {
    QString value("0.569999999999999951");
    auto document = ghg::QJsonDocument::fromJson(QByteArray("{\"value\": ") + value.toUtf8() + "}");
    QVERIFY2(document.object()["value"].isDouble(), "'value' must be a double.");

    ttmath::Conv conv;
    conv.base = 10;
    conv.round = 18;
    conv.trim_zeroes = false;
    const auto& tmp = document.object()["value"].toDecimal().ToString(conv);
    auto decimalRepresentation = QString(tmp.c_str());
    QCOMPARE(decimalRepresentation, value);

    auto doubleRepresentation = QString::number(document.object()["value"].toDouble(), 'f', 18);
    const auto& error  =(QString("double representation should be exactly equal ") + value).toStdString();
    QVERIFY2(doubleRepresentation == value, error.c_str());
  }

  void testParseNumberAbove()
  {
    QString value("0.569999999999999952");
    auto document = ghg::QJsonDocument::fromJson(QByteArray("{\"value\": ") + value.toUtf8() + "}");
    QVERIFY2(document.object()["value"].isDouble(), "'value' must be a double.");

    ttmath::Conv conv;
    conv.base = 10;
    conv.round = 18;
    conv.trim_zeroes = false;
    const auto& tmp = document.object()["value"].toDecimal().ToString(conv);
    auto decimalRepresentation = QString(tmp.c_str());
    QCOMPARE(decimalRepresentation, value);

    auto doubleRepresentation = QString::number(document.object()["value"].toDouble(), 'f', 18);
    const auto& error  =(QString("double representation should not exactly equal ") + value).toStdString();
    QVERIFY2(doubleRepresentation != value, error.c_str());
  }

  void testBackConversion()
  {
    auto document = ghg::QJsonDocument::fromJson("{\"bool\": true, \"integer\": 1, \"number\": 1.5, \"string\": \"string\"}");
    auto json = document.toJson();
    QCOMPARE(document, ghg::QJsonDocument::fromJson(json));
  }

private:

  ghg::QJsonObject getTemporary()
  {
    ghg::QJsonObject object;
    object["value"] = ghg::QDecimal("0.57");
    qDebug() << object["value"];
    return object;
  }

};


QTEST_APPLESS_MAIN(QJsonDocumentTest)
#include "QJsonDocumentTest.moc"
