# Copied from https://github.com/moben/qmk_firmware/blob/master/users/manna-harbour_miryoku/rules.mk
# then modified to my needs

MOUSEKEY_ENABLE = yes # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
AUTO_SHIFT_ENABLE = yes # Auto Shift

SRC += everglowz.c \
       encoder.c \
       process_records.c

# alternative layouts:

# alphas
ifneq ($(strip $(MIRYOKU_ALPHAS)),)
  OPT_DEFS += -DMIRYOKU_ALPHAS_$(MIRYOKU_ALPHAS)
endif

# nav
ifneq ($(strip $(MIRYOKU_NAV)),)
  OPT_DEFS += -DMIRYOKU_NAV_$(MIRYOKU_NAV)
endif

# clipboard
ifneq ($(strip $(MIRYOKU_CLIPBOARD)),)
  OPT_DEFS += -DMIRYOKU_CLIPBOARD_$(MIRYOKU_CLIPBOARD)
endif

# layers
ifneq ($(strip $(MIRYOKU_LAYERS)),)
  OPT_DEFS += -DMIRYOKU_LAYERS_$(MIRYOKU_LAYERS)
endif

# subset mappings
ifneq ($(strip $(MIRYOKU_MAPPING)),)
  OPT_DEFS += -DMIRYOKU_MAPPING_$(MIRYOKU_MAPPING)
endif

# copied from https://github.com/moben/qmk_firmware/blob/master/users/manna-harbour_miryoku/rules.mk
ifneq ($(strip $(MIRYOKU_EXTRA_LAYERS)),)
  OPT_DEFS += -DMIRYOKU_EXTRA_LAYERS=$(MIRYOKU_EXTRA_LAYERS)
endif