using System.Collections.Generic;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

namespace BTHLibrary
{
    public class BTHClient : BTHSocket
    {
        #region Private fields
        private BluetoothDeviceInfo[] DevicesAvailable;
        private BluetoothDeviceInfo[] DevicesPaired;
        private List<string> DeviceList;
        #endregion

        #region Protected fields
        protected BluetoothDeviceInfo Server;
        #endregion

        #region Properties
        public List<string> DeviceNameList
        {
            get
            {
                return DeviceList;
            }
        }
        #endregion

        /// <summary>
        /// Constructor; calls a constructor of base class
        /// </summary>

        public BTHClient() : base() { }

        /// <summary>
        /// Discovers all Bluetooth devices in range
        /// </summary>

        public void DiscoverBTHDevices()
        {
            DevicesAvailable = LocalClient.DiscoverDevicesInRange();
            DeviceList = new List<string>();

            foreach (BluetoothDeviceInfo Device in DevicesAvailable)
                DeviceList.Add(Device.DeviceName);
        }

        /// <summary>
        /// Attempts to pair selected device; if succeed sets the device as a server
        /// </summary>
        /// <param name="DeviceName"></param>
        /// <param name="DevicePin"></param>

        public void DevicePairing(string DeviceName, string DevicePin)
        {
            DevicesPaired = LocalClient.DiscoverDevices(200, false, true, false, false);
            bool IsPaired = false;

            foreach(BluetoothDeviceInfo Device in DevicesAvailable)
                if (Device.DeviceName.Equals(DeviceName))
                {
                    if (!Device.Authenticated)
                    {
                        IsPaired = BluetoothSecurity.PairRequest(Device.DeviceAddress, DevicePin);
                        if (!IsPaired)
                            throw new BTHException("Nie mozna sparowac wybranego urzadzenia");
                    }

                    Server = Device;
                }
        }

        public bool CheckIfAuthenticated(string DeviceNameToCheck)
        {
            foreach (BluetoothDeviceInfo NextDevice in DevicesAvailable)
                if (NextDevice.DeviceName.Equals(DeviceNameToCheck))
                    return NextDevice.Authenticated;

            return false;
        }
    }
}
