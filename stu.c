#define  _CRT_SECURE_NO_WARNINGS
#include "stu.h"

// �˵�����
int Menu(void) {
    int posy = 5;
    int option;
    int i, j;
    SetPosition(POS_X3, posy);
    printf("ѧ���ɼ�����ϵͳ\n");     //���ϵͳ����
    //���ϵͳ���ֺ͹���˵��֮������ж̺���
    for (i = 0; i < 2; i++)
    {

        SetPosition(POS_X1, ++posy);
        for (j = 0; j < 55; j++)
        {
            printf("-");
        }
    }
    //���ϵͳ֧�ֵĹ��ܺͶ�Ӧ�Ĺ��ܴ���
    SetPosition(POS_X1, ++posy);
    printf("1.����ѧ����Ϣ");
    SetPosition(POS_X4, posy);
    printf("2.����ѧ���ɼ�");
    SetPosition(POS_X1, posy += 2);
    printf("3.ɾ��ѧ����Ϣ");
    SetPosition(POS_X4, posy);
    printf("4.��ѧ�Ų��Ҽ�¼");
    SetPosition(POS_X1, posy += 2);
    printf("5.���������Ҽ�¼");
    SetPosition(POS_X4, posy);
    printf("6.�޸�ѧ����Ϣ");
    SetPosition(POS_X1, posy += 2);
    printf("7.����ѧ���ɼ�");
    SetPosition(POS_X4, posy);
    printf("8.����γ̳ɼ�");
    SetPosition(POS_X1, posy += 2);
    printf("9.��ѧ������");
    SetPosition(POS_X4, posy);
    printf("10.����������");
    SetPosition(POS_X1, posy += 2);
    printf("11.���ܳɼ���������");
    SetPosition(POS_X4, posy);
    printf("12.���ܳɼ���������");
    SetPosition(POS_X1, posy += 2);
    printf("13.ѧ���ɼ�ͳ��");
    SetPosition(POS_X4, posy);
    printf("14.��ӡѧ����¼");
    SetPosition(POS_X1, posy += 2);
    printf("15.ѧ����¼����");
    SetPosition(POS_X4, posy);
    printf("16.�Ӵ��̶�ȡѧ����¼");
    SetPosition(POS_X1, posy += 2);
    printf("0.�˳�");
    //���ϵͳ֧�ֵĹ�����������ʾ��֮������ж̺���
    for (i = 0; i < 2; i++)
    {
        SetPosition(POS_X1, ++posy);
        for (j = 0; j < 55; j++)
        {
            printf("-");
        }
    }
    //��ʾ�û�������Ҫִ�еĹ��ܴ���
    SetPosition(POS_X1, ++posy);
    printf("��ѡ������Ҫ���еĲ���[0-16]:[  ]\b\b\b");
    scanf("%d", &option);
    return option;
}

// ���ù��λ��
void SetPosition(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hOut, pos);
}

// ����ѧ����Ϣ����̬��������
void InputRecord(STU* head, int* m) {
    int n;
    printf("ѧ��������");
    scanf("%d", &n);
    printf("�γ�����");
    scanf("%d", m);

    STU tail = NULL;
    for (int i = 0; i < n; i++) {
        STU newNode = (STU)malloc(sizeof(Node));
        printf("����ѧ�š������͸��Ƴɼ���");
        scanf("%ld %s", &newNode->num, newNode->name);
        for (int j = 0; j < *m; j++) {
            scanf("%f", &newNode->score[j]);
        }
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

// ׷��ѧ����¼
void AppendRecord(STU* head, int m) {
    int num;
    printf("׷��������");
    scanf("%d", &num);

    STU tail = *head;
    while (tail && tail->next) tail = tail->next;

    for (int i = 0; i < num; i++) {
        STU newNode = (STU)malloc(sizeof(Node));
        printf("����ѧ�š������͸��Ƴɼ���");
        scanf("%ld %s", &newNode->num, newNode->name);
        for (int j = 0; j < m; j++) {
            scanf("%f", &newNode->score[j]);
        }
        newNode->next = NULL;

        if (!tail) {
            *head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
    }
}

// ɾ��ѧ����¼
void DeleteRecord(STU* head, long id) {
    STU prev = NULL, curr = *head;
    while (curr) {
        if (curr->num == id) {
            if (prev) prev->next = curr->next;
            else *head = curr->next;
            free(curr);
            printf("ɾ���ɹ���\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("δ�ҵ�ѧ����\n");
}

// ��ѧ�Ų���
STU SearchByNumber(STU head, long id) {
    STU curr = head;
    while (curr) {
        if (curr->num == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

// ����������
void SearchByName(STU head, const char* name) {
    STU curr = head;
    int found = 0;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            PrintRecord(curr, 0);  // ����ȫ����֪�γ���
            found = 1;
        }
        curr = curr->next;
    }
    if (!found) printf("δ�ҵ�ѧ����\n");
}

// �޸ļ�¼
void ModifyRecord(STU head, int m) {
    long id;
    printf("����ѧ�ţ�");
    scanf("%ld", &id);
    STU target = SearchByNumber(head, id);
    if (!target) { printf("δ�ҵ�ѧ����\n"); return; }

    printf("��������Ϣ��ѧ�� ���� �ɼ�����");
    scanf("%ld %s", &target->num, target->name);
    for (int j = 0; j < m; j++) {
        scanf("%f", &target->score[j]);
    }
}

// ����ѧ���ֺܷ�ƽ����
void CalculateScoreOfStudent(STU head, int m) {
    STU curr = head;
    while (curr) {
        curr->sum = 0;
        for (int j = 0; j < m; j++) curr->sum += curr->score[j];
        curr->aver = curr->sum / m;
        curr = curr->next;
    }
    printf("������ɣ�\n");
}

// ��ѧ�����򣨲�������
void SortByNumber(STU* head) {
    if (*head == NULL || (*head)->next == NULL) return;

    STU sorted = NULL;    // �����������ͷ�ڵ�
    STU current = *head;  // ��ǰ������ڵ�

    while (current != NULL) {
        STU next = current->next;  // ������һ��������ڵ�

        // ��current���뵽sorted�������ȷλ��
        if (sorted == NULL || sorted->num >= current->num) {
            // ���뵽sorted����ͷ��
            current->next = sorted;
            sorted = current;
        }
        else {
            // ��sorted�����в��Ҳ���λ��
            STU temp = sorted;
            while (temp->next != NULL && temp->next->num < current->num) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;  // ����ͷָ��
    printf("��ѧ��������ɣ�\n");
}

// ����������ð������
void SortByName(STU* head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    STU ptr1;
    STU lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->name, ptr1->next->name) > 0) {
                // �����ڵ����ݣ���ʵ�֣�ʵ��Ӧ�����ڵ�ָ�룩
                long tempNum = ptr1->num;
                char tempName[NAME_LEN];
                strcpy(tempName, ptr1->name);
                float tempScores[COURSE_NUM];
                memcpy(tempScores, ptr1->score, COURSE_NUM * sizeof(float));
                float tempSum = ptr1->sum;
                float tempAver = ptr1->aver;

                // ��ptr1->next���ݸ��Ƶ�ptr1
                ptr1->num = ptr1->next->num;
                strcpy(ptr1->name, ptr1->next->name);
                memcpy(ptr1->score, ptr1->next->score, COURSE_NUM * sizeof(float));
                ptr1->sum = ptr1->next->sum;
                ptr1->aver = ptr1->next->aver;

                // �������temp���ݸ��Ƶ�ptr1->next
                ptr1->next->num = tempNum;
                strcpy(ptr1->next->name, tempName);
                memcpy(ptr1->next->score, tempScores, COURSE_NUM * sizeof(float));
                ptr1->next->sum = tempSum;
                ptr1->next->aver = tempAver;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("������������ɣ�\n");
}

// ���ܷ�����֧������/����
void SortByScore(STU* head, int (*compare)(float, float)) {
    if (*head == NULL || (*head)->next == NULL) return;

    STU sorted = NULL;
    STU current = *head;

    while (current != NULL) {
        STU next = current->next;

        // ���Ҳ���λ��
        if (sorted == NULL || compare(current->sum, sorted->sum)) {
            current->next = sorted;
            sorted = current;
        }
        else {
            STU temp = sorted;
            while (temp->next != NULL && !compare(current->sum, temp->next->sum)) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
    printf("���ܷ�������ɣ�\n");
}

// �ȽϺ���
int Ascending(float a, float b) { return a < b; }
int Descending(float a, float b) { return a > b; }
// ͳ�Ƹ�����������
void StatisticAnalysis(STU head, int m) {
    if (head == NULL) {
        printf("��ѧ�����ݣ�\n");
        return;
    }

    // �γ̳ɼ�ͳ��
    for (int j = 0; j < m; j++) {
        int categories[6] = { 0 };  // <60, 60-69, 70-79, 80-89, 90-99, 100
        STU current = head;

        while (current != NULL) {
            float score = current->score[j];
            if (score < 60)        categories[0]++;
            else if (score < 70)   categories[1]++;
            else if (score < 80)   categories[2]++;
            else if (score < 90)   categories[3]++;
            else if (score < 100)  categories[4]++;
            else                   categories[5]++;
            current = current->next;
        }

        // ����γ�ͳ�ƽ��
        printf("\n�γ� %d �ɼ��ֲ���\n", j + 1);
        printf("------------------------------------------------\n");
        printf("������\t\t����\tռ��\n");
        for (int i = 0; i < 6; i++) {
            float percentage = (float)categories[i] / (float)GetListLength(head) * 100;
            switch (i) {
            case 0: printf("<60\t\t%d\t%.2f%%\n", categories[i], percentage); break;
            case 1: printf("60-69\t\t%d\t%.2f%%\n", categories[i], percentage); break;
            case 2: printf("70-79\t\t%d\t%.2f%%\n", categories[i], percentage); break;
            case 3: printf("80-89\t\t%d\t%.2f%%\n", categories[i], percentage); break;
            case 4: printf("90-99\t\t%d\t%.2f%%\n", categories[i], percentage); break;
            case 5: printf("100\t\t%d\t%.2f%%\n", categories[i], percentage); break;
            }
        }
    }

    // ƽ����ͳ��
    int avgCategories[6] = { 0 };
    STU current = head;
    while (current != NULL) {
        float avg = current->aver;
        if (avg < 60)        avgCategories[0]++;
        else if (avg < 70)   avgCategories[1]++;
        else if (avg < 80)   avgCategories[2]++;
        else if (avg < 90)   avgCategories[3]++;
        else if (avg < 100)  avgCategories[4]++;
        else                 avgCategories[5]++;
        current = current->next;
    }

    printf("\nѧ��ƽ���ֲַ���\n");
    printf("------------------------------------------------\n");
    printf("������\t\t����\tռ��\n");
    for (int i = 0; i < 6; i++) {
        float percentage = (float)avgCategories[i] / (float)GetListLength(head) * 100;
        switch (i) {
        case 0: printf("<60\t\t%d\t%.2f%%\n", avgCategories[i], percentage); break;
        case 1: printf("60-69\t\t%d\t%.2f%%\n", avgCategories[i], percentage); break;
        case 2: printf("70-79\t\t%d\t%.2f%%\n", avgCategories[i], percentage); break;
        case 3: printf("80-89\t\t%d\t%.2f%%\n", avgCategories[i], percentage); break;
        case 4: printf("90-99\t\t%d\t%.2f%%\n", avgCategories[i], percentage); break;
        case 5: printf("100\t\t%d\t%.2f%%\n", avgCategories[i], percentage); break;
        }
    }
}

// ������������ȡ������
int GetListLength(STU head) {
    int count = 0;
    STU current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// д���ļ�
void WriteToFile(STU head, int m) {
    FILE* fp = fopen("student.dat", "wb");
    if (fp == NULL) {
        printf("�ļ���ʧ�ܣ�\n");
        return;
    }

    // д��ѧ�������Ϳγ���
    int n = GetListLength(head);
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(&m, sizeof(int), 1, fp);

    // д��ÿ��ѧ������
    STU current = head;
    while (current != NULL) {
        fwrite(&current->num, sizeof(long), 1, fp);
        fwrite(current->name, sizeof(char), NAME_LEN, fp);
        fwrite(current->score, sizeof(float), m, fp);
        fwrite(&current->sum, sizeof(float), 1, fp);
        fwrite(&current->aver, sizeof(float), 1, fp);
        current = current->next;
    }

    fclose(fp);
    printf("�ɹ����� %d ����¼���ļ���\n", n);
}

// ��ȡ�ļ�
STU ReadFromFile(int* m) {
    FILE* fp = fopen("student.dat", "rb");
    if (fp == NULL) {
        printf("�ļ���ʧ�ܣ�\n");
        return NULL;
    }

    // ��ȡѧ�������Ϳγ���
    int n;
    fread(&n, sizeof(int), 1, fp);
    fread(m, sizeof(int), 1, fp);

    // ��������
    STU head = NULL, tail = NULL;
    for (int i = 0; i < n; i++) {
        STU newNode = (STU)malloc(sizeof(Node));
        fread(&newNode->num, sizeof(long), 1, fp);
        fread(newNode->name, sizeof(char), NAME_LEN, fp);
        fread(newNode->score, sizeof(float), *m, fp);
        fread(&newNode->sum, sizeof(float), 1, fp);
        fread(&newNode->aver, sizeof(float), 1, fp);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
    printf("�ɹ����ļ����� %d ����¼��\n", n);
    return head;
}
void FreeList(STU head) {
    STU current = head;
    while (current != NULL) {
        STU temp = current;
        current = current->next;
        free(temp);
    }
}
/**
 * �������ܣ���ӡ����ѧ����¼
 * ����˵����
 *   - head: ����ͷָ��
 *   - m: �γ�����
 */
void PrintRecord(STU head, int m) {
    if (head == NULL) {
        printf("��ѧ����¼�ɴ�ӡ��\n");
        return;
    }

    // ��ӡ��ͷ
    printf("\n%-12s%-12s", "ѧ��", "����");
    for (int j = 0; j < m; j++) {
        printf("�γ�%-6d", j + 1);
    }
    printf("%-10s%-10s\n", "�ܷ�", "ƽ����");
    printf("------------------------------------------------------------\n");

    // ���������ӡÿ��ѧ����Ϣ
    STU current = head;
    while (current != NULL) {
        printf("%-12ld%-12s", current->num, current->name);
        for (int j = 0; j < m; j++) {
            printf("%-8.1f ", current->score[j]);
        }
        printf("%-10.1f%-10.1f\n", current->sum, current->aver);
        current = current->next;
    }
}
/**
 * �������ܣ�����ÿ�ſγ̵��ֺܷ�ƽ����
 * ����˵����
 *   - head: ����ͷָ��
 *   - m: �γ�����
 */
void CalculateScoreOfCourse(STU head, int m) {
    if (head == NULL || m <= 0) {
        printf("����Ч���ݿɼ��㣡\n");
        return;
    }

    // ��ʼ���γ��ܷ�����
    float courseSum[COURSE_NUM] = { 0 };
    int studentCount = 0;

    // ���������ۼ�ÿ�ſγ̳ɼ�
    STU current = head;
    while (current != NULL) {
        for (int j = 0; j < m; j++) {
            courseSum[j] += current->score[j];
        }
        studentCount++;
        current = current->next;
    }

    // ���㲢��ӡ���
    printf("\n%-12s%-12s%-12s\n", "�γ̱��", "�ܷ�", "ƽ����");
    printf("------------------------------------\n");
    for (int j = 0; j < m; j++) {
        float average = (studentCount > 0) ? courseSum[j] / studentCount : 0;
        printf("�γ�%-8d%-12.1f%-12.1f\n", j + 1, courseSum[j], average);
    }
}