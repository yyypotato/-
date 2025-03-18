#define  _CRT_SECURE_NO_WARNINGS
#include "stu.h"

// 菜单函数
int Menu(void) {
    int posy = 5;
    int option;
    int i, j;
    SetPosition(POS_X3, posy);
    printf("学生成绩管理系统\n");     //输出系统名字
    //输出系统名字和功能说明之间的两行短横线
    for (i = 0; i < 2; i++)
    {

        SetPosition(POS_X1, ++posy);
        for (j = 0; j < 55; j++)
        {
            printf("-");
        }
    }
    //输出系统支持的功能和对应的功能代号
    SetPosition(POS_X1, ++posy);
    printf("1.输入学生信息");
    SetPosition(POS_X4, posy);
    printf("2.增加学生成绩");
    SetPosition(POS_X1, posy += 2);
    printf("3.删除学生信息");
    SetPosition(POS_X4, posy);
    printf("4.按学号查找记录");
    SetPosition(POS_X1, posy += 2);
    printf("5.按姓名查找记录");
    SetPosition(POS_X4, posy);
    printf("6.修改学生信息");
    SetPosition(POS_X1, posy += 2);
    printf("7.计算学生成绩");
    SetPosition(POS_X4, posy);
    printf("8.计算课程成绩");
    SetPosition(POS_X1, posy += 2);
    printf("9.按学号排序");
    SetPosition(POS_X4, posy);
    printf("10.按姓名排序");
    SetPosition(POS_X1, posy += 2);
    printf("11.按总成绩降序排序");
    SetPosition(POS_X4, posy);
    printf("12.按总成绩升序排序");
    SetPosition(POS_X1, posy += 2);
    printf("13.学生成绩统计");
    SetPosition(POS_X4, posy);
    printf("14.打印学生记录");
    SetPosition(POS_X1, posy += 2);
    printf("15.学生记录存盘");
    SetPosition(POS_X4, posy);
    printf("16.从磁盘读取学生记录");
    SetPosition(POS_X1, posy += 2);
    printf("0.退出");
    //输出系统支持的功能与输入提示语之间的两行短横线
    for (i = 0; i < 2; i++)
    {
        SetPosition(POS_X1, ++posy);
        for (j = 0; j < 55; j++)
        {
            printf("-");
        }
    }
    //提示用户输入所要执行的功能代号
    SetPosition(POS_X1, ++posy);
    printf("请选择你想要进行的操作[0-16]:[  ]\b\b\b");
    scanf("%d", &option);
    return option;
}

// 设置光标位置
void SetPosition(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hOut, pos);
}

// 输入学生信息（动态创建链表）
void InputRecord(STU* head, int* m) {
    int n;
    printf("学生人数：");
    scanf("%d", &n);
    printf("课程数：");
    scanf("%d", m);

    STU tail = NULL;
    for (int i = 0; i < n; i++) {
        STU newNode = (STU)malloc(sizeof(Node));
        printf("输入学号、姓名和各科成绩：");
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

// 追加学生记录
void AppendRecord(STU* head, int m) {
    int num;
    printf("追加人数：");
    scanf("%d", &num);

    STU tail = *head;
    while (tail && tail->next) tail = tail->next;

    for (int i = 0; i < num; i++) {
        STU newNode = (STU)malloc(sizeof(Node));
        printf("输入学号、姓名和各科成绩：");
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

// 删除学生记录
void DeleteRecord(STU* head, long id) {
    STU prev = NULL, curr = *head;
    while (curr) {
        if (curr->num == id) {
            if (prev) prev->next = curr->next;
            else *head = curr->next;
            free(curr);
            printf("删除成功！\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("未找到学生！\n");
}

// 按学号查找
STU SearchByNumber(STU head, long id) {
    STU curr = head;
    while (curr) {
        if (curr->num == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

// 按姓名查找
void SearchByName(STU head, const char* name) {
    STU curr = head;
    int found = 0;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            PrintRecord(curr, 0);  // 假设全局已知课程数
            found = 1;
        }
        curr = curr->next;
    }
    if (!found) printf("未找到学生！\n");
}

// 修改记录
void ModifyRecord(STU head, int m) {
    long id;
    printf("输入学号：");
    scanf("%ld", &id);
    STU target = SearchByNumber(head, id);
    if (!target) { printf("未找到学生！\n"); return; }

    printf("输入新信息（学号 姓名 成绩）：");
    scanf("%ld %s", &target->num, target->name);
    for (int j = 0; j < m; j++) {
        scanf("%f", &target->score[j]);
    }
}

// 计算学生总分和平均分
void CalculateScoreOfStudent(STU head, int m) {
    STU curr = head;
    while (curr) {
        curr->sum = 0;
        for (int j = 0; j < m; j++) curr->sum += curr->score[j];
        curr->aver = curr->sum / m;
        curr = curr->next;
    }
    printf("计算完成！\n");
}

// 按学号排序（插入排序）
void SortByNumber(STU* head) {
    if (*head == NULL || (*head)->next == NULL) return;

    STU sorted = NULL;    // 已排序链表的头节点
    STU current = *head;  // 当前待排序节点

    while (current != NULL) {
        STU next = current->next;  // 保存下一个待处理节点

        // 将current插入到sorted链表的正确位置
        if (sorted == NULL || sorted->num >= current->num) {
            // 插入到sorted链表头部
            current->next = sorted;
            sorted = current;
        }
        else {
            // 在sorted链表中查找插入位置
            STU temp = sorted;
            while (temp->next != NULL && temp->next->num < current->num) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;  // 更新头指针
    printf("按学号排序完成！\n");
}

// 按姓名排序（冒泡排序）
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
                // 交换节点数据（简化实现，实际应交换节点指针）
                long tempNum = ptr1->num;
                char tempName[NAME_LEN];
                strcpy(tempName, ptr1->name);
                float tempScores[COURSE_NUM];
                memcpy(tempScores, ptr1->score, COURSE_NUM * sizeof(float));
                float tempSum = ptr1->sum;
                float tempAver = ptr1->aver;

                // 将ptr1->next数据复制到ptr1
                ptr1->num = ptr1->next->num;
                strcpy(ptr1->name, ptr1->next->name);
                memcpy(ptr1->score, ptr1->next->score, COURSE_NUM * sizeof(float));
                ptr1->sum = ptr1->next->sum;
                ptr1->aver = ptr1->next->aver;

                // 将保存的temp数据复制到ptr1->next
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
    printf("按姓名排序完成！\n");
}

// 按总分排序（支持升序/降序）
void SortByScore(STU* head, int (*compare)(float, float)) {
    if (*head == NULL || (*head)->next == NULL) return;

    STU sorted = NULL;
    STU current = *head;

    while (current != NULL) {
        STU next = current->next;

        // 查找插入位置
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
    printf("按总分排序完成！\n");
}

// 比较函数
int Ascending(float a, float b) { return a < b; }
int Descending(float a, float b) { return a > b; }
// 统计各分数段人数
void StatisticAnalysis(STU head, int m) {
    if (head == NULL) {
        printf("无学生数据！\n");
        return;
    }

    // 课程成绩统计
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

        // 输出课程统计结果
        printf("\n课程 %d 成绩分布：\n", j + 1);
        printf("------------------------------------------------\n");
        printf("分数段\t\t人数\t占比\n");
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

    // 平均分统计
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

    printf("\n学生平均分分布：\n");
    printf("------------------------------------------------\n");
    printf("分数段\t\t人数\t占比\n");
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

// 辅助函数：获取链表长度
int GetListLength(STU head) {
    int count = 0;
    STU current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// 写入文件
void WriteToFile(STU head, int m) {
    FILE* fp = fopen("student.dat", "wb");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }

    // 写入学生人数和课程数
    int n = GetListLength(head);
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(&m, sizeof(int), 1, fp);

    // 写入每个学生数据
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
    printf("成功保存 %d 条记录到文件！\n", n);
}

// 读取文件
STU ReadFromFile(int* m) {
    FILE* fp = fopen("student.dat", "rb");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return NULL;
    }

    // 读取学生人数和课程数
    int n;
    fread(&n, sizeof(int), 1, fp);
    fread(m, sizeof(int), 1, fp);

    // 创建链表
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
    printf("成功从文件加载 %d 条记录！\n", n);
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
 * 函数功能：打印所有学生记录
 * 参数说明：
 *   - head: 链表头指针
 *   - m: 课程门数
 */
void PrintRecord(STU head, int m) {
    if (head == NULL) {
        printf("无学生记录可打印！\n");
        return;
    }

    // 打印表头
    printf("\n%-12s%-12s", "学号", "姓名");
    for (int j = 0; j < m; j++) {
        printf("课程%-6d", j + 1);
    }
    printf("%-10s%-10s\n", "总分", "平均分");
    printf("------------------------------------------------------------\n");

    // 遍历链表打印每个学生信息
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
 * 函数功能：计算每门课程的总分和平均分
 * 参数说明：
 *   - head: 链表头指针
 *   - m: 课程门数
 */
void CalculateScoreOfCourse(STU head, int m) {
    if (head == NULL || m <= 0) {
        printf("无有效数据可计算！\n");
        return;
    }

    // 初始化课程总分数组
    float courseSum[COURSE_NUM] = { 0 };
    int studentCount = 0;

    // 遍历链表累加每门课程成绩
    STU current = head;
    while (current != NULL) {
        for (int j = 0; j < m; j++) {
            courseSum[j] += current->score[j];
        }
        studentCount++;
        current = current->next;
    }

    // 计算并打印结果
    printf("\n%-12s%-12s%-12s\n", "课程编号", "总分", "平均分");
    printf("------------------------------------\n");
    for (int j = 0; j < m; j++) {
        float average = (studentCount > 0) ? courseSum[j] / studentCount : 0;
        printf("课程%-8d%-12.1f%-12.1f\n", j + 1, courseSum[j], average);
    }
}