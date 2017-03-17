using System;
using System.IO;

namespace MainAssembly
{
    internal class FLog
    {
        static FileStream ostrm;
        static StreamWriter writer;

        internal static void SetLogToFile()
        {
            try
            {
                string filename = "QLog-" + DateTime.Now.ToString("yyyy-MM-dd") + ".txt";

                string path = Path.GetFullPath("D:\\Log\\");
                if (!Directory.Exists(path))
                {
                    Directory.CreateDirectory(path);
                }

                ostrm = new FileStream("D:\\Log\\" + filename, FileMode.Append, FileAccess.Write);
                writer = new StreamWriter(ostrm);
                writer.AutoFlush = true;
            }
            catch (Exception e)
            {
                Console.WriteLine("[Log] Cannot open QLog.txt for writing.");
                Console.WriteLine(e.Message);
                return;
            }
            Console.SetOut(writer);
        }

        internal static void WriteLog(string level, string content)
        {
            Console.WriteLine("[{0}] {1} {2}", level, DateTime.Now.ToString("hh.mm.ss"), content);
        }

        internal static void Warning(string content)
        {
            WriteLog("Warning", content);
        }

        internal static void Debug(string content)
        {
            WriteLog("Debug", content);
        }

        internal static void Error(string content)
        {
            WriteLog("Error", content);
        }
    }
}
