using System;
using System.Collections.Generic;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试初始化设置参数相关的接口
    /// </summary>
    public class InitTest : MonoComponent
    {
        public int TestValue = 10;

        protected override void Initialize()
        {
            base.Initialize();
            Log.Debug("[InitTest] Initialize： value: " + TestValue);
            Event.AddListener("TestListener", Listener);
        }
        public void Listener()
        {
            Log.Error("[InitTest] Listener");
        }

        protected override void BeginPlay()
        {
            base.BeginPlay();
            Log.Debug("[InitTest] BeginPlay ： value: " + TestValue);
        }

        public override void OnEvent(string evt)
        {
            base.OnEvent(evt);
            Log.Debug("[InitTest] OnEvent ： value: " + evt);
        }
    }
}
