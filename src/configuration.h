/* Anagiwahst - A Qt Property Editor/Creator
 *
 * Copyright (c) 2015-2017 Buschtrommel/Matthias Fehring <kontakt@buschmann23.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    explicit Configuration(QObject *parent = nullptr);
    ~Configuration();

    int getWindowWidth() const;
    int getWindowHeight() const;
    bool hasWindowMaximized() const;
    QString getLastSaveAllPath() const;
    QString getLastSaveSinglePath() const;

    void setWindowWidth(int windowWidth);
    void setWindowHeight(int windowHeight);
    void setWindowMaximized(bool windowMaximized);
    void setLastSaveAllPath(const QString &lastSaveAllPath);
    void setLastSaveSinglePath(const QString &lastSaveSinglePath);


signals:
    void windowWidthChanged(int windowWidth);
    void windowHeightChanged(int windowHeight);
    void windowMaximizedChanged(bool windowMaximized);
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
