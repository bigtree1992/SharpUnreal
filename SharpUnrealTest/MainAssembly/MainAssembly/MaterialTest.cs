using System;
using UnrealEngine;

namespace MainAssembly
{
    /// <summary>
    /// 测试材质相关的功能
    /// </summary>
    public class MaterialTest : ActorComponent
    {
        protected override void Initialize()
        {
            TestMaterial();
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
                Log.Error("[MaterialTest] mesh is null");
            }

            mesh.SetScalarParameter("ChooseType", 0.0f);

            var mat = mesh.GetMaterial(2);
            if (mat == null)
            {
                Log.Error("[MaterialTest] get mat is null");
            }

            var m = Resource.LoadMaterial("Resources/UI/选人/Material__72");
            if(m == null)
            {
                Log.Error("[MaterialTest] load mat is null");
            }

            var dm = DynamicMaterial.Create(m, Actor);
            if (dm == null)
            {
                Log.Error("[MaterialTest] create DynamicMaterial is null");
            }

            var tex = Resource.LoadTexture("Resources/Textures/Ground4");
            if (tex == null)
            {
                Log.Error("[MaterialTest] LoadTexture is null");
                return;
            }

            mesh.SetMaterial(2, dm);
            dm.SetTextureParameter("Texture", tex);
        }

        /// <summary>
        /// 测试动态加载一个静态材质
        /// </summary>
        private void TestMaterial()
        {
            var mesh = Actor.GetComponent<StaticMeshComponent>();
            if (mesh == null)
            {
                Log.Error("[MaterialTest] mesh is null");
            }
            var mat = mesh.GetMaterial(0);
            if (mat == null)
            {
                Log.Error("[MaterialTest] mat is null");
            }

            var m = Resource.LoadMaterial("Resources/UI/选人/Standard_7");
            if (m == null)
            {
                Log.Error("[MaterialTest] load mat is null");
            }

            mesh.SetMaterial(0, m);     
        }
    }
}

