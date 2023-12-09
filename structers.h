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
 * @brief функци¤ дл¤ добавлени¤ новго сотрудника в хранилище Employees_storage
 * @param storage_ указатель на хранилище структур
 * @param surname_ фамили¤
 * @param name_ им¤
 * @param ptrnmc_ отчество
 * @param post_ должность
 * @param sex_ пол
 * @param hire_date_d_ день приЄма на работу 
 * @param hire_date_m_ мес¤ц приЄма на работу
 * @param hire_date_y_ год приЄма на работу
*/
void addEmployee(Employees_storage* storage_, const char* surname_, const char* name_, const char* ptrnmc_, const char* post_, \
   const char* sex_, int hire_date_d_, int hire_date_m_, int hire_date_y_);

/** 
* @brief  функци¤ вывода информации о сотрудниках из хранилища Employees_storage
* @param storage_ указатель на хранилище струткур 
*/
void printStorage(const Employees_storage* storage_);

/**
 * @brief функци¤ вывод¤щ¤¤ информацию о сотрудниках, стаж которых превышает 10 лет
 * @param storage_ указатель на хранилище структур
*/
void checkExp(const Employees_storage* storage_);