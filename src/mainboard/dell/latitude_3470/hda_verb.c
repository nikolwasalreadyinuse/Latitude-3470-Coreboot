/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/azalia_device.h>
//This file is based on mainboard/51nb/x210/hda_verb.c
const u32 cim_verb_data[] = {
	/*According to Gemini, the HDA hardware needs specific timing delays to cycle it's transistors and clear it's internal state. As an artificial delay when we don't have a timer library this early in boot, we send this command 4 times in a row to stall.*/
	0x0017ff00,    /* Function Reset */
	0x0017ff00,    /* Double Function Reset */
	0x0017ff00,
	0x0017ff00,

	//AZALIA_SUBVENDOR(Address,Subsystem Id). This sets the model variables for the card, so /proc can recognize this chip is in a Dell Laptop.
	AZALIA_SUBVENDOR(0, 0x102806f2),

	//The pins, finally.
	//Some of these were marked as disconnected in my Latitude 3470, but since the Latitude 3570 uses the same motherboard, they may be necessary for audio on other models.
	AZALIA_PIN_CFG(0, 0x12, 0x90a60140),
	AZALIA_PIN_CFG(0, 0x13, 0x40000000),
	AZALIA_PIN_CFG(0, 0x14, 0x90170110),
	AZALIA_PIN_CFG(0, 0x18, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x19, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1a, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1b, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x1d, 0x4077992d),
	AZALIA_PIN_CFG(0, 0x1e, 0x411111f0),
	AZALIA_PIN_CFG(0, 0x21, 0x02211020),

};


const u32 pc_beep_verbs[] = {
};

struct azalia_codec mainboard_azalia_codecs[] = {
	{
		.name         = "Realtek ALC3246",
		.vendor_id    = 0x10ec0256,
		.subsystem_id = 0x102806f2,
		.address      = 0,
		.verbs        = cim_verb_data,
		.verb_count   = ARRAY_SIZE(cim_verb_data),
	},
	{ /* terminator */ }
};

AZALIA_ARRAY_SIZES;
/* Manually defining what the macro used to do, bypassing the naming restriction */
//const u32 cim_verb_data_size = sizeof(cim_verb_data);
//const u32 pc_beep_verbs_size = sizeof(pc_beep_verbs);
