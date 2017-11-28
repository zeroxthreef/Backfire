#ifndef EVENT_H__
#define EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  unsigned type;
  unsigned long length;
  unsigned char *data;
} Backfire_Event;

#ifdef __cplusplus
}
#endif

#endif /* EVENT_H__*/
