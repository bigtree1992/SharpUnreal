using System;
using System.Collections.Generic;
using System.IO;

namespace CodeGen
{
    class Program
    {
        static void Main(string[] args)
        {
            if(args.Length < 1)
            {
                Console.WriteLine("没有输入的文件。");
            }

            string filename = args[0];
            Console.WriteLine("输入的文件:" + args[0]);
            var codegen = new CodeGen.CodeGender();
            codegen.Process(filename);
            codegen.PrintAllData();
            codegen.GenerateCS();
            codegen.GenerateCPP();

        }


        

    }
}
