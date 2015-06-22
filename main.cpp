#include <QApplication>
#include <QJsonObject>
#include <QQmlApplicationEngine>

namespace slackfish {
class User : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY updated)
    Q_PROPERTY(QString name READ name NOTIFY updated)
    Q_PROPERTY(QUrl image READ image NOTIFY updated)
public:
    User() {}

    void fromJson(const QJsonObject &json) {
        _id = json[QStringLiteral("id")].toString();
        _name = json[QStringLiteral("name")].toString();
        _image_48 = json[QStringLiteral("image_48")].toString();
        emit updated();
    }

    QString id() const { return _id; }
    QString name() const { return _name; }
    QUrl image() const { return _image_48; }

signals:
    void updated();

private:
    QString _id;
    QString _name;
    QUrl _image_48;
};

class SlackApi {
public:
    explicit SlackApi(const QString &token) : _token(token) {
    }

private:
    QString _token;
};

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
