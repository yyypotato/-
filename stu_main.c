#define  _CRT_SECURE_NO_WARNINGS
#include "stu.h"

int main() {
    STU head = NULL;        // 链表头指针
    int m = 0;              // 课程数量
    int first = 1;          // 首次运行标志
    char ch;

    // 控制台初始化
    system("mode con cols=130 lines=60");
    system("color 0E");

    while (1) {
        system("cls");
        ch = Menu();
        switch (ch) {
        case 1:
            system("cls");
            InputRecord(&head, &m);
            first = 0;
            break;
        case 2:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            AppendRecord(&head, m);
            break;
        case 3:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            long id;
            printf("输入要删除的学号：");
            scanf("%ld", &id);
            DeleteRecord(&head, id);
            break;
        case 4:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            printf("输入要查找的学号：");
            scanf("%ld", &id);
            STU target = SearchByNumber(head, id);
            if (target) PrintRecord(target, m);
            else printf("未找到学生！\n");
            break;
        case 5:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            char name[NAME_LEN];
            printf("输入要查找的姓名：");
            scanf("%s", name);
            SearchByName(head, name);
            break;
        case 6:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            ModifyRecord(head, m);
            break;
        case 7:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            CalculateScoreOfStudent(head, m);
            break;
        case 8:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            CalculateScoreOfCourse(head, m);
            break;
        case 9:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            SortByNumber(&head);
            break;
        case 10:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            SortByName(&head);
            break;
        case 11:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            SortByScore(&head, Descending);
            break;
        case 12:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            SortByScore(&head, Ascending);
            break;
        case 13:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            StatisticAnalysis(head, m);
            break;
        case 14:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            PrintRecord(head, m);
            break;
        case 15:
            system("cls");
            if (first) { printf("请先输入数据！\n"); break; }
            WriteToFile(head, m);
            break;
        case 16:
            system("cls");
            FreeList(head);
            head = ReadFromFile(&m);
            if (head) first = 0;
            break;
        case 0:
            FreeList(head);
            printf("退出系统！\n");
            exit(0);
        default:
            printf("无效选项！\n");
        }
        system("pause");
    }
    return 0;
}