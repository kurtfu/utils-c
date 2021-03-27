#ifndef HOOK_H
#define HOOK_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define HOOK_OK              0
#define HOOK_NULL_PTR       -1
#define HOOK_ATTACH_FAILED  -2

#define HOOK_OP_END  0
#define HOOK_OP_RUN  1

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

struct subject
{
    struct hook* list;
};

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int hook_attach(struct subject* subject, int (*hook)(void* args), void* args);
int hook_detach(struct subject* subject, int (*hook)(void* args));
int hook_notify(struct subject* subject);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* HOOK_H */
