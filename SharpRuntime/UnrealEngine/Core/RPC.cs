using System;

namespace UnrealEngine
{
    public class RPC : Attribute
    {
        public RPC(int id)
        {
            ID = id;
        }

        public int ID { get; set; }
    }
}
