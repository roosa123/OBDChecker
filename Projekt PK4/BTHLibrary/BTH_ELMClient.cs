using System;
using System.Threading;
using InTheHand.Net.Bluetooth;

namespace BTHLibrary
{
    public class BTH_ELMClient : BTHClient
    {
        public bool IfConnected { get; set; }

        /// <summary>
        /// Constructor; calls base class constructor
        /// </summary>

        public BTH_ELMClient() : base() {
            IfConnected = false;
        }

        /// <summary>
        /// Asynchronously connects with selected device
        /// </summary>

        public void ConnectWithELM()
        {
            LocalClient.BeginConnect(Server.DeviceAddress, BluetoothService.SerialPort, new AsyncCallback(ConnectCallback), Server);
        }

        /// <summary>
        /// Callback function; here is executed all process of communication with the server device
        /// </summary>
        /// <param name="Result"></param>

        public void ConnectCallback(IAsyncResult Result)
        {
            if (Result.IsCompleted)
            {
                bool Terminate = false;
                IfConnected = true;

                while (!Terminate)
                {
                    Thread.BeginCriticalRegion();
                    BTH_Semaphores.CommandReady.WaitOne();
                    BTH_Semaphores.MemoryLock.WaitOne();

                    SendData(BTH_ELMCommandBuffer.Command);

                    Thread.Sleep(200);
                    
                    BTH_ELMCommandBuffer.Response = ReceiveData();

                    if (BTH_ELMCommandBuffer.LastCommand)
                        Terminate = true;

                    BTH_Semaphores.MemoryLock.ReleaseMutex();
                    BTH_Semaphores.ResponseReady.Release();
                    Thread.EndCriticalRegion();
                }
            }

            BTH_Semaphores.TerminateConnection.WaitOne();

            LocalClient.EndConnect(Result);
            LocalClient.Close();
            BTStream.Close();

            BTH_Semaphores.ConnectionTerminated.Release();
        }
    }
}
