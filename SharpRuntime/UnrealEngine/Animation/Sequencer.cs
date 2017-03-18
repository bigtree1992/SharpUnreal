using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    /// <summary>
    /// 定序器
    /// </summary>
    public class Sequencer : Actor
    {
        public void Play()
        {
        }

        public void Pause()
        {
        }

        public void Stop()
        {
        }

        public int GetLength()
        {
            return 0;
        }

        public int Current
        {
            get;
            set;
        }

        public void AddEvent(string evt,Action callback) {}
        public void RemoveEvent(string evt) { }
    }
}
