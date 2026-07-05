
#include <cpu/x86/smm.h>
#include <ec/dell/mec5035/mec5035.h>

void mainboard_smi_sleep(u8 slp_typ)
{
	mec5035_smi_sleep(slp_typ);
}
