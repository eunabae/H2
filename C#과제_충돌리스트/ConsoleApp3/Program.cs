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

        public void printAllNodes()
        {
            Node current = head;
            while (current != null)
            {
                Console.Write("  " + current.data);
                current = current.next;
            }
            Console.WriteLine();
        }

        public Object Delete()
        {
            Node cur = new Node();
            cur = head;
            while (cur != null)
            {
                if (head == Interlocked.CompareExchange(ref head, cur.next, cur))
                {
                    return cur.data;
                }
                cur = head;
            }
            return null;
        }

        public void AddLast(Node newnode)
        {
            do
            {
                Node temp = new Node();
                temp.data = newnode.data;
                temp.next = head;
                Interlocked.CompareExchange(ref head, temp, head);
            } while (head.data != newnode.data);
        }

    }

    class Program
    {
        static LinkedList myList1 = new LinkedList();
        static Node node = new Node();
        static int flag = 0;
        static DateTime start;
        static DateTime end;

        static void ThreadBody()
        {
            if (flag == 0)
            {
                ++flag;
                for (int i = 100000; i > 0; i--)
                {
                    node.data = i;
                    myList1.AddLast(node);
                }

                for (int i = 99999; i > 0; i--)
                {
                    myList1.Delete();
                }
                flag--;
            }
        }
        static void ThreadBody2()
        {
            if (flag == 0)
            {
                ++flag;
                for (int i = 100000; i > 0; i--)
                {
                    node.data = i;
                    myList1.AddLast(node);
                }

                for (int i = 99999; i > 0; i--)
                {
                    myList1.Delete();
                }
                flag--;
            }
        }

        static void Main(string[] args)
        {
            start = DateTime.Now;

            //Thread t = new Thread(ThreadBody);
            //t.Start();
            //Thread t2 = new Thread(ThreadBody2);
            //t2.Start();

            if (flag == 0)
            {
                ++flag;
                for (int i = 10; i > 0; i--)
                {
                    node.data = i;
                    myList1.AddLast(node);
                }

                for (int i = 9; i > 0; i--)
                {
                    myList1.Delete();
                    //Console.Write("  " + myList1.Delete());
                }
                flag--;
            }

            //t.Join();
            //t2.Join();

            //Console.WriteLine();
            end = DateTime.Now;
            Console.WriteLine("finish: " + (end - start));
            Console.WriteLine("Remained data: ");
            myList1.printAllNodes();

        }
    }
}