// extension board IO
#define GPIO_LAMP GPIO_NUM_46
#define GPIO_ACC GPIO_NUM_45
#define GPIO_RESET GPIO_NUM_44
#define GPIO_HOUR GPIO_NUM_43
#define GPIO_MINUTE GPIO_NUM_42

// screen
#define SCREEN_X 536
#define SCREEN_Y 240

// canvas
#define CANVAS_X 510
#define CANVAS_Y 146

// max/min screen brightness
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 55

// maximum loop cycles to register GPIO event (prevents noise causing faulty inputs)
#define GPIO_HOLD_COUNT 5

typedef struct {
    bool accessory;
    bool lamp;
    bool reset;
    bool hour;
    bool minute;
} gpio_state_t;

typedef struct {
    uint8_t accessory;
    uint8_t lamp;
    uint8_t reset;
    uint8_t hour;
    uint8_t minute;
} gpio_hold_state_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} clock_state_t;