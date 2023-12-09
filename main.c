#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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
} Employees_Data;

typedef struct {
   Employees_Data employee[MAX_EMPL_NUM];
   int num_empl;
} Employees_storage;

//функция для добавления новго сотрудника в хранилище Employees_storage
void addEmployee(Employees_storage* storage_, const char* surname_, const char* name_, const char* ptrnmc_, const char* post_, \
   const char* sex_, int hire_date_d_,int hire_date_m_, int hire_date_y_)
{

   if (storage_->num_empl < MAX_EMPL_NUM)
   {
      Employees_Data new_employee;
      strcpy_s(new_employee.surname, sizeof(new_employee.surname), surname_);
      strcpy_s(new_employee.name, sizeof(new_employee.name), name_);
      strcpy_s(new_employee.ptrnmc, sizeof(new_employee.ptrnmc), ptrnmc_);
      strcpy_s(new_employee.post, sizeof(new_employee.post), post_);
      strcpy_s(new_employee.sex, sizeof(new_employee.sex), sex_);
      new_employee.hiredate_d = hire_date_d_;
      new_employee.hiredate_m = hire_date_m_;
      new_employee.hiredate_y = hire_date_y_;
      //strcpy_s(new_employee.hiredate, sizeof(new_employee.sex), hire_date_);

      storage_->employee[storage_->num_empl] = new_employee;
      storage_->num_empl++;
   }

   else
   {
      printf("Хранилище заполнено! Добавить нового сотрудника невозможно");
   }
}

// функция вывода информации о сотрудниках из хранилища Employees_storage
void printStorage(const Employees_storage* storage_)
{
   printf("Сведения о сотрудниках:\n-------------------------------------\n");

   for (int i = 0; i < storage_->num_empl; i++)
   {
      printf("Сотрудник №%d\n", i + 1);
      printf("Фамилия: %s\n", storage_->employee[i].surname);
      printf("Имя: %s\n", storage_->employee[i].name);
      printf("Отчество: %s\n", storage_->employee[i].ptrnmc);
      printf("Должность: %s\n", storage_->employee[i].post);
      printf("Пол: %s\n", storage_->employee[i].sex);
      printf("Дата приёма на работу: %d-%d-%d\n", storage_->employee[i].hiredate_d, storage_->employee[i].hiredate_m, storage_->employee[i].hiredate_y);
      printf("-------------------------------------\n");
   }
}

// функция выводящяя информацию о сотрудниках, стаж которых превышает 10 лет
void checkExp(const Employees_storage* storage_)
{

}

int main()
{
   setlocale(LC_ALL, "Rus");

   FILE* file;
   errno_t err = fopen_s(&file, "file.txt", "r");

   if (err != 0 || !file)
   {
      perror("File cant't open!");
      return 1;
   }

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

   printf("Данные считываются.\n");
   int count = 0;
   while (count < MAX_EMPL_NUM)
   {
      if (feof(file))
      {
         printf("Все данные успешно считаны считаны.\n");
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

         addEmployee(&employees, sur_name, na_me, ptr_nmc, po_st, s_ex, hire_date_d, hire_date_m, hire_date_y);
         count++;
      }
   }

   printStorage(&employees);

   return 0;
}


