using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试定序器相关的接口
    /// </summary>
    public class SequencerTest : MonoComponent
    {
        protected override void BeginPlay()
        {
            base.BeginPlay();
            TestSequence();
        }

        private void TestSequence()
        {
            Timer.DelayInvoke(2.0f, () => {
                Sequencer seq = Actor.Sequencer;
                if (seq == null)
                {
                    Log.Error("[SequencerTest] Sequencer is null");
                }
                seq.Play();
                Log.Error("[SequencerTest] Sequencer Current: " + seq.Current);
            });
        }
    }
}
