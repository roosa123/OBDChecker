using System.Threading;

namespace BTHLibrary
{
    public class BTH_Semaphores
    {
        public static Mutex MemoryLock { get; set; }
        public static Semaphore CommandReady { get; set; }
        public static Semaphore ResponseReady { get; set; }
        public static Semaphore CommandExecution { get; set; }
        public static Semaphore TerminateConnection { get; set; }
        public static Semaphore ConnectionTerminated { get; set; }

        static BTH_Semaphores()
        {
            MemoryLock = new Mutex();
            CommandReady = new Semaphore(0, 1);
            ResponseReady = new Semaphore(0, 1);
            CommandExecution = new Semaphore(1, 1);
            TerminateConnection = new Semaphore(1, 1);
            ConnectionTerminated = new Semaphore(0, 1);
        }
    }
}
