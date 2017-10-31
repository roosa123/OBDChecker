using System;

namespace BTHLibrary
{
    public class BTHException : Exception
    {
        public BTHException(string Message) : base(Message) { }
    }
}
