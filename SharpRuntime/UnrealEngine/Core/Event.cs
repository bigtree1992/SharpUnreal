using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    /// <summary>
    /// 一个通用的事件类
    /// </summary>
    public static class Event
    {
        private static Dictionary<string, Delegate> s_EventTable = new Dictionary<string, Delegate>();

        #region AddListener
        //No parameters
        public static void AddListener(string eventType, Action handler)
        {
            OnListenerAdding(eventType, handler);
            var action = (Action)s_EventTable[eventType];
            action -= handler;
            s_EventTable[eventType] = action + handler;
        }

        //Single parameter
        public static void AddListener<T>(string eventType, Action<T> handler)
        {
            OnListenerAdding(eventType, handler);
            var action = (Action<T>)s_EventTable[eventType];
            action -= handler;
            s_EventTable[eventType] = action + handler;
        }

        //Two parameters
        public static void AddListener<T, U>(string eventType, Action<T, U> handler)
        {
            OnListenerAdding(eventType, handler);
            var action = (Action<T, U>)s_EventTable[eventType];
            action -= handler;
            s_EventTable[eventType] = action + handler;
        }

        //Three parameters
        public static void AddListener<T, U, V>(string eventType, Action<T, U, V> handler)
        {
            OnListenerAdding(eventType, handler);
            var action = (Action<T, U, V>)s_EventTable[eventType];
            action -= handler;
            s_EventTable[eventType] = action + handler;
        }
        #endregion

        #region RemoveListener
        //No parameters
        public static void RemoveListener(string eventType, Action handler)
        {
            try
            {
                OnListenerRemoving(eventType, handler);
                s_EventTable[eventType] = (Action)s_EventTable[eventType] - handler;
                OnListenerRemoved(eventType);
            }
            catch(Exception e)
            {

            }
        }

        //Single parameter
        public static void RemoveListener<T>(string eventType, Action<T> handler)
        {
            try
            {
                OnListenerRemoving(eventType, handler);
                s_EventTable[eventType] = (Action<T>)s_EventTable[eventType] - handler;
                OnListenerRemoved(eventType);
            }
            catch(Exception e)
            {

            }
}

        //Two parameters
        public static void RemoveListener<T, U>(string eventType, Action<T, U> handler)
        {
            try
            {
                OnListenerRemoving(eventType, handler);
                s_EventTable[eventType] = (Action<T, U>)s_EventTable[eventType] - handler;
                OnListenerRemoved(eventType);
            }
            catch(Exception e)
            {

            }
        }

        //Three parameters
        public static void RemoveListener<T, U, V>(string eventType, Action<T, U, V> handler)
        {
            try
            {
                OnListenerRemoving(eventType, handler);
                s_EventTable[eventType] = (Action<T, U, V>)s_EventTable[eventType] - handler;
                OnListenerRemoved(eventType);
            }
            catch(Exception e)
            {

            }
        }
        #endregion

        #region SendEvent
        //No parameters
        public static void Send(string eventType)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                var callback = d as Action;

                if (callback != null)
                {
                    callback();
                }
                else
                {
                    throw CreateEventException(eventType);
                }
            }
        }

        //Single parameter
        public static void Send<T>(string eventType, T arg1)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                var callback = d as Action<T>;

                if (callback != null)
                {
                    var list = callback.GetInvocationList();
                    for (int i = 0; i < list.Length; i++)
                    {
                        try
                        {
                            var ci = list[i] as Action<T>;
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
                    throw CreateEventException(eventType);
                }
            }
        }

        //Two parameters
        public static void Send<T, U>(string eventType, T arg1, U arg2)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                var callback = d as Action<T, U>;

                if (callback != null)
                {
                    var list = callback.GetInvocationList();
                    for (int i = 0; i < list.Length; i++)
                    {
                        try
                        {
                            var ci = list[i] as Action<T, U>;
                            ci(arg1, arg2);
                        }
                        catch (Exception e)
                        {
                            Log.Error("[Broadcast] Excute A Event(Two) Failed : " + e.Message);
                        }
                    }
                }
                else
                {
                    throw CreateEventException(eventType);
                }
            }
        }

        //Three parameters
        public static void Send<T, U, V>(string eventType, T arg1, U arg2, V arg3)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(eventType, out d))
            {
                var callback = d as Action<T, U, V>;

                if (callback != null)
                {
                    var list = callback.GetInvocationList();
                    for (int i = 0; i < list.Length; i++)
                    {
                        try
                        {
                            var ci = list[i] as Action<T, U, V>;
                            ci(arg1, arg2, arg3);
                        }
                        catch (Exception e)
                        {
                            Log.Error("[Broadcast] Excute A Event(Three) Failed : " + e.Message);
                        }
                    }
                }
                else
                {
                    throw CreateEventException(eventType);
                }
            }
        }
        #endregion

        #region AddCallable
        public static void SetCallable<TResult>(string callableType, Func<TResult> handler)
        {
            s_EventTable[callableType] =  handler;
        }

        public static void SetCallable<T,TResult>(string callableType, Func<T, TResult> handler)
        {
            s_EventTable[callableType] =  handler;
        }

        public static void SetCallable<T, U, TResult>(string callableType, Func<T, U, TResult> handler)
        {
            s_EventTable[callableType] = handler;
        }

        public static void SetCallable<T, U, V, TResult>(string callableType, Func<T, U, V, TResult> handler)
        {
            s_EventTable[callableType] = handler;
        }
        #endregion

        #region ClearCallable
        public static void ClearCallable(string callableType)
        {
            if (s_EventTable.ContainsKey(callableType))
            {
                s_EventTable.Remove(callableType);
            }            
        }
       
        #endregion

        #region Call
        public static TResult Call<TResult>(string callableType)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(callableType, out d))
            {
                var function = d as Func<TResult>;

                if (function != null)
                {
                    return function();
                }
                else
                {
                    throw CreateCallableException(callableType);
                }
            }
            return default(TResult);
        }

        public static TResult Call<T, TResult>(string callableType,T t)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(callableType, out d))
            {
                var function = d as Func<T , TResult>;

                if (function != null)
                {
                    return function(t);
                }
                else
                {
                    throw CreateCallableException(callableType);
                }
            }
            return default(TResult);
        }

        public static TResult Call<T, U, TResult>(string callableType, T t, U u)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(callableType, out d))
            {
                var function = d as Func<T, U, TResult>;

                if (function != null)
                {
                    return function(t,u);
                }
                else
                {
                    throw CreateCallableException(callableType);
                }
            }
            return default(TResult);
        }

        public static TResult Call<T, U, V, TResult>(string callableType, T t, U u, V v)
        {
            Delegate d;
            if (s_EventTable.TryGetValue(callableType, out d))
            {
                var function = d as Func<T, U, V, TResult>;

                if (function != null)
                {
                    return function(t, u, v);
                }
                else
                {
                    throw CreateCallableException(callableType);
                }
            }
            return default(TResult);
        }
        #endregion

        #region Helper methods

        public static void PrintEventTable()
        {
		    Log.Debug("\t\t\t=== Event PrintEventTable ===");

		    foreach (KeyValuePair<string, Delegate> pair in s_EventTable) {
			    Log.Debug("\t\t\t" + pair.Key + "\t\t" + pair.Value);
		    }
		    
		    Log.Debug("\n");
        }
        #endregion

        #region Message logging and exception throwing
        private static void OnListenerAdding(string eventType, Delegate listenerBeingAdded)
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

        private static void OnListenerRemoving(string eventType, Delegate listenerBeingRemoved)
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

        private static void OnListenerRemoved(string eventType)
        {
            if (s_EventTable[eventType] == null)
            {
                s_EventTable.Remove(eventType);
            }
        }

        private static EventException CreateEventException(string eventType)
        {
            return new EventException(string.Format("[Event] Sending message \"{0}\" but listeners have a different signature.", eventType));
        }

        private static CallableException CreateCallableException(string callableType)
        {
            return new CallableException(string.Format("[Event] Call On \"{0}\" but listener have a different signature.", callableType));
        }

        public class EventException : Exception
        {
            public EventException(string msg)
            : base(msg)
            {
            }
        }

        public class CallableException : Exception
        {
            public CallableException(string msg)
            : base(msg)
            {
            }
        }

        #endregion

        internal static void Clear()
        {
            s_EventTable.Clear();
        }
    }
}
