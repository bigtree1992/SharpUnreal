using System;
using System.Collections.Generic;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试初始化设置参数相关的接口
    /// </summary>
    public class InitTest : ActorComponent
    {
        public float TestValue;

        protected override void Initialize()
        {
            base.Initialize();
            Log.Debug("[InitTest] Initialize： value: " + TestValue);
        }

        protected override void BeginPlay()
        {
            base.BeginPlay();
            Log.Debug("[InitTest] BeginPlay ： value: " + TestValue);
        }
    }
}
