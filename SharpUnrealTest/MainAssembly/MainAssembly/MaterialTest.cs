using System;
using UnrealEngine;

namespace MainAssembly
{
    public class MaterialTest : ActorComponent
    {
        protected override void Initialize()
        {
            base.Initialize();
            TestDynamicMaterial();
        }

        private void TestDynamicMaterial()
        {
            var mesh = Actor.GetComponent<StaticMeshComponent>();
            if (mesh == null)
            {
                return;
            }
            var mat = mesh.GetMaterial(0);
            if (mat == null)
            {
                return;
            }

            var m = Resource.LoadMaterial("/Game/Materials/NewMaterial");
            if (m == null)
            {
                return;
            }

            var dm = DynamicMaterial.Create(m, Actor);
            if (dm == null)
            {
                return;
            }

            var tex = Resource.LoadTexture("/Game/Textures/Ground4");
            if (tex == null)
            {
                Log.Debug("tex != null.");
                return;
            }

            mesh.SetMaterial(0, dm);
            dm.SetTextureParameter("MainTex", tex);
        }

        private void TestMaterial()
        {
            var mesh = Actor.GetComponent<StaticMeshComponent>();
            if (mesh == null)
            {
                return;
            }
            var mat = mesh.GetMaterial(0);
            if (mat == null)
            {
                return;
            }

            var m = Resource.LoadMaterial("/Game/Materials/NewMaterial");
            if (m == null)
            {
                return;
            }

            mesh.SetMaterial(0, m);     
        }
    }
}

