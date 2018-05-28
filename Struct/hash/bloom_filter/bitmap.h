#pragma once
#include<stdint.h>

typedef uint64_t BitmapType;
#define BitmapMaxSize 1000
typedef struct Bitmap
{
    uint64_t* data;
    uint64_t capacity;//位图最多能容纳多少位
}Bitmap;
//初始化
void BitmapInit(Bitmap* bm,uint64_t capacity);
//销毁
void BitmapDestroy(Bitmap* bm);
//将某一位设置为1
void BitmapSet(Bitmap* bm,uint64_t index);
//将某一位设置为0
void BitmapUnset(Bitmap* bm,uint64_t index);
//将所有位设置为1
void BitmapFill(Bitmap* bm);
//将所有位设置为0
void BitmapClear(Bitmap* bm);
//测试某一位是否为1
int BitmapTest(Bitmap* bm,uint64_t index);
