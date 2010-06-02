#ifndef RENDERERCREATOR_H
#define RENDERERCREATOR_H

#include <QObject>

#include "mainwindow.h"

class RendererCreator : public QObject
{
public:
    RendererCreator(MainWindow& aUi);
    
private:
    void generateFolders();
    void generateResource();
    void generateBuildFile();
    void generateMMP();
    void generateHeader();
    void generateSource();

    void replaceData( QString sourceFile, QString destFile );

private:
    MainWindow& iUi;
};

#endif // RENDERERCREATOR_H
