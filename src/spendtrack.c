#include <sqlite3.h>

#include "spendtrack.h"

int create_db(const char *filename, sqlite3 *db) {
  int result = sqlite3_open(filename, &db);
  return result;
}

#ifdef IS_EXE

int main(void) { return 0; }

#endif
