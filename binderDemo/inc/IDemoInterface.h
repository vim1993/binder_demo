#ifndef __IDEMO_INTERFACE_H__
#define __IDEMO_INTERFACE_H__

#include <binder/IInterface.h>

#include <binder/Parcel.h>

#include <binder/IServiceManager.h>

#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>

using namespace android;

class IDemoService : public IInterface {
    public:
        DECLARE_META_INTERFACE(DemoService);

        virtual void setBinderNotify(sp<IBinder> & obj) = 0;
        virtual void setData(unsigned int data) = 0;
        virtual unsigned int getData(void) const = 0;
};

class BnDemoService:public BnInterface<IDemoService> {
    unsigned int m_data;
    sp<IBinder> m_notify;

    void sendEvent(unsigned int msgid, int extcode);

    public:
        BnDemoService()
            : m_data(0) {

        };

        void setBinderNotify(sp<IBinder> & obj);

        void setData(unsigned int data);

        unsigned int getData(void) const {
            return m_data;
        };

        status_t onTransact(uint32_t code, const Parcel & data, Parcel * reply, uint32_t flags);
};

class BpDemoService:public BpInterface <IDemoService> {
    public:
        BpDemoService(const sp<IBinder>& obj)
            : BpInterface<IDemoService>(obj){

        };

        void setData(unsigned int data) {
            return;
        };

        unsigned int getData(void) const    {
            return 0;
        };

        void setBinderNotify(sp<IBinder> & obj) {

        };
};

class IDemoClient : public IInterface {
    public:
        virtual void setData(unsigned int data) = 0;
        virtual unsigned int getData(void) = 0;
        virtual void setBinderNotify(sp<IBinder> & obj) = 0;
};

class BpDemoClient : public BpInterface < IDemoClient > {
    IBinder * m_binder;

    public:
        BpDemoClient(const sp<IBinder> & obj)
            : BpInterface< IDemoClient >(obj)
            , m_binder(obj.get()) {

        };

        void setData(unsigned int data);
        unsigned int getData(void);
        void setBinderNotify(sp<IBinder> & obj);
};

enum {
    FISRT_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
    SET_DATA_TRANSACTION = FISRT_TRANSACTION+1,
    GET_DATA_TRANSACTION = SET_DATA_TRANSACTION + 1,
    SET_NOTIFY_TRANSACTION = GET_DATA_TRANSACTION + 1
};

#endif