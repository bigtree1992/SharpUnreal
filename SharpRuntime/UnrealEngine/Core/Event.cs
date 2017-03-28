using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    /// <summary>
    /// 一个通用的事件类
    /// </summary>
    public delegate void Callback();
    public delegate void Callback<T>(T arg1);
    public delegate void Callback<T, U>(T arg1, U arg2);
    public delegate void Callback<T, U, V>(T arg1, U arg2, V arg3);

    static public class Event
    {
        #region 内部变量
        static private Dictionary<string, Delegate> s_EventTable = new Dictionary<string, Delegate>();
        //event handlers that should never be removed, regardless of calling Cleanup
        static private List<string> s_PermanentEvents = new List<string>();
        #endregion
        
        #region Helper methods
        //Marks a certain message as permanent.
        static public void MarkAsPermanent(string eventType)
        {
            s_PermanentEvents.Add(eventType);
        }

        /// <summary>
        /// 移除所有除了设置为永久事件的事件注册信息
        /// </summary>
        static public void Cleanup()
        {
            List<string> eventsToRemove = new List<string>();

            foreach (KeyValuePair<string, Delegate> pair in s_EventTable)
            {
                bool wasFound = false;

                foreach (string message in s_PermanentEvents)
                {
                    if (pair.Key == message)
                    {
                        wasFound = true;
                        break;
                    }
                }

                if (!wasFound)
                    eventsToRemove.Add(pair.Key);
            }

            foreach (string message in eventsToRemove)
            {
                s_EventTable.Remove(message);
            }
        }

        static public void PrintEventTable()
        {
		    Log.Debug("\t\t\t=== Event PrintEventTable ===");

		    foreach (KeyValuePair<string, Delegate> pair in s_EventTable) {
			    Log.Debug("\t\t\t" + pair.Key + "\t\t" + pair.Value);
		    }
		    
		    Log.Debug("\n");
        }
        #endregion

        #region Message logging and exception throwing
        static public void OnListenerAdding(string eventType, Delegate listenerBeingAdded)
        {
            if (!s_EventTable.ContainsKey(eventType))
            {
                s_EventTable.Add(eventType, null);
            }

            Delegate d = s_EventTable[eventType];
            if (d != null && d.GetType() != listenerBeingAdded.GetType())
            {
                Log.Warning(String.Format("[OnListenerAdding] Type Not Match : {0} - {1}",d.GetType(),listenerBeingAdded.GetType()));
            }
        }

        static public void OnListenerRemoving(string eventType, Delegate listenerBeingRemoved)
        {

            if (s_EventTable.ContainsKey(eventType))
            {
                Delegate d = s_EventTable[eventType];

                if (d == null)
                {

                }
                else if (d.GetType() != listenerBeingRemoved.GetType())
                {
                    Log.Warning(String.Format("[OnListenerRemoving] Type Not Match : {0} - {1}", d.GetType(), listenerBeingRemoved.GetType()));
                }
            }
            else
            {

            }
        }

        static public void OnListenerRemoved(string eventType)
        {
            if (s_EventTable[eventType] == null)
            {
                s_EventTable.Remove(eventType);
            }
        }

        static public void OnBroadcasting(string eventType)
        {

        }

        static public BroadcastException CreateBroadcastSignatureException(string eventType)
        {
            return new BroadcastException(string.Format("Broadcasting message \"{0}\" but listeners have a different signature than the broadcaster.", eventType));
        }

        public class BroadcastException : Exception
        {
            public BroadcastException(string msg)
            : base(msg)
            {
            }
        }

        public class ListenerException : Exception
        {
            public ListenerException(string msg)
            : base(msg)
            {
            }
        }
        #endregion

        #region AddListener
        //No parameters
        static public void AddListener(string eventType, Callback handler)
        {
            OnListenerAdding(eventType, handler);
            s_EventTable[eventType] = (Callback)s_EventTable[eventType] + handler;
        }

        //Single parameter
        static public void AddListener<T>(string eventType, Callback<T> handler)
        {
            OnListenerAdding(eventType, handler);
            s_EventTable[eventType] = (Callback<T>)s_EventTable[eventType] + handler;
        }

        //Two parameters
        static public void AddListener<T, U>(string eventType, Callback<T, U> handler)
        {
            OnListenerAdding(eventType, handler);
            s_EventTable[eventType] = (Callback<T, U>)s_EventTable[eventType] + handler;
        }

        //Three parameters
        static public void AddListener<T, U, V>(string eventType, Callback<T, U, V> handler)
        {
            OnListenerAdding(eventType, handler);
            s_EventTable[eventType] = (Callback<T, U, V>)s_EventTable[eventType] + handler;
        }
        #endregion

        #region RemoveListener
        //No parameters
        static public void RemoveListener(string eventType, Callback handler)
        {
            OnListenerRemoving(eventType, handler);
            s_EventTable[eventType] = (Callback)s_EventTable[eventType] - handler;
            OnListenerRemoved(eventType);
        }

        //Single parameter
        static public void RemoveListener<T>(string eventType, Callback<T> handler)
        {
            OnListenerRemoving(eventType, handler);
            s_EventTable[eventType] = (Callback<T>)s_EventTable[eventType] - handler;
            OnListenerRemoved(eventType);
        }

        //Two parameters
        static public void RemoveListener<T, U>(string eventType, Callback<T, U> handler)
        {
            OnListenerRemoving(eventType, handler);
            s_EventTable[eventType] = (Callback<T, U>)s_EventTable[eventType] - handler;
            OnListenerRemoved(eventType);
        }

        //Three parameters
        static public void RemoveListener<T, U, V>(string eventType, Callback<T, U, V> handler)
        {
            OnListenerRemoving(eventType, handler);
            s_EventTable[eventType] = (Callback<T, U, V>)s_EventTable[eventType] - handler;
            OnListenerRemoved(eventType);
        }
        #endregion

        #region Broadcast
        //No parameters
        static public void Broadcast(string eventType)
        {
            OnBroadcasting(eventType);

            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                Callback callback = d as Callback;

                if (callback != null)
                {
                    callback();
                }
                else
                {
                    throw CreateBroadcastSignatureException(eventType);
                }
            }
        }

        //Single parameter
        static public void Broadcast<T>(string eventType, T arg1)
        {
            OnBroadcasting(eventType);

            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                Callback<T> callback = d as Callback<T>;

                if (callback != null)
                {
                    var list = callback.GetInvocationList();
                    for (int i = 0; i < list.Length; i++)
                    {
                        try
                        {
                            var ci = list[i] as Callback<T>;
                            ci(arg1);
                        }
                        catch (Exception e)
                        {
                            Log.Error("[Broadcast] Excute A Event(Single) Failed : " + e.Message);
                        }
                    }
                }
                else
                {
                    throw CreateBroadcastSignatureException(eventType);
                }
            }
        }

        //Two parameters
        static public void Broadcast<T, U>(string eventType, T arg1, U arg2)
        {
            OnBroadcasting(eventType);

            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                Callback<T, U> callback = d as Callback<T, U>;

                if (callback != null)
                {
                    var list = callback.GetInvocationList();
                    for(int i = 0; i < list.Length; i++)
                    {
                        try
                        {
                            var ci = list[i] as Callback<T, U>;
                            ci(arg1, arg2);
                        }
                        catch(Exception e)
                        {
                            Log.Error("[Broadcast] Excute A Event(Two) Failed : " + e.Message);
                        }
                    }                 
                }
                else
                {
                    throw CreateBroadcastSignatureException(eventType);
                }
            }
        }

        //Three parameters
        static public void Broadcast<T, U, V>(string eventType, T arg1, U arg2, V arg3)
        {
            OnBroadcasting(eventType);

            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                Callback<T, U, V> callback = d as Callback<T, U, V>;

                if (callback != null)
                {
                    var list = callback.GetInvocationList();
                    for (int i = 0; i < list.Length; i++)
                    {
                        try
                        {
                            var ci = list[i] as Callback<T, U, V>;
                            ci(arg1,arg2,arg3);
                        }
                        catch (Exception e)
                        {
                            Log.Error("[Broadcast] Excute A Event(Three) Failed : " + e.Message);
                        }
                    }
                }
                else
                {
                    throw CreateBroadcastSignatureException(eventType);
                }
            }
        }
        #endregion
    }
}
