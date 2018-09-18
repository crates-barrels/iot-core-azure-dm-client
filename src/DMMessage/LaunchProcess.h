
// ADDED: geertp 23/03/2018 ->
#pragma once
#include "IRequestIResponse.h"
#include "SerializationHelper.h"
#include "DMMessageKind.h"
#include "StatusCodeResponse.h"
#include "Blob.h"

using namespace Platform;
using namespace Platform::Metadata;
using namespace Windows::Data::Json;

namespace Microsoft {
	namespace Devices {
		namespace Management {
			namespace Message
			{
				public ref class LaunchProcessRequest sealed : public IRequest
				{
					String^ command;

				public:
					LaunchProcessRequest(String^ command) : command(command) {}

					virtual Blob^ Serialize() {
						JsonObject^ jsonObject = ref new JsonObject();
						jsonObject->Insert("command", JsonValue::CreateStringValue(command));
						return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
					}

					static IDataPayload^ Deserialize(Blob^ blob) {
						assert(blob->Tag == DMMessageKind::LaunchProcess);
						String^ str = SerializationHelper::GetStringFromBlob(blob);
						JsonObject^ jsonObject = JsonObject::Parse(str);
						Platform::String^ command = jsonObject->Lookup("command")->GetString();
						return ref new LaunchProcessRequest(command);
					}

					virtual property DMMessageKind Tag {
						DMMessageKind get();
					}

					property String^ Command {
						String^ get() { return command; }
					}

				};


			}
		}
	}
}
// ADDED: geertp 23/03/2018 <-
