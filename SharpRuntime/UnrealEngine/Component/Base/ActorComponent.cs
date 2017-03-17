using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnrealEngine
{
    public class ActorComponent : UObject
    {
        public ActorComponent()
        {
        }

        public bool Activited { get; set; }

        public bool CanEverTick { get; set; }

        public virtual void OnRegister()
        {          
        }

        public virtual void OnUnregister()
        {
        }

        public virtual void Initialize()
        {
        }

        public virtual void Uninitialize()
        {
        }

        public virtual void BeginPlay()
        {
        }

        public virtual void EndPlay()
        {
        }

        public virtual void Tick(float dt)
        {
        }

        public Actor GetOwner()
        {
            return null;
        }

        public bool ComponentHasTag(string tag)
        {
            return false;
        }

        public void SetTickableWhenPaused(bool bTickableWhenPaused)
        {
        }
    }
}
