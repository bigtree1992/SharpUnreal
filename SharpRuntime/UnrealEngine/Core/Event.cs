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
        public static void AddListener(EventType type, string evt, Action callback)
        {

        }

        public static void RemoveListener(EventType type, string evt, Action callback)
        {

        }

        public static void SendEvent(EventType type, string evt)
        {

        }

        /// <summary>
        /// 给蓝图发送事件
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public static void SendStringToBlueprint(string evt,string data)
        {

        }

        /// <summary>
        /// 给蓝图发送事件
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public static void SendIntToBlueprint(string evt, int data)
        {

        }

        /// <summary>
        /// 由C++调用，用于传递蓝图发过来的事件
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public static void _OnBlueprintEventString(string evt, string data)
        {

        }

        /// <summary>
        /// 由C++调用，用于传递蓝图发过来的事件
        /// </summary>
        /// <param name="evt"></param>
        /// <param name="data"></param>
        public static void _OnBlueprintEventInt(string evt, int data)
        {

        }

        private static void ExecuteEvent(string evt)
        {

        }
    }
}
