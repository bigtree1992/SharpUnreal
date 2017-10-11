using System;
using System.Collections.Generic;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// Actor有关的测试
    /// </summary>
    public class ActorTest : MonoComponent
    {
        private StaticMeshComponent m_Root;
        private StaticMeshComponent m_Child;

        protected override void Initialize()
        {
            base.Initialize();
            //TimerTest.DelayInvoke(3.0f, () => {
            //    string result = Event.Call<string>("TestCallable");
            //    Log.Error("[ActorTest] callresult:" + result);
            //    Event.Send("TestListener");

            //    //int i = Event.Call<string, int>("TestCallable1", "lewis");
            //    //Log.Error("[ActorTest] callresult:" + i);

            //    //bool b = Event.Call<string,int,bool>("TestCallable2", "lewis",123);
            //    //Log.Error("[ActorTest] callresult:" + b);

            //    //i = Event.Call<string, int, Vector, int>("TestCallable3", "lewis", 123, new Vector(4,2,1));
            //    //Log.Error("[ActorTest] callresult:" + i);

            //    //Event.Send("TestListener");
            //    //Event.Send<string>("TestListener1","awei");
            //    //Event.Send<string,int>("TestListener2","awei",123);
            //    //Event.Send<string,int,Vector>("TestListener3","awei",123,new Vector(123,123,123));
            //});
        }

        protected override void BeginPlay()
        {
            base.BeginPlay();
            m_Root = Actor.GetComponentByTag<StaticMeshComponent>("root");
            m_Child = Actor.GetComponentByTag<StaticMeshComponent>("child");
            if(m_Root == null)
            {
                Log.Print("root is null");
                return;
            }
            if (m_Child == null)
            {
                Log.Print("child is null");
                return;
            }

            m_Child.AttachTo(m_Root);
            //m_Child.AttachToSocket(m_Root, "Socket");
        }

    }
}
