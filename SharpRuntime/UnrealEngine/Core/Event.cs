using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnrealEngine
{
    public enum EventType
    {
        System = 1,
        Blueprint = 2,
        Actor = 3,
    }

    /// <summary>
    /// 一个通用的事件类
    /// </summary>
    public class Event
    {
        public void AddListener(EventType type, string evt, Action callback)
        {

        }

        public void RemoveListener(EventType type, string evt, Action callback)
        {

        }

        public void SendEvent(EventType type, string evt)
        {

        }
    }
}
