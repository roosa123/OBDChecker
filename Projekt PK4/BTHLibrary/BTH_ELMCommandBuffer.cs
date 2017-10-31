namespace BTHLibrary
{
    public class BTH_ELMCommandBuffer
    {
        public static bool LastCommand { get; set; }
        public static string Command { get; set; }
        public static string Response { get; set; }

        static BTH_ELMCommandBuffer()
        {
            LastCommand = false;
            Command = "No command set";
            Response = "No response yet";
        }
    }
}
