using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试播放音效相关的接口
    /// </summary>
    public class AudioTest : MonoComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            TestAudio();
        }

        private void TestAudio()
        {
            var audio = Actor.GetComponent<AudioComponent>();
            if(audio == null)
            {
                Log.Error("[AudioTest] audio is null");
            }

            audio.RegAudioFinished(this);
            audio.RegAudioPlaybackPercent(this);

            audio.Play();
            //TimerTest.DelayInvoke(1, () =>
            //{
            //    if (audio.IsPlaying)
            //    {
            //        Log.Error("[AudioTest] audio is playing");
            //    }
            //    else
            //    {
            //        Log.Error("[AudioTest] audio is pause");
            //    }
            //});
            //TimerTest.DelayInvoke(2, () =>
            //{
            //    audio.SetPaused(true);
            //});
            //TimerTest.DelayInvoke(5, () =>
            //{
            //    audio.SetPaused(false);
            //});
            //TimerTest.DelayInvoke(7, () =>
            //{
            //    if (audio.IsPlaying)
            //    {
            //        Log.Error("[AudioTest] audio is playing");
            //    }
            //    else
            //    {
            //        Log.Error("[AudioTest] audio is pause");
            //    }
            //});
            //TimerTest.DelayInvoke(10, () =>
            //{
            //    audio.PitchMultiplier = 0;
            //});
            //TimerTest.DelayInvoke(20, () =>
            //{
            //    audio.VolumeMultiplier = 0;
            //});
            //TimerTest.DelayInvoke(30, () =>
            //{
            //    audio.Stop();
            //});
        }

        public override void OnAudioFinished(string event_name)
        {
            base.OnAudioFinished(event_name);
            Log.Error("[AudioTest] OnAudioFinished,event_name:" + event_name);
        }

        public override void OnAudioPlaybackPercent(string event_name, float percent)
        {
            base.OnAudioPlaybackPercent(event_name, percent);
            Log.Error("[AudioTest] OnAudioPlaybackPercent,event_name:" + event_name + ",percent:" + percent);
        }

    }
}
