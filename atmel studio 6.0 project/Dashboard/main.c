//******************************************************************************
//! @file Dashboard.c
//!
//! Michael Aebli, Created: 04.03.2014 23:56:45
//!
//! @brief Main Function for dashboard Project
//!
//!
//! @version 1.0
//!
//! @todo
//! @bug
//******************************************************************************

#include <stdlib.h>
#include "includes/MyCommon.h"
#include "includes/GlobalIncludes.h"
#include "includes/Led.h"


int main(void){	

	main_init();
	
	while(1){	
		wdt_reset();
		EventHandleEvent();
	};


	main_deinit();
	
	return 0;
}

