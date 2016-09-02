/* Anagiwahst - A Qt Property Editor/Creator
 *
 * Copyright (c) 2015 Buschtrommel/Matthias Fehring <kontakt@buschmann23.de>
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

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlEngine>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTextStream>
#include <QLocale>
#include <QTranslator>
#include <QQmlContext>

#include "property.h"
#include "propertymodel.h"
#include "propertywriter.h"
#include "configuration.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationDisplayName(QStringLiteral("Anagiwahst"));
    app.setApplicationName(QStringLiteral("Anagiwahst"));
    app.setOrganizationDomain(QStringLiteral("buschmann23.de"));
    app.setOrganizationName(QStringLiteral("Buschtrommel"));
    app.setApplicationVersion(QStringLiteral(APP_VERSION));

    QString locale = QLocale::system().name();

    QTranslator *translator = new QTranslator;
    if (translator->load(QStringLiteral("anagiwahst_")+locale, QStringLiteral(L10N_DIR))) {
        app.installTranslator(translator);
    }

    if (argc > 1) {

        QCommandLineParser clparser;
        clparser.setApplicationDescription(QCoreApplication::translate("main","Anagiwahst is a Qt property creator/editor."));
        clparser.addHelpOption();
        clparser.addVersionOption();
        clparser.addPositionalArgument(QStringLiteral("<class name>"), QCoreApplication::translate("main", "The class name."));
        clparser.addPositionalArgument(QStringLiteral("<type>"), QCoreApplication::translate("main", "Default type for all properties or list of related data types."));
        clparser.addPositionalArgument(QStringLiteral("<property>"), QCoreApplication::translate("main", "The name of the property or list of properties."));

        QCommandLineOption privateOption(QStringList() << QStringLiteral("p") << QStringLiteral("private"), QCoreApplication::translate("main", "The class has a private section in a separate file."));
        clparser.addOption(privateOption);

        QCommandLineOption noReadOption(QStringLiteral("no-read"), QCoreApplication::translate("main", "Do not create a read accessor function."));
        clparser.addOption(noReadOption);

        QCommandLineOption noWriteOption(QStringLiteral("no-write"), QCoreApplication::translate("main", "Do not create a write accessor function."));
        clparser.addOption(noWriteOption);

        QCommandLineOption noNotifyOption(QStringLiteral("no-notify"), QCoreApplication::translate("main", "Do not add a notify signal."));
        clparser.addOption(noNotifyOption);

        QCommandLineOption memberOption(QStringList() << QStringLiteral("m") << QStringLiteral("member"), QCoreApplication::translate("main", "Use a member variable association."));
        clparser.addOption(memberOption);

        QCommandLineOption unsetOption(QStringList() << QStringLiteral("u") << QStringLiteral("unset"), QCoreApplication::translate("main", "Create a reset/unset function."));
        clparser.addOption(unsetOption);

        QCommandLineOption outputOption(QStringList() << QStringLiteral("o") << QStringLiteral("output"), QCoreApplication::translate("main", "Write the output directly into files in <director>."), QCoreApplication::translate("main", "directory"));
        clparser.addOption(outputOption);

        QCommandLineOption forceOption(QStringList() << QStringLiteral("f") << QStringLiteral("force"), QCoreApplication::translate("main", "Force overwriting existing files. (If output directory is specified.)"));
        clparser.addOption(forceOption);

        clparser.process(app);

        const QStringList args = clparser.positionalArguments();

        if (args.size() < 3) {
            clparser.showHelp(1);
        }

        const QString className = args.at(0);
        const QString typeString = args.at(1);
        const QString propString = args.at(2);

        QStringList types = typeString.split(' ');
        const QStringList props = propString.split(' ');

        if (!props.isEmpty()) {

            if (types.size() < props.size()) {

                quint8 diffSize = props.size() - types.size();
                QString lastType = types.last();

                for (quint8 i = 0; i < diffSize; ++i) {
                    types.append(lastType);
                }

            }

            QString outputDir = clparser.value(outputOption);

            bool privateClass = clparser.isSet(privateOption);
            bool read = !clparser.isSet(noReadOption);
            bool write = !clparser.isSet(noWriteOption);
            bool notify = !clparser.isSet(noNotifyOption);
            bool member = clparser.isSet(memberOption);
            bool unset = clparser.isSet(unsetOption);

            if (!read) {
                member = true;
            }

            if (read && write) {
                member = false;
            }

            PropertyModel propModel;
            propModel.setClassName(className);

            for (int i = 0; i < props.size(); ++i) {

                propModel.addProperty(props.at(i),types.at(i), read, write, member, unset, notify, privateClass);

            }

            if (outputDir.isEmpty()) {
                QTextStream out(stdout, QIODevice::WriteOnly);
                out << "=========================================================================\n";
                out << "||                          Header file                                ||\n";
                out << "=========================================================================\n";
                out << propModel.createOutput(PropertyModel::HeaderFile) << "\n";
                out.flush();

                if (privateClass) {
                    out << "\n\n\n";
                    out << "=========================================================================\n";
                    out << "||                         Private header file                          ||\n";
                    out << "=========================================================================\n";
                    out << propModel.createOutput(PropertyModel::PrivateHeaderFile) << "\n";
                    out.flush();
                }
                out << "\n\n\n";
                out << "=========================================================================\n";
                out << "||                            Code file                                ||\n";
                out << "=========================================================================\n";
                out << propModel.createOutput(PropertyModel::CodeFile) << "\n";
                out.flush();

            } else {

                bool force = clparser.isSet(forceOption);

                if (!PropertyWriter::write(PropertyWriter::HeaderFile, outputDir, className, propModel.createOutput(PropertyModel::HeaderFile), force)) {
                    return 2;
                }
                if (privateClass) {
                    PropertyWriter::write(PropertyWriter::PrivateHeaderFile, outputDir, className, propModel.createOutput(PropertyModel::PrivateHeaderFile), force);
                }
                PropertyWriter::write(PropertyWriter::CodeFile, outputDir, className, propModel.createOutput(PropertyModel::CodeFile), force);

            }
        }

        return 0;
    }

    Configuration configuration;

    qmlRegisterType<Property>("Buschtrommel.Anagiwahst", 1, 0, "Property");
    qmlRegisterType<PropertyModel>("Buschtrommel.Anagiwahst.Models", 1, 0, "PropertyModel");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("config"), &configuration);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
