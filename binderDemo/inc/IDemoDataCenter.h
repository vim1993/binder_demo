#ifndef __I_DATA_CENTER_H__
#define __I_DATA_CENTER_H__


#include <binder/IInterface.h>

#include <binder/Parcel.h>

#include <binder/IServiceManager.h>

#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

using namespace android;

typedef struct msg_s {
    unsigned int msgid;
    int extcode;
}msg_s;

class IDataCenterService : public IInterface {
    public:
        DECLARE_META_INTERFACE(DataCenterService);
        virtual void notify(unsigned int msgid, int extcode) = 0;
};

class BnDataCenterService : public BnInterface<IDataCenterService> {
    public:
        BnDataCenterService();
        void notify(unsigned int msgid, int extcode);
        status_t onTransact(uint32_t code, const Parcel & data, Parcel * reply, uint32_t flags);
};

class BpDataCenterService : public BpInterface < IDataCenterService > {
    public:
        BpDataCenterService(const sp<IBinder> & obj)
            : BpInterface < IDataCenterService >(obj) {

        };

        void notify(unsigned int msgid, int extcode) {

        };
};

class IDataCenterClient : public IInterface {
    public:
        virtual void notify(msg_s * msg) = 0;
};

class BpDataCenterClient : public BpInterface < IDataCenterClient > {
    public:
        BpDataCenterClient();
        BpDataCenterClient(sp<IBinder> & obj);
        void notify(msg_s * msg);
};

enum {
    FIRST_TRANSATION = IBinder::FIRST_CALL_TRANSACTION,
    NOTIFY_TRANSATION = FIRST_TRANSATION + 1,
};

#endif