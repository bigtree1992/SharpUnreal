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
                int result = task.Tick(delta);
                if (result != 0)
                {
                    m_Tasks.RemoveAt(i);
                    i--;
                    if(result == 1)
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
