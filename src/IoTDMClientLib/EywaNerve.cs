// ADDED: geertp 23/03/2018 ->
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Devices.Management;

namespace Microsoft.Devices.Management
{
    public class EywaNerve
    {
        public EywaNerve()
        {
            this._systemConfiguratorProxy = new SystemConfiguratorProxy();
        }

        public async Task<string> LaunchProcess(string command)
        {
            var result = await this._systemConfiguratorProxy.SendCommandAsync(new Message.LaunchProcessRequest(command));
            return (result as Message.StringResponse).Response;
        }

        SystemConfiguratorProxy _systemConfiguratorProxy;
    }
}
// ADDED: geertp 23/03/2018 <-
