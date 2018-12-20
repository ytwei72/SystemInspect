#include "input_pwd.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "push_button.h"
#include "common.h"

extern QString PWD;
extern int Flag_Read_Pwd;
extern int Flag_Read_Pwd_times;

Input_Pwd::Input_Pwd(QDialog *parent) :
    DropShadowWidget(parent)
{
    setFixedSize(300,200);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    Flag_Cancel = 0; //初始化取消操作为0
    setWindowTitle(tr("input pwd window"));
    QDesktopWidget *d = QApplication::desktop();
    this->move((d->width()-300)/2, (d->height()-200)/2);

    /******* Layout ***********/
    tips = new QLabel(tr("深度测评需root权限"));
    remind  = new QLabel(tr("密码"));
    pwd_edit = new QLineEdit();
    pwd_edit->setEchoMode(QLineEdit::Password);
    submit = new QPushButton(tr("确定"));
    cancel = new QPushButton(tr("取消"));
    tips->setFixedHeight(30);
    remind->setFixedHeight(30);
    pwd_edit->setFixedHeight(30);
    submit->setFixedHeight(30);
    cancel->setFixedHeight(30);
    pro_pwd = new QProcess();
    // TODO: should rewrite the modules for the root privileges
    // set the not-verify-root mode
    Flag_Read_Pwd = 1;
//    Flag_Read_Pwd = 0;
    Flag_Read_Pwd_times = 0;
    pwd_edit->setPlaceholderText(tr("请输入密码"));

    QFont font;
    font.setPixelSize(16);
    tips->setFont(font);

    QHBoxLayout *top_layout = new QHBoxLayout();
    top_layout->addWidget(tips, 0, Qt::AlignLeft);
    top_layout->setContentsMargins(30,0,30,0);
    QHBoxLayout *center_layout = new QHBoxLayout();
    center_layout->addWidget(remind);
    center_layout->addSpacing(10);
    center_layout->addWidget(pwd_edit);
    center_layout->setContentsMargins(30,0,30,0);
    QHBoxLayout *buttom_layout = new QHBoxLayout();
    buttom_layout->addSpacing(80);
    buttom_layout->addWidget(submit);
    buttom_layout->addStretch();
    buttom_layout->addWidget(cancel);
    buttom_layout->setContentsMargins(0,0,30,0);
    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addSpacing(15);
    main_layout->addLayout(top_layout);
    main_layout->addLayout(center_layout);
    main_layout->addLayout(buttom_layout);
    main_layout->setContentsMargins(0,50,0,20);
    this->setLayout(main_layout);

    connect(submit, SIGNAL(clicked()), this, SLOT(Set_Pwd()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(Set_Cancel()));
}

Input_Pwd::~Input_Pwd()
{

}

#if 0
void Input_Pwd::Set_Pwd()
{
    PWD = pwd_edit->text();
    QString program = "bash";
    QStringList arguments;
//    arguments<<"/usr/bin/testpwd/testpwd.sh"<<PWD;
    arguments<<g_sWorkingPath + "/Scripts/testpwd/testpwd.sh"<<PWD;

         out_pwd = "  ";
         pro_pwd->start(program, arguments);
         while(pro_pwd->waitForReadyRead())
             out_pwd = pro_pwd->readAll().trimmed();
             if(out_pwd == "Y")
             {
                 Flag_Read_Pwd = 1;
                 Flag_Cancel = 0;
                 pwd_edit->clear();
                 pwd_edit->setFocus();
                 this->close();
             }
             else if(out_pwd == "N")
             {
                 Flag_Read_Pwd = 0;
                 Flag_Read_Pwd_times++;
                 pwd_edit->clear();//清空
                 pwd_edit->setFocus();//光标位置
                 if(Flag_Read_Pwd_times == 1)
                        pwd_edit->setPlaceholderText("您还有两次机会");//提示信息
                 else if(Flag_Read_Pwd_times == 2)
                     pwd_edit->setPlaceholderText("您还有一次机会");
             }
        if(Flag_Read_Pwd_times == 3)
        {
            QMessageBox::warning(this, tr("警告!"), tr("密码错误!"), QMessageBox::Yes);
            Flag_Read_Pwd_times = 0;
            this->close();
        }
}
#else
void Input_Pwd::Set_Pwd()
{
    static int nFailedCount = 0;
    static const int MAX_RETRY = 3;

    // Get the password from the pwd contrtol
    QString strPwd = pwd_edit->text();

    // Using the bash command, prevent "chmod" operation for scripts
    QString strCommand = "bash";

    QStringList strArgs;
    // Give the sh script to be run
    strArgs.append(g_sWorkingPath + "/NewScripts/verification/verify_pwd.sh");
    // Set the password to be transferred to the shell
    strArgs.append(strPwd);

    QString strTempCmd = "bash ";
    strTempCmd.append(g_sWorkingPath + "/NewScripts/verification/verify_pwd2.sh ");
    strTempCmd.append(strPwd);
    strTempCmd = QString("sudo echo \"%1\" | su - root").arg(strPwd);

    // Not assign the parent object, to be deleted manually
    QProcess * procVerifyPwd = new QProcess();
//    procVerifyPwd->setArguments(strArgs);
//    procVerifyPwd->start();
    procVerifyPwd->start(strCommand, strArgs);
//    procVerifyPwd->start(strTempCmd);

    bool bAuthFailed;
    // Wait for the process to be ready for read, setting timeout to 5s
    bool bReady = procVerifyPwd->waitForFinished(10000);
    // Timeout equals to failure
    if (!bReady) {
        bAuthFailed = true;
    } else {
        QString strResult2 = procVerifyPwd->readAllStandardError();
        // if the running result is "Y", the auth is success, else failure
        QString strResult = procVerifyPwd->readAll().trimmed();
        bAuthFailed = (strResult == "Y") ? false : true;
    }

    Flag_Read_Pwd = bAuthFailed ? 0 : 1;

    // If failed to authentication ...
    if (bAuthFailed) {
        // Increase the failed count
        nFailedCount++;

        // Reach the MAX retry times, pop up the error tips
        if (nFailedCount >= MAX_RETRY) {
            QMessageBox::warning(this, tr("警告!"), tr("密码错误!"), QMessageBox::Yes);
        } else {
            QString strTips = QString("您还有%1次机会").arg(MAX_RETRY - nFailedCount);
            pwd_edit->setPlaceholderText(strTips); // tip for users
        }
    }

    // Destroy the process object
    procVerifyPwd->deleteLater();

    // Quit the authentication window, if success or too many failures
    if (!bAuthFailed || (nFailedCount >= MAX_RETRY)) {
        this->close();
    } else {
        // Clear the input password, ready for new input
        pwd_edit->clear();
        pwd_edit->setFocus();
    }
}
#endif

void Input_Pwd::Set_Cancel()
{
    Flag_Cancel = 1;
    Flag_Read_Pwd_times = 0;
    this->close();
}

void Input_Pwd::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    int width = this->width();
    int height = this->height();
    int draw_height = 60;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(DEFAULT_SKIN));

    QPainter painter2(this);
    painter2.setPen(Qt::NoPen);
    painter2.setBrush(QColor("#eaeaea"));
    painter2.drawRect(QRect(0, draw_height, width, height-draw_height));

}


