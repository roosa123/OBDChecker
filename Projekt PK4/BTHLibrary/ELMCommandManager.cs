using System;
using System.Threading;

namespace BTHLibrary
{
    public class ELMCommandManager
    {
        #region Private fields
        private Thread ELMCommunication;
        #endregion

        #region Properties
        public BTH_ELMClient ELMClient { get; }
        #endregion

        /// <summary>
        /// Default constructor; creates a new client //and discovers available devices in range
        /// </summary>

        public ELMCommandManager()
        {
            ELMClient = new BTH_ELMClient();
        }

        /// <summary>
        /// Constructor; calls BluetoothClient's method, which carries out attempting to pair selected device. Also creates a new thread necessary for performing data exchange
        /// </summary>
        /// <param name="DeviceName"></param>
        /// <param name="DevicePin"></param>

        public ELMCommandManager(string DeviceName, string DevicePin)
        {
            ELMClient = new BTH_ELMClient();

            ELMClient.DiscoverBTHDevices();
            ELMClient.DevicePairing(DeviceName, DevicePin);

            ELMCommunication = new Thread(new ThreadStart(ELMClient.ConnectWithELM));
        }

        /// <summary>
        /// Sets the server (if the instance of the class was created with the default constructor)
        /// </summary>
        /// <param name="DeviceName"></param>
        /// <param name="DevicePin"></param>

        public void SetTheServer(string DeviceName, string DevicePin)
        {
            ELMClient.DevicePairing(DeviceName, DevicePin);
            ELMCommunication = new Thread(new ThreadStart(ELMClient.ConnectWithELM));
        }

        /// <summary>
        /// Starts a thread created in constructor
        /// </summary>

        public void StartThread()
        {
            try
            {
                ELMCommunication.Start();
            }
            catch (Exception exc)
            {
                throw;
            }
        }

        /// <summary>
        /// Performs data exchange between PC and remote Bluetooth device
        /// </summary>
        /// <param name="Command"></param>
        /// <param name="IfLast"></param>
        /// <returns></returns>

        public string ExecuteCommand(string Command, bool IfLast)
        {
            Thread.BeginCriticalRegion();

            BTH_Semaphores.CommandExecution.WaitOne();
            BTH_Semaphores.MemoryLock.WaitOne();

            BTH_ELMCommandBuffer.Command = Command;

            if (IfLast)
                BTH_ELMCommandBuffer.LastCommand = true;

            BTH_Semaphores.MemoryLock.ReleaseMutex();
            BTH_Semaphores.CommandReady.Release();

            // ====================================

            BTH_Semaphores.ResponseReady.WaitOne();
            BTH_Semaphores.MemoryLock.WaitOne();

            string ResponseFromDevice = BTH_ELMCommandBuffer.Response;

            BTH_Semaphores.MemoryLock.ReleaseMutex();
            BTH_Semaphores.CommandExecution.Release();

            Thread.EndCriticalRegion();

            return ResponseFromDevice;
        }

        /// <summary>
        /// Joins a thread created in constructor
        /// </summary>

        public void JoinThread()
        {
            BTH_Semaphores.ConnectionTerminated.WaitOne();

            ELMCommunication.Join();

            BTH_Semaphores.TerminateConnection.Release();
        }
    }
}

/*

                BTH_ELMClient ELMClient = new BTH_ELMClient();

            ELMClient.DevicePairing("V-LINK", "1234");

            Thread ELMCommunication = new Thread(new ThreadStart(ELMClient.ConnectWithELM));
            //BTH_Semaphores Sem = new BTH_Semaphores();

            ELMCommunication.Start();

            #region
            ---

            BTH_Semaphores.CommandReady.WaitOne();
            BTH_Semaphores.MemoryLock.WaitOne();

            SendData(BTH_ELMCommandBuffer.Command);

Thread.Sleep(200);

            BTH_ELMCommandBuffer.Response = ReceiveData();

            if (BTH_ELMCommandBuffer.LastCommand)
                Terminate = true;

            BTH_Semaphores.MemoryLock.ReleaseMutex();
            BTH_Semaphores.ResponseReady.Release();

            //---
            
            #endregion

            for (int i = 0; i< 3; ++i)
            {
                BTH_Semaphores.ResponseReady.WaitOne();
                BTH_Semaphores.MemoryLock.WaitOne();

                Console.WriteLine(BTH_ELMCommandBuffer.Response);
                BTH_ELMCommandBuffer.Command = "ATI\r";

                if (i == 2)
                    BTH_ELMCommandBuffer.LastCommand = true;

                BTH_Semaphores.MemoryLock.ReleaseMutex();
                BTH_Semaphores.CommandReady.Release();
            }

            ELMCommunication.Join();

            Console.ReadLine();

*/