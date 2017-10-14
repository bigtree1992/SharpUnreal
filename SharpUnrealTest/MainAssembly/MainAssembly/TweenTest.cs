using System;
using System.Collections.Generic;

using UnrealEngine;

namespace MainAssembly
{
    public class TweenTest : MonoComponent
    {
        protected override void BeginPlay()
        {
            base.BeginPlay();

            var task = new VTweenTask();
            task.StartValue = Actor.Root.LocalPosition;
            task.TargetValue = task.StartValue + new Vector(0, 0, 100);
            task.TotalTime = 1.0f;
            task.OnSetValue = (value) => { Actor.Root.LocalPosition = value; };
            task.OnComplete = () => { Log.Print("Complete!"); };
            task.EaseType = EaseType.ElasticInOut;
            task.Start();

            var taskr = new RTweenTask();
            taskr.StartValue = Actor.Root.LocalRotation;
            taskr.TargetValue = Actor.Root.LocalRotation + new Rotator(0, 100, 0);
            taskr.TotalTime = 1.0f;
            taskr.OnSetValue = (value) => { Actor.Root.LocalRotation = value; };
            taskr.OnComplete = () => { Log.Print("Complete R!"); };
            taskr.EaseType = EaseType.Linear;
            taskr.Start();

        }
    }
}
