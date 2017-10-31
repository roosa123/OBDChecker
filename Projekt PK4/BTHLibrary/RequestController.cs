using System.Collections.Generic;
using System.IO;
using ParserBridge;

namespace BTHLibrary
{
    public enum CommandGroup
    {
        Initialization,
        CheckingPids,
        RetrievingRealtimeData,
        RetrievingVehicleInformation
    }

    public class RequestController
    {
        #region Private fields
        private Dictionary<CommandGroup, IEnumerable<string>> AvailableCommands;
        private string ResponseFromELM;
        private const char CarriageReturn = '\r';
        #endregion

        #region Properties
        public ParserManaged ResponseInterpreter { get; set; }
        public ELMCommandManager MainExecuter { get; }
        public Dictionary<CommandGroup, IEnumerable<string>> CommandMap
        {
            get
            {
                return AvailableCommands;
            }
        }
        #endregion

        /// <summary>
        /// Constructor; calls new executing object and a calls and fills the commands' dictionary with commands
        /// </summary>
        public RequestController()
        {
            MainExecuter = new ELMCommandManager();
            AvailableCommands = new Dictionary<CommandGroup, IEnumerable<string>>();
            FillInCommandMap();
        }

        /// <summary>
        /// appends the command dictionary with next command group
        /// </summary>
        /// <param name="NextFileName"></param>
        /// <param name="Group"></param>
        private void AppendMap(string NextFileName, CommandGroup Group)
        {
            var ReadCommands = File.ReadLines(NextFileName);
            AvailableCommands.Add(Group, ReadCommands);
        }

        /// <summary>
        /// fills the command dictionary
        /// </summary>
        private void FillInCommandMap()
        {
            const string INIT_FILE_NAME = "InitCommands.txt";
            const string CHECK_PIDS = "CheckPids.txt";
            const string REAL_TIME_COMMANDS = "RealTimecommands.txt";
            const string VEHICLE_INFORMATION_COMMANDS = "VehicleInformationCommands.txt";

            const int TotalGroups = 4;

            for(int i = 0; i < TotalGroups; ++i)
                switch ((CommandGroup)i)
                {
                    case CommandGroup.Initialization:
                        AppendMap(INIT_FILE_NAME, CommandGroup.Initialization);
                        break;

                    case CommandGroup.CheckingPids:
                        AppendMap(CHECK_PIDS, CommandGroup.CheckingPids);
                        break;

                    case CommandGroup.RetrievingRealtimeData:
                        AppendMap(REAL_TIME_COMMANDS, CommandGroup.RetrievingRealtimeData);
                        break;

                    case CommandGroup.RetrievingVehicleInformation:
                        AppendMap(VEHICLE_INFORMATION_COMMANDS, CommandGroup.RetrievingVehicleInformation);
                        break;

                    default:
                        continue;
                }
        }

        /// <summary>
        /// Initializes ELM327
        /// </summary>
        public void InitializeELM()
        {
            foreach(string NextCommand in AvailableCommands[CommandGroup.Initialization])
            {
                ResponseFromELM = MainExecuter.ExecuteCommand(NextCommand + CarriageReturn, false);

                if(NextCommand.Contains("SP"))
                {
                    string ECUCommand = string.Empty;
                    using (IEnumerator<string> Enumerator = AvailableCommands[CommandGroup.CheckingPids].GetEnumerator())
                        if (Enumerator.MoveNext())
                            ECUCommand = Enumerator.Current;

                    MainExecuter.ExecuteCommand(ECUCommand + CarriageReturn, false);
                }

                if (NextCommand.Contains("DP"))
                {
                    if (ResponseFromELM.Contains("CAN"))
                        ResponseInterpreter = new ParserOBD_CAN_Managed();
                    else
                        ResponseInterpreter = new ParserOBD_Managed();

                    ResponseInterpreter.SetResponseOrError(ResponseFromELM);
                    ResponseInterpreter.RetrieveVehicleInformation();
                }
            }
        }

        /// <summary>
        /// Retrieves real time data by executing proper commands
        /// </summary>
        public void RequestRealTimeData()
        {
            const string MODE = "01";
            const int CANCommandComposition = 3;
            const char SeparatorSpace = ' ';
            int Counter = 0;
            bool IfCAN = false;

            string CANCommand = MODE;

            if (ResponseInterpreter is ParserOBD_CAN_Managed)
                IfCAN = true;

            foreach(string NextCommand in AvailableCommands[CommandGroup.RetrievingRealtimeData])
            {
                string Command = MODE + NextCommand;
                if (IfCAN)
                {
                    CANCommand += SeparatorSpace + NextCommand;
                    ++Counter;

                    if (Counter < CANCommandComposition)
                        continue;
                    else
                    {
                        Command = CANCommand;
                        CANCommand = MODE;
                        Counter = 0;
                    }
                }

                ResponseFromELM = MainExecuter.ExecuteCommand(Command + CarriageReturn, false);
                ResponseInterpreter.SetResponseOrError(ResponseFromELM);
                ResponseInterpreter.RetrieveRealTimeParameters();
            }
        }

        /// <summary>
        /// Retrieves vehicle information by executing proper commands
        /// </summary>
        public void RequestVehicleInformation()
        {
            const string MODE = "01";
            
            foreach(string NextCommand in AvailableCommands[CommandGroup.RetrievingVehicleInformation])
            {
                if (NextCommand.Contains("AT"))
                    ResponseFromELM = MainExecuter.ExecuteCommand(NextCommand + CarriageReturn, false);
                else
                    ResponseFromELM = MainExecuter.ExecuteCommand(MODE + NextCommand + CarriageReturn, false);

                ResponseInterpreter.SetResponseOrError(ResponseFromELM);
                ResponseInterpreter.RetrieveVehicleInformation();
            }
        }
    }
}
