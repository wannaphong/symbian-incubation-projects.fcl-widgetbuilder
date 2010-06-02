#include <QFile>
#include <QDir>

#include "publishercreator.h"

PublisherCreator::PublisherCreator(MainWindow& aUi) : iUi( aUi )
{
    copyFiles();
}

void PublisherCreator::copyFiles()
{
    QDir dir;

    // Copy publisher interface as is
    dir.mkpath( iUi.widgetName() + "/publisherif/inc");
    QFile::copy ( "data/publisherif/inc/hspublisher.h",
                  iUi.widgetName() + "/publisherif/inc/hspublisher.h");
    QFile::copy ( "data/publisherif/inc/hspublisherimpl.h",
                  iUi.widgetName() + "/publisherif/inc/hspublisherimpl.h");
    QFile::copy ( "data/publisherif/inc/hswidgetobserver.h",
                  iUi.widgetName() + "/publisherif/inc/hswidgetobserver.h");
    QFile::copy ( "data/publisherif/inc/transaction.h",
                  iUi.widgetName() + "/publisherif/inc/transaction.h");


    dir.mkpath( iUi.widgetName() + "/publisherif/src");
    QFile::copy ( "data/publisherif/src/hspublisher.cpp",
                  iUi.widgetName() + "/publisherif/src/hspublisher.cpp");
    QFile::copy ( "data/publisherif/src/hspublisherimpl.cpp",
                  iUi.widgetName() + "/publisherif/src/hspublisherimpl.cpp");
    QFile::copy ( "data/publisherif/src/transaction.cpp",
                  iUi.widgetName() + "/publisherif/src/transaction.cpp");

    // Copy test publisher
    dir.mkpath( iUi.widgetName() + "/testpublisher/data");
    QFile::copy ( "data/testpublisher/data/testpublisher.rls",
                  iUi.widgetName() + "/testpublisher/data/testpublisher.rls");
    QFile::copy ( "data/testpublisher/data/testpublisher.rss",
                  iUi.widgetName() + "/testpublisher/data/testpublisher.rss");
    QFile::copy ( "data/testpublisher/data/testpublisher_reg.rss",
                  iUi.widgetName() + "/testpublisher/data/testpublisher_reg.rss");

    dir.mkpath( iUi.widgetName() + "/testpublisher/gfx");
    QFile::copy ( "data/testpublisher/gfx/qgn_menu_TestPublisher.svg",
                  iUi.widgetName() + "/testpublisher/gfx/qgn_menu_TestPublisher.svg");
    QFile::copy ( "data/testpublisher/gfx/f1.png",
                  iUi.widgetName() + "/testpublisher/gfx/f1.png");
    QFile::copy ( "data/testpublisher/gfx/cricket.png",
                  iUi.widgetName() + "/testpublisher/gfx/cricket.png");
    QFile::copy ( "data/testpublisher/gfx/tennis.png",
                  iUi.widgetName() + "/testpublisher/gfx/tennis.png");

    dir.mkpath( iUi.widgetName() + "/testpublisher/group");
    QFile::copy ( "data/testpublisher/group/bld.inf",
                  iUi.widgetName() + "/testpublisher/group/bld.inf");
    QFile::copy ( "data/testpublisher/group/icons_scalable_dc.mk",
                  iUi.widgetName() + "/testpublisher/group/icons_scalable_dc.mk");
    QFile::copy ( "data/testpublisher/group/testpublisher.mmp",
                  iUi.widgetName() + "/testpublisher/group/testpublisher.mmp");

    dir.mkpath( iUi.widgetName() + "/testpublisher/inc");
    QFile::copy ( "data/testpublisher/inc/testpublisher.hrh",
                  iUi.widgetName() + "/testpublisher/inc/testpublisher.hrh");
    QFile::copy ( "data/testpublisher/inc/testpublisher.pan",
                  iUi.widgetName() + "/testpublisher/inc/testpublisher.pan");
    QFile::copy ( "data/testpublisher/inc/testpublisherapplication.h",
                  iUi.widgetName() + "/testpublisher/inc/testpublisherapplication.h");
    QFile::copy ( "data/testpublisher/inc/testpublisherappui.h",
                  iUi.widgetName() + "/testpublisher/inc/testpublisherappui.h");
    QFile::copy ( "data/testpublisher/inc/testpublisherappview.h",
                  iUi.widgetName() + "/testpublisher/inc/testpublisherappview.h");
    QFile::copy ( "data/testpublisher/inc/testpublisherdocument.h",
                  iUi.widgetName() + "/testpublisher/inc/testpublisherdocument.h");

    dir.mkpath( iUi.widgetName() + "/testpublisher/sis");
    QFile::copy ( "data/testpublisher/sis/backup_registration.xml",
                  iUi.widgetName() + "/testpublisher/sis/backup_registration.xml");
    QFile::copy ( "data/testpublisher/sis/TestPublisher_S60_3_X_v_1_0_0.pkg",
                  iUi.widgetName() + "/testpublisher/sis/TestPublisher_S60_3_X_v_1_0_0.pkg");

    dir.mkpath( iUi.widgetName() + "/testpublisher/src");
    QFile::copy ( "data/testpublisher/src/testpublisher.cpp",
                  iUi.widgetName() + "/testpublisher/src/testpublisher.cpp");
    QFile::copy ( "data/testpublisher/src/testpublisherapplication.cpp",
                  iUi.widgetName() + "/testpublisher/src/testpublisherapplication.cpp");
    QFile::copy ( "data/testpublisher/src/testpublisherappui.cpp",
                  iUi.widgetName() + "/testpublisher/src/testpublisherappui.cpp");
    //QFile::copy ( "data/testpublisher/src/testpublisherappview.cpp",
    //              iUi.widgetName() + "/testpublisher/src/testpublisherappview.cpp");
    QFile::copy ( "data/testpublisher/src/testpublisherdocument.cpp",
                  iUi.widgetName() + "/testpublisher/src/testpublisherdocument.cpp");

    iUi.replaceData("data/testpublisher/src/testpublisherappview.cpp",
                iUi.widgetName() + "/testpublisher/src/testpublisherappview.cpp" );

}
