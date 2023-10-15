#include "sendimg.h"


extern QUEUE_DATA<MESG> queue_send;

SendImg::SendImg(QObject *par):QThread(par)
{

}

//消费线程 , 取出任务
void SendImg::run()
{
    WRITE_LOG("start sending picture thread: 0x%p", QThread::currentThreadId());
    m_isCanRun = true;
    for(;;)
    {
        queue_lock.lock(); //加锁

        while(imgqueue.size() == 0)
        {
            //队列为空 , 就阻塞在这里 , 直到生产者线程生产任务再被唤醒 ; 或者等待 WAITSECONDS 秒后直接返回
            bool f = queue_waitCond.wait(&queue_lock, WAITSECONDS * 1000);
			if (f == false) //timeout
			{
				QMutexLocker locker(&m_lock);
				if (m_isCanRun == false)
				{
                    queue_lock.unlock();
					WRITE_LOG("stop sending picture thread: 0x%p", QThread::currentThreadId());
					return;
				}
			}
        }

        QByteArray img = imgqueue.front();
        imgqueue.pop_front();

        queue_lock.unlock();//解锁
        queue_waitCond.wakeOne(); //唤醒生产者线程


        //构造消息体
        MESG* imgsend = (MESG*)malloc(sizeof(MESG));

        if (imgsend == NULL)
        {
            WRITE_LOG("imgsend malloc error");
            qDebug() << "malloc imgsend fail";
        }
        else
        {
            memset(imgsend, 0, sizeof(MESG));
			imgsend->msg_type = IMG_SEND;
			imgsend->len = img.size();

            qDebug() << "img size :" << img.size();
            imgsend->data = (uchar*)malloc(imgsend->len);

            if (imgsend->data == nullptr)
            {
                free(imgsend);
                WRITE_LOG("imgsend->data malloc error");
                //qDebug() << "send img error";
                continue;
            }
            else
            {
                memset(imgsend->data, 0, imgsend->len);
				memcpy_s(imgsend->data, imgsend->len, img.data(), img.size());
				//加入发送队列
				queue_send.push_msg(imgsend);
            }
        }
    }
}

//添加线程
void SendImg::pushToQueue(QImage img)
{
    //压缩
    QByteArray byte;
    QBuffer buf(&byte);
    buf.open(QIODevice::WriteOnly);
    img.save(&buf, "JPEG");

    //压缩转码
    QByteArray ss = qCompress(byte);
    QByteArray vv = ss.toBase64();

    queue_lock.lock();
    while(imgqueue.size() > QUEUE_MAXSIZE)
    {
        queue_waitCond.wait(&queue_lock);
    }
    imgqueue.push_back(vv);

    queue_lock.unlock();
    queue_waitCond.wakeOne();
}

void SendImg::ImageCapture(QImage img)
{
    pushToQueue(img);
}

void SendImg::clearImgQueue()
{
    qDebug() << "清空视频队列";
    QMutexLocker locker(&queue_lock);
    imgqueue.clear();
}


void SendImg::stopImmediately()
{
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
}
