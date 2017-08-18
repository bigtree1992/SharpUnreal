using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试C# Event模块的用法
    /// </summary>
    public class EventTest : ActorComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            Event.SetCallable("TestCallable", Callable);
            Event.SetCallable<string,int>("TestCallable1", Callable1);
            Event.SetCallable<string,int,bool>("TestCallable2", Callable2);
            Event.SetCallable<string,int,Vector,int>("TestCallable3", Callable3);
            Event.AddListener("TestListener",Listener);
            Event.AddListener<string>("TestListener1", Listener1);
            Event.AddListener<string, int>("TestListener2", Listener2);
            Event.AddListener<string, int, Vector>("TestListener3", Listener3);
            Event.ClearCallable("TestCallable");
            Event.RemoveListener("TestListener",Listener);
        }

        public string Callable()
        {
            Log.Error("[EventTest] Callable");
            return "EventTest Callable";
        }

        public int Callable1(string str)
        {
            Log.Error("[EventTest] Callable,str:" + str);
            return 199;
        }
        public bool Callable2(string str,int i)
        {
            Log.Error("[EventTest] Callable str:" +str + " ,i:" + i);
            return true;
        }
        public int Callable3(string str,int i,Vector v)
        {
            Log.Error("[EventTest] Callable(str:" + str + ",i" + i + ",v" + v + ")");
            return 1989;
        }

        public void Listener()
        {
            Log.Error("[EventTest] Listener");
        }
        public void Listener1(string str)
        {
            Log.Error("[EventTest] Listener,str:" + str);
        }
        public void Listener2(string str, int i)
        {
            Log.Error("[EventTest] Listener str:" + str + " ,i:" + i);
        }
        public void Listener3(string str, int i, Vector v)
        {
            Log.Error("[EventTest] Listener(str:" + str + ",i" + i + ",v" + v + ")");
        }
    }
}
