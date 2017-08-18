using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试播放骨骼动画（通过蓝图事件实现）
    /// </summary>
    public class PlayAnimTest : ActorComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            TestSimpleAnimation();
            TestBPAnimation();
           
        }

        private void TestSimpleAnimation()
        {
            TimerTest.DelayInvoke(2, () => {
                this.SendEvent("Play");
                TimerTest.DelayInvoke(5, () => {
                    this.SendEvent("Pause");
                });
            });
        }

        private void TestBPAnimation()
        {
            TimerTest.DelayInvoke(2, () => {
                this.SendEvent("SetHorseWoman",1);
                TimerTest.DelayInvoke(5, () => {
                    this.SendEvent("SetHorseWoman",2);
                });
            });
        }
    }
}
