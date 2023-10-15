#include "netheader.h"
#include "logqueue.h"


QUEUE_DATA<MESG> queue_send; //锟侥憋拷锟斤拷锟斤拷频锟斤拷锟酵讹拷锟斤拷
QUEUE_DATA<MESG> queue_recv; //锟斤拷锟秸讹拷锟斤拷
QUEUE_DATA<MESG> audio_recv; //锟斤拷频锟斤拷锟秸讹拷锟斤拷

LogQueue *logqueue = nullptr;

void log_print(const char *filename, const char *funcname, int line, const char *fmt, ...)
{
    Log *log = (Log *) malloc(sizeof (Log));
    if(log == nullptr)
    {
        qDebug() << "malloc log fail";
    }
    else
    {
        memset(log, 0, sizeof (Log));
        log->ptr = (char *) malloc(1 * KB);
        if(log->ptr == nullptr)
        {
            free(log);
            qDebug() << "malloc log.ptr fail";
            return;
        }
        else
        {
            memset(log->ptr, 0, 1 * KB);
            time_t t = time(NULL);

            int pos = 0;
            int m = strftime(log->ptr + pos, KB - 2 - pos, "%F %H:%M:%S ", localtime(&t));
			pos += m;

            m = snprintf(log->ptr + pos, KB - 2 - pos, "%s:%s::%d>>>", filename, funcname, line);
			pos += m;

			va_list ap;
			va_start(ap, fmt);
            m = _vsnprintf(log->ptr + pos, KB - 2 - pos, fmt, ap);
			pos += m;
			va_end(ap);
            strcat_s(log->ptr+pos, KB-pos, "\n");
            log->len = strlen(log->ptr);

            //把日志 添加到 日志队列中
			logqueue->pushLog(log);
        }
    }
}
