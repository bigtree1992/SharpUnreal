using System;
using UnrealEngine;

namespace MainAssembly
{
    class TagTest: MonoComponent
    {
        protected override void BeginPlay()
        {
            base.BeginPlay();
            Actor.AddTag("Actor");
            if (Actor.HasTag("Actor"))
            {
                Log.Print("Add Actor have tag");
            }
            else
            {
                Log.Print("Actor have no tag");
            }
            Actor.RemoveTag("Actor");
            if (Actor.HasTag("Actor"))
            {
                Log.Print("Actor have tag");
            }
            else
            {
                Log.Print("Remove Actor have no tag");
            }

            var cube = Actor.GetComponent<StaticMeshComponent>();
            cube.AddTag("Actor");
            if (cube.HasTag("Actor"))
            {
                Log.Print("Add cube have tag");
            }
            else
            {
                Log.Print("Actor have no tag");
            }
            cube.RemoveTag("Actor");
            if (cube.HasTag("Actor"))
            {
                Log.Print("Actor have tag");
            }
            else
            {
                Log.Print("Remove cube have no tag");
            }
        }
    }
}
