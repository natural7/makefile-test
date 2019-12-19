#输出文件夹
OUTFILE=debug
#可执行程序文件夹
OUTBIN=bin
#连接目标文件夹
OBJFILE=obj


#判断输出文件夹是否存在，如果不存在自动填充
#https://blog.csdn.net/zhangxinrun/article/details/19561567
#这里使用的比较高级的方法
ifneq ($(OUTFILE), $(wildcard $(OUTFILE)))
#https://zhidao.baidu.com/question/1895995908299110100.html
#如果父目录没有，mkdir -p可以连带创建父级目录
$(shell mkdir -p $(OUTFILE) $(OUTFILE)/$(OUTBIN) $(OUTFILE)/$(OBJFILE))
#下边这句话的意思是：在debug目录下创建并写入makefile
#https://blog.csdn.net/kehyuanyu/article/details/21454789
#https://blog.csdn.net/huohongpeng/article/details/72624910 对比
# $$：针对 shell 变量(也就是指令中的变量，比如下边 shell xxx,形成的指令)，$针对makefile中的变量
#这里不能写为$，  因为$var是空的
# 使用 $() 执行并获取命令输出赋值给变量
#添加 -e，来识别 \n(换行) \t(tab键),否则有时候识别不到。
$(shell echo -e 'OBJS=*.o\nODIR=obj\n$$(ROOT_DIR)/$$(BIN_DIR)/$$(BIN):$$(ODIR)/$$(OBJS)\n\t$$(CC) -o $$@ $$^ $$(CFLAGS) $$(LDFLAGS)'>$(OUTFILE)/Makefile)
#上述语句形成下边的语句
#OBJS=*.o
#ODIR=obj
#$(ROOT_DIR)/$(BIN_DIR)/$(BIN):$(ODIR)/$(OBJS)
#	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
endif
#下面给出了判断路径下有木有 文件，文件夹 的方法
#输出文件夹下Makefile文件是否存在
#这里直接使用了 Makefile，没有再包一层
ifneq ($(OUTFILE)/Makefile, $(wildcard $(OUTFILE)/Makefile))
$(shell echo 'OBJS=*.o\nODIR=obj\n$$(ROOT_DIR)/$$(BIN_DIR)/$$(BIN):$$(ODIR)/$$(OBJS)\n\t$$(CC) -o $$@ $$^ $$(CFLAGS) $$(LDFLAGS)'>$(OUTFILE)/Makefile)
endif
#判断可执行程序文件夹是否存在
ifneq ($(OUTFILE)/$(OUTBIN), $(wildcard $(OUTFILE)/$(OUTBIN)))
$(shell mkdir -p $(OUTFILE)/$(OUTBIN))
endif
#判断连接目标文件夹是否存在
ifneq ($(OUTFILE)/$(OBJFILE), $(wildcard $(OUTFILE)/$(OBJFILE)))
$(shell mkdir -p $(OUTFILE)/$(OBJFILE))
#just for test
$(shell echo aaa > tem.txt)
endif



#设置编译器
CC=gcc
CPP=g++
#debug文件夹里的makefile文件需要最后执行，所以这里需要执行的子目录要排除debug文件夹，这里使用awk排除了debug文件夹，读取剩下的文件夹
#grep ^d 查找文件夹
#$$9 第9个参数，从第一个开始 比如$$1 为“drwxr-xr-x”这个
#https://www.cnblogs.com/ftl1012/p/9250541.html
#以空格为默认分隔符将每行切片，切开的部分再进行各种分析处理
#print 将结果print到SUBDIRS
#这里有个问题，只添加了最外层的文件路径，内部的没有添加
#可以通过三种方式添加：
#1.直接添加到include文件中，简答粗暴，内层的可能不想暴露给外边，include属于外层了  目前项目一般这么做
#2.递归过程中添加
#3.直接递归查找文件夹
SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
# $(@echo $(SUBDIRS))
#SUBDIRS删除includes文件夹，因为这个文件中是头文件，不需要make
SUBDIRS:=$(patsubst includes,,$(SUBDIRS))
#无需下一行的注释代码，因为我们已经知道debug里的makefile是最后执行的，所以最后直接去debug目录下执行指定的makefile文件就行，具体下面有注释
#DEBUG=$(shell ls -l | grep ^d | awk '{if($$9 == "debug") print $$9}')
#记住当前工程的根目录路径
ROOT_DIR=$(shell pwd)
#最终bin文件的名字，可以更改为自己需要的
BIN=myapp
#目标文件所在的目录
OBJS_DIR=debug/obj
#bin文件所在的目录
BIN_DIR=debug/bin
#获取 当前目录下  的c文件集，放在变量CUR_SOURCE中
CUR_SOURCE=${wildcard *.c}
#将 当前目录下 对应的c文件名转为o文件后放在下面的CUR_OBJS变量中  重要：最终所有的.o都放到这里，这样好编译
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}
#删除
RM=rm -rf
## debug flag
DBG_ENABLE   = 0
## 需要的库，都放这里，可以有多个
LIBS := mylib mylib2
## used headers  file path
#这里单独加include路径，不影响 上边 所说的SUBDIRS，编译问题
INCLUDE_PATH = $(ROOT_DIR)/includes/
#这里单独加include路径
INCLUDE_PATH += $(SUBDIRS)
INCLUDE_PATH += ../
#使用的库目录，静态库和动态库添加在这里
#这个地址最终在debug文件中使用，所以是以debug的路径为起始 相对
LIBRARY_PATH := ../../  ../../lib2
## debug for debug info, when use gdb to debug
ifeq (1, ${DBG_ENABLE}) 
	CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
endif
#3种路径
## get all include path
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))
## get all library path/路径，可以有多个
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))
## get all librarys 库的名字，也是可以有多个
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))
#将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CC BIN OBJS_DIR BIN_DIR ROOT_DIR LDFLAGS CFLAGS
#注意这里的顺序，需要先执行SUBDIRS最后才能是DEBUG
# build: $(SUBDIRS) $(CUR_OBJS) DEBUG
all: $(clean) $(SUBDIRS) $(CUR_OBJS) DEBUG
#递归执行子目录下的makefile文件，这是递归执行的关键
$(SUBDIRS):ECHO
	make -C $@
DEBUG:ECHO
#直接去debug目录下执行makefile文件
	make -C debug

#注意这里获取echo 的方法
#注释写的位置也有讲究，不可写在下边和@echo对齐。。。
ECHO:
	@echo $(SUBDIRS)
#将c文件编译为o文件，并放在指定放置目标文件的目录中即OBJS_DIR
$(CUR_OBJS):%.o:%.c
	$(CC) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@ $(CFLAGS) $(LDFLAGS)
clean:
	@rm $(OBJS_DIR)/*.o
	@$(RM) $(BIN_DIR)/*