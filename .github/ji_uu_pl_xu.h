#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct knote
{
    struct knote* next;
    int val;
} knote, * link;
//定义节点结构体

typedef struct head_rear
{
    int max_digit;
    int length;
    link head;
    link rear;
} all;
//定义包含链表头尾，长度的结构体，方便修改和查找

typedef struct one_ten
{
    all ten[10];
} scoreboard;
//此结构体用来存储每次分类的链表

void initial_all(all& a)
{
    a.max_digit = 0;
    a.length = 0;
    a.head = NULL;
    a.rear = NULL;
}
//初始化all

void initial_knot(knote& c)
{
    c.val = 0;
    c.next = NULL;
}
//初始化节点结构体

void last_insert(all& a, int b)
{
    link c = (link)malloc(sizeof(knote));
    initial_knot(*c);
    c->val = b;
    if (a.length == 0)
    {
        a.head = c;
        a.rear = c;
        a.length++;
    }
    else
    {
        a.rear->next = c;
        a.rear = c;
        a.length++;
    }
}
//把一个数据输入到all中

void input_original(all& a)
{
    int b;
    int input_OK;
    int max_data = 0;
    while (1)
    {
        input_OK = scanf("%d", &b);
        if (input_OK == 1 && b >= 0)
        {
            if (b == 99999)
            {
                printf("--------------------\n");
                printf("初始数据已全部输入\n");
                printf("已成功输入%d个数据\n", a.length);
                printf("初始链表输入模式已结束\n");
                printf("--------------------\n");
                if (max_data == 0)
                {
                    a.max_digit = 0;
                    printf("输入的数据中，最大的有%d位", a.max_digit);
                }
                else
                {
                    (a.max_digit) = (int)log10((double)(max_data)) + 1;
                    printf("输入的数据中，最大的有%d位", a.max_digit);
                }
                break;
            }
            if (b > max_data)
            {
                max_data = b;
            }
            last_insert(a, b);
            printf("数据“%d”已进入初始链表\n", b);
        }
        else
        {
            int key_in;
            while ((key_in = getchar()) != '\n' && key_in != EOF);
            printf("输入错误，请输入一个非负整数。\n");
        }
    }
}
//往all里面输入数据b，并由此构建链表,找出位数最高的数据的位数

void link_last_insert(all& original, all& b)
{
    if (original.head == NULL)
    {
        return;
    }

    link p = original.head;
    original.head = original.head->next;
    p->next = NULL;
    if (b.rear == NULL)
    {
        b.head = p;
        b.rear = p;
    }
    else
    {
        b.rear->next = p;
        b.rear = p;
    }
    if (original.head==NULL)
    {
        original.rear = NULL;
    }
}

void connect(all& a, all& b)//把a链表的尾节点焊接在b节点的头节点上
{
    if (a.rear == NULL)
    {
        a.head = b.head;
        a.rear = b.rear;
        return;
    }
    else
    {
        if (b.rear == NULL || b.head == NULL)
        {
            return;
        }
        else
        {
            a.rear->next = b.head;
            a.rear = b.rear;
        }
    }
}

void output_link(all original)
{
    printf("\n");
    link p = original.head;
    if (p == NULL)
    {
        return;
    }
    while (p != NULL)
    {
        printf(" %d ", p->val);
        p = p->next;
    }
}

//接下来是对数据进行分类
void classify(all& original, scoreboard& ot)
{
    link p = original.head;
    int a = 10, b = 1, c = 0;
    //a是高位求余数的除数，除去高位的影响
    //b是低位求商的除数，除去低位的影响
    //c是低位求商的结果，就是我们要求的数
    for (int i = 0; i < original.max_digit; i++)
    {
        p = original.head;

        while (p != NULL)
        {
            c = ((p->val) % a) / b;
            //接下来安排一个插入函数，把original里面的当前节点尾插插入到ten里面
            link_last_insert(original, ot.ten[c]);
            p = original.head;
        }
        a = a * 10;
        b = b * 10;
        original.head = ot.ten[0].head;
        connect(original, ot.ten[0]);
        initial_all(ot.ten[0]);
        connect(original, ot.ten[1]);
        initial_all(ot.ten[1]);
        connect(original, ot.ten[2]);
        initial_all(ot.ten[2]);
        connect(original, ot.ten[3]);
        initial_all(ot.ten[3]);
        connect(original, ot.ten[4]);
        initial_all(ot.ten[4]);
        connect(original, ot.ten[5]);
        initial_all(ot.ten[5]);
        connect(original, ot.ten[6]);
        initial_all(ot.ten[6]);
        connect(original, ot.ten[7]);
        initial_all(ot.ten[7]);
        connect(original, ot.ten[8]);
        initial_all(ot.ten[8]);
        connect(original, ot.ten[9]);
        initial_all(ot.ten[9]);
    }
}