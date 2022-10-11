#include "contiki.h"
#include "DCT.h"
#include "sys/log.h"

#define LOG_MODULE "DCT log "
#define LOG_LEVEL LOG_LEVEL_DBG

PROCESS(main_process, "main_process");
AUTOSTART_PROCESSES(&main_process);

PROCESS_THREAD(main_process, ev, data){
  PROCESS_BEGIN();
  LOG_DBG("some debug message\n");

  clock_init(); 

  clock_time_t start_time, end_time, comp_time;

  unsigned long start_time = clock_seconds();
  compress_and_decompress();
  unsigned long end_time = clock_seconds();
  comp_time = end_time-start_time;

  LOG_DBG("Time = %ld \n", comp_time);

  PROCESS_END();
}
/*
void main(){
  //Gen_H();
  //compress_and_decompress();
}*/
