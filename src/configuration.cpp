#include "configuration.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \brief Constructs an empty Configuration.
 */
Configuration::Configuration(QObject *parent) : QSettings(parent)
{
    m_windowWidth = value(QStringLiteral("window/width"), 640).toInt();
    m_windowHeight = value(QStringLiteral("window/height"), 480).toInt();
    m_windowMaximized = value(QStringLiteral("window/maximized"), false).toBool();
    m_lastSaveAllPath = value(QStringLiteral("save/allPath")).toString();
    m_lastSaveSinglePath = value(QStringLiteral("save/singlePath")).toString();
}


/*!
 * \brief Deconstructs Configuration.
 */
Configuration::~Configuration()
{
}


/*!
 * \property Configuration::windowWidth
 * \brief Width of the window when the Application was closed.
 *
 * \par Access functions:
 * <TABLE><TR><TD>int</TD><TD>getWindowWidth() const</TD></TR><TR><TD>void</TD><TD>setWindowWidth(int windowWidth)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>windowWidthChanged(int windowWidth)</TD></TR></TABLE>
 */

/*!
 * \fn void Configuration::windowWidthChanged(const int &windowWidth)
 * \brief Part of the \link Configuration::windowWidth windowWidth \endlink property.
 */

/*!
 * \brief Part of the \link Configuration::windowWidth windowWidth \endlink property.
 */
int Configuration::getWindowWidth() const { return m_windowWidth; }

/*!
 * \brief Part of the \link Configuration::windowWidth windowWidth \endlink property.
 */
void Configuration::setWindowWidth(int windowWidth)
{
    if (windowWidth != m_windowWidth) {
        m_windowWidth = windowWidth;
#ifdef QT_DEBUG
        qDebug() << "Changed windowWidth to" << m_windowWidth;
#endif
        setValue(QStringLiteral("window/width"), m_windowWidth);
        
        emit windowWidthChanged(getWindowWidth());
    }
}




/*!
 * \property Configuration::windowHeight
 * \brief Height of the window when the application was closed.
 *
 * \par Access functions:
 * <TABLE><TR><TD>int</TD><TD>getWindowHeight() const</TD></TR><TR><TD>void</TD><TD>setWindowHeight(int windowHeight)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>windowHeightChanged(int windowHeight)</TD></TR></TABLE>
 */

/*!
 * \fn void Configuration::windowHeightChanged(const int &windowHeight)
 * \brief Part of the \link Configuration::windowHeight windowHeight \endlink property.
 */

/*!
 * \brief Part of the \link Configuration::windowHeight windowHeight \endlink property.
 */
int Configuration::getWindowHeight() const { return m_windowHeight; }

/*!
 * \brief Part of the \link Configuration::windowHeight windowHeight \endlink property.
 */
void Configuration::setWindowHeight(int windowHeight)
{
    if (windowHeight != m_windowHeight) {
        m_windowHeight = windowHeight;
#ifdef QT_DEBUG
        qDebug() << "Changed windowHeight to" << m_windowHeight;
#endif
        setValue(QStringLiteral("window/height"), m_windowHeight);
        
        emit windowHeightChanged(getWindowHeight());
    }
}




/*!
 * \property Configuration::windowMaximized
 * \brief Stores if the window was maximized when it was closed.
 *
 * \par Access functions:
 * <TABLE><TR><TD>bool</TD><TD>hasWindowMaximized() const</TD></TR><TR><TD>void</TD><TD>setWindowMaximized(bool windowMaximized)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>windowMaximizedChanged(bool windowMaximized)</TD></TR></TABLE>
 */

/*!
 * \fn void Configuration::windowMaximizedChanged(const bool &windowMaximized)
 * \brief Part of the \link Configuration::windowMaximized windowMaximized \endlink property.
 */

/*!
 * \brief Part of the \link Configuration::windowMaximized windowMaximized \endlink property.
 */
bool Configuration::hasWindowMaximized() const { return m_windowMaximized; }

/*!
 * \brief Part of the \link Configuration::windowMaximized windowMaximized \endlink property.
 */
void Configuration::setWindowMaximized(bool windowMaximized)
{
    if (windowMaximized != m_windowMaximized) {
        m_windowMaximized = windowMaximized;
#ifdef QT_DEBUG
        qDebug() << "Changed windowMaximized to" << m_windowMaximized;
#endif
        setValue(QStringLiteral("window/maximized"), m_windowMaximized);
        
        emit windowMaximizedChanged(hasWindowMaximized());
    }
}




/*!
 * \property Configuration::lastSaveAllPath
 * \brief Last used path to save all files.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>getLastSaveAllPath() const</TD></TR><TR><TD>void</TD><TD>setLastSaveAllPath(const QString & lastSaveAllPath)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>lastSaveAllPathChanged(const QString & lastSaveAllPath)</TD></TR></TABLE>
 */

/*!
 * \fn void Configuration::lastSaveAllPathChanged(const QString &lastSaveAllPath)
 * \brief Part of the \link Configuration::lastSaveAllPath lastSaveAllPath \endlink property.
 */

/*!
 * \brief Part of the \link Configuration::lastSaveAllPath lastSaveAllPath \endlink property.
 */
QString Configuration::getLastSaveAllPath() const { return m_lastSaveAllPath; }

/*!
 * \brief Part of the \link Configuration::lastSaveAllPath lastSaveAllPath \endlink property.
 */
void Configuration::setLastSaveAllPath(const QString & lastSaveAllPath)
{
    if (lastSaveAllPath != m_lastSaveAllPath) {
        m_lastSaveAllPath = lastSaveAllPath;
#ifdef QT_DEBUG
        qDebug() << "Changed lastSaveAllPath to" << m_lastSaveAllPath;
#endif
        setValue(QStringLiteral("save/allPath"), m_lastSaveAllPath);
        
        emit lastSaveAllPathChanged(getLastSaveAllPath());
    }
}




/*!
 * \property Configuration::lastSaveSinglePath
 * \brief Last used path to save a single file.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>getLastSaveSinglePath() const</TD></TR><TR><TD>void</TD><TD>setLastSaveSinglePath(const QString & lastSaveSinglePath)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>lastSaveSinglePathChanged(const QString & lastSaveSinglePath)</TD></TR></TABLE>
 */

/*!
 * \fn void Configuration::lastSaveSinglePathChanged(const QString &lastSaveSinglePath)
 * \brief Part of the \link Configuration::lastSaveSinglePath lastSaveSinglePath \endlink property.
 */

/*!
 * \brief Part of the \link Configuration::lastSaveSinglePath lastSaveSinglePath \endlink property.
 */
QString Configuration::getLastSaveSinglePath() const { return m_lastSaveSinglePath; }

/*!
 * \brief Part of the \link Configuration::lastSaveSinglePath lastSaveSinglePath \endlink property.
 */
void Configuration::setLastSaveSinglePath(const QString & lastSaveSinglePath)
{
    if (lastSaveSinglePath != m_lastSaveSinglePath) {
        m_lastSaveSinglePath = lastSaveSinglePath;
#ifdef QT_DEBUG
        qDebug() << "Changed lastSaveSinglePath to" << m_lastSaveSinglePath;
#endif
        setValue(QStringLiteral("save/singlePath"), m_lastSaveSinglePath);
        
        emit lastSaveSinglePathChanged(getLastSaveSinglePath());
    }
}




