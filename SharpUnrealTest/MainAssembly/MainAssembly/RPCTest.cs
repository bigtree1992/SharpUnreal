using System;
using UnrealEngine;

namespace MainAssembly
{
    class RPCTest: NetComponent
    {
        [RPC(1)]
        void ClientRPC(Rotator data)
        {
            SendEvent("ClientRPC" + data.Yaw + data.Pitch + data.Roll);
        }

        [RPC(2)]
        void ServerRPC(Rotator data)
        {
            SendEvent("ServerRPC" + +data.Yaw + data.Pitch + data.Roll);
        }

        [RPC(3)]
        void AllRPC(Rotator data)
        {
            SendEvent("AllRPC" + +data.Yaw + data.Pitch + data.Roll);
        }


        public override void OnEvent(string evt)
        {
            base.OnEvent(evt);
            switch (evt)
            {
                case "server":
                    //if(IsSelf())
                        CallOnServerWithRotator(2, new Rotator(1, 1, 1));
                    break;
                case "client":
                    break;
                case "all":
                    //if (IsSelf())
                        CallOnAllWithRotator(3, new Rotator(1, 1, 3));
                    break;
            }
        }
    }
}
