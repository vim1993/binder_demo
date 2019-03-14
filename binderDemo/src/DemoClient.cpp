#include <stdio.h>

#include <binder/IInterface.h>

#include <binder/Parcel.h>

#include <binder/IServiceManager.h>

#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

#include <unistd.h>

#include "IDemoDataCenter.h"
#include "IDemoInterface.h"

#define LOG_TAG "BINDERDEMO"

using namespace android;

void BpDemoClient::setData(unsigned int dataValue) {
    Parcel data, reply;

    data.writeInt32(dataValue);

    m_binder->transact(SET_DATA_TRANSACTION, data, &reply);

    return;
}

unsigned int BpDemoClient::getData(void) {
    Parcel data, reply;
    m_binder->transact(GET_DATA_TRANSACTION, data, &reply);

    return reply.readInt32();
}

void BpDemoClient::setBinderNotify(sp<IBinder> & obj) {
    Parcel data, reply;

    data.writeStrongBinder(obj);

    m_binder->transact(SET_NOTIFY_TRANSACTION, data, &reply);

    return;
}

int main(int argc, char * * argv) {
    sp<IBinder> binder;

    sp<IServiceManager> sm = defaultServiceManager();


    do {
        binder = sm->getService(String16("BinderDemoService"));
        if(binder.get() != 0) {
            ALOGE("hava get binder service");
            break;
        }

        usleep(200*1000);

    }while(1);

    BpDemoClient bpDemoC(binder);
    BnDataCenterService * notify = new BnDataCenterService();
    sp<IBinder> notifyBinder = notify->asBinder();

    bpDemoC.setBinderNotify(notifyBinder);

    bpDemoC.setData(10);

    ALOGE("getdata:%d", bpDemoC.getData());

    while(1) {
        usleep(2000*1000);
    }
}