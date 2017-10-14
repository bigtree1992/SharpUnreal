using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    internal class TweenManager
    {
        private static List<ITweenTask> m_Tasks = new List<ITweenTask>();

        internal static void ScheduleTask(ITweenTask task)
        {
            if (!m_Tasks.Contains(task))
            {
                m_Tasks.Add(task);
            }
            else
            {
                Log.Warning("[TweenManager] ScheduleTask A Dup Task:" + task.ToString());
            }
        }

        internal void Tick(float delta)
        {
            for (int i = 0; i < m_Tasks.Count; i++)
            {
                var task = m_Tasks[i];
                if (!task.Tick(delta))
                {
                    m_Tasks.RemoveAt(i);
                    i--;
                    task.Complete();
                }
            }
        }

        internal void Clear()
        {
            m_Tasks.Clear();
        }

    }
}
