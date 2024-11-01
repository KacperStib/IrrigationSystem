SET(SOURCES ui_MainMenu.c
    ui_Garden.c
    ui_Tent.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})
