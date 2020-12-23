using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Test2019
{
    public class Node
    {
        public Node next;
        public Object data;
    }

    public class LinkedList
    {
        private Node head;
        static int count = -1;

        public void printAllNodes()
        {
            Node current = head;
            while (current != null)
            {
                Console.Write("  " + current.data);
                current = current.next;
            }
        }

        public Object Delete()
        {
            if (count < 0)
            {
                return null;
            }
            else
            {
                Node temp = new Node();
                temp = head;
                object data = temp.data;
                head = temp.next;
                temp = null;
                return data;
            }
        }

        public void AddLast(Object data)
        {
            Node temp = new Node();
            temp.data = data;
            temp.next = head;
            head = temp;
            count++;
        }

    }

    class Program
    {
        static LinkedList myList1 = new LinkedList();
        private static Mutex mut = new Mutex();

        static DateTime start;
        static DateTime end;

        static void ThreadBody()
        {
            mut.WaitOne();
            for (int i = 100000; i > 0; i--)
            {             
                myList1.AddLast(i);
                //Thread.Sleep(10);              
            }

            for (int i = 99999; i > 0; i--)
            {              
                myList1.Delete();
                //Thread.Sleep(10);            
            }
            mut.ReleaseMutex();
        }

        static void ThreadBody2()
        {
            mut.WaitOne();
            for (int i = 100000; i > 0; i--)
            {              
                myList1.AddLast(i);
                //Thread.Sleep(10);              
            }

            for (int i = 99999; i > 0; i--)
            {               
                myList1.Delete();
                //Thread.Sleep(10);              
            }
            mut.ReleaseMutex();
        }

        static void Main(string[] args)
        {
            start = DateTime.Now;
            Thread t = new Thread(ThreadBody);
            t.Start();
            Thread t2 = new Thread(ThreadBody2);
            t2.Start();

            mut.WaitOne();
            for (int i = 100000; i > 0; i--)
            {
                  myList1.AddLast(i);
                //Thread.Sleep(10);             
            }

            for (int i = 99999; i > 0; i--)
            {       
                myList1.Delete();
                //Console.Write("  " + myList1.Delete());
                //Thread.Sleep(10);          
            }
            mut.ReleaseMutex();

            t.Join();
            t2.Join();

            end = DateTime.Now;
            Console.WriteLine("\n finish: " + (end - start));
            Console.WriteLine("Remained data: ");
            myList1.printAllNodes();
        }
    }
}