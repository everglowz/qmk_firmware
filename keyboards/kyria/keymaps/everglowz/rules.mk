# Would have liked to use below, but can't since I need to add my own layers.
#USER_NAME := manna-harbour_miryoku

OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow

LEADER_ENABLE = yes        # Enable the Leader Key feature

MIRYOKU_CLIPBOARD = WIN
#MIRYOKU_LAYERS = FLIP
#MIRYOKU_NAV = INVERTEDT

MIRYOKU_EXTRA_LAYERS = "QWERTY, COLEMAKDH_NO_HOLD_L, COLEMAKDH_NO_HOLD_R, QWERTY_NO_HOLD_L, QWERTY_NO_HOLD_R"

SRC += oled.c
