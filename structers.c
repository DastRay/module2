#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "structers.h"

void readFile(FILE* file)
{
   Employees_storage employees;
   employees.num_empl = 0;

   char sur_name[MAX_NAME_LEN];
   char na_me[MAX_NAME_LEN];
   char ptr_nmc[MAX_NAME_LEN];
   char po_st[MAX_POST_LEN];
   char s_ex[MAX_SEX_LEN];
   int hire_date_d;
   int hire_date_m;
   int hire_date_y;

   printf("������ � ����������� �������� �����������\n");
   int count = 0;

   while (count < MAX_EMPL_NUM)
   {
      if (feof(file))
      {
         printf("��� ������ ������� ������� �������\n");
         printf("\n");
         break;
      }
      else
      {
         fscanf_s(file, "%s", sur_name, MAX_NAME_LEN);
         fscanf_s(file, "%s", na_me, MAX_NAME_LEN);
         fscanf_s(file, "%s", ptr_nmc, MAX_NAME_LEN);
         fscanf_s(file, "%s", po_st, MAX_POST_LEN);
         fscanf_s(file, "%s", s_ex, MAX_SEX_LEN);
         fscanf_s(file, "%d-%d-%d", &hire_date_d, &hire_date_m, &hire_date_y);

         addEmployee(&employees, sur_name, na_me, ptr_nmc, po_st, s_ex, hire_date_d, hire_date_m, hire_date_y); // ���������� ����������
         count++;
      }
   }

   MyMenu(&employees, file);
}

void printStorage(const Employees_storage* storage_)
{
   printf("�������� � �����������:\n-------------------------------------\n");

   for (int i = 0; i < storage_->num_empl; i++)
   {
      printf("��������� �%d\n", i + 1);
      printf("�������: %s\n", storage_->employee[i].surname);
      printf("���: %s\n", storage_->employee[i].name);
      printf("��������: %s\n", storage_->employee[i].ptrnmc);
      printf("���������: %s\n", storage_->employee[i].post);
      printf("���: %s\n", storage_->employee[i].sex);
      printf("���� ����� �� ������: %d-%d-%d\n", storage_->employee[i].hiredate_d, storage_->employee[i].hiredate_m, storage_->employee[i].hiredate_y);
      printf("-------------------------------------\n");
   }
}

void addEmployee(Employees_storage* storage_, const char* surname_, const char* name_, const char* ptrnmc_, const char* post_, \
   const char* sex_, const int hire_date_d_, const int hire_date_m_, const int hire_date_y_)
{
   storage_->eror = true;

   if (storage_->num_empl < MAX_EMPL_NUM)
   {
      Employee new_employee;

      strcpy_s(new_employee.surname, sizeof(new_employee.surname), surname_);
      strcpy_s(new_employee.name, sizeof(new_employee.name), name_);
      strcpy_s(new_employee.ptrnmc, sizeof(new_employee.ptrnmc), ptrnmc_);
      strcpy_s(new_employee.post, sizeof(new_employee.post), post_);
      strcpy_s(new_employee.sex, sizeof(new_employee.sex), sex_);
      new_employee.hiredate_d = hire_date_d_;
      new_employee.hiredate_m = hire_date_m_;
      new_employee.hiredate_y = hire_date_y_;

      storage_->employee[storage_->num_empl] = new_employee;
      storage_->num_empl++;
   }

   else
   {
      printf("��������� ���������! �������� ������ ���������� ����������\n");
      storage_->eror = false;
   }
}

void addEmployeeFile(const Employees_storage* storage_, FILE* file)
{
   char sur_name[MAX_NAME_LEN];
   char na_me[MAX_NAME_LEN];
   char ptr_nmc[MAX_NAME_LEN];
   char po_st[MAX_POST_LEN];
   char s_ex[MAX_SEX_LEN];
   unsigned int datee[3]; //datee[0] - �����, datee[1] - �����, datee[2] - ���
   printf("���������� ����������:\n");
   printf("������� �������: ");
   scanf_s("%s", sur_name, MAX_NAME_LEN);
   printf("������� ���: ");
   scanf_s("%s", na_me, MAX_NAME_LEN);
   printf("������� ��������: ");
   scanf_s("%s", ptr_nmc, MAX_NAME_LEN);
   printf("������� ���������: ");
   scanf_s("%s", po_st, MAX_POST_LEN);
   printf("������� ���: ");
   scanf_s("%s", s_ex, MAX_SEX_LEN);
   printf("������� ���� ����� �� ������ ��-��-����: ");
   scanf_s("%u-%u-%u", &datee[0], &datee[1], &datee[2]);
   addEmployee(storage_, sur_name, na_me, ptr_nmc, po_st, s_ex, datee[0], datee[1], datee[2]);

   if (storage_->eror != false)
   {
      fputs("\n", file);
      fprintf(file, "%s %s %s %s %s ", sur_name, na_me, ptr_nmc, po_st, s_ex);
      fprintf(file, "%u-%u-%u", datee[0], datee[1], datee[2]);

      printf("��������� ������� ��������\n");
   }
   printf("\n");
}

void deleteEmployeeFile(const Employees_storage* storage_, FILE* file_)
{
   unsigned int number;
   printf("������� ����� ���������� �������� ���������� ������� �� ������: ");
   scanf_s("%u", &number);

   fclose(file_);

   FILE* copy;
   errno_t err = fopen_s(&copy, "file.txt", "w");

   if (err != 0 || !copy)
   {
      perror("File cant't open!");
      exit(1);
   }

   for (int i = 0; i < storage_->num_empl; i++)
   {
      if (i == number - 1)
      {
         continue;
      }

      if (i != 0) {
         fputs("\n", copy);
      }
      fprintf(copy, "%s %s %s %s %s ", storage_->employee[i].surname, storage_->employee[i].name, storage_->employee[i].ptrnmc, storage_->employee[i].post, storage_->employee[i].sex);
      fprintf(copy, "%d-%d-%d", storage_->employee[i].hiredate_d, storage_->employee[i].hiredate_m, storage_->employee[i].hiredate_y);
   }

   printf("��������� ������� �����\n");
   printf("���������� ������ � �����������...\n");
   fclose(copy);

   FILE* file;
   errno_t erro = fopen_s(&file, "file.txt", "a+");

   if (erro != 0 || !file)
   {
      perror("File cant't open!");
      return 1;
   }

   readFile(file);
   printf("\n");
}

void checkExp(const Employees_storage* storage_)
{
   unsigned int num;
   printf("1 - ������� ������ � ����������� ���� ������� ��������� n ���\n");
   printf("2 - ������� ������ � ����������� ���� ������� ������ n ���\n");
   printf("3 - ������� ������ � ����������� ���� ������� ����� n ���\n");
   printf("�������� ��������: ");
   scanf_s("%u", &num);

   unsigned int choice;
   printf("������ ������� ���� �������������?\n1 - ��\n2 - ���\n");
   printf("�������� 1 ��� 2: ");
   scanf_s("%u", &choice);

   unsigned int day;
   unsigned int month;
   unsigned int year;
   unsigned int exp;

   if (choice == 1)
   {
      time_t mytime = time(NULL);
      struct tm* now = localtime(&mytime);

      day = now->tm_mday;
      month = now->tm_mon + 1;
      year = now->tm_year + 1900;
   }
   else
   {
      printf("������� ������� ���� � ������� ��-��-����: ");
      scanf_s("%u-%u-%u", &day, &month, &year);
   }

   printf("������� ���� (���������� ���): ");
   scanf_s("%u", &exp);
   printf("\n");

   switch (num)
   {
   case 1:
   {
      printf("����������, ���� ������� ��������� %d ���:\n", exp);
      printf("-------------------------------------\n");

      for (int i = 0; i < storage_->num_empl; i++)
      {
         if ((storage_->employee[i].hiredate_y < (year - exp)) || (storage_->employee[i].hiredate_y == (year - exp) && storage_->employee[i].hiredate_m < month) || (storage_->employee[i].hiredate_y == (year - exp) && storage_->employee[i].hiredate_m == month && storage_->employee[i].hiredate_d < day))
         {
            printf("��������� �%d\n", i + 1);
            printf("�������: %s\n", storage_->employee[i].surname);
            printf("���: %s\n", storage_->employee[i].name);
            printf("��������: %s\n", storage_->employee[i].ptrnmc);
            printf("���������: %s\n", storage_->employee[i].post);
            printf("���: %s\n", storage_->employee[i].sex);
            printf("���� ����� �� ������: %d-%d-%d\n", storage_->employee[i].hiredate_d, storage_->employee[i].hiredate_m, storage_->employee[i].hiredate_y);
            printf("-------------------------------------\n");
         }
      }
      break;
   }
   case 2:
   {
      printf("����������, ���� ������� ������ %d ���:\n", exp);
      printf("-------------------------------------\n");

      for (int i = 0; i < storage_->num_empl; i++)
      {
         if ((storage_->employee[i].hiredate_y > (year - exp)) || (storage_->employee[i].hiredate_y == (year - exp) && storage_->employee[i].hiredate_m > month) || (storage_->employee[i].hiredate_y == (year - exp) && storage_->employee[i].hiredate_m == month && storage_->employee[i].hiredate_d > day))
         {
            printf("��������� �%d\n", i + 1);
            printf("�������: %s\n", storage_->employee[i].surname);
            printf("���: %s\n", storage_->employee[i].name);
            printf("��������: %s\n", storage_->employee[i].ptrnmc);
            printf("���������: %s\n", storage_->employee[i].post);
            printf("���: %s\n", storage_->employee[i].sex);
            printf("���� ����� �� ������: %d-%d-%d\n", storage_->employee[i].hiredate_d, storage_->employee[i].hiredate_m, storage_->employee[i].hiredate_y);
            printf("-------------------------------------\n");
         }
      }
      break;
   }
   case 3:
   {
      printf("����������, ���� ������� ����� %d ���:\n", exp);
      printf("-------------------------------------\n");

      for (int i = 0; i < storage_->num_empl; i++)
      {
         if (storage_->employee[i].hiredate_y == (year - exp) && storage_->employee[i].hiredate_m == month && storage_->employee[i].hiredate_d == day)
         {
            printf("��������� �%d\n", i + 1);
            printf("�������: %s\n", storage_->employee[i].surname);
            printf("���: %s\n", storage_->employee[i].name);
            printf("��������: %s\n", storage_->employee[i].ptrnmc);
            printf("���������: %s\n", storage_->employee[i].post);
            printf("���: %s\n", storage_->employee[i].sex);
            printf("���� ����� �� ������: %d-%d-%d\n", storage_->employee[i].hiredate_d, storage_->employee[i].hiredate_m, storage_->employee[i].hiredate_y);
            printf("-------------------------------------\n");
         }
      }
      break;
   }
   default:
   {
      printf("�������� ��������");
      break;
   }  
   }
}

void MyMenu(const Employees_storage* storage_, FILE* file)
{
   unsigned int f = 0;
   while (1)
   {
      printf("0 - ������� ���������\n1 - ������� ������ � ���� �����������\n2 - ������� ������ � �����������, ���� ������� ������/������/����� n-���\n\
3 - �������� ����������\n4 - ������� ����������\n�������� ��������: ");
      scanf_s("%u", &f);
      printf("\n");

      switch (f)
      {
      case 0:
      {
         printf("����������� ����� �� ���������");
         exit(1);
      }
      case 1:
      {
         printStorage(storage_);
         printf("\n");
         break;
      }
      case 2:
      {
         checkExp(storage_);
         printf("\n");
         break;
      }
      case 3:
      {
         addEmployeeFile(storage_, file);
         break;
      }
      case 4:
      {
         deleteEmployeeFile(storage_, file);
         break;
      }
      default:
      {
         printf("�������� ��������\n");
         break;
      }
      }
   } 
}