#ifndef PUBLISHERCREATOR_H
#define PUBLISHERCREATOR_H

#include "mainwindow.h"

class PublisherCreator
{
public:
    PublisherCreator(MainWindow& aUi);

private:
    void copyFiles();

private:
    MainWindow& iUi;
};

#endif // PUBLISHERCREATOR_H
