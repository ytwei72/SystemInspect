#-------------------------------------------------
#
#
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = systemtest
TEMPLATE = app

QT += widgets network
QT += testlib
QT += charts
CONFIG += thread


#QT += widgets
#QT += webkit
#QT += webkitwidgets/webview
#QT += network

SOURCES += main.cpp\
        main_widget.cpp \
    tool_button.cpp \
    drop_shadow_widget.cpp \
    title_widget.cpp \
    boot_start_time.cpp \
    input_pwd.cpp \
    common.cpp \
    push_button.cpp \
    sys_test_widget.cpp \
    buttom_widget.cpp \
    show_percent_page.cpp \
    main_page_one.cpp \
    main_page_two.cpp \
    main_page_three.cpp \
    main_page_four.cpp \
    main_page_five.cpp \
    main_page_six.cpp \
    user_msg.cpp \
    net_speed.cpp \
    main_page_serven.cpp \
    main_menu.cpp \
    about_us.cpp \
    wait_dialog.cpp \
    Utils/csysutils.cpp \
    Utils/cwebutils.cpp \
    Pages/cpagesysperformance.cpp \
    Charts/ccpudynamicchart.cpp \
    Charts/cmemorydynamicchart.cpp \
    Charts/czoomchartview.cpp \
    Charts/cmemallocchart.cpp \
    Charts/cprocmemranking.cpp \
    Charts/modeltablechartwidget.cpp \
    Charts/rankingtablemodel.cpp \
    Charts/execscriptsslavethread.cpp

HEADERS  += main_widget.h \
    tool_button.h \
    drop_shadow_widget.h \
    title_widget.h \
    boot_start_time.h \
    common.h \
    input_pwd.h \
    push_button.h \
    sys_test_widget.h \
    buttom_widget.h \
    show_percent_page.h \
    main_page_one.h \
    main_page_two.h \
    main_page_three.h \
    main_page_four.h \
    main_page_five.h \
    main_page_six.h \
    user_msg.h \
    net_speed.h \
    main_page_serven.h \
    main_menu.h \
    about_us.h \
    get_point.h \
    wait_dialog.h \
    Utils/csysutils.h \
    Utils/cwebutils.h \
    Pages/cpagesysperformance.h \
    Charts/ccpudynamicchart.h \
    Charts/cmemorydynamicchart.h \
    Charts/czoomchartview.h \
    Charts/cmemallocchart.h \
    Charts/cprocmemranking.h \
    Charts/modeltablechartwidget.h \
    Charts/rankingtablemodel.h \
    Charts/execscriptsslavethread.h

RESOURCES += \
    sources/resources.qrc
QT += widgets
QT += charts
#QT += webkit
QT += network


TRANSLATIONS += sources/sys_test.ts
RC_FILE = logo1.rc

OTHER_FILES +=

DISTFILES += \
    debug/systemtest \
    debug/NewScripts/verification/verify_pwd.sh \
    debug/NewScripts/verification/verify_pwd2.sh \
    debug/Scripts/boot_start/time1.sh \
    debug/Scripts/cpu_show/cpu_cal_rate.sh \
    debug/Scripts/cpu_show/cpu_show1.sh \
    debug/Scripts/cpu_show/cpu_show2.sh \
    debug/Scripts/disk/disktool/dd_test.sh \
    debug/Scripts/disk/disktool/disk_hdparm.sh \
    debug/Scripts/disk/disktool/hddtemp_install.sh \
    debug/Scripts/disk/disktool/hddtemp_judge.sh \
    debug/Scripts/disk/disktool/hddtemp_remove.sh \
    debug/Scripts/disk/disktool/hddtemp_tool.sh \
    debug/Scripts/disk/disktool/iostat_tool.sh \
    debug/Scripts/disk/disktool/sysstat_install.sh \
    debug/Scripts/disk/disktool/sysstat_judge.sh \
    debug/Scripts/disk/disktool/sysstat_remove.sh \
    debug/Scripts/disk/diskinfo.sh \
    debug/Scripts/disk/diskinfosu.sh \
    debug/Scripts/disk/io_diskstats.sh \
    debug/Scripts/flush_percent/cpu-mem.sh \
    debug/Scripts/flush_percent/cpu_rate.sh \
    debug/Scripts/flush_percent/mem_rate.sh \
    debug/Scripts/home_info/ethnetspeedhome.sh \
    debug/Scripts/home_info/homeinfo_btime.sh \
    debug/Scripts/home_info/homeinfousr.sh \
    debug/Scripts/home_info/netspeedhome.sh \
    debug/Scripts/home_info/wlannetspeedhome.sh \
    debug/Scripts/mem_show/mem_show1.sh \
    debug/Scripts/mem_show/mem_show2.sh \
    debug/Scripts/netinfo/1/netinfo.sh \
    debug/Scripts/netinfo/1/netinfosu.sh \
    debug/Scripts/netinfo/2/ethavgflow.sh \
    debug/Scripts/netinfo/2/netspeed.sh \
    debug/Scripts/netinfo/2/tcp_udp.sh \
    debug/Scripts/netinfo/2/test_netlink.sh \
    debug/Scripts/netinfo/2/wlanavgflow.sh \
    debug/Scripts/netinfo/3/firewall.sh \
    debug/Scripts/netinfo/3/net_secure.sh \
    debug/Scripts/netinfo/4/eth.sh \
    debug/Scripts/netinfo/4/wlan.sh \
    debug/Scripts/otherinfo/hardwareinfo.sh \
    debug/Scripts/otherinfo/hardwareinfomore.sh \
    debug/Scripts/otherinfo/startup.sh \
    debug/Scripts/otherinfo/systeminfo.sh \
    debug/Scripts/otherinfo/systemrun.sh \
    debug/Scripts/security/1/1.sh \
    debug/Scripts/security/1/2.sh \
    debug/Scripts/security/2/1.sh \
    debug/Scripts/security/2/2.sh \
    debug/Scripts/security/3/part1.sh \
    debug/Scripts/security/3/part2.sh \
    debug/Scripts/security/3/part3.sh \
    debug/Scripts/security/4/part1.sh \
    debug/Scripts/security/4/remove.sh \
    debug/Scripts/security/4/test.sh \
    debug/Scripts/security/4/test1.sh \
    debug/Scripts/security/5/part1.sh \
    debug/Scripts/security/5/remove.sh \
    debug/Scripts/security/5/test.sh \
    debug/Scripts/security/5/test1.sh \
    debug/Scripts/security/6/part1.sh \
    debug/Scripts/security/6/remove.sh \
    debug/Scripts/security/6/test.sh \
    debug/Scripts/security/6/test1.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_hyper.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_iowait.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_run_threads.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_sys_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_user_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_virtual.sh \
    debug/Scripts/sys_test/体检/一键测评/mem_evaluation/mem_user.sh \
    debug/Scripts/sys_test/体检/一键测评/开机时间/earntime.sh \
    debug/Scripts/sys_test/体检/一键测评/arp_secure.sh \
    debug/Scripts/sys_test/体检/一键测评/checkdisk.sh \
    debug/Scripts/sys_test/体检/一键测评/checkroot.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_hyper.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_iowait.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_run_threads.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_sys_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_user_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_virtual.sh \
    debug/Scripts/sys_test/体检/一键测评/earntime.sh \
    debug/Scripts/sys_test/体检/一键测评/firefox_cookies.sh \
    debug/Scripts/sys_test/体检/一键测评/google_cookies.sh \
    debug/Scripts/sys_test/体检/一键测评/google_history.sh \
    debug/Scripts/sys_test/体检/一键测评/init_arp.sh \
    debug/Scripts/sys_test/体检/一键测评/io_await.sh \
    debug/Scripts/sys_test/体检/一键测评/io_reqnum.sh \
    debug/Scripts/sys_test/体检/一键测评/io_svctm.sh \
    debug/Scripts/sys_test/体检/一键测评/io_util.sh \
    debug/Scripts/sys_test/体检/一键测评/iptables_judge.sh \
    debug/Scripts/sys_test/体检/一键测评/junk_files.sh \
    debug/Scripts/sys_test/体检/一键测评/mem_user.sh \
    debug/Scripts/sys_test/体检/一键测评/recent_used.sh \
    debug/Scripts/sys_test/体检/一键测评/startup_items.sh \
    debug/Scripts/sys_test/arp_secure.sh \
    debug/Scripts/sys_test/checkdisk.sh \
    debug/Scripts/sys_test/cpu_hyper.sh \
    debug/Scripts/sys_test/cpu_iowait.sh \
    debug/Scripts/sys_test/cpu_run_threads.sh \
    debug/Scripts/sys_test/cpu_sys_rate.sh \
    debug/Scripts/sys_test/cpu_user_rate.sh \
    debug/Scripts/sys_test/cpu_virtual.sh \
    debug/Scripts/sys_test/earntime.sh \
    debug/Scripts/sys_test/firefox_cookies.sh \
    debug/Scripts/sys_test/google_cookies.sh \
    debug/Scripts/sys_test/google_history.sh \
    debug/Scripts/sys_test/init_arp.sh \
    debug/Scripts/sys_test/io_await.sh \
    debug/Scripts/sys_test/io_reqnum.sh \
    debug/Scripts/sys_test/io_svctm.sh \
    debug/Scripts/sys_test/io_util.sh \
    debug/Scripts/sys_test/junk_files.sh \
    debug/Scripts/sys_test/mem_user.sh \
    debug/Scripts/sys_test/recent_used.sh \
    debug/Scripts/sys_test_result/show_result.sh \
    debug/Scripts/testpwd/testpwd.sh \
    sources/score.gif \
    sources/html/picture/1.jpg \
    sources/html/picture/new_11.jpg \
    sources/html/picture/new_13.jpg \
    sources/html/picture/new_15.jpg \
    sources/html/picture/new_6.jpg \
    sources/html/picture/new_8.jpg \
    sources/html/picture/new_9.jpg \
    sources/img/skin/15.jpg \
    sources/img/skin/15_big.jpg \
    sources/img/skin/16.jpg \
    sources/img/skin/16_big.jpg \
    sources/img/skin/17.jpg \
    sources/img/skin/17_big.jpg \
    sources/img/skin/18.jpg \
    sources/img/skin/18_big.jpg \
    sources/img/skin/19.jpg \
    sources/img/skin/19_big.jpg \
    sources/img/skin/20.jpg \
    sources/img/skin/20_big.jpg \
    sources/img/skin/21.jpg \
    sources/img/skin/21_big.jpg \
    sources/img/skin/22.jpg \
    sources/img/skin/22_big.jpg \
    sources/img/skin/23.jpg \
    sources/img/skin/23_big.jpg \
    sources/1_big.jpg \
    sources/3_big.jpg \
    sources/4_big.jpg \
    sources/5_big.jpg \
    sources/6_big.jpg \
    sources/7_big.jpg \
    sources/cpu1.jpg \
    sources/cpu2.jpg \
    sources/disk1.jpg \
    sources/disk2.jpg \
    sources/disk3.jpg \
    sources/disk4.jpg \
    sources/net1.jpg \
    sources/net2.jpg \
    sources/net3.jpg \
    sources/net4.jpg \
    sources/os1.jpg \
    sources/os2.jpg \
    sources/os3.jpg \
    sources/html/picture/new_1.png \
    sources/html/picture/new_10.png \
    sources/html/picture/new_12.png \
    sources/html/picture/new_14.png \
    sources/html/picture/new_16.png \
    sources/html/picture/new_2.png \
    sources/html/picture/new_3.png \
    sources/html/picture/new_4.png \
    sources/html/picture/new_5.png \
    sources/html/picture/new_7.png \
    sources/img/skin/12_big.png \
    sources/img/skin/13.png \
    sources/img/skin/13_big.png \
    sources/img/skin/14.png \
    sources/img/skin/14_big.png \
    sources/img/skin/9.png \
    sources/img/11 \
    sources/img/loading.png \
    sources/2_big.png \
    sources/8_big.png \
    sources/arrow_down.png \
    sources/check.png \
    sources/close.png \
    sources/close_hover.png \
    sources/close_pressed.png \
    sources/feedback.png \
    sources/feedback_hover.png \
    sources/feedback_pressed.png \
    sources/func1.png \
    sources/func2.png \
    sources/func3.png \
    sources/func4.png \
    sources/func5.png \
    sources/func6.png \
    sources/func7.png \
    sources/func8.png \
    sources/logo.png \
    sources/logo1.png \
    sources/logo2.png \
    sources/menu.png \
    sources/menu_hover.png \
    sources/menu_pressed.png \
    sources/min.png \
    sources/min_hover.png \
    sources/min_pressed.png \
    sources/power.png \
    sources/score.png \
    sources/security_1.png \
    sources/security_2.png \
    sources/security_3.png \
    sources/security_4.png \
    sources/skin.png \
    sources/skin_hover.png \
    sources/skin_pressed.png \
    sources/xx.png \
    sources/xxxx.png \
    sources/logo.ico \
    sources/html/index.html \
    sources/index.html \
    debug/Scripts/security/5/bin.2015-01-20_15_55_38.file \
    debug/Scripts/sys_test/体检/一键测评/测评标准 \
    sources/logo1.rc \
    sources/sys_test.ts \
    debug/NewScripts/memory/mem_info.sh \
    debug/NewScripts/verification/verify_pwd.sh \
    debug/NewScripts/verification/verify_pwd2.sh \
    debug/Scripts/boot_start/time1.sh \
    debug/Scripts/cpu_show/cpu_cal_rate.sh \
    debug/Scripts/cpu_show/cpu_show1.sh \
    debug/Scripts/cpu_show/cpu_show2.sh \
    debug/Scripts/disk/disktool/dd_test.sh \
    debug/Scripts/disk/disktool/disk_hdparm.sh \
    debug/Scripts/disk/disktool/hddtemp_install.sh \
    debug/Scripts/disk/disktool/hddtemp_judge.sh \
    debug/Scripts/disk/disktool/hddtemp_remove.sh \
    debug/Scripts/disk/disktool/hddtemp_tool.sh \
    debug/Scripts/disk/disktool/iostat_tool.sh \
    debug/Scripts/disk/disktool/sysstat_install.sh \
    debug/Scripts/disk/disktool/sysstat_judge.sh \
    debug/Scripts/disk/disktool/sysstat_remove.sh \
    debug/Scripts/disk/diskinfo.sh \
    debug/Scripts/disk/diskinfosu.sh \
    debug/Scripts/disk/io_diskstats.sh \
    debug/Scripts/flush_percent/cpu-mem.sh \
    debug/Scripts/flush_percent/cpu_rate.sh \
    debug/Scripts/flush_percent/mem_rate.sh \
    debug/Scripts/home_info/ethnetspeedhome.sh \
    debug/Scripts/home_info/homeinfo_btime.sh \
    debug/Scripts/home_info/homeinfousr.sh \
    debug/Scripts/home_info/netspeedhome.sh \
    debug/Scripts/home_info/wlannetspeedhome.sh \
    debug/Scripts/mem_show/mem_show1.sh \
    debug/Scripts/mem_show/mem_show2.sh \
    debug/Scripts/netinfo/1/netinfo.sh \
    debug/Scripts/netinfo/1/netinfosu.sh \
    debug/Scripts/netinfo/2/ethavgflow.sh \
    debug/Scripts/netinfo/2/netspeed.sh \
    debug/Scripts/netinfo/2/tcp_udp.sh \
    debug/Scripts/netinfo/2/test_netlink.sh \
    debug/Scripts/netinfo/2/wlanavgflow.sh \
    debug/Scripts/netinfo/3/firewall.sh \
    debug/Scripts/netinfo/3/net_secure.sh \
    debug/Scripts/netinfo/4/eth.sh \
    debug/Scripts/netinfo/4/wlan.sh \
    debug/Scripts/otherinfo/hardwareinfo.sh \
    debug/Scripts/otherinfo/hardwareinfomore.sh \
    debug/Scripts/otherinfo/startup.sh \
    debug/Scripts/otherinfo/systeminfo.sh \
    debug/Scripts/otherinfo/systemrun.sh \
    debug/Scripts/security/1/1.sh \
    debug/Scripts/security/1/2.sh \
    debug/Scripts/security/2/1.sh \
    debug/Scripts/security/2/2.sh \
    debug/Scripts/security/3/part1.sh \
    debug/Scripts/security/3/part2.sh \
    debug/Scripts/security/3/part3.sh \
    debug/Scripts/security/4/part1.sh \
    debug/Scripts/security/4/remove.sh \
    debug/Scripts/security/4/test.sh \
    debug/Scripts/security/4/test1.sh \
    debug/Scripts/security/5/part1.sh \
    debug/Scripts/security/5/remove.sh \
    debug/Scripts/security/5/test.sh \
    debug/Scripts/security/5/test1.sh \
    debug/Scripts/security/6/part1.sh \
    debug/Scripts/security/6/remove.sh \
    debug/Scripts/security/6/test.sh \
    debug/Scripts/security/6/test1.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_hyper.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_iowait.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_run_threads.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_sys_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_user_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_evaluation/cpu_virtual.sh \
    debug/Scripts/sys_test/体检/一键测评/mem_evaluation/mem_user.sh \
    debug/Scripts/sys_test/体检/一键测评/开机时间/earntime.sh \
    debug/Scripts/sys_test/体检/一键测评/arp_secure.sh \
    debug/Scripts/sys_test/体检/一键测评/checkdisk.sh \
    debug/Scripts/sys_test/体检/一键测评/checkroot.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_hyper.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_iowait.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_run_threads.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_sys_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_user_rate.sh \
    debug/Scripts/sys_test/体检/一键测评/cpu_virtual.sh \
    debug/Scripts/sys_test/体检/一键测评/earntime.sh \
    debug/Scripts/sys_test/体检/一键测评/firefox_cookies.sh \
    debug/Scripts/sys_test/体检/一键测评/google_cookies.sh \
    debug/Scripts/sys_test/体检/一键测评/google_history.sh \
    debug/Scripts/sys_test/体检/一键测评/init_arp.sh \
    debug/Scripts/sys_test/体检/一键测评/io_await.sh \
    debug/Scripts/sys_test/体检/一键测评/io_reqnum.sh \
    debug/Scripts/sys_test/体检/一键测评/io_svctm.sh \
    debug/Scripts/sys_test/体检/一键测评/io_util.sh \
    debug/Scripts/sys_test/体检/一键测评/iptables_judge.sh \
    debug/Scripts/sys_test/体检/一键测评/junk_files.sh \
    debug/Scripts/sys_test/体检/一键测评/mem_user.sh \
    debug/Scripts/sys_test/体检/一键测评/recent_used.sh \
    debug/Scripts/sys_test/体检/一键测评/startup_items.sh \
    debug/Scripts/sys_test/arp_secure.sh \
    debug/Scripts/sys_test/checkdisk.sh \
    debug/Scripts/sys_test/cpu_hyper.sh \
    debug/Scripts/sys_test/cpu_iowait.sh \
    debug/Scripts/sys_test/cpu_run_threads.sh \
    debug/Scripts/sys_test/cpu_sys_rate.sh \
    debug/Scripts/sys_test/cpu_user_rate.sh \
    debug/Scripts/sys_test/cpu_virtual.sh \
    debug/Scripts/sys_test/earntime.sh \
    debug/Scripts/sys_test/firefox_cookies.sh \
    debug/Scripts/sys_test/google_cookies.sh \
    debug/Scripts/sys_test/google_history.sh \
    debug/Scripts/sys_test/init_arp.sh \
    debug/Scripts/sys_test/io_await.sh \
    debug/Scripts/sys_test/io_reqnum.sh \
    debug/Scripts/sys_test/io_svctm.sh \
    debug/Scripts/sys_test/io_util.sh \
    debug/Scripts/sys_test/junk_files.sh \
    debug/Scripts/sys_test/mem_user.sh \
    debug/Scripts/sys_test/recent_used.sh \
    debug/Scripts/sys_test_result/show_result.sh \
    debug/Scripts/testpwd/testpwd.sh \
    debug/Scripts/security/5/bin.2015-01-20_15_55_38.file \
    debug/Scripts/sys_test/体检/一键测评/测评标准 \
    debug/NewScripts/memory/mem_ranking.sh

FORMS +=

