using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    /// <summary>
    /// 定时器类，使用前请把脚本挂载到场景中
    /// </summary>
    public class Timer : MonoComponent
    {
        protected class TimeEvent
        {
            public TimeEvent(float delay, Action callback)
            {
                this.Delay = delay;
                this.Callback = callback;
            }

            public float Delay;
            public Action Callback;
        }

        protected static List<TimeEvent> m_Events = new List<TimeEvent>();

        protected static bool s_Init;

        internal static TweenManager m_TweenManager = new TweenManager();

        protected override void Initialize()
        {
            CanEverTick = true;
            s_Init = true;
        }

        protected override void Tick(float dt)
        {
            for (int i = 0; i < m_Events.Count; i++)
            {
                TimeEvent evt = m_Events[i];
                evt.Delay -= dt;
                
                if (evt.Delay > 0.0f)
                {
                    continue;
                }

                try
                {
                    evt.Callback();
                }
                catch (Exception e)
                {
                    Log.Error("[Timer]  CallBack Failed :" + e);
                }

                m_Events.RemoveAt(i);
                i--;
            }

            m_TweenManager.Tick(dt);
        }

        public static void DelayInvoke(float delay, Action callback)
        {
            if (!s_Init)
            {
                Log.Error("[Timer] Timer Not In World.");
            }

            if (delay < 0.0f || callback == null )
            {
                return;
            }

            m_Events.Add(new TimeEvent(delay, callback));
        }

        protected override void Uninitialize()
        {
            CanEverTick = false;
            s_Init = false;
        }

        internal static void Clear()
        {
            m_Events.Clear();
            m_TweenManager.Clear();
        }
    }
}
