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
    dir.mkpath( iUi.widgetName().toLower() + "/renderingplugin");
    dir.setPath( iUi.widgetName().toLower() + "/renderingplugin");
    dir.mkpath( "data" );
    dir.mkpath( "group" );
    dir.mkpath( "inc" );
    dir.mkpath( "src" );
}

void RendererCreator::generateResource()
{
    QString widgetName( iUi.widgetName().toLower() );
    QString rendererName( iUi.rendererName().toLower() );

    iUi.replaceData("data/renderingplugin/data/renderer.rss",
                widgetName + "/renderingplugin/data/" + rendererName +  "renderer.rss");
}

void RendererCreator::generateBuildFile()
{
    QString widgetName( iUi.widgetName().toLower() );

    iUi.replaceData("data/renderingplugin/group/bld.inf",
                 widgetName + "/renderingplugin/group/bld.inf");
}

void RendererCreator::generateMMP()
{
    QString widgetName( iUi.widgetName().toLower() );
    QString rendererName( iUi.rendererName().toLower() );

    iUi.replaceData("data/renderingplugin/group/renderer.mmp",
                widgetName + "/renderingplugin/group/" + rendererName +  "renderer.mmp");
}

void RendererCreator::generateHeader()
{
    QString widgetName( iUi.widgetName().toLower() );
    QString rendererName( iUi.rendererName().toLower() );

    iUi.replaceData("data/renderingplugin/inc/renderer.h",
                 widgetName + "/renderingplugin/inc/" + rendererName +  "renderer.h");
}

void RendererCreator::generateSource()
{
    QString widgetName( iUi.widgetName().toLower() );
    QString rendererName( iUi.rendererName().toLower() );

    iUi.replaceData("data/renderingplugin/src/renderer.cpp",
                widgetName + "/renderingplugin/src/" + rendererName +  "renderer.cpp");
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
        if( line.contains("#replace#Renderer.h", Qt::CaseInsensitive ))
        {
            line.replace(QString("#replace#"), iUi.rendererName().toLower());
        }
        else
        {
            line.replace(QString("#replace#"), iUi.rendererName());
            line.replace(QString("#replaceuid#"), iUi.rendererUid());
        }
        out << line << "\n";
    }
}
