/*========================================================================
** ring_test.c
** Circular buffer testing
** ECEN5813
** Reference: http://cunit.sourceforge.net/example.html
** Author: Amreeta Sengupta and Ridhi Shah
**========================================================================*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "CUnit/Basic.h"
#include <CUnit/Automated.h>
#include <CUnit/CUnit.h>
#include "../Include/ring.h"

ring_t *ptr_test[10];
int length_test[10], num_buff,buff_index;

int init_suite1(void)
{
	srand(time(0));
	return 0;
}


int clean_suite1(void)
{
	free(ptr_test[0]);
	ptr_test[0]=NULL;
	return 0;
}


void test_init()
{
	num_buff =(rand()%10)+1;
	printf("\n%d random number of buffers will be created!\n",num_buff);
	for (int i = 0; i<num_buff; i++)
	{
		length_test[i] = (rand()%1000)+1;
		printf("Buffer %d of %d random size will be created!\n",i+1,length_test[i]);
		CU_ASSERT_NOT_EQUAL(length_test[i],0);
		ptr_test[i]= init(length_test[i]);
		CU_ASSERT_NOT_EQUAL(ptr_test[i],NULL);
	}
	buff_index = (rand()%num_buff);
	printf("Buffer Tests will be performed on Buffer Number %d\n",buff_index + 1);
}

void test_insert()
{
	char ele;
	for(int i=0; i<length_test[buff_index]-1; i++)
	{
		ele = rand() % 256;
		CU_ASSERT_EQUAL(insert(ptr_test[buff_index],i),0);
	}
	CU_ASSERT_EQUAL(insert(ptr_test[buff_index],2),1); //Buffer full condition
}

void test_remove()
{
	char ele;
	for(int i=0; i<length_test[buff_index]-1; i++)
	{
		CU_ASSERT_EQUAL(remove_element(ptr_test[buff_index],&ele),0);
	}
		CU_ASSERT_EQUAL(remove_element(ptr_test[buff_index],&ele),1); //Buffer empty condition
	
}

void test_resize()
{
	char ele;
	int temp;
	temp = (rand()%(length_test[buff_index]-1))+1;
	
	for(int i=0; i<temp; i++)
	{
		ele = rand() % 256;
		insert(ptr_test[buff_index],i);
	}
	CU_ASSERT_EQUAL(resize(ptr_test[buff_index],temp),1); //Resize should fail beacuse data will be lost in resized buffer
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
 
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of INIT()", test_init)) ||
       (NULL == CU_add_test(pSuite, "test of INSERT()", test_insert)) ||
       (NULL == CU_add_test(pSuite, "test of REMOVE()", test_remove))||
       (NULL == CU_add_test(pSuite, "test of RESIZE()", test_resize)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_automated_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

