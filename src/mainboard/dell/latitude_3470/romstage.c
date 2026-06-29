/* SPDX-License-Identifier: GPL-2.0-or-later */
//Based on romstage.c from mainboard/51nb/x210/romstage.c

#include <assert.h>
#include <soc/romstage.h>
#include <spd_bin.h>
#include <string.h>

static void mainboard_fill_rcomp_res_data(void *rcomp_ptr)
{
	/* Rcomp resistor */
	const u16 RcompResistor[3] = { 121, 81, 100 }; //These values were double checked in the Latitude 3470 schematic.
	memcpy(rcomp_ptr, RcompResistor, sizeof(RcompResistor));
}


static void mainboard_fill_rcomp_strength_data(void *rcomp_strength_ptr)
{
	/* Rcomp target */
	//Believe it or not, I did a hexadecimal search for these values (64 00 28 00 14 00 14 00 1A 00) and found them in the stock Latitude 3470 bios image next to strings that said "Micron, Hynix, Elpida, and Samsung."
	const u16 RcompTarget[5] = { 100, 40, 20, 20, 26 };
	memcpy(rcomp_strength_ptr, RcompTarget, sizeof(RcompTarget));
}

void mainboard_memory_init_params(FSPM_UPD *mupd)
/*DIM A: SO-DIMMA SPD Address is 0xA0 (0xA0 >> 1 = 0x50)
  DIM B: SO-DIMMB SPD Address is 0xA4 (0xA4 >> 1 = 0x52) -Schematic */
{
	FSP_M_CONFIG *mem_cfg;
	struct spd_block blk = {
		.addr_map = { 0x50, 0x52 },
	};

	mem_cfg = &mupd->FspmConfig;

	get_spd_smbus(&blk);
	dump_spd_info(&blk);
	assert(blk.spd_array[0][0] != 0);

	mainboard_fill_rcomp_res_data(&mem_cfg->RcompResistor);
	mainboard_fill_rcomp_strength_data(&mem_cfg->RcompTarget);

	/*The pins are interleaved.
	  They are not in all wired to their counterparts.
	  ex:
	  M_A_DQ3 to DQ0,
	  M_A_DQ1 to DQ1,
	  M_A_DQ4 to DQ2,
	  M_A_DQ7 to DQ3,
	  M_A_DQ2 to DQ4,
	  etc. */
	
	mem_cfg->DqPinsInterleaved = TRUE; //Gemini said that memory cell 2 to data line 4 is called Data Lane Swizzling, which is a typical way to keep boards simple, but is different from Interleaving, which is you use lines from different RAM chips as if they were one chip.
	mem_cfg->CaVrefConfig = 0; //Gemini said this setting is much more common on laptops and is a safer bet. I got 2 as the correct value from the schematic and that was the former selection here.
	mem_cfg->MemorySpdDataLen = blk.len;
	mem_cfg->MemorySpdPtr00 = (uintptr_t)blk.spd_array[0];
	mem_cfg->MemorySpdPtr10 = (uintptr_t)blk.spd_array[1];
}
