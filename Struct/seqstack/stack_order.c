#include <stdio.h>
#include<stddef.h>
#include"seqstack.h"
//返回1表示能够变换成功
//返回0表示不能变换成功
int StackOrder(char input[],size_t input_size,char output[],size_t output_size)
{
    SeqStack stack;
    SeqStackInit(&stack);
    //循环的把input的元素入栈
    size_t i = 0;
    size_t output_index = 0;
        char top;
    for(;i < input_size;++i)
    {
        SeqStackPush(&stack,input[i]);
        int ret = SeqStackTop(&stack,&top);
        if(ret == 0)
        {
            //栈已空,准备进行最终审判
            break;
        }
        //取栈顶元素，和output_index指向的元素比较
        while(1)
        {
            if(output_index >= output_size )
            {
                //output序列已经遍历完了，也得进行最终审判
                break;
            }
            if(top != output[output_index])
            {
                break;
            }
            ++output_index;
            SeqStackPop(&stack);
        }
    }
    while(1)
     {
        //如果不相等，继续循化取下一个input元素入栈
        //如果相等
        //a）移进output_index
        //b) 把栈顶元素出栈
        //c）循环的比较栈顶元素和output_index指向的元素的值
        SeqStackTop(&stack,&top);
        if(output_index >= output_size)
        {
             //output序列已经遍历完了，也得进行最终审判
               break;
         }
        if(top != output[output_index])
        {
             break;
         }
        ++output_index;
         SeqStackPop(&stack);
    }
  //如果最终栈为空并且output_index指向output数组中的最后一个元素，就认为能够变换得到
    //否则就无法变换得到
    if(stack.size == 0 && output_index == output_size)
    {
        return 1;
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n======================================%s===================================\n",__FUNCTION__);

void TestStackOrder()
{
    TEST_HEADER;
    char input[5] = {'a','b','c','d','e'};
    char output1[5] = {'d','e','c','b','a'};
    char output2[5] = {'a','b','c','d','e'};
    char output3[5] = {'e','d','c','b','a'};
    char output4[5] = {'d','e','a','b','c'};
    int size_in = sizeof(input);
    int size_out1 = sizeof(output1);
    int size_out2 = sizeof(output2);
    int size_out3 = sizeof(output3);
    int size_out4 = sizeof(output4);
    int ret = StackOrder(input,size_in,output1,size_out1);
    printf("ret : expected 1,actual %d\n",ret);
    ret = StackOrder(input,size_in,output2,size_out2);
    printf("ret : expected 1,actual %d\n",ret);
    ret = StackOrder(input,size_in,output3,size_out3);
    printf("ret : expected 1,actual %d\n",ret);
    ret = StackOrder(input,size_in,output4,size_out4);
    printf("ret : expected 0,actual %d\n",ret);
}
int main()
{
    TestStackOrder();
    return 0;
}
#endif
