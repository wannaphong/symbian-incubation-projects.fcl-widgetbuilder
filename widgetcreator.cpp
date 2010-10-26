#include "widgetcreator.h"
#include <QDir>
#include <QTextStream>
#include <QCheckBox>

WidgetCreator::WidgetCreator(MainWindow& aUi, QObject *parent ) :
    QObject(parent), iUi( aUi )
{
    generateFolders();
    generateBuildFile();
    generateHSPSManifest();
    generateEmptyDat();
    generateHSPSConf();
    generateXml();
    generateCss();
    generateDat();
    generateDtd();
    generatePkg();
    generateBur();
}

QString WidgetCreator::widgetName()
{
    return iUi.widgetName().toLower();
}

QString WidgetCreator::widgetUid()
{
    return iUi.widgetUid().toLower();
}

QString WidgetCreator::widgetLayout()
{
    return iUi.widgetLayout();
}

void WidgetCreator::generateFolders()
{    
    QDir dir;
    dir.mkpath( widgetName() + "/widget");
    dir.setPath( widgetName() + "/widget" );
    dir.mkpath( "group" );
    dir.mkpath( "hsps/00" );
    dir.mkpath( "xuikon/00" );
    dir.mkpath( "sis" );
}

void WidgetCreator::generateBuildFile()
{
    iUi.replaceData("data/commonwidgetdata/group/bld.inf", widgetName() + "/widget/group/bld.inf", 1);
}

void WidgetCreator::generateHSPSManifest()
{
    iUi.replaceData("data/commonwidgetdata/hsps/00/manifest.dat",
                widgetName() + "/widget/hsps/00/manifest.dat");
}

void WidgetCreator::generateHSPSConf()
{
    iUi.replaceData( "data/commonwidgetdata/hsps/00/widgetconfiguration.xml",
                 widgetName() + "/widget/hsps/00/widgetconfiguration.xml" );
}

void WidgetCreator::generateEmptyDat()
{
    QDir dir;
    dir.setPath( widgetName() + "/widget/hsps/00");
    QFile file(dir.filePath("empty.dat"));
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
}

void WidgetCreator::generateXml()
{
    if( iUi.rendererCheckBox().isChecked())
    {
        iUi.replaceData( "data/commonwidgetdata/xuikon/00/replacerenderer.xml",
             widgetName() + "/widget/xuikon/00/" + widgetName() +  ".xml");
    }
    else
    {
        iUi.replaceData( "data/" + widgetLayout() +"/xuikon/00/replace.xml",
             widgetName() + "/widget/xuikon/00/" + widgetName() +  ".xml");
    }

}  
        
void WidgetCreator::generateCss()
{
    if( iUi.rendererCheckBox().isChecked())
    {
        iUi.replaceData( "data/commonwidgetdata/xuikon/00/replacerenderer.css",
             widgetName() + "/widget/xuikon/00/" + widgetName() +  ".css");
    }
    else
    {
        iUi.replaceData( "data/" + widgetLayout() +"/xuikon/00/replace.css",
             widgetName() + "/widget/xuikon/00/" + widgetName() +  ".css");
    }
}

void WidgetCreator::generateDat()
{
    iUi.replaceData("data/commonwidgetdata/xuikon/00/replace.dat",
                widgetName() + "/widget/xuikon/00/" + widgetName() + "_" + iUi.widgetUidNoHex() + ".dat");
}

void WidgetCreator::generateDtd()
{
    QDir dir;
    dir.setPath( widgetName() + "/widget/xuikon/00");
    QFile file(dir.filePath(widgetName()+".dtd"));
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

}

void WidgetCreator::generatePkg()
{
    iUi.replaceData("data/commonwidgetdata/sis/replace.pkg",
                widgetName() + "/widget/sis/"+ widgetName() + ".pkg", 1); // 1 =no hex uid used
   }

void WidgetCreator::generateBur()
{
    QDir dir;
    dir.setPath( widgetName() + "/widget/sis");
    QFile file(dir.filePath("backup_registration.xml"));
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << "<?xml version=\"1.0\" standalone=\"yes\"?>\n"
    << "<backup_registration>\n"
    << "<system_backup/>\n"
    << "<restore requires_reboot = \"no\"/>\n"
    << "</backup_registration>\n";
}
