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
#include "IRequestIResponse.h"
#include "SerializationHelper.h"
#include "DMMessageKind.h"
#include "StatusCodeResponse.h"
#include "Blob.h"

#include <collection.h>

using namespace Platform;
using namespace Platform::Metadata;
using namespace Platform::Collections;
using namespace Windows::Data::Json;
using namespace Windows::Foundation::Collections;

namespace Microsoft { namespace Devices { namespace Management { namespace Message
{
    public ref class TpmGetServiceUrlRequest sealed : public IRequest
    {
        int32_t slot;

    public:
        TpmGetServiceUrlRequest(int32_t slot) : slot(slot) {}

        virtual Blob^ Serialize() {
            JsonObject^ jsonObject = ref new JsonObject();
            jsonObject->Insert("Slot", JsonValue::CreateNumberValue(slot));
            return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
        }

        static IDataPayload^ Deserialize(Blob^ blob) {
            assert(blob->Tag == DMMessageKind::TpmGetServiceUrl);
            String^ str = SerializationHelper::GetStringFromBlob(blob);
            JsonObject^ jsonObject = JsonObject::Parse(str);
            int32_t slot = (int32_t)jsonObject->Lookup("Slot")->GetNumber();
            return ref new TpmGetServiceUrlRequest(slot);
        }

        virtual property DMMessageKind Tag {
            DMMessageKind get();
        }

        property int Slot {
            int get() { return slot; }
        }

    };

    public ref class TpmGetSASTokenRequest sealed : public IRequest
    {
        int32_t slot;
        uint32_t expiration;
    public:
        TpmGetSASTokenRequest(int32_t slot, uint32_t expiration) : slot(slot), expiration(expiration) {}

        virtual Blob^ Serialize() {
            JsonObject^ jsonObject = ref new JsonObject();
            jsonObject->Insert("Slot", JsonValue::CreateNumberValue(slot));
            jsonObject->Insert("Expiration", JsonValue::CreateNumberValue(expiration));
            return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
        }

        static IDataPayload^ Deserialize(Blob^ blob) {
            assert(blob->Tag == DMMessageKind::TpmGetSASToken);
            String^ str = SerializationHelper::GetStringFromBlob(blob);
            JsonObject^ jsonObject = JsonObject::Parse(str);
            int32_t slot = (int32_t)jsonObject->Lookup("Slot")->GetNumber();
            uint32_t expiration = (uint32_t)jsonObject->Lookup("Expiration")->GetNumber();
            return ref new TpmGetSASTokenRequest(slot, expiration);
        }

        virtual property DMMessageKind Tag {
            DMMessageKind get();
        }

        property int Slot {
            int get() { return slot; }
        }

        property int Expiration {
            int get() { return expiration; }
        }

    };

	// ADDED: geertp 20/03/2018 ->
	public ref class TpmStoreServiceUrlRequest sealed : public IRequest
	{
		int32_t slot;
		String^ url;

	public:
		TpmStoreServiceUrlRequest(int32_t slot, String^ url) : slot(slot), url(url) {}

		virtual Blob^ Serialize() {
			JsonObject^ jsonObject = ref new JsonObject();
			jsonObject->Insert("Slot", JsonValue::CreateNumberValue(slot));
			jsonObject->Insert("Url", JsonValue::CreateStringValue(url));
			return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
		}

		static IDataPayload^ Deserialize(Blob^ blob) {
			assert(blob->Tag == DMMessageKind::TpmStoreServiceUrl);
			String^ str = SerializationHelper::GetStringFromBlob(blob);
			JsonObject^ jsonObject = JsonObject::Parse(str);
			int32_t slot = (int32_t)jsonObject->Lookup("Slot")->GetNumber();
			String^ url = jsonObject->Lookup("Url")->GetString();
			return ref new TpmStoreServiceUrlRequest(slot, url);
		}

		virtual property DMMessageKind Tag {
			DMMessageKind get();
		}

		property int Slot {
			int get() { return slot; }
		}

		property String^ Url {
			String^ get() { return url; }
		}

	};

	public ref class TpmCreatePersistedHmacKeyRequest sealed : public IRequest
	{
		int32_t slot;
		String^ hmacKey;

	public:
		TpmCreatePersistedHmacKeyRequest(int32_t slot, String^ hmacKey) : slot(slot), hmacKey(hmacKey) {}

		virtual Blob^ Serialize() {
			JsonObject^ jsonObject = ref new JsonObject();
			jsonObject->Insert("Slot", JsonValue::CreateNumberValue(slot));
			jsonObject->Insert("HmacKey", JsonValue::CreateStringValue(hmacKey));
			return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
		}

		static IDataPayload^ Deserialize(Blob^ blob) {
			assert(blob->Tag == DMMessageKind::TpmCreatePersistedHmacKey);
			String^ str = SerializationHelper::GetStringFromBlob(blob);
			JsonObject^ jsonObject = JsonObject::Parse(str);
			int32_t slot = (int32_t)jsonObject->Lookup("Slot")->GetNumber();
			String^ hmacKey = jsonObject->Lookup("HmacKey")->GetString();
			return ref new TpmCreatePersistedHmacKeyRequest(slot, hmacKey);
		}

		virtual property DMMessageKind Tag {
			DMMessageKind get();
		}

		property int Slot {
			int get() { return slot; }
		}

		property String^ HmacKey {
			String^ get() { return hmacKey; }
		}

	};

	public ref class TpmDestroyServiceUrlRequest sealed : public IRequest
	{
		int32_t slot;

	public:
		TpmDestroyServiceUrlRequest(int32_t slot) : slot(slot) {}

		virtual Blob^ Serialize() {
			JsonObject^ jsonObject = ref new JsonObject();
			jsonObject->Insert("Slot", JsonValue::CreateNumberValue(slot));
			return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
		}

		static IDataPayload^ Deserialize(Blob^ blob) {
			assert(blob->Tag == DMMessageKind::TpmDestroyServiceUrl);
			String^ str = SerializationHelper::GetStringFromBlob(blob);
			JsonObject^ jsonObject = JsonObject::Parse(str);
			int32_t slot = (int32_t)jsonObject->Lookup("Slot")->GetNumber();
			return ref new TpmDestroyServiceUrlRequest(slot);
		}

		virtual property DMMessageKind Tag {
			DMMessageKind get();
		}

		property int Slot {
			int get() { return slot; }
		}

	};

	public ref class TpmEvictHmacKeyRequest sealed : public IRequest
	{
		int32_t slot;

	public:
		TpmEvictHmacKeyRequest(int32_t slot) : slot(slot) {}

		virtual Blob^ Serialize() {
			JsonObject^ jsonObject = ref new JsonObject();
			jsonObject->Insert("Slot", JsonValue::CreateNumberValue(slot));
			return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
		}

		static IDataPayload^ Deserialize(Blob^ blob) {
			assert(blob->Tag == DMMessageKind::TpmEvictHmacKey);
			String^ str = SerializationHelper::GetStringFromBlob(blob);
			JsonObject^ jsonObject = JsonObject::Parse(str);
			int32_t slot = (int32_t)jsonObject->Lookup("Slot")->GetNumber();
			return ref new TpmEvictHmacKeyRequest(slot);
		}

		virtual property DMMessageKind Tag {
			DMMessageKind get();
		}

		property int Slot {
			int get() { return slot; }
		}

	};
	// ADDED: geertp 20/03/2018 <-

}}}}
