#include <QFontDatabase>
#include <QApplication>

#include "core/settings.h"
#include "core/mainwindow.h"


/**
 * @brief main
 * @param argc
 * @param argv
 * @return DEBUG comments are placed in lines SOLELY for DEBUG purposes.
 * In development stage (when executing on real dashboard with real motorbike) you are encouraged to remove all lines
 * and modules with the DEBUG mark.
 * Thanks,
 *             The developers.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName(QString::fromUtf8("QuartodilitroUNIPD"));
    QCoreApplication::setOrganizationDomain(QString::fromUtf8("quartodilitro.it"));
    QCoreApplication::setApplicationName(QString::fromUtf8("Dashboard"));

    QFontDatabase fontDB;  // set global font in app
    int font_id = fontDB.addApplicationFont(":/font/orbitron");
    if (font_id >= 0) {
        QString font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
        a.setFont(QFont(font_family));
    }

    MainWindow w;
    w.setAutoFillBackground(true);
    w.updateSettings();
    w.show();

    return a.exec();
}
