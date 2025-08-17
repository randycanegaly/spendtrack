#include "../external/src/unity.h"
#include "../src/spendtrack.h"

void setUp(void) {}

void tearDown(void) {}

void test_create_db(void) {
  int result = create_db();
  TEST_ASSERT_EQUAL_INT(1, result);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_create_db);
  return UNITY_END();
}
