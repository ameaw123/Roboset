/********************************************************************************
** Form generated from reading UI file 'SCTcpToolWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCTCPTOOLWIDGET_H
#define UI_SCTCPTOOLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SCTcpToolWidget
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_ip;
    QLabel *label_3;
    QComboBox *comboBox_port;
    QLabel *label_9;
    QLineEdit *lineEdit_sendCommand;
    QLabel *label_4;
    QLineEdit *lineEdit_number;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QTextEdit *textEdit_sendData;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_send;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_getrobo;
    QLabel *label_revText;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QCheckBox *checkBox_revHex;
    QTextEdit *textEdit_revData;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_automatically;
    QPushButton *pushButton_clearInfo;
    QTextEdit *textEdit_info;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QLineEdit *lineEdit_ip_cam;
    QLabel *label_10;
    QLineEdit *lineEdit_username;
    QLabel *label_8;
    QLineEdit *lineEdit_password;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_connect_cam;
    QPushButton *pushButton_close;
    QPushButton *pushButton_getcam;
    QPushButton *pushButton;
    QPushButton *pushButton_catch;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QSplitter *splitter_7;
    QSplitter *splitter_3;
    QLabel *label_7;
    QComboBox *comboBox_robo;
    QSplitter *splitter_4;
    QLabel *label_11;
    QComboBox *comboBox_cam;
    QSplitter *splitter_6;
    QLabel *label_14;
    QLineEdit *lineEdit_taskname;
    QSplitter *splitter_5;
    QLabel *label_13;
    QPushButton *pushButton_taskset;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_15;
    QLineEdit *lineEdit_save;
    QPushButton *read_set;
    QPushButton *save_set;
    QSplitter *splitter_9;
    QTextEdit *textEdit_setinfo;
    QPushButton *pushButton_start;
    QLabel *label;

    void setupUi(QWidget *SCTcpToolWidget)
    {
        if (SCTcpToolWidget->objectName().isEmpty())
            SCTcpToolWidget->setObjectName(QStringLiteral("SCTcpToolWidget"));
        SCTcpToolWidget->resize(932, 472);
        SCTcpToolWidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	\n"
"	font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        gridLayout = new QGridLayout(SCTcpToolWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_2 = new QSplitter(SCTcpToolWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        lineEdit_ip = new QLineEdit(groupBox);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_ip);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        comboBox_port = new QComboBox(groupBox);
        comboBox_port->setObjectName(QStringLiteral("comboBox_port"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox_port);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_9);

        lineEdit_sendCommand = new QLineEdit(groupBox);
        lineEdit_sendCommand->setObjectName(QStringLiteral("lineEdit_sendCommand"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_sendCommand);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEdit_number = new QLineEdit(groupBox);
        lineEdit_number->setObjectName(QStringLiteral("lineEdit_number"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_number);


        verticalLayout_2->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);


        verticalLayout_2->addLayout(horizontalLayout);

        textEdit_sendData = new QTextEdit(groupBox);
        textEdit_sendData->setObjectName(QStringLiteral("textEdit_sendData"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit_sendData->sizePolicy().hasHeightForWidth());
        textEdit_sendData->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(textEdit_sendData);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_connect = new QPushButton(groupBox);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setCheckable(true);

        horizontalLayout_4->addWidget(pushButton_connect);

        pushButton_send = new QPushButton(groupBox);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));

        horizontalLayout_4->addWidget(pushButton_send);


        verticalLayout_2->addLayout(horizontalLayout_4);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_getrobo = new QPushButton(groupBox_2);
        pushButton_getrobo->setObjectName(QStringLiteral("pushButton_getrobo"));

        verticalLayout->addWidget(pushButton_getrobo);

        label_revText = new QLabel(groupBox_2);
        label_revText->setObjectName(QStringLiteral("label_revText"));

        verticalLayout->addWidget(label_revText);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_5->addWidget(label_12);

        checkBox_revHex = new QCheckBox(groupBox_2);
        checkBox_revHex->setObjectName(QStringLiteral("checkBox_revHex"));

        horizontalLayout_5->addWidget(checkBox_revHex);


        verticalLayout->addLayout(horizontalLayout_5);

        textEdit_revData = new QTextEdit(groupBox_2);
        textEdit_revData->setObjectName(QStringLiteral("textEdit_revData"));
        sizePolicy2.setHeightForWidth(textEdit_revData->sizePolicy().hasHeightForWidth());
        textEdit_revData->setSizePolicy(sizePolicy2);
        textEdit_revData->setReadOnly(true);

        verticalLayout->addWidget(textEdit_revData);

        splitter->addWidget(groupBox_2);
        splitter_2->addWidget(splitter);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        checkBox_automatically = new QCheckBox(layoutWidget);
        checkBox_automatically->setObjectName(QStringLiteral("checkBox_automatically"));
        checkBox_automatically->setChecked(true);

        horizontalLayout_2->addWidget(checkBox_automatically);

        pushButton_clearInfo = new QPushButton(layoutWidget);
        pushButton_clearInfo->setObjectName(QStringLiteral("pushButton_clearInfo"));

        horizontalLayout_2->addWidget(pushButton_clearInfo);


        verticalLayout_3->addLayout(horizontalLayout_2);

        textEdit_info = new QTextEdit(layoutWidget);
        textEdit_info->setObjectName(QStringLiteral("textEdit_info"));
        textEdit_info->setReadOnly(true);

        verticalLayout_3->addWidget(textEdit_info);

        splitter_2->addWidget(layoutWidget);

        gridLayout->addWidget(splitter_2, 1, 0, 1, 1);

        groupBox_5 = new QGroupBox(SCTcpToolWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_4 = new QVBoxLayout(groupBox_5);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        lineEdit_ip_cam = new QLineEdit(groupBox_3);
        lineEdit_ip_cam->setObjectName(QStringLiteral("lineEdit_ip_cam"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_ip_cam);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_10);

        lineEdit_username = new QLineEdit(groupBox_3);
        lineEdit_username->setObjectName(QStringLiteral("lineEdit_username"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEdit_username);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_8);

        lineEdit_password = new QLineEdit(groupBox_3);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEdit_password);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButton_connect_cam = new QPushButton(groupBox_3);
        pushButton_connect_cam->setObjectName(QStringLiteral("pushButton_connect_cam"));
        pushButton_connect_cam->setCheckable(true);

        horizontalLayout_6->addWidget(pushButton_connect_cam);

        pushButton_close = new QPushButton(groupBox_3);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));

        horizontalLayout_6->addWidget(pushButton_close);

        pushButton_getcam = new QPushButton(groupBox_3);
        pushButton_getcam->setObjectName(QStringLiteral("pushButton_getcam"));

        horizontalLayout_6->addWidget(pushButton_getcam);

        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_6->addWidget(pushButton);

        pushButton_catch = new QPushButton(groupBox_3);
        pushButton_catch->setObjectName(QStringLiteral("pushButton_catch"));

        horizontalLayout_6->addWidget(pushButton_catch);


        formLayout_2->setLayout(3, QFormLayout::FieldRole, horizontalLayout_6);


        verticalLayout_6->addLayout(formLayout_2);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(groupBox_5);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        splitter_7 = new QSplitter(groupBox_4);
        splitter_7->setObjectName(QStringLiteral("splitter_7"));
        splitter_7->setOrientation(Qt::Horizontal);
        splitter_3 = new QSplitter(splitter_7);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        label_7 = new QLabel(splitter_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        splitter_3->addWidget(label_7);
        comboBox_robo = new QComboBox(splitter_3);
        comboBox_robo->setObjectName(QStringLiteral("comboBox_robo"));
        splitter_3->addWidget(comboBox_robo);
        splitter_7->addWidget(splitter_3);
        splitter_4 = new QSplitter(splitter_7);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setOrientation(Qt::Vertical);
        label_11 = new QLabel(splitter_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        splitter_4->addWidget(label_11);
        comboBox_cam = new QComboBox(splitter_4);
        comboBox_cam->setObjectName(QStringLiteral("comboBox_cam"));
        splitter_4->addWidget(comboBox_cam);
        splitter_7->addWidget(splitter_4);
        splitter_6 = new QSplitter(splitter_7);
        splitter_6->setObjectName(QStringLiteral("splitter_6"));
        splitter_6->setOrientation(Qt::Vertical);
        label_14 = new QLabel(splitter_6);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setAlignment(Qt::AlignCenter);
        splitter_6->addWidget(label_14);
        lineEdit_taskname = new QLineEdit(splitter_6);
        lineEdit_taskname->setObjectName(QStringLiteral("lineEdit_taskname"));
        splitter_6->addWidget(lineEdit_taskname);
        splitter_7->addWidget(splitter_6);
        splitter_5 = new QSplitter(splitter_7);
        splitter_5->setObjectName(QStringLiteral("splitter_5"));
        splitter_5->setOrientation(Qt::Vertical);
        label_13 = new QLabel(splitter_5);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);
        splitter_5->addWidget(label_13);
        pushButton_taskset = new QPushButton(splitter_5);
        pushButton_taskset->setObjectName(QStringLiteral("pushButton_taskset"));
        splitter_5->addWidget(pushButton_taskset);
        splitter_7->addWidget(splitter_5);

        verticalLayout_5->addWidget(splitter_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_3->addWidget(label_15);

        lineEdit_save = new QLineEdit(groupBox_4);
        lineEdit_save->setObjectName(QStringLiteral("lineEdit_save"));

        horizontalLayout_3->addWidget(lineEdit_save);

        read_set = new QPushButton(groupBox_4);
        read_set->setObjectName(QStringLiteral("read_set"));

        horizontalLayout_3->addWidget(read_set);

        save_set = new QPushButton(groupBox_4);
        save_set->setObjectName(QStringLiteral("save_set"));

        horizontalLayout_3->addWidget(save_set);


        verticalLayout_5->addLayout(horizontalLayout_3);

        splitter_9 = new QSplitter(groupBox_4);
        splitter_9->setObjectName(QStringLiteral("splitter_9"));
        splitter_9->setOrientation(Qt::Horizontal);
        textEdit_setinfo = new QTextEdit(splitter_9);
        textEdit_setinfo->setObjectName(QStringLiteral("textEdit_setinfo"));
        splitter_9->addWidget(textEdit_setinfo);
        pushButton_start = new QPushButton(splitter_9);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        pushButton_start->setCheckable(true);
        splitter_9->addWidget(pushButton_start);

        verticalLayout_5->addWidget(splitter_9);


        verticalLayout_4->addWidget(groupBox_4);


        gridLayout->addWidget(groupBox_5, 1, 1, 1, 1);

        label = new QLabel(SCTcpToolWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 2);


        retranslateUi(SCTcpToolWidget);

        QMetaObject::connectSlotsByName(SCTcpToolWidget);
    } // setupUi

    void retranslateUi(QWidget *SCTcpToolWidget)
    {
        SCTcpToolWidget->setWindowTitle(QApplication::translate("SCTcpToolWidget", "SeerTCPTest", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SCTcpToolWidget", "\350\257\267\346\261\202", Q_NULLPTR));
        label_2->setText(QApplication::translate("SCTcpToolWidget", "IP:", Q_NULLPTR));
        lineEdit_ip->setText(QApplication::translate("SCTcpToolWidget", "192.168.1.5", Q_NULLPTR));
        label_3->setText(QApplication::translate("SCTcpToolWidget", "\347\253\257\345\217\243\345\217\267:", Q_NULLPTR));
        comboBox_port->clear();
        comboBox_port->insertItems(0, QStringList()
         << QApplication::translate("SCTcpToolWidget", "19204", Q_NULLPTR)
         << QApplication::translate("SCTcpToolWidget", "19205", Q_NULLPTR)
         << QApplication::translate("SCTcpToolWidget", "19206", Q_NULLPTR)
         << QApplication::translate("SCTcpToolWidget", "19207", Q_NULLPTR)
         << QApplication::translate("SCTcpToolWidget", "19208", Q_NULLPTR)
         << QApplication::translate("SCTcpToolWidget", "19209", Q_NULLPTR)
         << QApplication::translate("SCTcpToolWidget", "19210", Q_NULLPTR)
        );
        label_9->setText(QApplication::translate("SCTcpToolWidget", "\346\212\245\346\226\207\347\261\273\345\236\213\357\274\210API\347\274\226\345\217\267\357\274\211:", Q_NULLPTR));
        lineEdit_sendCommand->setText(QApplication::translate("SCTcpToolWidget", "1301", Q_NULLPTR));
        label_4->setText(QApplication::translate("SCTcpToolWidget", "\345\272\217\345\217\267\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("SCTcpToolWidget", "\346\225\260\346\215\256\345\214\272:", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("SCTcpToolWidget", "\345\274\200\345\247\213\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("SCTcpToolWidget", "\345\217\221\351\200\201", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SCTcpToolWidget", "\345\223\215\345\272\224", Q_NULLPTR));
        pushButton_getrobo->setText(QApplication::translate("SCTcpToolWidget", "\346\210\252\345\217\226\346\234\272\345\231\250\344\272\272\344\273\273\345\212\241\344\275\215\347\275\256\347\202\271", Q_NULLPTR));
        label_revText->setText(QString());
        label_12->setText(QApplication::translate("SCTcpToolWidget", "\346\216\245\346\224\266\345\214\272:", Q_NULLPTR));
        checkBox_revHex->setText(QApplication::translate("SCTcpToolWidget", "\345\215\201\345\205\255\350\277\233\345\210\266", Q_NULLPTR));
        textEdit_revData->setHtml(QApplication::translate("SCTcpToolWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        checkBox_automatically->setText(QApplication::translate("SCTcpToolWidget", "\350\207\252\345\212\250\346\273\232\345\212\250", Q_NULLPTR));
        pushButton_clearInfo->setText(QApplication::translate("SCTcpToolWidget", "\346\270\205\347\251\272", Q_NULLPTR));
        groupBox_5->setTitle(QString());
        groupBox_3->setTitle(QApplication::translate("SCTcpToolWidget", "\346\221\204\345\203\217\345\244\264\350\277\236\346\216\245", Q_NULLPTR));
        label_6->setText(QApplication::translate("SCTcpToolWidget", "IP:", Q_NULLPTR));
        lineEdit_ip_cam->setText(QApplication::translate("SCTcpToolWidget", "192.168.1.64", Q_NULLPTR));
        label_10->setText(QApplication::translate("SCTcpToolWidget", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        lineEdit_username->setText(QApplication::translate("SCTcpToolWidget", "admin", Q_NULLPTR));
        label_8->setText(QApplication::translate("SCTcpToolWidget", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        lineEdit_password->setText(QApplication::translate("SCTcpToolWidget", "seer1234", Q_NULLPTR));
        pushButton_connect_cam->setText(QApplication::translate("SCTcpToolWidget", "\345\274\200\345\247\213\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("SCTcpToolWidget", "\346\226\255\345\274\200", Q_NULLPTR));
        pushButton_getcam->setText(QApplication::translate("SCTcpToolWidget", "\350\216\267\345\217\226\351\242\204\347\275\256\347\202\271", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SCTcpToolWidget", "\350\275\254\345\210\260\351\242\204\347\275\256\347\202\271", Q_NULLPTR));
        pushButton_catch->setText(QApplication::translate("SCTcpToolWidget", "\346\212\223\345\233\276", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("SCTcpToolWidget", "\345\205\263\350\201\224\351\205\215\347\275\256", Q_NULLPTR));
        label_7->setText(QApplication::translate("SCTcpToolWidget", "\346\234\272\345\231\250\344\272\272\344\275\215\347\275\256\347\202\271", Q_NULLPTR));
        label_11->setText(QApplication::translate("SCTcpToolWidget", "\346\221\204\345\203\217\345\244\264\351\242\204\347\275\256\347\202\271", Q_NULLPTR));
        label_14->setText(QApplication::translate("SCTcpToolWidget", "\345\220\215\347\247\260", Q_NULLPTR));
        label_13->setText(QApplication::translate("SCTcpToolWidget", "\345\205\263\350\201\224", Q_NULLPTR));
        pushButton_taskset->setText(QApplication::translate("SCTcpToolWidget", "set", Q_NULLPTR));
        label_15->setText(QApplication::translate("SCTcpToolWidget", "\345\233\276\345\203\217\344\277\235\345\255\230\344\275\215\347\275\256", Q_NULLPTR));
        lineEdit_save->setText(QApplication::translate("SCTcpToolWidget", "C:\\\\Users\\\\LHM\\\\Desktop\\\\11", Q_NULLPTR));
        read_set->setText(QApplication::translate("SCTcpToolWidget", "\345\257\274\345\205\245\351\205\215\347\275\256\346\226\207\344\273\266", Q_NULLPTR));
        save_set->setText(QApplication::translate("SCTcpToolWidget", "\344\277\235\345\255\230\351\205\215\347\275\256\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("SCTcpToolWidget", "start", Q_NULLPTR));
        label->setText(QApplication::translate("SCTcpToolWidget", "\346\234\272\345\231\250\344\272\272\345\267\241\346\243\200\346\221\204\345\203\217\345\244\264\351\205\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SCTcpToolWidget: public Ui_SCTcpToolWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCTCPTOOLWIDGET_H
