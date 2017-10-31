using System;
using System.Threading;
using System.Net.Sockets;
using InTheHand.Net;
using InTheHand.Net.Sockets;
using InTheHand.Net.Bluetooth;

namespace BTHLibrary
{
    public class BTHSocket
    {
        #region Private Fields
        private BluetoothAddress LocalMACAddress;
        private BluetoothEndPoint LocalEndPoint;
        #endregion

        #region Protected Fields
        protected BluetoothClient LocalClient;
        protected NetworkStream BTStream;
        #endregion

        /// <summary>
        /// Construcor; finds MaC address of local adapter, creates a new end point and client
        /// </summary>

        public BTHSocket() {
            try
            {
                FindLocalMACBTAddress();
            }
            catch (BTHException Exc)
            {
                throw;
            }

            LocalEndPoint = new BluetoothEndPoint(LocalMACAddress, BluetoothService.BluetoothBase);
            LocalClient = new BluetoothClient(LocalEndPoint);
        }

        /// <summary>
        /// Finds MAC adress of the local Bluetooth adapter. It's necessary to turn the adapter on manually before finding the address
        /// </summary>
        
        private void FindLocalMACBTAddress() // no trudno, jednak trzeba tego drania wlaczyc recznie... Ale dziala! :)
        {
            BluetoothRadio LocalRadio = BluetoothRadio.PrimaryRadio;
            if (LocalRadio == null)
                throw new BTHException("Nie znaleziono adresu MAC adaptera Bluetooth");

            // Warning: LocalAddress is null if the radio is powered-off.
            LocalMACAddress = LocalRadio.LocalAddress;
        }

        /// <summary>
        /// Sends a message using local client's stream
        /// </summary>
        /// <param name="Message"></param>

        public void SendData(string Message)
        {
            try
            {
                if(BTStream == null)
                    BTStream = LocalClient.GetStream();

                byte[] buffer = System.Text.Encoding.ASCII.GetBytes(Message);

                BTStream.Write(buffer, 0, buffer.Length);
                BTStream.Flush();
            }catch(Exception exc)
            {
                throw;
            }
        }

        /// <summary>
        /// Receives a device's response using local client's stream and returns as a string
        /// </summary>
        /// <returns></returns>
        
        public string ReceiveData()
        {
            if (!BTStream.CanRead)
                throw new BTHException("Unable to read response");

            byte[] ReadBuffer = new byte[1024];
            string CompleteMessage = string.Empty;
            
            int BytesRead = 0;

            while (BTStream.DataAvailable || !CompleteMessage.Contains("\r\n>"))
            {
                BytesRead = BTStream.Read(ReadBuffer, 0, ReadBuffer.Length);
                CompleteMessage += System.Text.Encoding.Default.GetString(ReadBuffer, 0, BytesRead);

                Thread.Sleep(200);
            }

            return CompleteMessage.ToString();
        }
    }
}
