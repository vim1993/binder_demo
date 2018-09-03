#include <stdio.h>
#include <unistd.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include  <utils/threads.h>

#include "../../inc/itest.h"

using namespace android;

IMPLEMENT_META_INTERFACE(NativeTestServer, "NativeBinderService");

unsigned int mdata = 0;

unsigned int BnNativeTestServer::getData(void) {
      printf("[%s][%d]! data:%d\n", __func__, __LINE__, mdata);
      return mdata;
}

void BnNativeTestServer::setData(unsigned int data) {
      mdata = data;
      printf("[%s][%d]! data:%d\n", __func__, __LINE__, mdata);
}

status_t BnNativeTestServer::onTransact(uint code, const Parcel &data, Parcel *reply, uint flags) {
      switch(code) {
            case SET_DATA:
                  setData(data.readInt32());
                  break;

            case GET_DATA:
                  reply->writeInt32(getData());
                  break;

            case SET_EVENT:
                  Parcel data_event, reply_event;

                  mEventBinder = data.readStrongBinder();
                  data_event.writeInt32(1);
                  mEventBinder->transact(CALLBACK_EVENT, data_event, &reply_event);
                  break;
      }

      return 0;
}

int main(int argc, char const *argv[])
{
      sp<ProcessState> proc(ProcessState::self());
	//获取ServiceManager
	sp<IServiceManager> sm = defaultServiceManager();
	//注册service
      printf("start add NativeBinderService...\n");
	sm->addService(String16("NativeBinderService"), new BnNativeTestServer());
      printf("complete add NativeBinderService...\n");
	//启动线程池，
	ProcessState::self()->startThreadPool();
	//把服务添加到Binder闭合循环进程
	IPCThreadState::self()->joinThreadPool();

      return 0;
}

