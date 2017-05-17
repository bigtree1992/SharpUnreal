using System;
using System.Collections.Generic;

namespace UnrealEngine
{
    public class Data
    {
        private static Dictionary<string,string> ms_SDict = new Dictionary<string, string>();
        private static Dictionary<string, int> ms_IDict = new Dictionary<string, int>();
        private static Dictionary<string, float> ms_FDict = new Dictionary<string, float>();
        private static Dictionary<string, Vector> ms_VDict = new Dictionary<string, Vector>();
        private static Dictionary<string, Rotator> ms_RDict = new Dictionary<string, Rotator>();
        private static Dictionary<string, Quat> ms_QDict = new Dictionary<string, Quat>();

        public static int GetInt(string key)
        {
            int result = 0;
            ms_IDict.TryGetValue(key, out result);
            return result;
        }

        public static void SetInt(string key,int value)
        {
            ms_IDict[key] = value;
        }

        public static float GetFloat(string key)
        {            
            float result = 0;
            ms_FDict.TryGetValue(key ,out result);
            return result;
        }

        public static void SetFloat(string key,float value)
        {
            ms_FDict[key] = value;
        }

        public static string GetString(string key)
        {
            string reslut;
            ms_SDict.TryGetValue(key, out reslut);
            return reslut;
        }

        public static void SetString(string key,string value)
        {
            ms_SDict[key] = value;
        }

        public static Vector GetVector(string key)
        {
            Vector reslut;
            ms_VDict.TryGetValue(key, out reslut);
            return reslut;
        }

        public static void SetString(string key, Vector value)
        {
            ms_VDict[key] = value;
        }

        public static Rotator GetRotator(string key)
        {
            Rotator reslut;
            ms_RDict.TryGetValue(key, out reslut);
            return reslut;
        }

        public static void SetRotator(string key, Rotator value)
        {
            ms_RDict[key] = value;
        }

        public static Quat GetQuat(string key)
        {
            Quat reslut;
            ms_QDict.TryGetValue(key, out reslut);
            return reslut;
        }

        public static void SetQuat(string key, Quat value)
        {
            ms_QDict[key] = value;
        }
    }
}
