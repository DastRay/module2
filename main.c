#include <stdio.h>
#include <string.h>
#include <locale.h>


enum {
   max_name_len = 30,
   max_post_len = 20,
   max_date_len = 12,
   max_empl_num = 100
};

typedef struct {
   char surname[max_name_len];
   char name[max_name_len];
   char ptrnmc[max_name_len]; // patronymic
   char post[max_post_len];
   char sex[10];
   char hire_date[max_date_len];
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
      strcpy_s(new_employee.hire_date, sizeof(new_employee.hire_date), hire_date_);

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
      printf("Сотрудник № %d\n", i + 1);
      printf("Фамилия: %s\n", storage_->employee[i].surname);
      printf("Имя: %s\n", storage_->employee[i].name);
      printf("Отчество: %s\n", storage_->employee[i].ptrnmc);
      printf("Должность: %s\n", storage_->employee[i].post);
      printf("Пол: %s\n", storage_->employee[i].sex);
      printf("Дата приёма на работу: %s\n", storage_->employee[i].hire_date);
      printf("-------------------------------------\n");
   }
}

int main()
{
   setlocale(LC_ALL, "Rus");

   Employees_storage employees;
   employees.num_empl = 0;

   addEmployee(&employees, "Иванов", "Иван", "Иванович", "Директор", "Мужской", "01-01-2000");
   addEmployee(&employees, "Александров", "Александр", "Александрович", "Менеджер", "Мужской", "02-01-2000");
   addEmployee(&employees, "Ильин", "Александр", "Валерьевич", "Бухгалтер", "Мужской", "31-01-2020");
   addEmployee(&employees, "Ильин", "Александр", "Валерьевич", "Бухгалтер", "Мужской", "31-01-2020");
   addEmployee(&employees, "Сидорова", "Елена", "Викторовна", "Бухгалтер", "Женский", "10-10-2012");

   printStorage(&employees);

   return 0;
}



