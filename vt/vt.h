/*------------------------------------------------------------------------------
* vt.h : header file for virtual console
*
*          Copyright (C) 2015 by T.TAKASU, All rights reserved.
*
* version : $Revision:$ $Date:$
* history : 2015/01/11 1.0  separated from rtkrcv.c
*-----------------------------------------------------------------------------*/
#ifndef VT_H
#define VT_H
#include <termios.h>
#include "rtklib.h"

#define MAXBUFF     4096                /* size of line buffer */
#define MAXHIST     256                 /* size of history buffer */

/* type definitions ----------------------------------------------------------*/
typedef struct vt_tag {                 /* virtual console type */          // 
    int state;                          /* state(0:close,1:open) */         // (0:close,1:open)
    int type;                           /* type (0:dev,1:telnet) */         // (0:dev,1:telnet)
    int in,out;                         /* input/output file descriptor */  // 输入、输出文件描述符
    int n,nesc;                         /* number of line buffer/escape */  // 当前行数
    int cur;                            /* cursor position */               // 光标位置
    int cur_h;                          /* current history */               // 光标历史位置
    int brk;                            /* break status */                  // 
    int blind;                          /* blind inpu mode */               // 
    struct termios tio;                 /* original terminal attribute */   // 屏蔽输入模式
    char buff[MAXBUFF];                 /* line buffer */                   //
    char esc[8];                        /* escape buffer */                 //
    char *hist[MAXHIST];                /* history buffer */                // 历史字符串
    FILE *logfp;                        /* log file pointer */              // log 文件指针
} vt_t;

/* function prototypes -------------------------------------------------------*/
extern vt_t *vt_open(int sock, const char *dev);
extern void vt_close(vt_t *vt);
extern int vt_getc(vt_t *vt, char *c);
extern int vt_gets(vt_t *vt, char *buff, int n);
extern int vt_putc(vt_t *vt, char c);
extern int vt_puts(vt_t *vt, const char *buff);
extern int vt_printf(vt_t *vt, const char *format, ...);
extern int vt_chkbrk(vt_t *vt);
extern int vt_openlog(vt_t *vt, const char *file);
extern void vt_closelog(vt_t *vt);

#endif /* VT_H */
