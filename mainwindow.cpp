#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgetcreator.h"
#include "renderercreator.h"
#include "publishercreator.h"

#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), iLayoutIndex( 0 ), iLayoutCount( -1 )
{
    ui->setupUi(this);
    iTimer = new QTimer(this);
    connect(iTimer, SIGNAL(timeout()), this, SLOT(updateLayout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString MainWindow::widgetName()
{
    return ui->widgetName->text();
}

QString MainWindow::widgetUid()
{
    return ui->widgetUid->text().toLower();
}

QCheckBox& MainWindow::rendererCheckBox()
{
    return *ui->renderingCheckBox;
}

QString MainWindow::rendererName()
{
    return ui->rendererName->text();
}

QString MainWindow::rendererUid()
{
    return ui->rendererUid->text().toLower();
}

void MainWindow::on_pushButton_clicked()
{
    if( widgetName().isEmpty() || widgetUid().isEmpty() )
    {
        QMessageBox msgBox;
        msgBox.setText("Widget name and UID must be given.");
        msgBox.exec();
        return;
    }

    bool ok;
    uint uidVal = widgetUid().toUInt(&ok, 16 );
    if( widgetUid().length() != 10 || !widgetUid().startsWith( "0x",Qt::CaseInsensitive ) || !ok )
    {
        QMessageBox msgBox;
        msgBox.setText("UID must be in 4 byte hexadecimal format\n 0x11223344.");
        msgBox.exec();
        return;
    }

    if( uidVal >= 2147483648 ) //0x80000000
    {
        QMessageBox msgBox;
        msgBox.setText("UID must be less than\n 0x80000000.");
        msgBox.exec();
        return;
    }

    if (widgetLayout().length() == 0 && !rendererCheckBox().isChecked())
    {
        QMessageBox msgBox;
        msgBox.setText("Layout data not available yet.");
        msgBox.exec();
        return;
    }

    generateMainBuildFile();

    PublisherCreator* publisherCreator = new PublisherCreator(*this);
    delete publisherCreator;
    
    WidgetCreator* widgetCreator = new WidgetCreator(*this);
    delete widgetCreator;
    
    if( ui->renderingCheckBox->isChecked() )
    {
        if( rendererName().isEmpty() || rendererUid().isEmpty() )
        {
            QMessageBox msgBox;
            msgBox.setText("Renderer name and UID must be given.");
            msgBox.exec();
            return;
        }
        if( rendererUid().length() != 10 || !rendererUid().startsWith( "0x",Qt::CaseInsensitive ))
        {
            QMessageBox msgBox;
            msgBox.setText("UID must be in hexadecimal format\n 0x11223344.");
            msgBox.exec();
            return;
        }
        RendererCreator * renderer = new RendererCreator(*this);
        delete renderer;
    }

    QMessageBox msgBox;
    msgBox.setText("Widget created.");
    msgBox.exec();
    return;
}

void MainWindow::generateMainBuildFile()
{
    QDir dir;
    dir.mkpath( widgetName().toLower() + "/group");
    dir.setPath( widgetName().toLower() + "/group");
    QFile file( dir.filePath("bld.inf"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    generateLicense( out );
    
    //out << "#include \"../publisherif/group/bld.inf\"\n";
    out << "#include \"../testpublisher/group/bld.inf\"\n";
    out << "#include \"../widget/group/bld.inf\"\n";
    if( ui->renderingCheckBox->isChecked() )
    {
        out << "#include \"../renderingplugin/group/bld.inf\"\n\n";
    }
    out << "// End of File\n";
}

void MainWindow::generateLicense( QTextStream& aStream )
{
    aStream << "/*\n";
    aStream << "* Copyright (c) {Year(s)} {Copyright owner}.\n";
    aStream << "* All rights reserved.\n";
    aStream << "* This component and the accompanying materials are made available\n";
    aStream << "* under the terms of the \"Eclipse Public License v1.0\"\n";
    aStream << "* which accompanies this distribution, and is available\n";
    aStream << "* at the URL \"http://www.symbianfoundation.org/legal/sfl-v10.html\".\n";
    aStream << "*\n";
    aStream << "* Initial Contributors:\n";
    aStream << "* {Name} {Company} – Initial contribution\n";
    aStream << "*\n";
    aStream << "* Contributors:\n";
    aStream << "* {Name} {Company} – {{Description of contribution}}\n";
    aStream << "*\n";
    aStream << "* Description:\n";
    aStream << "* {{Description of the file}}\n";
    aStream << "*\n";
    aStream << "*/\n\n";
}

QString MainWindow::widgetUidNoHex()
{
    QString uid( widgetUid() );
    if( uid.startsWith( "0x",Qt::CaseInsensitive ))
    {
        return uid.right(8);
    }
    else
    {
        return uid;
    }

}

void MainWindow::replaceData( QString sourceFile, QString destFile, bool noHexUid )
{
    QString path = QDir::currentPath();
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
        line.replace(QString("#replace#"), widgetName());

        if( noHexUid )
        {
            line.replace(QString("#replaceuid#"), widgetUidNoHex());
        }
        else
        {
            line.replace(QString("#replaceuid#"), widgetUid());
        }
        out << line << "\n";
    }
}

void MainWindow::on_renderingCheckBox_stateChanged(int state )
{
    iTimer->stop();
    if( state == Qt::Unchecked )
    {
        ui->rendererName->setEnabled( false );
        ui->rendererUid->setEnabled( false );
        ui->comboBox->setEnabled( true );
        updateLayout();
    }
    else if ( state == Qt::Checked)
    {
        ui->rendererName->setEnabled( true );
        ui->rendererUid->setEnabled( true);
        ui->comboBox->setEnabled( false );
    }

}

QString MainWindow::widgetLayout()
{
    switch (iLayoutIndex)
    {
    case 0:
        {
            return QString( "feed" );
        }
        break;
    case 1:
        {
            return QString( "text" );
        }
        break;
    case 2:
        {
            return QString( "iconstext" );
        }
        break;
    case 3:
        {
            return QString( "graphictext" );
        }
        break;
    case 4:
        {
            return QString( "graphiciconstext" );
        }
        break;

    };

    return QString( "" );
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    iLayoutIndex = index;
    iLayoutCount = 3;
    updateLayout();
}

void MainWindow::updateLayout()
{
    switch (iLayoutIndex)
    {
    case 0:
        {
            iTimer->stop();
            showFeedsLayout();
        }
        break;
    case 1:
        {
            showTextLayout();
            iTimer->start(2000);
        }
        break;
    case 2:
        {
            showIconsTextLayout();
            iTimer->start(2000);
        }
        break;
    case 3:
        {
            showGraphicsTextLayout();
            iTimer->start(2000);
        }
        break;
    case 4:
        {
            showGraphicsIconTextLayout();
            iTimer->start(2000);
        }
        break;
    case 5:
        {
            iTimer->stop();
            showGraphicsGridLayout();
        }
        break;
    case 6:
        {
            iTimer->stop();
            showGraphicsGridTextLayout();
        }
        break;
    case 7:
        {
            iTimer->stop();
            showWidgeImageLayout();
        }
        break;
    case 8:
        {
            iTimer->stop();
            showGraphicsCarouselLayout();
        }
        break;
    };

    if( iLayoutCount > 1)
    {
        iLayoutCount--;
    }
    else
    {
        iLayoutCount = 3;
    }
}

void MainWindow::showFeedsLayout()
{
    ui->layoutGraphics->setPixmap(QPixmap(QString::fromUtf8(":/widgets/images/feeds_layout.jpg")));
}

void MainWindow::showGraphicsGridLayout()
{
    ui->layoutGraphics->setPixmap(QPixmap(QString::fromUtf8(":/widgets/images/graphicsgrid_layout.jpg")));
}

void MainWindow::showGraphicsGridTextLayout()
{
    ui->layoutGraphics->setPixmap(QPixmap(QString::fromUtf8(":/widgets/images/graphicsgridtext_layout.jpg")));
}

void MainWindow::showWidgeImageLayout()
{
    ui->layoutGraphics->setPixmap(QPixmap(QString::fromUtf8(":/widgets/images/wideimage_layout.jpg")));
}

void MainWindow::showGraphicsCarouselLayout()
{
    ui->layoutGraphics->setPixmap(QPixmap(QString::fromUtf8(":/widgets/images/graphicscarousel_layout.jpg")));
}

void MainWindow::showTextLayout()
{
    QString imagePath(":/widgets/images/text_layout_");
    QString cnt;
    cnt.setNum( iLayoutCount );
    imagePath.append( cnt );
    imagePath.append( ".jpg" );
    ui->layoutGraphics->setPixmap(QPixmap(imagePath));
}

void MainWindow::showIconsTextLayout()
{
    QString imagePath(":/widgets/images/iconstext_layout_");
    QString cnt;
    cnt.setNum( iLayoutCount );
    imagePath.append( cnt );
    imagePath.append( ".jpg" );
    ui->layoutGraphics->setPixmap(QPixmap(imagePath));
}

void MainWindow::showGraphicsTextLayout()
{
    QString imagePath(":/widgets/images/graphicstext_layout_");
    QString cnt;
    cnt.setNum( iLayoutCount );
    imagePath.append( cnt );
    imagePath.append( ".jpg" );
    ui->layoutGraphics->setPixmap(QPixmap(imagePath));
}

void MainWindow::showGraphicsIconTextLayout()
{
    QString imagePath(":/widgets/images/graphicsiconstext_layout_");
    QString cnt;
    cnt.setNum( iLayoutCount );
    imagePath.append( cnt );
    imagePath.append( ".jpg" );
    ui->layoutGraphics->setPixmap(QPixmap(imagePath));
}

