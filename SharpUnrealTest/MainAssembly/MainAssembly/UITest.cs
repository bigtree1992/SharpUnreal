using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试UI相关的交互（通过蓝图事件实现）
    /// </summary>
    public class UITest : ActorComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            TestUI();
        }

        private void TestUI()
        {
            TimerTest.DelayInvoke(2, () => {
                this.SendEvent("SetTitle", "奇境森林");
            });
            TimerTest.DelayInvoke(4, () => {
                this.SendEvent("SetContent", "UIContent：奇境森林\r\n奇境森林\r\n奇境森林\r\n奇境森林\r\n奇境森林");
            });
        }
    }
}
