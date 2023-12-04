#include <stdio.h>
#include <locale.h>

enum {
   max_name_len = 30,
   max_post_len = 20,
   max_date_len = 12,
   max_sex_len = 10,
   max_empl_num = 100
};

typedef struct {
   char surname[max_name_len];
   char name[max_name_len];
   char ptrnmc[max_name_len]; // patronymic
   char post[max_post_len];
   char sex[max_sex_len];
   char hiredate[max_date_len];
} Employees_Data;

typedef struct {
   Employees_Data employee[max_empl_num];
   int num_empl;
} Employees_storage;

//функция для добавления новго сотрудника в хранилище Employees_storage
void addEmployee(Employees_storage* storage_, const char* surname_, const char* name_, const char* ptrnmc_, const char* post_, \
   const char* sex_,  const char* hire_date_)
{
   if (storage_->num_empl < max_empl_num)
   {
      Employees_Data new_employee;
      strcpy_s(new_employee.surname, sizeof(new_employee.surname), surname_);
      strcpy_s(new_employee.name, sizeof(new_employee.name), name_);
      strcpy_s(new_employee.ptrnmc, sizeof(new_employee.ptrnmc), ptrnmc_);
      strcpy_s(new_employee.post, sizeof(new_employee.post), post_);
      strcpy_s(new_employee.sex, sizeof(new_employee.sex), sex_);
      strcpy_s(new_employee.hiredate, sizeof(new_employee.hiredate), hire_date_);

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
      printf("Фамилия: %s", storage_->employee[i].surname);
      printf("Имя: %s", storage_->employee[i].name);
      printf("Отчество: %s", storage_->employee[i].ptrnmc);
      printf("Должность: %s", storage_->employee[i].post);
      printf("Пол: %s", storage_->employee[i].sex);
      printf("Дата приёма на работу: %s", storage_->employee[i].hiredate);
      printf("\n-------------------------------------\n");
   }
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

   char sur_name[max_name_len];
   char na_me[max_name_len];
   char ptr_nmc[max_name_len];
   char po_st[max_post_len];
   char s_ex[max_sex_len];
   char hire_date[max_date_len];

   printf("Данные считываются.\n");
   int count = 0;
   while (count < max_empl_num)
   {
      if (feof(file))
      {
         printf("Все данные успешно считаны считаны.\n");
         printf("\n");
         break;
      }

      else
      {
         fgets(sur_name, max_name_len, file);
         fgets(na_me, max_name_len, file);
         fgets(ptr_nmc, max_name_len, file);
         fgets(po_st, max_post_len, file);
         fgets(s_ex, max_sex_len, file);
         fgets(hire_date, max_date_len, file);
         

         addEmployee(&employees, sur_name, na_me, ptr_nmc, po_st, s_ex, hire_date);
         count++;
      }
   }
  
   /*addEmployee(&employees, "Иванов", "Иван", "Иванович", "Директор", "Мужской", "01-01-2000");
   addEmployee(&employees, "Александров", "Александр", "Александрович", "Менеджер", "Мужской", "02-01-2000");
   addEmployee(&employees, "Ильин", "Александр", "Валерьевич", "Бухгалтер", "Мужской", "31-01-2020");
   addEmployee(&employees, "Ильин", "Александр", "Валерьевич", "Бухгалтер", "Мужской", "31-01-2020");
   addEmployee(&employees, "Сидорова", "Елена", "Викторовна", "Бухгалтер", "Женский", "10-10-2012");*/

   printStorage(&employees);

   return 0;
}



