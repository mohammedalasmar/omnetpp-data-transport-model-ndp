/********************************************************************************
** Form generated from reading UI file 'preferencesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *general;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *userInterface;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *confirmExit;
    QHBoxLayout *horizontalLayout;
    QLabel *hideNamespaceText;
    QComboBox *hideNameSpace;
    QGroupBox *simulationExecution;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_2;
    QLabel *expressText;
    QLineEdit *express;
    QSpacerItem *generalSapcer;
    QWidget *logsPage;
    QVBoxLayout *verticalLayout_17;
    QGroupBox *logs;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *initBanners;
    QCheckBox *eventBanners;
    QVBoxLayout *bannersSubLayout;
    QCheckBox *shortBanners;
    QGridLayout *gridLayout_2;
    QLabel *logPrefixText;
    QLineEdit *logPrefix;
    QLabel *logLevelText;
    QComboBox *logLevel;
    QLabel *settings;
    QGridLayout *gridLayout_3;
    QLabel *overallText;
    QLineEdit *overall;
    QLabel *scrollbackText;
    QLineEdit *scrollback;
    QLabel *applies;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_3;
    QWidget *layouting;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *layoutingBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *layoutingText;
    QFrame *frame;
    QVBoxLayout *verticalLayout_19;
    QRadioButton *fastRadio;
    QRadioButton *advancedRadio;
    QRadioButton *adaptiveRadio;
    QCheckBox *showLayouting;
    QGroupBox *display;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *arrange;
    QCheckBox *allowZoom;
    QSpacerItem *layoutingSpacer;
    QWidget *animation;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *animGeneral;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *animMsg;
    QVBoxLayout *msgSubLayout;
    QCheckBox *animBroadcast;
    QCheckBox *showArrows;
    QCheckBox *animCalls;
    QHBoxLayout *delayLayout;
    QLabel *delayText;
    QLineEdit *delayEdit;
    QCheckBox *showMarker;
    QCheckBox *showBubbles;
    QGroupBox *messages;
    QVBoxLayout *verticalLayout_14;
    QCheckBox *dispName;
    QCheckBox *dispClass;
    QCheckBox *colorMsg;
    QCheckBox *penguinMode;
    QSpacerItem *animSpacer;
    QWidget *filtering;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *timeLine;
    QVBoxLayout *verticalLayout_15;
    QCheckBox *selfMsg;
    QCheckBox *nonSelfMsg;
    QCheckBox *silentMsg;
    QGroupBox *animationBox;
    QVBoxLayout *verticalLayout_16;
    QLabel *excludeMsgText;
    QTextEdit *excludMsgEdit;
    QLabel *details;
    QSpacerItem *filteringSpacer;
    QWidget *fonts;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *fontsBox;
    QGridLayout *gridLayout;
    QLabel *userInterfaceText;
    QLabel *timeLineText;
    QLabel *canvasText;
    QLabel *logText;
    QSpacerItem *fontsSpacer;
    QFontComboBox *userInterfaceBox;
    QFontComboBox *logBox;
    QSpinBox *canvasNumBox;
    QFontComboBox *timeLineBox;
    QSpinBox *userInterfaceNumBox;
    QFontComboBox *canvasBox;
    QSpinBox *logNumBox;
    QSpinBox *timeLineNumBox;
    QFontComboBox *timeBox;
    QLabel *timeText;
    QSpinBox *timeNumBox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *restoreLayout;
    QSpacerItem *restoreSpacer;
    QPushButton *restoreButton;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QStringLiteral("PreferencesDialog"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDialog->sizePolicy().hasHeightForWidth());
        PreferencesDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PreferencesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(PreferencesDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        general = new QWidget();
        general->setObjectName(QStringLiteral("general"));
        verticalLayout_4 = new QVBoxLayout(general);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        userInterface = new QGroupBox(general);
        userInterface->setObjectName(QStringLiteral("userInterface"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(userInterface->sizePolicy().hasHeightForWidth());
        userInterface->setSizePolicy(sizePolicy1);
        verticalLayout_9 = new QVBoxLayout(userInterface);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        confirmExit = new QCheckBox(userInterface);
        confirmExit->setObjectName(QStringLiteral("confirmExit"));

        verticalLayout_9->addWidget(confirmExit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        hideNamespaceText = new QLabel(userInterface);
        hideNamespaceText->setObjectName(QStringLiteral("hideNamespaceText"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(hideNamespaceText->sizePolicy().hasHeightForWidth());
        hideNamespaceText->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(hideNamespaceText);

        hideNameSpace = new QComboBox(userInterface);
        hideNameSpace->setObjectName(QStringLiteral("hideNameSpace"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(hideNameSpace->sizePolicy().hasHeightForWidth());
        hideNameSpace->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(hideNameSpace);


        verticalLayout_9->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(userInterface);

        simulationExecution = new QGroupBox(general);
        simulationExecution->setObjectName(QStringLiteral("simulationExecution"));
        sizePolicy1.setHeightForWidth(simulationExecution->sizePolicy().hasHeightForWidth());
        simulationExecution->setSizePolicy(sizePolicy1);
        verticalLayout_11 = new QVBoxLayout(simulationExecution);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        expressText = new QLabel(simulationExecution);
        expressText->setObjectName(QStringLiteral("expressText"));

        horizontalLayout_2->addWidget(expressText);

        express = new QLineEdit(simulationExecution);
        express->setObjectName(QStringLiteral("express"));

        horizontalLayout_2->addWidget(express);


        verticalLayout_11->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(simulationExecution);

        generalSapcer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(generalSapcer);

        tabWidget->addTab(general, QString());
        logsPage = new QWidget();
        logsPage->setObjectName(QStringLiteral("logsPage"));
        verticalLayout_17 = new QVBoxLayout(logsPage);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        logs = new QGroupBox(logsPage);
        logs->setObjectName(QStringLiteral("logs"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(logs->sizePolicy().hasHeightForWidth());
        logs->setSizePolicy(sizePolicy4);
        verticalLayout_10 = new QVBoxLayout(logs);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        initBanners = new QCheckBox(logs);
        initBanners->setObjectName(QStringLiteral("initBanners"));

        verticalLayout_10->addWidget(initBanners);

        eventBanners = new QCheckBox(logs);
        eventBanners->setObjectName(QStringLiteral("eventBanners"));

        verticalLayout_10->addWidget(eventBanners);

        bannersSubLayout = new QVBoxLayout();
        bannersSubLayout->setObjectName(QStringLiteral("bannersSubLayout"));
        bannersSubLayout->setContentsMargins(18, -1, -1, -1);
        shortBanners = new QCheckBox(logs);
        shortBanners->setObjectName(QStringLiteral("shortBanners"));

        bannersSubLayout->addWidget(shortBanners);


        verticalLayout_10->addLayout(bannersSubLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        logPrefixText = new QLabel(logs);
        logPrefixText->setObjectName(QStringLiteral("logPrefixText"));

        gridLayout_2->addWidget(logPrefixText, 0, 0, 1, 1);

        logPrefix = new QLineEdit(logs);
        logPrefix->setObjectName(QStringLiteral("logPrefix"));

        gridLayout_2->addWidget(logPrefix, 0, 1, 1, 1);

        logLevelText = new QLabel(logs);
        logLevelText->setObjectName(QStringLiteral("logLevelText"));

        gridLayout_2->addWidget(logLevelText, 1, 0, 1, 1);

        logLevel = new QComboBox(logs);
        logLevel->setObjectName(QStringLiteral("logLevel"));
        sizePolicy1.setHeightForWidth(logLevel->sizePolicy().hasHeightForWidth());
        logLevel->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(logLevel, 1, 1, 1, 1);


        verticalLayout_10->addLayout(gridLayout_2);

        settings = new QLabel(logs);
        settings->setObjectName(QStringLiteral("settings"));
        settings->setWordWrap(true);

        verticalLayout_10->addWidget(settings);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        overallText = new QLabel(logs);
        overallText->setObjectName(QStringLiteral("overallText"));

        gridLayout_3->addWidget(overallText, 0, 0, 1, 1);

        overall = new QLineEdit(logs);
        overall->setObjectName(QStringLiteral("overall"));

        gridLayout_3->addWidget(overall, 0, 1, 1, 1);

        scrollbackText = new QLabel(logs);
        scrollbackText->setObjectName(QStringLiteral("scrollbackText"));

        gridLayout_3->addWidget(scrollbackText, 1, 0, 1, 1);

        scrollback = new QLineEdit(logs);
        scrollback->setObjectName(QStringLiteral("scrollback"));

        gridLayout_3->addWidget(scrollback, 1, 1, 1, 1);


        verticalLayout_10->addLayout(gridLayout_3);

        applies = new QLabel(logs);
        applies->setObjectName(QStringLiteral("applies"));
        applies->setWordWrap(true);

        verticalLayout_10->addWidget(applies);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_10->addItem(verticalSpacer);


        verticalLayout_17->addWidget(logs);

        verticalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_3);

        tabWidget->addTab(logsPage, QString());
        layouting = new QWidget();
        layouting->setObjectName(QStringLiteral("layouting"));
        verticalLayout_5 = new QVBoxLayout(layouting);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        layoutingBox = new QGroupBox(layouting);
        layoutingBox->setObjectName(QStringLiteral("layoutingBox"));
        sizePolicy1.setHeightForWidth(layoutingBox->sizePolicy().hasHeightForWidth());
        layoutingBox->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(layoutingBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        layoutingText = new QLabel(layoutingBox);
        layoutingText->setObjectName(QStringLiteral("layoutingText"));

        verticalLayout_3->addWidget(layoutingText);

        frame = new QFrame(layoutingBox);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_19 = new QVBoxLayout(frame);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        fastRadio = new QRadioButton(frame);
        buttonGroup = new QButtonGroup(PreferencesDialog);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(fastRadio);
        fastRadio->setObjectName(QStringLiteral("fastRadio"));

        verticalLayout_19->addWidget(fastRadio);

        advancedRadio = new QRadioButton(frame);
        buttonGroup->addButton(advancedRadio);
        advancedRadio->setObjectName(QStringLiteral("advancedRadio"));

        verticalLayout_19->addWidget(advancedRadio);

        adaptiveRadio = new QRadioButton(frame);
        buttonGroup->addButton(adaptiveRadio);
        adaptiveRadio->setObjectName(QStringLiteral("adaptiveRadio"));

        verticalLayout_19->addWidget(adaptiveRadio);


        verticalLayout_3->addWidget(frame);

        showLayouting = new QCheckBox(layoutingBox);
        showLayouting->setObjectName(QStringLiteral("showLayouting"));

        verticalLayout_3->addWidget(showLayouting);


        verticalLayout_5->addWidget(layoutingBox);

        display = new QGroupBox(layouting);
        display->setObjectName(QStringLiteral("display"));
        sizePolicy1.setHeightForWidth(display->sizePolicy().hasHeightForWidth());
        display->setSizePolicy(sizePolicy1);
        verticalLayout_12 = new QVBoxLayout(display);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        arrange = new QCheckBox(display);
        arrange->setObjectName(QStringLiteral("arrange"));

        verticalLayout_12->addWidget(arrange);

        allowZoom = new QCheckBox(display);
        allowZoom->setObjectName(QStringLiteral("allowZoom"));

        verticalLayout_12->addWidget(allowZoom);


        verticalLayout_5->addWidget(display);

        layoutingSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(layoutingSpacer);

        tabWidget->addTab(layouting, QString());
        animation = new QWidget();
        animation->setObjectName(QStringLiteral("animation"));
        verticalLayout_6 = new QVBoxLayout(animation);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        animGeneral = new QGroupBox(animation);
        animGeneral->setObjectName(QStringLiteral("animGeneral"));
        sizePolicy1.setHeightForWidth(animGeneral->sizePolicy().hasHeightForWidth());
        animGeneral->setSizePolicy(sizePolicy1);
        verticalLayout_13 = new QVBoxLayout(animGeneral);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        animMsg = new QCheckBox(animGeneral);
        animMsg->setObjectName(QStringLiteral("animMsg"));

        verticalLayout_13->addWidget(animMsg);

        msgSubLayout = new QVBoxLayout();
        msgSubLayout->setObjectName(QStringLiteral("msgSubLayout"));
        msgSubLayout->setContentsMargins(18, -1, -1, -1);
        animBroadcast = new QCheckBox(animGeneral);
        animBroadcast->setObjectName(QStringLiteral("animBroadcast"));

        msgSubLayout->addWidget(animBroadcast);

        showArrows = new QCheckBox(animGeneral);
        showArrows->setObjectName(QStringLiteral("showArrows"));

        msgSubLayout->addWidget(showArrows);


        verticalLayout_13->addLayout(msgSubLayout);

        animCalls = new QCheckBox(animGeneral);
        animCalls->setObjectName(QStringLiteral("animCalls"));

        verticalLayout_13->addWidget(animCalls);

        delayLayout = new QHBoxLayout();
        delayLayout->setObjectName(QStringLiteral("delayLayout"));
        delayLayout->setContentsMargins(18, -1, -1, -1);
        delayText = new QLabel(animGeneral);
        delayText->setObjectName(QStringLiteral("delayText"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(delayText->sizePolicy().hasHeightForWidth());
        delayText->setSizePolicy(sizePolicy5);

        delayLayout->addWidget(delayText);

        delayEdit = new QLineEdit(animGeneral);
        delayEdit->setObjectName(QStringLiteral("delayEdit"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(delayEdit->sizePolicy().hasHeightForWidth());
        delayEdit->setSizePolicy(sizePolicy6);

        delayLayout->addWidget(delayEdit);

        delayLayout->setStretch(0, 2);
        delayLayout->setStretch(1, 1);

        verticalLayout_13->addLayout(delayLayout);

        showMarker = new QCheckBox(animGeneral);
        showMarker->setObjectName(QStringLiteral("showMarker"));

        verticalLayout_13->addWidget(showMarker);

        showBubbles = new QCheckBox(animGeneral);
        showBubbles->setObjectName(QStringLiteral("showBubbles"));

        verticalLayout_13->addWidget(showBubbles);


        verticalLayout_6->addWidget(animGeneral);

        messages = new QGroupBox(animation);
        messages->setObjectName(QStringLiteral("messages"));
        sizePolicy1.setHeightForWidth(messages->sizePolicy().hasHeightForWidth());
        messages->setSizePolicy(sizePolicy1);
        verticalLayout_14 = new QVBoxLayout(messages);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        dispName = new QCheckBox(messages);
        dispName->setObjectName(QStringLiteral("dispName"));

        verticalLayout_14->addWidget(dispName);

        dispClass = new QCheckBox(messages);
        dispClass->setObjectName(QStringLiteral("dispClass"));

        verticalLayout_14->addWidget(dispClass);

        colorMsg = new QCheckBox(messages);
        colorMsg->setObjectName(QStringLiteral("colorMsg"));

        verticalLayout_14->addWidget(colorMsg);

        penguinMode = new QCheckBox(messages);
        penguinMode->setObjectName(QStringLiteral("penguinMode"));

        verticalLayout_14->addWidget(penguinMode);


        verticalLayout_6->addWidget(messages);

        animSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(animSpacer);

        tabWidget->addTab(animation, QString());
        filtering = new QWidget();
        filtering->setObjectName(QStringLiteral("filtering"));
        verticalLayout_7 = new QVBoxLayout(filtering);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        timeLine = new QGroupBox(filtering);
        timeLine->setObjectName(QStringLiteral("timeLine"));
        sizePolicy1.setHeightForWidth(timeLine->sizePolicy().hasHeightForWidth());
        timeLine->setSizePolicy(sizePolicy1);
        verticalLayout_15 = new QVBoxLayout(timeLine);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        selfMsg = new QCheckBox(timeLine);
        selfMsg->setObjectName(QStringLiteral("selfMsg"));

        verticalLayout_15->addWidget(selfMsg);

        nonSelfMsg = new QCheckBox(timeLine);
        nonSelfMsg->setObjectName(QStringLiteral("nonSelfMsg"));

        verticalLayout_15->addWidget(nonSelfMsg);

        silentMsg = new QCheckBox(timeLine);
        silentMsg->setObjectName(QStringLiteral("silentMsg"));

        verticalLayout_15->addWidget(silentMsg);


        verticalLayout_7->addWidget(timeLine);

        animationBox = new QGroupBox(filtering);
        animationBox->setObjectName(QStringLiteral("animationBox"));
        sizePolicy1.setHeightForWidth(animationBox->sizePolicy().hasHeightForWidth());
        animationBox->setSizePolicy(sizePolicy1);
        verticalLayout_16 = new QVBoxLayout(animationBox);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        excludeMsgText = new QLabel(animationBox);
        excludeMsgText->setObjectName(QStringLiteral("excludeMsgText"));

        verticalLayout_16->addWidget(excludeMsgText);

        excludMsgEdit = new QTextEdit(animationBox);
        excludMsgEdit->setObjectName(QStringLiteral("excludMsgEdit"));

        verticalLayout_16->addWidget(excludMsgEdit);

        details = new QLabel(animationBox);
        details->setObjectName(QStringLiteral("details"));
        details->setWordWrap(true);

        verticalLayout_16->addWidget(details);


        verticalLayout_7->addWidget(animationBox);

        filteringSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(filteringSpacer);

        tabWidget->addTab(filtering, QString());
        fonts = new QWidget();
        fonts->setObjectName(QStringLiteral("fonts"));
        verticalLayout_8 = new QVBoxLayout(fonts);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        fontsBox = new QGroupBox(fonts);
        fontsBox->setObjectName(QStringLiteral("fontsBox"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(fontsBox->sizePolicy().hasHeightForWidth());
        fontsBox->setSizePolicy(sizePolicy7);
        gridLayout = new QGridLayout(fontsBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        userInterfaceText = new QLabel(fontsBox);
        userInterfaceText->setObjectName(QStringLiteral("userInterfaceText"));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(2);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(userInterfaceText->sizePolicy().hasHeightForWidth());
        userInterfaceText->setSizePolicy(sizePolicy8);

        gridLayout->addWidget(userInterfaceText, 0, 0, 1, 1);

        timeLineText = new QLabel(fontsBox);
        timeLineText->setObjectName(QStringLiteral("timeLineText"));

        gridLayout->addWidget(timeLineText, 1, 0, 1, 1);

        canvasText = new QLabel(fontsBox);
        canvasText->setObjectName(QStringLiteral("canvasText"));

        gridLayout->addWidget(canvasText, 2, 0, 1, 1);

        logText = new QLabel(fontsBox);
        logText->setObjectName(QStringLiteral("logText"));

        gridLayout->addWidget(logText, 3, 0, 1, 1);

        fontsSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Ignored);

        gridLayout->addItem(fontsSpacer, 5, 1, 1, 1);

        userInterfaceBox = new QFontComboBox(fontsBox);
        userInterfaceBox->setObjectName(QStringLiteral("userInterfaceBox"));
        sizePolicy2.setHeightForWidth(userInterfaceBox->sizePolicy().hasHeightForWidth());
        userInterfaceBox->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(userInterfaceBox, 0, 1, 1, 1);

        logBox = new QFontComboBox(fontsBox);
        logBox->setObjectName(QStringLiteral("logBox"));
        sizePolicy5.setHeightForWidth(logBox->sizePolicy().hasHeightForWidth());
        logBox->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(logBox, 3, 1, 1, 1);

        canvasNumBox = new QSpinBox(fontsBox);
        canvasNumBox->setObjectName(QStringLiteral("canvasNumBox"));
        sizePolicy7.setHeightForWidth(canvasNumBox->sizePolicy().hasHeightForWidth());
        canvasNumBox->setSizePolicy(sizePolicy7);
        canvasNumBox->setMinimum(4);
        canvasNumBox->setMaximum(70);

        gridLayout->addWidget(canvasNumBox, 2, 2, 1, 1);

        timeLineBox = new QFontComboBox(fontsBox);
        timeLineBox->setObjectName(QStringLiteral("timeLineBox"));
        sizePolicy5.setHeightForWidth(timeLineBox->sizePolicy().hasHeightForWidth());
        timeLineBox->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(timeLineBox, 1, 1, 1, 1);

        userInterfaceNumBox = new QSpinBox(fontsBox);
        userInterfaceNumBox->setObjectName(QStringLiteral("userInterfaceNumBox"));
        QSizePolicy sizePolicy9(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy9.setHorizontalStretch(1);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(userInterfaceNumBox->sizePolicy().hasHeightForWidth());
        userInterfaceNumBox->setSizePolicy(sizePolicy9);
        userInterfaceNumBox->setMinimum(4);
        userInterfaceNumBox->setMaximum(70);

        gridLayout->addWidget(userInterfaceNumBox, 0, 2, 1, 1);

        canvasBox = new QFontComboBox(fontsBox);
        canvasBox->setObjectName(QStringLiteral("canvasBox"));
        sizePolicy5.setHeightForWidth(canvasBox->sizePolicy().hasHeightForWidth());
        canvasBox->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(canvasBox, 2, 1, 1, 1);

        logNumBox = new QSpinBox(fontsBox);
        logNumBox->setObjectName(QStringLiteral("logNumBox"));
        sizePolicy7.setHeightForWidth(logNumBox->sizePolicy().hasHeightForWidth());
        logNumBox->setSizePolicy(sizePolicy7);
        logNumBox->setMinimum(4);
        logNumBox->setMaximum(70);

        gridLayout->addWidget(logNumBox, 3, 2, 1, 1);

        timeLineNumBox = new QSpinBox(fontsBox);
        timeLineNumBox->setObjectName(QStringLiteral("timeLineNumBox"));
        sizePolicy7.setHeightForWidth(timeLineNumBox->sizePolicy().hasHeightForWidth());
        timeLineNumBox->setSizePolicy(sizePolicy7);
        timeLineNumBox->setMinimum(4);
        timeLineNumBox->setMaximum(70);

        gridLayout->addWidget(timeLineNumBox, 1, 2, 1, 1);

        timeBox = new QFontComboBox(fontsBox);
        timeBox->setObjectName(QStringLiteral("timeBox"));

        gridLayout->addWidget(timeBox, 4, 1, 1, 1);

        timeText = new QLabel(fontsBox);
        timeText->setObjectName(QStringLiteral("timeText"));

        gridLayout->addWidget(timeText, 4, 0, 1, 1);

        timeNumBox = new QSpinBox(fontsBox);
        timeNumBox->setObjectName(QStringLiteral("timeNumBox"));

        gridLayout->addWidget(timeNumBox, 4, 2, 1, 1);


        verticalLayout_8->addWidget(fontsBox);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_2);

        restoreLayout = new QHBoxLayout();
        restoreLayout->setObjectName(QStringLiteral("restoreLayout"));
        restoreSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        restoreLayout->addItem(restoreSpacer);

        restoreButton = new QPushButton(fonts);
        restoreButton->setObjectName(QStringLiteral("restoreButton"));
        sizePolicy7.setHeightForWidth(restoreButton->sizePolicy().hasHeightForWidth());
        restoreButton->setSizePolicy(sizePolicy7);

        restoreLayout->addWidget(restoreButton);


        verticalLayout_8->addLayout(restoreLayout);

        tabWidget->addTab(fonts, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(PreferencesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy10);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(PreferencesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PreferencesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PreferencesDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0));
        userInterface->setTitle(QApplication::translate("PreferencesDialog", "User Interface", 0));
        confirmExit->setText(QApplication::translate("PreferencesDialog", "Confirm exit when simulation is in progress", 0));
        hideNamespaceText->setText(QApplication::translate("PreferencesDialog", "Hide namespaces from C++ class names:", 0));
        hideNameSpace->clear();
        hideNameSpace->insertItems(0, QStringList()
         << QApplication::translate("PreferencesDialog", "none", 0)
         << QApplication::translate("PreferencesDialog", "omnetpp", 0)
         << QApplication::translate("PreferencesDialog", "all", 0)
        );
        simulationExecution->setTitle(QApplication::translate("PreferencesDialog", "Simulation Execution", 0));
        expressText->setText(QApplication::translate("PreferencesDialog", "Display update frequency for Express Run (ms):", 0));
        tabWidget->setTabText(tabWidget->indexOf(general), QApplication::translate("PreferencesDialog", "General", 0));
        logs->setTitle(QApplication::translate("PreferencesDialog", "Logs", 0));
        initBanners->setText(QApplication::translate("PreferencesDialog", "Print initialization banners", 0));
        eventBanners->setText(QApplication::translate("PreferencesDialog", "Print event banners", 0));
        shortBanners->setText(QApplication::translate("PreferencesDialog", "Short event banners", 0));
        logPrefixText->setText(QApplication::translate("PreferencesDialog", "Log prefix format:", 0));
#ifndef QT_NO_TOOLTIP
        logPrefix->setToolTip(QApplication::translate("PreferencesDialog", "Here are some of the format characters that you can use in the log prefix.\n"
"See the manual or the LogFormatter class for the complete list.\n"
"\n"
"General:\n"
"  - %l, %c: log level (INFO, DEBUG, etc) and category string\n"
"  - %e, %t, %g: event number, simulation time, and fingerprint if enabled\n"
"  - %f, %i, %u: source file, line number, and function\n"
"\n"
"Objects:\n"
"  - %E event object (class name, name)\n"
"  - %U module of current event (NED type, full path)\n"
"  - %C context component (NED type, full path)\n"
"  - %K context component, if different from event module (NED type, full path)\n"
"  - %J source component or object (NED type or class, full path or pointer)\n"
"  - %L source component or object, if different from context (NED type or class, full path or pointer)\n"
"\n"
"Padding with spaces:\n"
"  - %[0-9]+ add spaces until specified column\n"
"  - %| adaptive tabstop: add padding until longest prefix seen so far\n"
"  - %> function call depth times 2-space indentation (see Enter_M"
                        "ethod, Enter_Method_Silent)", 0));
#endif // QT_NO_TOOLTIP
        logLevelText->setText(QApplication::translate("PreferencesDialog", "Log level:", 0));
        logLevel->clear();
        logLevel->insertItems(0, QStringList()
         << QApplication::translate("PreferencesDialog", "FATAL", 0)
         << QApplication::translate("PreferencesDialog", "ERROR", 0)
         << QApplication::translate("PreferencesDialog", "WARN", 0)
         << QApplication::translate("PreferencesDialog", "INFO", 0)
         << QApplication::translate("PreferencesDialog", "DETAIL", 0)
         << QApplication::translate("PreferencesDialog", "DEBUG", 0)
         << QApplication::translate("PreferencesDialog", "TRACE", 0)
        );
        settings->setText(QApplication::translate("PreferencesDialog", "The above settings apply to subsequent simulation events. Hover mouse to get help on log prefix syntax.", 0));
        overallText->setText(QApplication::translate("PreferencesDialog", "Overall history size (in events):", 0));
        scrollbackText->setText(QApplication::translate("PreferencesDialog", "Scrollback buffer (lines):", 0));
        applies->setText(QApplication::translate("PreferencesDialog", "Applies to main window and module log windows. Leave blank for unlimited. Minimum value is 500 lines.", 0));
        tabWidget->setTabText(tabWidget->indexOf(logsPage), QApplication::translate("PreferencesDialog", "Logs", 0));
        layoutingBox->setTitle(QApplication::translate("PreferencesDialog", "Layouting", 0));
        layoutingText->setText(QApplication::translate("PreferencesDialog", "Layouting algorithm:", 0));
        fastRadio->setText(QApplication::translate("PreferencesDialog", "Fast", 0));
        advancedRadio->setText(QApplication::translate("PreferencesDialog", "Advanced", 0));
        adaptiveRadio->setText(QApplication::translate("PreferencesDialog", "Adaptive (Fast for large networks, Advanced for smaller ones)", 0));
        showLayouting->setText(QApplication::translate("PreferencesDialog", "Show layouting process", 0));
        display->setTitle(QApplication::translate("PreferencesDialog", "Display", 0));
        arrange->setText(QApplication::translate("PreferencesDialog", "Arrange connections on vector gates parallel to each other", 0));
        allowZoom->setText(QApplication::translate("PreferencesDialog", "Zoom out if necessary to fit network into window", 0));
        tabWidget->setTabText(tabWidget->indexOf(layouting), QApplication::translate("PreferencesDialog", "Layouting", 0));
        animGeneral->setTitle(QApplication::translate("PreferencesDialog", "General", 0));
        animMsg->setText(QApplication::translate("PreferencesDialog", "Animate messages", 0));
#ifndef QT_NO_TOOLTIP
        animBroadcast->setToolTip(QApplication::translate("PreferencesDialog", "Animates send/sendDirect calls concurrently, after processing each event (i.e. out of sequence)", 0));
#endif // QT_NO_TOOLTIP
        animBroadcast->setText(QApplication::translate("PreferencesDialog", "Broadcast animation", 0));
        showArrows->setText(QApplication::translate("PreferencesDialog", "Show arrows for sendDirect animation", 0));
        animCalls->setText(QApplication::translate("PreferencesDialog", "Animate method calls", 0));
        delayText->setText(QApplication::translate("PreferencesDialog", "Method call duration (ms):", 0));
        showMarker->setText(QApplication::translate("PreferencesDialog", "Show next event markers", 0));
        showBubbles->setText(QApplication::translate("PreferencesDialog", "Show bubbles (bubble() calls)", 0));
        messages->setTitle(QApplication::translate("PreferencesDialog", "Messages", 0));
        dispName->setText(QApplication::translate("PreferencesDialog", "Display message names during animation", 0));
        dispClass->setText(QApplication::translate("PreferencesDialog", "Display message class during animation", 0));
#ifndef QT_NO_TOOLTIP
        colorMsg->setToolTip(QApplication::translate("PreferencesDialog", "Color code (message kind modulo 8): 0=red 1=green 2=blue 3=white 4=yellow 5=cyan 6=magenta 7=black", 0));
#endif // QT_NO_TOOLTIP
        colorMsg->setText(QApplication::translate("PreferencesDialog", "Color messages by message kind", 0));
        penguinMode->setText(QApplication::translate("PreferencesDialog", "Penguin mode", 0));
        tabWidget->setTabText(tabWidget->indexOf(animation), QApplication::translate("PreferencesDialog", "Animation", 0));
        timeLine->setTitle(QApplication::translate("PreferencesDialog", "Timeline", 0));
        selfMsg->setText(QApplication::translate("PreferencesDialog", "Show self-messages", 0));
        nonSelfMsg->setText(QApplication::translate("PreferencesDialog", "Show non-self messages", 0));
        silentMsg->setText(QApplication::translate("PreferencesDialog", "Show silent (non-animated) messages, see below", 0));
        animationBox->setTitle(QApplication::translate("PreferencesDialog", "Animation", 0));
        excludeMsgText->setText(QApplication::translate("PreferencesDialog", "Messages to exclude from animation:", 0));
        details->setText(QApplication::translate("PreferencesDialog", "One expression per line. Wildcards, AND, OR, NOT, numeric ranges ({5..10}), field matchers (className(..), kind(..), byteLength(..), etc.) are accepted.", 0));
        tabWidget->setTabText(tabWidget->indexOf(filtering), QApplication::translate("PreferencesDialog", "Filtering", 0));
        fontsBox->setTitle(QApplication::translate("PreferencesDialog", "Fonts", 0));
        userInterfaceText->setText(QApplication::translate("PreferencesDialog", "User interface:", 0));
        timeLineText->setText(QApplication::translate("PreferencesDialog", "Timeline:", 0));
        canvasText->setText(QApplication::translate("PreferencesDialog", "Canvas:", 0));
        logText->setText(QApplication::translate("PreferencesDialog", "Log windows:", 0));
        timeText->setText(QApplication::translate("PreferencesDialog", "Time:", 0));
        restoreButton->setText(QApplication::translate("PreferencesDialog", "Restore Defaults", 0));
        tabWidget->setTabText(tabWidget->indexOf(fonts), QApplication::translate("PreferencesDialog", "Fonts", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
