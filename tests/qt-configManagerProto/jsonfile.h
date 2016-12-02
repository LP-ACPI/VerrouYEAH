#ifndef JSONFILE_H
#define JSONFILE_H

#include <QObject>
#include <QFile>
#include <QVariant>

class JsonFile : public QObject
{
Q_OBJECT
Q_PROPERTY(QString name READ name WRITE setName)
Q_PROPERTY(QString fileName READ fileName)
Q_PROPERTY(bool exists READ exists)
Q_PROPERTY(bool writeable READ writeable)
Q_PROPERTY(bool readable READ readable)
Q_PROPERTY(qint64 size READ size)
Q_PROPERTY(QString error READ error)

private:
    QFile m_file;
    QString m_error;

public:
    explicit JsonFile(QObject *parent = 0);
    JsonFile(const QString &name, QObject *parent = 0);

    inline QString name() const { return m_file.fileName(); }
    QString fileName() const;
    inline bool exists() const { return m_file.exists(); }
    inline bool writeable() const { return m_file.permissions().testFlag(QFileDevice::WriteUser); }
    inline bool readable() const { return m_file.permissions().testFlag(QFileDevice::ReadUser); }
    inline qint64 size() const { return m_file.size(); }
    inline QString error() const { return m_error; }

    Q_INVOKABLE QString relativeFilePath(const QString &dir = QString()) const;

    Q_INVOKABLE bool write(const QVariant &data);
    Q_INVOKABLE QVariant read();


};

#endif // JSONFILE_H
