/*
Copyright 2017 Microsoft
Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "AppInstall.h"
#include "AppLifecycle.h"
#include "AppUninstall.h"
#include "CheckForUpdates.h"
#include "CertificateConfiguration.h"
#include "CertificateDetails.h"
#include "DeviceDMStorage.h"
#include "DeviceHealthAttestation.h"
#include "DeviceInfo.h"
#include "ErrorResponse.h"
#include "EventTracingConfiguration.h"
#include "ExitDM.h"
#include "FactoryReset.h"
#include "FileTransfer.h"
// ADDED: geertp 23/03/2018 ->
#include "LaunchProcess.h"
// ADDED: geertp 23/03/2018 <-
#include "ListApps.h"
#include "Reboot.h"
#include "RemoteWipe.h"
#include "StartupApp.h"
#include "StatusCodeResponse.h"
#include "StringResponse.h"
#include "StringListResponse.h"
#include "TimeInfo.h"
#include "TimeService.h"
#include "TpmRequests.h"
#include "UsoClientCmd.h"
#include "WifiConfiguration.h"
#include "WifiDetails.h"
#include "WindowsTelemetry.h"
#include "WindowsUpdatePolicy.h"
#include "WindowsUpdateRebootPolicy.h"
#include "WindowsUpdates.h"

#define EMPTY_REQUEST(A) \
public ref class A##Request sealed : public IRequest \
{ \
public: \
    virtual Blob^ Serialize() { \
        return SerializationHelper::CreateEmptyBlob((uint32_t)Tag); \
    } \
 \
    static IDataPayload^ Deserialize(Blob^ bytes) { \
        return ref new A##Request(); \
    } \
 \
    virtual property DMMessageKind Tag { \
        DMMessageKind get(); \
    } \
} \


namespace Microsoft { namespace Devices { namespace Management { namespace Message
{
    EMPTY_REQUEST(ListApps);
    EMPTY_REQUEST(GetStartupForegroundApp);
    EMPTY_REQUEST(ListStartupBackgroundApps);
}}}};
