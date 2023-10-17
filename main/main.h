typedef struct {
    bool accessory;
    bool lamp;
    bool reset;
    bool hour;
    bool minute;
} gpio_state_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} clock_state_t;