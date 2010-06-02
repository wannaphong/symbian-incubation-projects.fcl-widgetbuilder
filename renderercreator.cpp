#include "renderercreator.h"
#include <QDir>
#include <QTextStream>


RendererCreator::RendererCreator(MainWindow& aUi) : iUi( aUi )
{
    generateFolders();
    generateResource();
    generateBuildFile();
    generateMMP();
    generateHeader();
    generateSource();
}

void RendererCreator::generateFolders()
{
    QDir dir;
    dir.mkpath( iUi.widgetName() + "/renderingplugin");
    dir.setPath( iUi.widgetName() + "/renderingplugin");
    dir.mkpath( "data" );
    dir.mkpath( "group" );
    dir.mkpath( "inc" );
    dir.mkpath( "src" );
}

void RendererCreator::generateResource()
{
    iUi.replaceData("data/renderingplugin/data/renderer.rss",
                iUi.widgetName() + "/renderingplugin/data/" + iUi.rendererName() +  "renderer.rss");
}

void RendererCreator::generateBuildFile()
{
    iUi.replaceData("data/renderingplugin/group/bld.inf",
                 iUi.widgetName() + "/renderingplugin/group/bld.inf");
}

void RendererCreator::generateMMP()
{
    iUi.replaceData("data/renderingplugin/group/renderer.mmp",
                iUi.widgetName() + "/renderingplugin/group/" + iUi.rendererName() +  "renderer.mmp");
}

void RendererCreator::generateHeader()
{
    iUi.replaceData("data/renderingplugin/inc/renderer.h",
                 iUi.widgetName() + "/renderingplugin/inc/" + iUi.rendererName() +  "renderer.h");
}

void RendererCreator::generateSource()
{
    iUi.replaceData("data/renderingplugin/src/renderer.cpp",
                iUi.widgetName() + "/renderingplugin/src/" + iUi.rendererName() +  "renderer.cpp");
}

void RendererCreator::replaceData( QString sourceFile, QString destFile )
{
    QFile infile(sourceFile);
    if (!infile.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&infile);

    QFile outfile(destFile);
    if (!outfile.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream out(&outfile);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        line.replace(QString("#replace#"), iUi.rendererName());
        line.replace(QString("#replaceuid#"), iUi.rendererUid());
        out << line << "\n";
    }
}
