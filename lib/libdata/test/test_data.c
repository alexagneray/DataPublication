#include "../data.h"
#include <cunit.h>


int init_suite()
{
    if ( lib_data_init() == DATA_RET_OK )
    {
        return 0;
    }
    return -1;
}

int clean_suite()
{
    if ( lib_data_destroy() == DATA_RET_OK )
    {
        return 0;
    }
    return -1;
}

void test_data_list()
{
    add_group("Hello1");
}

int main()
{
    cunit_init();

	CUNIT_SUITE_BEGIN("Collect Mode Tests", NULL, NULL)
	CUNIT_TEST("Test Data List", test_data_list)
	CUNIT_SUITE_END()

	const int failed_count = cunit_run();
	if (failed_count != 2) { return -1; }
	return 0;
}