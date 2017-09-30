using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    ///  输入的回调测试，（通过蓝图事件实现）
    /// </summary>
    public class InputTest : MonoComponent
    {
        const int Axis_Horizantal = 0;
        const int Axis_Vertical = 1;

        private InputComponent m_Input;

        protected override void Initialize()
        {
            base.Initialize();
            CanEverTick = true;
        }

        protected override void BeginPlay()
        {
            base.BeginPlay();
            Log.Debug("[BeginPlay] " + typeof(InputComponent).Name);

            m_Input = Actor.GetComponent<InputComponent>();
            Log.Debug("[A] " + m_Input.NativeHandler.ToInt64());

            m_Input.BindAxis("Horizantal", Axis_Horizantal);
            m_Input.BindAxis("Vertical", Axis_Vertical);

        }

        protected override void Tick(float dt)
        {
            base.Tick(dt);

            if(m_Input != null)
            {
                Log.Debug("[Vertical] AxisValue : " + m_Input.GetAxisValue(Axis_Vertical));
                Log.Debug("[Horizantal] AxisValue : " + m_Input.GetAxisValue(Axis_Horizantal));
            }
            else
            {
            }
        }
    }
}
