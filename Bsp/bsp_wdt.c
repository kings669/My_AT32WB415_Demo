#include "bsp_wdt.h"


void wdt_init(void)
{
	if(crm_flag_get(CRM_WDT_RESET_FLAG) != RESET)
  {
		/* reset from wdt */
    crm_flag_clear(CRM_WDT_RESET_FLAG);
	}
		
	/* disable register write protection */
  wdt_register_write_enable(TRUE);

  /* set the wdt divider value */
  wdt_divider_set(WDT_CLK_DIV_4);
	
	/* set reload value

   timeout = reload_value * (divider / lick_freq )    (s)

   lick_freq    = 40000 Hz
   divider      = 4
   reload_value = 3000

   timeout = 3000 * (4 / 40000 ) = 0.3s = 300ms
  */
  wdt_reload_value_set(3000 - 1);

  /* enable wdt */
  wdt_enable();
}