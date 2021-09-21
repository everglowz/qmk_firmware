OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow

#LEADER_ENABLE = yes        # Enable the Leader Key feature

MIRYOKU_CLIPBOARD = WIN
#MIRYOKU_LAYERS = FLIP
#MIRYOKU_NAV = INVERTEDT

MIRYOKU_EXTRA_LAYERS = "QWERTY, COLEMAKDH_NO_HOLD_L, COLEMAKDH_NO_HOLD_R, QWERTY_NO_HOLD_L, QWERTY_NO_HOLD_R, VIEWER_FULL"

SRC += oled.c

# To save space
SPACE_CADET_ENABLE = no
MAGIC_ENABLE = no
GRAVE_ESCAPE_ENABLE = no
