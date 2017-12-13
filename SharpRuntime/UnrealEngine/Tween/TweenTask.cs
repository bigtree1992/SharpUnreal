using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public interface ITweenTask
    {
        void Start();

        void Stop();

        /// <summary>
        /// 返回值 0 执行tween 1完成tween 2结束tween
        /// </summary>
        /// <param name="deta"></param>
        /// <returns></returns>
        int Tick(float deta);

        void Complete();

        void Finish();
    }

    public class TweenTaskBase<T> : ITweenTask
    {
        protected bool m_Finish = false;
        protected bool m_Running = false;
        protected float m_CurrentTime;
        protected float m_TotalTime;
        protected T m_StartValue;
        protected T m_TargetValue;
        protected Func<float, float, float, float, float> m_TweenFunction = TweenFunction.LinearEaseNone;
        protected Action<T> m_SetValueCallback;
        protected Action m_CompleteCallback;

        public T StartValue
        {
            get { return m_StartValue; }
            set { m_StartValue = value; }
        }

        public T TargetValue
        {
            get { return m_TargetValue; }
            set { m_TargetValue = value; }
        }

        public float TotalTime
        {
            get { return m_TotalTime; }
            set { m_TotalTime = value; }
        }

        public EaseType EaseType
        {
            set
            {
                m_TweenFunction = TweenFunction.GetTweenFuncByType(value);
            }
        }

        public Action<T> OnSetValue
        {
            set
            {
                m_SetValueCallback = value;
            }
        }

        public Action OnComplete
        {
            set
            {
                m_CompleteCallback = value;
            }
        }

        public TweenTaskBase()
        {
        }

        public TweenTaskBase(T start,T target,float totalTime,EaseType type,Action<T> setCallback,Action complete = null)
        {
            m_StartValue = start;
            m_TargetValue = target;
            m_TotalTime = totalTime;
            m_TweenFunction = TweenFunction.GetTweenFuncByType(type);
            m_SetValueCallback = setCallback;
            m_CompleteCallback = complete;
        }

        public virtual void Start()
        {
            m_Running = true;

            TweenManager.ScheduleTask(this);
        }

        public virtual void Stop()
        {
            m_Running = false;
        }

        public virtual void Finish()
        {
            m_Finish = true;
        }

        public virtual int Tick(float delta)
        {
            m_CurrentTime += delta;

            if (m_Finish)
                return 2;

            if (!m_Running || m_CurrentTime > m_TotalTime)
            {                
                return 1;
            }

            return 0;
        }

        public void Complete()
        {
            try
            {
                m_CompleteCallback();
            }
            catch (Exception e)
            {
                Log.Error("[TweenTask] Complete Error:" + e.Message);
            }
        }
    }

    public class FTweenTask : TweenTaskBase<float>
    {     
        public FTweenTask() { }

        public FTweenTask(float start, float target, float totalTime,EaseType type, Action<float> setCallback, Action complete = null)
            :base(start,target,totalTime,type, setCallback, complete)
        {

        }

        public override int Tick(float delta)
        {
            int result = base.Tick(delta);
            if (result != 0)
                return result;

            float value = m_TweenFunction(
                m_CurrentTime,
                m_StartValue,
                (m_TargetValue - m_StartValue),
                m_TotalTime);
            try
            {
                m_SetValueCallback(value);
            }
            catch(Exception e)
            {
                Log.Error("[FTweenTask] SetValue Error:" + e.Message);
            }
            
            return 0;
        }
    }

    public class V2TweenTask : TweenTaskBase<Vector2D>
    {
        public V2TweenTask() { }

        public V2TweenTask(Vector2D start, Vector2D target, float totalTime, EaseType type, Action<Vector2D> setCallback, Action complete = null)
            : base(start, target, totalTime, type, setCallback, complete)
        {

        }

        public override int Tick(float delta)
        {
            int result = base.Tick(delta);
            if (result != 0)
                return result;

            float x = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.X,
                (m_TargetValue.X - m_StartValue.X),
                m_TotalTime);

            float y = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.Y,
                (m_TargetValue.Y - m_StartValue.Y),
                m_TotalTime);

            try
            {
                m_SetValueCallback(new Vector2D(x,y));
            }
            catch (Exception e)
            {
                Log.Error("[V2TweenTask] SetValue Error:" + e.Message);
            }

            return 0;
        }
    }

    public class VTweenTask : TweenTaskBase<Vector>
    {
        public VTweenTask() { }

        public VTweenTask(Vector start, Vector target, float totalTime, EaseType type, Action<Vector> setCallback, Action complete = null)
            : base(start, target, totalTime, type, setCallback, complete)
        {

        }

        public override int Tick(float delta)
        {
            int result = base.Tick(delta);
            if (result != 0)
                return result;

            float x = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.X,
                (m_TargetValue.X - m_StartValue.X),
                m_TotalTime);

            float y = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.Y,
                (m_TargetValue.Y - m_StartValue.Y),
                m_TotalTime);

            float z = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.Z,
                (m_TargetValue.Z - m_StartValue.Z),
                m_TotalTime);
            try
            {
                m_SetValueCallback(new Vector(x, y, z));
            }
            catch (Exception e)
            {
                Log.Error("[VTweenTask] SetValue Error:" + e.Message);
            }
            
            return 0;
        }
    }

    public class RTweenTask : TweenTaskBase<Rotator>
    {
        public RTweenTask() { }

        public RTweenTask(Rotator start, Rotator target, float totalTime, EaseType type, Action<Rotator> setCallback, Action complete = null)
            : base(start, target, totalTime, type, setCallback, complete)
        {

        }

        public override int Tick(float delta)
        {
            int result = base.Tick(delta);
            if (result != 0)
                return result;

            float Pitch = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.Pitch,
                (m_TargetValue.Pitch - m_StartValue.Pitch),
                m_TotalTime);

            float Yaw = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.Yaw,
                (m_TargetValue.Yaw - m_StartValue.Yaw),
                m_TotalTime);

            float Roll = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.Roll,
                (m_TargetValue.Roll - m_StartValue.Roll),
                m_TotalTime);
            
            try
            {
                m_SetValueCallback(new Rotator(Pitch, Yaw, Roll));
            }
            catch (Exception e)
            {
                Log.Error("[RTweenTask] SetValue Error:" + e.Message);
            }
            return 0;
        }
    }

    public class CTweenTask : TweenTaskBase<LinearColor>
    {
        public CTweenTask() { }

        public CTweenTask(LinearColor start, LinearColor target, float totalTime, EaseType type, Action<LinearColor> setCallback, Action complete = null)
            : base(start, target, totalTime, type, setCallback, complete)
        {

        }

        public override int Tick(float delta)
        {
            int result = base.Tick(delta);
            if (result != 0)
                return result;

            float R = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.R,
                (m_TargetValue.R - m_StartValue.R),
                m_TotalTime);

            float G = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.G,
                (m_TargetValue.G - m_StartValue.G),
                m_TotalTime);

            float B = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.B,
                (m_TargetValue.B - m_StartValue.B),
                m_TotalTime);

            float A = m_TweenFunction(
                m_CurrentTime,
                m_StartValue.A,
                (m_TargetValue.A - m_StartValue.A),
                m_TotalTime);
           
            try
            {
                m_SetValueCallback(new LinearColor(R,G,B,A));
            }
            catch (Exception e)
            {
                Log.Error("[CTweenTask] SetValue Error:" + e.Message);
            }
            return 0;
        }
    }
}
