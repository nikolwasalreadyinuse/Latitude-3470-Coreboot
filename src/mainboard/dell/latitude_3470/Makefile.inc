
# Tell the build system to track your raw EC firmware blob
cbfs-files-y += ec_blob
ec_blob-file := /home/niko/lat_coreboot/blobs_for_coreboot_use/final_use/ec_versionA7.bin
ec_blob-type := raw

# This flag commands cbfstool to bypass CBFS and flash it directly to the ECFW FMAP region
ec_blob-flags := -r ECFW

#bootblock-y += hda_verb.c
#romstage-y += early_init.c

#bootblock-y += bootblock.c


# Tell the build system to write the raw EC blob to the ECFW region right after the primary ROM layout is generated
PHONY += update_ecfw_region
coreboot: update_ecfw_region

update_ecfw_region: $(obj)/coreboot.rom
	@echo "    FORCING  ec_blob directly into raw FMAP region 'ECFW'..."
	$(CBFSTOOL) $(obj)/coreboot.rom write -r ECFW -f /home/niko/lat_coreboot/blobs_for_coreboot_use/final_use/ec_versionA7.bin