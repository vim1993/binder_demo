#include <stdio.h>
#include <unistd.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "../../inc/itest.h"

using namespace android;

BpNativeTestClient::BpNativeTestClient(const sp<IBinder> & impl, const sp<BnCallBackEventServer> & bevent):BpInterface<INativeTestClient>(impl) {
      mEventBinder = bevent->asBinder();
      this->setEventBinder(mEventBinder);
}

unsigned int BpNativeTestClient::getData(void) {
      Parcel data, reply;

      remote()->transact(GET_DATA, data, &reply);

      return reply.readInt32();
}

void BpNativeTestClient::setData(unsigned int _data) {
      Parcel data, reply;

      data.writeInt32(_data);
      remote()->transact(SET_DATA, data, &reply);
      printf("[%s][%d]! data:%d\n", __func__, __LINE__, _data);
      return;
}

void BpNativeTestClient::setEventBinder(const sp<IBinder> & eventBinder) {
      Parcel data, reply;

      data.writeStrongBinder(eventBinder);

      remote()->transact(SET_EVENT, data, &reply);
}

//for event call back
IMPLEMENT_META_INTERFACE(CallBackEventServer, "NativeBinderEventService");
status_t BnCallBackEventServer::onTransact(uint code, const Parcel &data, Parcel *reply, uint flags) {

      switch (code)
      {
            case CALLBACK_EVENT:
                  sendEvent(data.readInt32());
                  break;
      }


      return 0;
}

void BnCallBackEventServer::sendEvent(unsigned int _event) {
      printf("[%s][%d]! event:%d\n", __func__, __LINE__, _event);
      return;
}

int main(int argc, char const *argv[])
{
      sp<ProcessState> proc(ProcessState::self());
      ProcessState::self()->startThreadPool();

      sp <IServiceManager> sm = defaultServiceManager();
      sp<IBinder> binder;
      while(1)
      {
            binder = sm->getService(String16("NativeBinderService"));
            if(binder != NULL) {
                  printf("wait NativeBinderService...\n");
                  break;
            }

            usleep(200*1000);
      }

      sp<BnCallBackEventServer> bevent = new BnCallBackEventServer();

      BpNativeTestClient * bpclient = new BpNativeTestClient(binder, bevent);

      bpclient->setData(921);

      printf("getData:%d\n", bpclient->getData());

      while(1) {
            usleep(500*1000);
      }

      return 0;
}
