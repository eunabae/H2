using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Test2019
{
    class Program
    {
        private static volatile int _val = 0;
        static void AddValue(int value)
        {
            while (true)
            {
                var orgVal = _val;
                var newVal = orgVal + value;
                if (Interlocked.CompareExchange(ref _val, newVal, orgVal) == orgVal)
                    break;
            }
        }
        static void ThreadBody()
        {
            for (int i = 0; i < 100000; i++)  // Main 스레드와 병행 수행
                _val++;
        }
        static void Main(string[] args)
        {
            Console.WriteLine("2017920031 컴퓨터과학부 배은아");
            Thread t = new Thread(ThreadBody);
            t.Start();
            Thread t2 = new Thread(ThreadBody);
            t2.Start();

            for (int i = 0; i < 100000; i++)  // 스레드 t와 병행 수행
                _val++;

            t.Join();
            t2.Join();
            Console.WriteLine(_val);
        }
    }
}