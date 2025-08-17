#include "../external/src/unity.h"
#include "../src/spendtrack.h"

void setUp(void) {}

void tearDown(void) {}

void test_create_db(void) {
  sqlite3 *db;
  int result = create_db("test_db", db);
  TEST_ASSERT_EQUAL_INT(SQLITE_OK, result);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_create_db);
  return UNITY_END();
}
