#define  _CRT_SECURE_NO_WARNINGS
#include "stu.h"

int main() {
    STU head = NULL;        // ����ͷָ��
    int m = 0;              // �γ�����
    int first = 1;          // �״����б�־
    char ch;

    // ����̨��ʼ��
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
            if (first) { printf("�����������ݣ�\n"); break; }
            AppendRecord(&head, m);
            break;
        case 3:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            long id;
            printf("����Ҫɾ����ѧ�ţ�");
            scanf("%ld", &id);
            DeleteRecord(&head, id);
            break;
        case 4:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            printf("����Ҫ���ҵ�ѧ�ţ�");
            scanf("%ld", &id);
            STU target = SearchByNumber(head, id);
            if (target) PrintRecord(target, m);
            else printf("δ�ҵ�ѧ����\n");
            break;
        case 5:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            char name[NAME_LEN];
            printf("����Ҫ���ҵ�������");
            scanf("%s", name);
            SearchByName(head, name);
            break;
        case 6:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            ModifyRecord(head, m);
            break;
        case 7:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            CalculateScoreOfStudent(head, m);
            break;
        case 8:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            CalculateScoreOfCourse(head, m);
            break;
        case 9:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            SortByNumber(&head);
            break;
        case 10:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            SortByName(&head);
            break;
        case 11:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            SortByScore(&head, Descending);
            break;
        case 12:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            SortByScore(&head, Ascending);
            break;
        case 13:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            StatisticAnalysis(head, m);
            break;
        case 14:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
            PrintRecord(head, m);
            break;
        case 15:
            system("cls");
            if (first) { printf("�����������ݣ�\n"); break; }
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
            printf("�˳�ϵͳ��\n");
            exit(0);
        default:
            printf("��Чѡ�\n");
        }
        system("pause");
    }
    return 0;
}