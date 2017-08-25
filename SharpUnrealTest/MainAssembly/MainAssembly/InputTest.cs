using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    ///  输入的回调测试，（通过蓝图事件实现）
    /// </summary>
    public class InputTest : MonoComponent
    {
        public override void OnEventWithInt(string evt, int data)
        {
            base.OnEventWithInt(evt, data);
            Log.Error("evt:" + evt + ",data:" + data);
        }

        public override void OnEventWithString(string evt, string data)
        {
            base.OnEventWithString(evt, data);
            Log.Error("evt:" + evt + ",data:" + data);
        }

        public override void OnEventWithVector(string evt, Vector data)
        {
            base.OnEventWithVector(evt, data);
            Log.Error("evt:" + evt + ",data:" + data);
        }
    }
}
