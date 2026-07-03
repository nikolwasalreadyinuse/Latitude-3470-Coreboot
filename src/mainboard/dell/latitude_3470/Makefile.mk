## SPDX-License-Identifier: GPL-2.0-only

romstage-y += romstage.c #I could also go the direction of setting my memory configuration registers directly in devicetree.cb, but for now I will use the custom file.
ramstage-y += hda_verb.c
ramstage-$(CONFIG_MAINBOARD_USE_LIBGFXINIT) += gma-mainboard.ads

#bootblock-y += bootblock.c #to call mec5053 early init

#they had both in the ivybridge latitude folders
#bootblock-y += early_init.c
romstage-y += early_init.c

ramstage-y += ../../../drivers/i2c/generic/generic.c



