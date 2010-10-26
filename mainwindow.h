#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextStream;
class QCheckBox;
class QTimer;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString widgetName();
    QString widgetUid();
    QString widgetUidNoHex();
    QString rendererName();
    QString rendererUid();
    void generateLicense( QTextStream& aStream );
    QCheckBox& rendererCheckBox();
    QString widgetLayout();

    void replaceData( QString sourceFile, QString destFile, bool noHexUid = 0 );

protected:
    void changeEvent(QEvent *e);

private:
    void generateMainBuildFile();
    void showFeedsLayout();
    void showGraphicsGridLayout();
    void showGraphicsGridTextLayout();
    void showWidgeImageLayout();
    void showGraphicsCarouselLayout();
    void showTextLayout();
    void showIconsTextLayout();
    void showGraphicsTextLayout();
    void showGraphicsIconTextLayout();

private:
    Ui::MainWindow *ui;
    int iLayoutIndex;
    int iLayoutCount;
    QTimer *iTimer;

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_renderingCheckBox_stateChanged(int );
    void on_pushButton_clicked();
    void updateLayout();
};

#endif // MAINWINDOW_H
