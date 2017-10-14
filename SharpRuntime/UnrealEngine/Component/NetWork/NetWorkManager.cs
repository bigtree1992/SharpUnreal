using System;
using System.Runtime.CompilerServices;

namespace UnrealEngine
{
    public class NetWorkManager: MonoComponent
    {
        #region CallBack

        protected virtual void OnStartOnlieGameComplete(bool bSuccess) {}

        protected virtual void OnFindOnlieGameComplete(bool bSuccess) {}

        protected virtual void OnJoinOnlieGameComplete(bool bSuccess) {}

        protected virtual void OnDestroyOnlieGameComplete(bool bSuccess) {}

        #endregion

        protected void StartOnlineGame(string mapName, int playerNum)
        {
            _StartOnlineGame(NativeHandler,mapName, playerNum);
        }

        protected void FindOnlineGame()
        {
            _FindOnlineGame(NativeHandler);
        }

        protected void JoinOnlineGame()
        {
            _JoinOnlineGame(NativeHandler);
        }

        protected void DestroySessionAndLeaveGame()
        {
            _DestroySessionAndLeaveGame(NativeHandler);
        }

        protected int GetOnlineGamePlayerNum()
        {
            return _GetOnlineGamePlayerNum(NativeHandler);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _StartOnlineGame(IntPtr handler, string mapName, int playerNum);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _FindOnlineGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _JoinOnlineGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static void _DestroySessionAndLeaveGame(IntPtr handler);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern static int _GetOnlineGamePlayerNum(IntPtr handler);
    }
}
