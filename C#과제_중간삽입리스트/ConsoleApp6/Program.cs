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
        public int count;
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

        public Object Delete(int count) //count번째 노드 삭제
        {
            Node temp = new Node();
            Node cur = new Node();
            Node remo = new Node();
            Node test = new Node();

            cur = head;

            for (int i = 0; cur.next != null; i++)
            {
                if (cur.count == count - 1)
                {
                    temp = cur; //temp = 삭제될 노드 이전노드
                    cur = cur.next; //cur = 삭제될 노드
                    break;
                }
                else cur = cur.next;
            }

            remo = cur;
            if (temp == null)
            {
                test = head;
                Interlocked.CompareExchange(ref head, head.next, test); //head = head.next;
                head.count = 0;
                return remo.data;
            }
            else
            {
                test = temp.next;
                Interlocked.CompareExchange(ref temp.next, cur.next, test); //temp.next = cur.next;
                for (; cur.next != null; cur = cur.next)
                {
                    cur.count = count;
                    cur.next.count = count;
                }
                return remo.data;
            }
        }

        public void Add(int count, object data) //count 번째에 data 삽입
        {
            Node node = new Node();
            Node temp = new Node();
            Node cur = new Node();
            Node test = new Node();

            temp = head;
            node.data = data;

            if (head == null)
            {
                test = head;
                node.next = null;
                node.count = 0;
                Interlocked.CompareExchange(ref head, node, test); //head = node;
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    if (temp.count == count - 1)
                    {
                        test = node.next;
                        Interlocked.CompareExchange(ref node.next, temp.next, test); //node.next = temp.next;
                        test = temp.next;
                        Interlocked.CompareExchange(ref temp.next, node, test); //temp.next = node;
                        cur = node;
                        for (i = 0; cur.next != null; i++)
                        {
                            cur.count = count;
                            count++;
                            cur = cur.next;
                        }
                    }
                    else temp = temp.next;
                }
            }
        }
    }

    class Program
    {
        static LinkedList myList1 = new LinkedList();
        static DateTime start;
        static DateTime end;
        static int flag=0;
        
        static void ThreadBody()
        {
            if (flag == 0)
            {
                ++flag;
                for (int i = 1000; i > 0; i--)
                {
                    myList1.Add(1,i);
                }

                for (int i = 1000; i > 0; i--)
                {
                    myList1.Delete(1);
                }
                flag--;
            }
        }
        static void ThreadBody2()
        {
            if (flag == 0)
            {
                ++flag;
                for (int i = 1000; i > 0; i--)
                {
                    myList1.Add(1,i);
                }

                for (int i = 1000; i > 0; i--)
                {
                    myList1.Delete(1);
                }
                flag--;
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("2017920031 컴퓨터과학부 배은아");
            start = DateTime.Now;

            Thread t = new Thread(ThreadBody);
            t.Start();
            Thread t2 = new Thread(ThreadBody2);
            t2.Start();

            if (flag == 0)
            {
                ++flag;
                for (int i = 1000; i > 0; i--)
                {
                    myList1.Add(1,i);
                }
                for (int i = 1000; i > 0; i--)
                {
                    myList1.Delete(1);
                    //Console.Write("  " + myList1.Delete());
                }
                flag--;
            }
            t.Join();
            t2.Join();

            Console.Write("Remained data:");
            myList1.printAllNodes();
            Console.WriteLine();
            end = DateTime.Now;
            Console.WriteLine("finish: " + (end - start));


        }
    }
}