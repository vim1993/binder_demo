#ifndef __ITEST_H__
#define __ITEST_H__

#include <stdio.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

using namespace android;
///////////////////////////////////////////////////////////////////////////////////////////
/*
 * ICallBackInterface class 数据回调定义接口，由server->client端
 */
class ICallBackEventServer:public IInterface {
      public:
            DECLARE_META_INTERFACE(CallBackEventServer);
            virtual void sendEvent(unsigned int _event) = 0;
};

class BnCallBackEventServer:public BnInterface<ICallBackEventServer> {
      public:
            status_t onTransact(uint code, const Parcel &data, Parcel *reply, uint flags = 0);

            void sendEvent(unsigned int _event);
};

class BpCallBackEventServer:public BpInterface<ICallBackEventServer> {
      public:
            BpCallBackEventServer(const sp<IBinder>& obj):BpInterface<ICallBackEventServer>(obj) {

            };
            void sendEvent(unsigned int _event) {
                  return;
            };
};

class ICallBackEventClient:public IInterface {
      public:
            virtual void sendEvent(unsigned int _event) = 0;
};

class BpCallBackEventClient:public BpInterface<ICallBackEventClient> {
      public:
            void sendEvent(unsigned int _event);
};

enum {
      CALLBACK_EVENT = IBinder::FIRST_CALL_TRANSACTION + 1
};
////////////////////////////////////////////////////////

/*
 * ITestInterface class：
 *    client-server 数据交互接口
 *
 * ITestClient class:
 *    Bp接口
 * BpTestClient class:
 *    Bp接口实现
 *
 * ITestServer class:
 *    Bn接口
 * BnTestServer class:
 *    Bn接口实现
 *
 */
class INativeTestClient:public IInterface {
      protected:
            sp<IBinder> mEventBinder;

      public:
            virtual void setData(unsigned int data) = 0;
            virtual unsigned int getData(void) = 0;
};

class BpNativeTestClient:public BpInterface<INativeTestClient> {
      private:
            void setEventBinder(const sp<IBinder> & eventBinder);

      public:
            BpNativeTestClient(const sp<IBinder> & impl, const sp<BnCallBackEventServer> & bevent);

            void setData(unsigned int data);
            unsigned int getData(void);

};

class INativeTestServer:public IInterface {
      protected:
            sp<IBinder> mEventBinder;

      public:
            DECLARE_META_INTERFACE(NativeTestServer);
            virtual void setData(unsigned int data) = 0;
            virtual unsigned int getData(void) = 0;
};

class BnNativeTestServer:public BnInterface<INativeTestServer> {
      public:
            status_t onTransact(uint code, const Parcel &data, Parcel *reply, uint flags = 0);

            void setData(unsigned int data);
            unsigned int getData(void);
};

class BpNativeTestServer:public BpInterface<INativeTestServer> {

	public:
            BpNativeTestServer(const sp<IBinder> & obj):BpInterface<INativeTestServer>(obj) {

		};
		void setData(unsigned int data) {
			return;
		};

		unsigned int getData(void) {
			return 0;
		};
};

enum {
      SET_DATA = IBinder::FIRST_CALL_TRANSACTION + 1,
      GET_DATA = SET_DATA + 1,
      SET_EVENT = GET_DATA + 1
};
#endif
