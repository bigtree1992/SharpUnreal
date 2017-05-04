using System;
using UnrealEngine;

namespace MainAssembly
{
    public class MaterialTest : ActorComponent
    {
        protected override void Initialize()
        {
            TestDynamicMaterial();
        }

        /// <summary>
        /// 测试加载一个动态的可以设置参数的材质
        /// </summary>
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

            var m = Resource.LoadMaterial("/Materials/NewMaterial");
            if (m == null)
            {
                return;
            }

            var dm = DynamicMaterial.Create(m, Actor);
            if (dm == null)
            {
                return;
            }

            var tex = Resource.LoadTexture("/Textures/Ground4");
            if (tex == null)
            {
                Log.Debug("tex != null.");
                return;
            }

            mesh.SetMaterial(0, dm);
            dm.SetTextureParameter("MainTex", tex);
        }

        /// <summary>
        /// 测试动态加载一个静态材质
        /// </summary>
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

            var m = Resource.LoadMaterial("/Materials/NewMaterial");
            if (m == null)
            {
                return;
            }

            mesh.SetMaterial(0, m);     
        }
    }
}

