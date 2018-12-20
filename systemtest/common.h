/*
系统全局变量
*/
#ifndef COMMON_H
#define COMMON_H

#include <QString>

#define DEFAULT_SKIN ":/skin/7_big"
/*保存密码*/
extern QString PWD;
 /*密码操作标志*/
extern int Flag_Read_Pwd;//密码可读
extern int Flag_Read_Pwd_times;

extern int Flag_skin; //皮肤改变
extern int Flag_Cancel; //取消操作

extern int Flag_Sys_Test_Page;//是否一键检测页面

//extern int pp;
extern int Flag_Current_Main_Page;

//==============================================================
// New version written by Wei Yitao

extern QString g_sWorkingPath;  // Current running path of this desktop application

//==============================================================


#endif // COMMON_H
