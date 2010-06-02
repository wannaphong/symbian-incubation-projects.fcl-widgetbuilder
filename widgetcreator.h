#ifndef WIDGETCREATOR_H
#define WIDGETCREATOR_H

#include <QObject>

#include "mainwindow.h"

class QString;

class WidgetCreator : public QObject
{
    Q_OBJECT
public:
    explicit WidgetCreator( MainWindow& aUi, QObject *parent = 0);

signals:

public slots:

private:
    void generateFolders();
    void generateBuildFile();
    void generateHSPSManifest();
    void generateEmptyDat();
    void generateHSPSConf();
    void generateXml();
    void generateCss();
    void generateDat();
    void generateDtd();
    void generatePkg();
    void generateBur();

    QString widgetName();
    QString widgetUid();
    QString widgetLayout();

private:
    MainWindow& iUi;

};

#endif // WIDGETCREATOR_H
