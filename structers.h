#pragma once
enum {
   MAX_NAME_LEN = 30,
   MAX_POST_LEN = 20,
   MAX_SEX_LEN = 10,
   MAX_EMPL_NUM = 100
};

typedef struct {
   char surname[MAX_NAME_LEN];
   char name[MAX_NAME_LEN];
   char ptrnmc[MAX_NAME_LEN]; // patronymic
   char post[MAX_POST_LEN];
   char sex[MAX_SEX_LEN];
   int hiredate_d;
   int hiredate_m;
   int hiredate_y;
} Employee;

typedef struct {
   Employee employee[MAX_EMPL_NUM];
   int num_empl;
} Employees_storage;

/**
 * @brief ������ �� ��������� ����� ���������� � ��������� Employees_storage
 * @param storage_ ��������� �� ��������� ��������
 * @param surname_ ������
 * @param name_ ��
 * @param ptrnmc_ ��������
 * @param post_ ���������
 * @param sex_ ���
 * @param hire_date_d_ ���� ����� �� ������ 
 * @param hire_date_m_ ���� ����� �� ������
 * @param hire_date_y_ ��� ����� �� ������
*/
void addEmployee(Employees_storage* storage_, const char* surname_, const char* name_, const char* ptrnmc_, const char* post_, \
   const char* sex_, int hire_date_d_, int hire_date_m_, int hire_date_y_);

/** 
* @brief  ������ ������ ���������� � ����������� �� ��������� Employees_storage
* @param storage_ ��������� �� ��������� �������� 
*/
void printStorage(const Employees_storage* storage_);

/**
 * @brief ������ �������� ���������� � �����������, ���� ������� ��������� 10 ���
 * @param storage_ ��������� �� ��������� ��������
*/
void checkExp(const Employees_storage* storage_);