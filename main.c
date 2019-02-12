#include "log.h"
#include <stdio.h>

int main(void) {
	log_init(stdout);
	log_info("2 + 2 = %d you dipshit", 4);
	log_end();
	return 0;
}

