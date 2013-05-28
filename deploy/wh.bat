set mysql=D:\\Program Files\\MySQL\\MySQL Server 5.6

cd d:\Qt\Qt5.0.2\Sources\qtbase\src\plugins\sqldrivers\mysql\
qmake "INCLUDEPATH+=%mysql%\\include" "LIBS+=%mysql%\\lib\\libmysql.lib" mysql.pro
mingw32-make
