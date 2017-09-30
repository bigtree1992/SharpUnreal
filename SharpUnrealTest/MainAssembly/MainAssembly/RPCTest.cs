using System;
using UnrealEngine;

namespace MainAssembly
{
    class RPCTest: NetComponent
    {
        const int Func_ClientRPC = 1;
        const int Func_ServerRPC = 2;
        const int Func_AllRPC = 3;

        [RPC(Func_ClientRPC)]
        void ClientRPC(Rotator data)
        {
            SendEvent("ClientRPC" + data.Yaw + data.Pitch + data.Roll);
        }

        [RPC(Func_ServerRPC)]
        void ServerRPC(Rotator data)
        {
            SendEvent("ServerRPC" + +data.Yaw + data.Pitch + data.Roll);
        }

        [RPC(Func_AllRPC)]
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
                    if(IsSelf())
                        CallOnServerWithRotator(Func_ServerRPC, new Rotator(1, 1, 1));
                    break;
                case "client":
                    break;
                case "all":
                    if (IsSelf())
                        CallOnAllWithRotator(Func_AllRPC, new Rotator(1, 1, 3));
                    break;
            }
        }
    }
}
