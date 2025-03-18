#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define COURSE_NUM 10   // 课程门数上限
#define NAME_LEN 10     // 姓名最大长度
#define POS_X1 35  //1.菜单页，第一列所有功能输出起始位置的x坐标值
//2.排序之后输出提示起点x坐标值
#define POS_X2 40 //输入模块的提示语句起点的x坐标值
#define POS_X3 50 //第一次调用输出模块或磁盘数据读入模块功能以外的其他功能，提示“系统中尚无学生成绩信息，请先输入！”的初始位置的x坐标值
#define POS_X4 65 //菜单页，第二列所有功能输出起始位置的x坐标值；
#define POS_Y 3   //排序之后输出提示起点的y坐标值

// 定义链表节点结构
typedef struct Node {
    long num;                   // 学号
    char name[NAME_LEN];        // 姓名
    float score[COURSE_NUM];    // 各科成绩
    float sum;                  // 总分
    float aver;                 // 平均分
    struct Node* next;          // 指向下一个节点的指针
} Node, * STU;

// 函数声明
int Menu(void);
void SetPosition(int x, int y);
void InputRecord(STU* head, int* m);
void AppendRecord(STU* head, int m);
void DeleteRecord(STU* head, long id);
STU SearchByNumber(STU head, long id);
void SearchByName(STU head, const char* name);
void ModifyRecord(STU head, int m);
void CalculateScoreOfStudent(STU head, int m);
void CalculateScoreOfCourse(STU head, int m);
void SortByNumber(STU* head);
void SortByName(STU* head);
void SortByScore(STU* head, int (*compare)(float, float));
int Ascending(float a, float b);
int Descending(float a, float b);
void StatisticAnalysis(STU head, int m);
void PrintRecord(STU head, int m);
void WriteToFile(STU head, int m);
STU ReadFromFile(int* m);
void FreeList(STU head);