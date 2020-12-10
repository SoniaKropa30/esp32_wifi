#ifndef CLOCK_H
#define CLOCK_H

#include "esp_err.h"
#include <driver/timer.h>


#include "oled.h"
#include "math.h"
#include "mx_function.h"
#include "components.h"


#define TIMER_DIVIDER                   80
#define TIMER_SCALE                     (TIMER_BASE_CLK / TIMER_DIVIDER)
#define DAILY_TIME                      86400 //in second  1440 - in min

void timer_initialise (t_app *app);
void timer_task(void * data);
int set_time (char *argv[]);

#endif
