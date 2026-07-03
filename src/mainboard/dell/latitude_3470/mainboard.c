/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <soc/ramstage.h>
#include <ec/dell/mec5035/mec5035.h>


static void mainboard_enable(struct device *dev)
{
	/* Route 0x4e/4f to LPC */
	//lpc_enable_fixed_io_ranges(LPC_IOE_EC_4E_4F); //Believe it or not the 51nb/x210 which is also skylake came with this line.
	printk(BIOS_INFO, "Running LPC and MEC5035 init....\n");
	//AI said that things like FDD are enabling floppy ports, but I will leave everything on for the first attempt.
	/*pci_write_config16(PCH_LPC_DEV, LPC_EN, CNF1_LPC_EN | MC_LPC_EN
	  | KBC_LPC_EN | FDD_LPC_EN | LPT_LPC_EN
	  | COMB_LPC_EN | COMA_LPC_EN);*/

	//Fixed for skylake syntax

        /* 2. Open up all valid Skylake fixed legacy hardware channels */
	lpc_enable_fixed_io_ranges(LPC_IOE_EC_62_66 | 
	                           LPC_IOE_KBC_60_64 | 
	                           LPC_IOE_SUPERIO_2E_2F |
	                           LPC_IOE_LPT_EN | 
	                           LPC_IOE_FDD_EN);
	
	lpc_io_setup_comm_a_b();

	
	mec5035_early_init();
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};
