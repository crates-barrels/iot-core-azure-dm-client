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
using Microsoft.Devices.Management;
using System;
using System.Threading.Tasks;

namespace Microsoft.Devices.Management
{
    public class TpmDevice
    {
        private struct ServiceUrlParts
        {
            public string HostName;
            public string DeviceId;
        }

        public TpmDevice()
        {
            this._systemConfiguratorProxy = new SystemConfiguratorProxy();
        }

        private async Task<ServiceUrlParts> GetServiceUrlParts(int slot = -1)
        {
            var result = await this._systemConfiguratorProxy.SendCommandAsync(new Message.TpmGetServiceUrlRequest(slot));
            var serviceUrl = (result as Message.StringResponse).Response;
            var parts = serviceUrl.Split('/');

            if (parts.Length != 2)
            {
                throw new Exception("Unable to parse service Url in TPM");
            }

            ServiceUrlParts serviceUrlParts = new ServiceUrlParts();
            serviceUrlParts.HostName = parts[0];
            serviceUrlParts.DeviceId = parts[1];
            return serviceUrlParts;
        }

        public async Task<string> GetSASTokenAsync(int slot = -1, uint validity = 3600)
        {
            var result = await this._systemConfiguratorProxy.SendCommandAsync(new Message.TpmGetSASTokenRequest(slot, validity));
            return (result as Message.StringResponse).Response;
        }

        // ADDED: geertp 20/03/2018 ->
        public async Task StoreServiceUrl(int slot = -1, string url = "")
        {
            var result = await this._systemConfiguratorProxy.SendCommandAsync(new Message.TpmStoreServiceUrlRequest(slot, url));
        }

        public async Task CreatePersistedHmacKey(int slot = -1, string hmacKey = "")
        {
            var result = await this._systemConfiguratorProxy.SendCommandAsync(new Message.TpmCreatePersistedHmacKeyRequest(slot, hmacKey));
        }

        public async Task DestroyServiceUrl(int slot = -1)
        {
            var result = await this._systemConfiguratorProxy.SendCommandAsync(new Message.TpmDestroyServiceUrlRequest(slot));
        }

        public async Task EvictHmacKey(int slot = -1)
        {
            var result = await this._systemConfiguratorProxy.SendCommandAsync(new Message.TpmEvictHmacKeyRequest(slot));
        }

        public async Task<(string, string)> GetConnectionStringAsync(int slot = -1, uint validity = 3600)
        {
            ServiceUrlParts serviceUrlParts = await GetServiceUrlParts(slot);
            string sasToken = await GetSASTokenAsync(slot, validity);

            string connectionString = "";
            string deviceId = null;
            if ((serviceUrlParts.HostName.Length > 0) && (serviceUrlParts.DeviceId.Length > 0) && (sasToken.Length > 0))
            {
                deviceId = serviceUrlParts.DeviceId;
                connectionString = "HostName=" + serviceUrlParts.HostName + ";DeviceId=" + serviceUrlParts.DeviceId + ";SharedAccessSignature=" + sasToken;
            }
            return (connectionString, deviceId);
        }
        // ADDED: geertp 20/03/2018 <-

        // COMMENTED: geertp 20/03/2018 ->
        //public async Task<string> GetConnectionStringAsync(int slot = -1, uint validity = 3600)
        //{
        //    ServiceUrlParts serviceUrlParts = await GetServiceUrlParts(slot);
        //    string sasToken = await GetSASTokenAsync(slot, validity);

        //    string connectionString = "";
        //    if ((serviceUrlParts.HostName.Length > 0) && (serviceUrlParts.DeviceId.Length > 0) && (sasToken.Length > 0))
        //    {
        //        connectionString = "HostName=" + serviceUrlParts.HostName + ";DeviceId=" + serviceUrlParts.DeviceId + ";SharedAccessSignature=" + sasToken;
        //    }
        //    return connectionString;
        //}
        // COMMENTED: geertp 20/03/2018 <-

        SystemConfiguratorProxy _systemConfiguratorProxy;
    }
}
