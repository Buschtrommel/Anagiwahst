#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QSettings>

/*!
 * \brief The Configuration class.
 */
class Configuration : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(int windowWidth READ getWindowWidth WRITE setWindowWidth NOTIFY windowWidthChanged)
    Q_PROPERTY(int windowHeight READ getWindowHeight WRITE setWindowHeight NOTIFY windowHeightChanged)
    Q_PROPERTY(bool windowMaximized READ hasWindowMaximized WRITE setWindowMaximized NOTIFY windowMaximizedChanged)
    Q_PROPERTY(QString lastSaveAllPath READ getLastSaveAllPath WRITE setLastSaveAllPath NOTIFY lastSaveAllPathChanged)
    Q_PROPERTY(QString lastSaveSinglePath READ getLastSaveSinglePath WRITE setLastSaveSinglePath NOTIFY lastSaveSinglePathChanged)
public:
    Configuration(QObject *parent = nullptr);
    ~Configuration();

    int getWindowWidth() const;
    int getWindowHeight() const;
    bool hasWindowMaximized() const;
    QString getLastSaveAllPath() const;
    QString getLastSaveSinglePath() const;

    void setWindowWidth(const int &windowWidth);
    void setWindowHeight(const int &windowHeight);
    void setWindowMaximized(const bool &windowMaximized);
    void setLastSaveAllPath(const QString &lastSaveAllPath);
    void setLastSaveSinglePath(const QString &lastSaveSinglePath);


signals:
    void windowWidthChanged(const int &windowWidth);
    void windowHeightChanged(const int &windowHeight);
    void windowMaximizedChanged(const bool &windowMaximized);
    void lastSaveAllPathChanged(const QString &lastSaveAllPath);
    void lastSaveSinglePathChanged(const QString &lastSaveSinglePath);

private:
    int m_windowWidth;
    int m_windowHeight;
    bool m_windowMaximized;
    QString m_lastSaveAllPath;
    QString m_lastSaveSinglePath;

};

#endif // CONFIGURATION_H
