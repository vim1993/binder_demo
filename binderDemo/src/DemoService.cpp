#include <stdio.h>
#include <unistd.h>

#include <binder/IInterface.h>

#include <binder/Parcel.h>

#include <binder/IServiceManager.h>

#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

#include "IDemoDataCenter.h"
#include "IDemoInterface.h"

#define LOG_TAG "BINDERDEMO"

using namespace android;

IMPLEMENT_META_INTERFACE(DemoService, "com.orange.BinderDemoService");

void BnDemoService::sendEvent(unsigned int msgid, int extcode) {
    if(m_notify.get() == 0) {
        ALOGE("sendEvent failed, notify not init");
        return;
    }

    Parcel data;
    data.writeInt32(msgid);
    data.writeInt32(extcode);
    m_notify->transact(NOTIFY_TRANSATION, data, NULL);
    ALOGE("send Event:%d,%d", msgid, extcode);

    return;
}

void BnDemoService::setBinderNotify(sp < IBinder > & obj) {
    m_notify = obj;
    ALOGE("SET_NOTIFY_TRANSACTION %p", m_notify.get());

    return;
}

void BnDemoService::setData(unsigned int data) {
    m_data = data;
    ALOGE("m_data:%d", m_data);

    return;
}

status_t BnDemoService::onTransact(uint32_t code, const Parcel & data, Parcel * reply, uint32_t flags) {
    switch(code) {
        case SET_DATA_TRANSACTION:
            setData(data.readInt32());
            sendEvent(1, 0);
            break;

        case GET_DATA_TRANSACTION:
            reply->writeInt32(getData());
            sendEvent(2, 0);
            break;

        case SET_NOTIFY_TRANSACTION:
            sp < IBinder > binder = data.readStrongBinder();
            setBinderNotify(binder);
            sendEvent(3, 0);
            break;
    }

    return 0;
}

int main(int argc, char * argv[]) {

    sp<IServiceManager> sm = defaultServiceManager();
    sm->addService(String16("BinderDemoService"), new BnDemoService());
    ALOGE("start startThreadPool");
    ProcessState::self()->startThreadPool();
    ALOGE("start joinThreadPool");//startThreadPool开启线程用于接收数据并且加入线程池。

    //阻塞当前线程,防止退出当前进程。
    #if 0
    IPCThreadState::self()->joinThreadPool();
    #else
    while(1) {
            usleep(2000*1000);
    }
    #endif

    return 0;
}
