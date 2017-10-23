using System;
using UnrealEngine;

namespace MainAssembly
{
    public class RPCTest: NetComponent
    {
        const int Func_ClientRPC = 1;
        const int Func_ServerRPC = 2;
        const int Func_AllRPC = 3;
        const int Func_ProcessRotate = 4;

        static Vector[] Postions = { new Vector(-110,70,92), new Vector(-10,-110,92), new Vector(120,60,92) };
        static Rotator[] Rotators = { new Rotator(0,-39,0), new Rotator(0,90,0), new Rotator(0,-140,0)};
        static bool[] Flags = { false, false, false};

        private RotatorProperty m_Rot;

        private int m_Index = -1;

        protected override void OnRegister()
        {
            base.OnRegister();

            m_Rot = Actor.FindRotatorProperty("Rotate");
        }

        protected override void Initialize()
        {
            base.Initialize();


            //选取Index
            //都是服务器最先登陆进来，所以服务器的ID一直为0
            //其他客户端登陆进来后会顺序分配ID
            //ID第一次生成了之后都是保存到服务器的，客户端自己不知道，
            //需要进行一次查询，查询的时候可以发送一条指令，
            //参数使用本地配置的玩家名字或者配置的标记号作为区分

            for(int i = 0; i < 3; i++)
            {
                if(Flags[i] == true)
                {
                    continue;
                }

                Actor.Root.Position = Postions[i];
                Actor.Root.Rotation = Rotators[i].Quaternion();

                Flags[i] = true;
                m_Index = i;
                break;
            }

            if (m_Index != -1)
            {
                Log.Debug(m_Index + " : " + GetRole().ToString());
            }
            //同步的插值目标初始的时候必须要设置为当前的值
            m_Rot.Value = Actor.Root.LocalRotation;
            CanEverTick = true;
        }

        protected override void EndPlay(EndPlayReason reason)
        {
            base.EndPlay(reason);

            //因为静态变量在编辑器下重复运行，所以需要清理
            Flags[0] = false;
            Flags[1] = false;
            Flags[2] = false;
        }

        [RPC(Func_ServerRPC)]
        void ServerRPC(Vector pos, Quat data)
        {
            CallOnAllWithVQ(Func_AllRPC,pos, data);
        }

        [RPC(Func_AllRPC)]
        void AllRPC(Vector pos, Quat data)
        {
            Actor.Root.AddLocalOffset(new Vector(0, 0, 5));
            Actor.Root.AddLocalOffset(new Vector(0, 0, 100));
        }

        [RPC(5)]
        void TestQuat(Quat quat)
        {
            Log.Print(quat.ToString());
        }

        protected override void Tick(float dt)
        {
            base.Tick(dt);
            // 分两次判断，如果是客户端 那么是模拟的就是使用别人的值
            // 如果是在服务器，就根据本地配置的ID进行判断是不是自己，如果不是自己的话，也要用别人的值

            // 这个代表服务器端的用户的Index一直为0

            int ServerPlayerIndex = 0;

            if (GetRole() == ENetRole.ROLE_SimulatedProxy || 
                (GetRole() == ENetRole.ROLE_Authority && m_Index != ServerPlayerIndex))
            {
                ProcessInterpTo(m_Rot.Value);
            }
        }

       
        [RPC(Func_ProcessRotate)]
        void ServerProcessRotate(Rotator data)
        {
            //服务端被调用后需要设置同步变量才能通知模拟端
            // 广播给模拟端的是处理完的绝对值
            m_Rot.Value = data;
        }

        public override void OnEvent(string evt)
        {
            base.OnEvent(evt);

            switch (evt)
            {
                case "server":
                    CallOnServerWithQuat(5, new Quat(100, 100, 100, 100));
                    CallOnServerWithVQ(Func_ServerRPC, new Vector(0, 0, 100), new Quat(0, 10, 0, 0));

                    break;
                case "f":
                    // 3 Pawn在处理输入的时候 要本地自己处理，
                    ProcessInput(new Rotator(0, 10, 0));
                    // 处理完把处理的结果发送给服务器
                    CallOnServerWithRotator(Func_ProcessRotate, Actor.Root.LocalRotation);
                    break;                   
            }
        }

        /// <summary>
        /// 处理插值到目标
        /// </summary>
        /// <param name="rotator"></param>
        private void ProcessInterpTo(Rotator rotator)
        {
            Actor.Root.LocalRotation = rotator;
        }

        /// <summary>
        /// 根据业务逻辑处理输入值
        /// </summary>
        /// <param name="rotator"></param>
        private void ProcessInput(Rotator rotator)
        {
            Actor.Root.AddLocalRotation(rotator);
        }
    }
}
