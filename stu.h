#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define COURSE_NUM 10   // �γ���������
#define NAME_LEN 10     // ������󳤶�
#define POS_X1 35  //1.�˵�ҳ����һ�����й��������ʼλ�õ�x����ֵ
//2.����֮�������ʾ���x����ֵ
#define POS_X2 40 //����ģ�����ʾ�������x����ֵ
#define POS_X3 50 //��һ�ε������ģ���������ݶ���ģ�鹦��������������ܣ���ʾ��ϵͳ������ѧ���ɼ���Ϣ���������룡���ĳ�ʼλ�õ�x����ֵ
#define POS_X4 65 //�˵�ҳ���ڶ������й��������ʼλ�õ�x����ֵ��
#define POS_Y 3   //����֮�������ʾ����y����ֵ

// ��������ڵ�ṹ
typedef struct Node {
    long num;                   // ѧ��
    char name[NAME_LEN];        // ����
    float score[COURSE_NUM];    // ���Ƴɼ�
    float sum;                  // �ܷ�
    float aver;                 // ƽ����
    struct Node* next;          // ָ����һ���ڵ��ָ��
} Node, * STU;

// ��������
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