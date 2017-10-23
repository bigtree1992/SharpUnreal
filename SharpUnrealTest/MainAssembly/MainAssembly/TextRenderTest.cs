using System;
using UnrealEngine;

namespace MainAssembly
{
    public class TextRenderTest : MonoComponent
    {
        protected override void BeginPlay()
        {
            base.BeginPlay();

            var text = Actor.GetComponent<TextRenderComponent>();
            if(text != null)
            {
                text.Text = "2456";
            }
        }


    }
}
