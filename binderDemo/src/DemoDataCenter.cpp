#include <stdio.h>

#include <binder/IInterface.h>

#include <binder/Parcel.h>

#include <binder/IServiceManager.h>

#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

#include "IDemoDataCenter.h"
#include "IDemoInterface.h"

#define LOG_TAG "BINDERDEMO"

using namespace android;

IMPLEMENT_META_INTERFACE(DataCenterService, "com.orange.datacenter")

BnDataCenterService::BnDataCenterService() {
    ALOGE("BnDataCenterService construct");
}

void BnDataCenterService::notify(unsigned int msgid, int extcode) {
    ALOGE("recv msgid:%d, extcode:%d", msgid, extcode);

    return;
}

status_t BnDataCenterService::onTransact(uint32_t code, const Parcel & data, Parcel * reply, uint32_t flags) {
    switch(code) {
        case NOTIFY_TRANSATION:
            notify(data.readInt32(), data.readInt32());
            break;
    }

    return 0;
}
